#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

int main(void){
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	while(1){		
		if(Sensor_Read(SENSOR_PIN1) == SENSOR_ON)
			Led_On(LED_1);
		else
			Led_Off(LED_1);
		
		if(Sensor_Read(SENSOR_PIN2) == SENSOR_ON)
			Led_On(LED_2);
		else
			Led_Off(LED_2);
		
		if(Sensor_Read(SENSOR_PIN3) == SENSOR_ON)
			Led_On(LED_3);
		else
			Led_Off(LED_3);
		
		if(Sensor_Read(SENSOR_PIN4) == SENSOR_ON)
			Led_On(LED_4);
		else
			Led_Off(LED_4);
		Delay_ms(100);
	}
}
