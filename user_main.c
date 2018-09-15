#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"


//Setando status
volatile int status = 0, status1 = 0, status2 = 0;


void GPIO_INTERRUPT(){

	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS,gpio_status);

	if(gpio_status & BIT(0)){	//PIND3
		if(status2 == 0){
			gpio_output_set((1 << 12),0, (1 << 12),0);	//PIN D6
			status2++;
		}
		else{
			gpio_output_set(0,(1 << 12), (1 << 12),0);
			status2 = 0;
		}
	}

	if(gpio_status & BIT(4)){	//PIN D2
		if(status == 0){
			gpio_output_set((1 << 13),0, (1 << 13),0);	//PIN D7
			status++;
		}
		else{
			gpio_output_set(0,(1 << 13), (1 << 13),0);
			status=0;
		}
	}
	else if(gpio_status & BIT(5)){	//PIN D1
		if(status1 == 0){
			gpio_output_set((1 << 14),0, (1 << 14),0);	//PIN D5
			status1++;
		}
		else{
			gpio_output_set(0,(1 << 14), (1 << 14),0);
			status1 = 0;
		}
	}


}

void ICACHE_FLASH_ATTR user_init(){
    gpio_init();

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);

    //-----------------------------------------adiciona mais 2 botoes e 2 leds
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);


    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
    //-----------------------------------------     */

    GPIO_DIS_OUTPUT(GPIO_ID_PIN(0));
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO0_U); //habilita os pull-ups

    GPIO_DIS_OUTPUT(GPIO_ID_PIN(4));
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO4_U); //habilita os pull-ups

    GPIO_DIS_OUTPUT(GPIO_ID_PIN(5));
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO5_U); //habilita os pull-ups


    //---------------------------------------------------     */

    ETS_GPIO_INTR_DISABLE();
    ETS_GPIO_INTR_ATTACH(GPIO_INTERRUPT, NULL);

    gpio_pin_intr_state_set(GPIO_ID_PIN(0), GPIO_PIN_INTR_ANYEDGE);
    gpio_pin_intr_state_set(GPIO_ID_PIN(4), GPIO_PIN_INTR_ANYEDGE);
    gpio_pin_intr_state_set(GPIO_ID_PIN(5), GPIO_PIN_INTR_NEGEDGE);


    ETS_GPIO_INTR_ENABLE();

	gpio_output_set(0,(1 << 14), (1 << 14),0);
	gpio_output_set(0,(1 << 12), (1 << 12),0);
	gpio_output_set(0,(1 << 13), (1 << 13),0);

}
