# ESP8266_Interruption_GPIO
Toggle LEDs by external interruptions

#What does it do?
This code runs C native to control ESP8266. It sets 3 GPIO's as input and enable external interruptions on them.
Next, 3 other GPIO's are set as outputs (LEDs).
When an input GPIO trigger, the correspondent LED will become LOW or HIGH, the opposite of its last value.
