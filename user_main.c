#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

//Variables that control if LED will turn ON or OFF
volatile int status = 0, status1 = 0, status2 = 0;

void GPIO_INTERRUPT(){

	//Retrivies an array of GPIO's triggered.
	//Example: 0 1 1 0
	//	 	   3 2 1 0
	//In the case above, GPIO1 and GPIO2 had triggered
	
	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
	
	//Clear the array register
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);

	//Check what GPIO had triggered
	if(gpio_status & BIT(0)){	
		if(status == 0){
			
			//Set HIGH to GPIO 12
			gpio_output_set((1 << 12),0, (1 << 12),0);
			status++;
		}
		else{
			
			//Set LOW to GPIO12
			gpio_output_set(0,(1 << 12), (1 << 12),0);
			status = 0;
		}
	}

	if(gpio_status & BIT(4)){
		if(status1 == 0){
			gpio_output_set((1 << 13),0, (1 << 13),0);
			status1++;
		}
		else{
			gpio_output_set(0,(1 << 13), (1 << 13),0);
			status1=0;
		}
	}
	if(gpio_status & BIT(5)){
		if(status2 == 0){
			gpio_output_set((1 << 14),0, (1 << 14),0);
			status2++;
		}
		else{
			gpio_output_set(0,(1 << 14), (1 << 14),0);
			status2 = 0;
		}
	}


}

void ICACHE_FLASH_ATTR user_init(){
	
    //Starts GPIO's
    gpio_init();

    //Enable GPIO's 12,13,14,0,4,5
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
	
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
	
	//Set GPIO 0,4,5 as input (Disable output)
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(0));
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(4));
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(5));
	
	//Enable pull-up on inputs
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO0_U); 
	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO4_U); 
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO5_U); 


  	//Disable GPIO's interruptions
    ETS_GPIO_INTR_DISABLE();
	
	//Set which function will run when interruption trigger
    ETS_GPIO_INTR_ATTACH(GPIO_INTERRUPT, NULL);

	//Set input interrupt wave trigger (ANYEDGE, NEGEDGE, POSEDGE)
    gpio_pin_intr_state_set(GPIO_ID_PIN(0), GPIO_PIN_INTR_ANYEDGE);
    gpio_pin_intr_state_set(GPIO_ID_PIN(4), GPIO_PIN_INTR_ANYEDGE);
    gpio_pin_intr_state_set(GPIO_ID_PIN(5), GPIO_PIN_INTR_ANYEDGE);

	//Enable GPIO's interruptions
    ETS_GPIO_INTR_ENABLE();

	//Set GPIO's 12,13,14 to start in LOW level (1st parameter)		
	gpio_output_set(0,(1 << 14), (1 << 14),0);
	gpio_output_set(0,(1 << 12), (1 << 12),0);
	gpio_output_set(0,(1 << 13), (1 << 13),0);

}
