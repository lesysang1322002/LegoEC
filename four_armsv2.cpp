#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
#include "uart.h"
int status_previous = 0;
int previous_status = 0;
void ReTrai(double SpeedM1);
void RePhai(double SpeedM2);	
void dithang(double SpeedM1);
void UARTPrintf_Number(long number);
void PID();
void Convert(uint16_t Converted_value[]);
void oldstatus();
uint16_t SensorRead(uint16_t pin);
int  a=0;
float output;
uint8_t Sensor_v[5];
int main(void){
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	USART_config();
	GPIO_Config_TX_RX();	
	UARTPrintf_Number(20);
	uint16_t i=0;
	//Motor_SetForward(1 ,30);
	while(1){
		uint8_t sensor1 = Sensor_Read(SENSOR_PIN1);
    uint8_t sensor2 = Sensor_Read(SENSOR_PIN2);
    uint8_t sensor3 = Sensor_Read(SENSOR_PIN3);
    uint8_t sensor4 = Sensor_Read(SENSOR_PIN4);
    uint16_t sensor5 = SensorRead(SENSOR_PIN5);
		if (sensor1 && sensor2 && sensor3 && sensor4 && sensor5) {
          
            previous_status = status_previous;
        }
        
        
        oldstatus();
				output=30;
		switch ((sensor1 << 4) | (sensor2 << 3) | (sensor3 << 2) | (sensor4 << 1) | sensor5) {
			case 0b10001:
				RePhai(output);
				break;
			case 0b11110:
				RePhai(output);
				break;
			case 0b11100:
				RePhai(output);
				break;
			case 0b00001:
				ReTrai(output);
				break;
			case 0b10011:
				ReTrai(output);
				break;
			case 0b11101:
				RePhai(output);
				break;
			case 0b11011:
				dithang(output);
				break;
			case 0b11000:
				RePhai(output);
				break;
			case 0b00011:
				ReTrai(output);
				break;
			case 0b11111:
		    	oldstatus();
				break;
			default:
		    
					break;
	}
		//PID();
	
	}
}
void RePhai(double SpeedM1){
	Motor_SetForward(MOTOR_1, SpeedM1);
  Motor_SetStopping(MOTOR_2);
	status_previous = 2;
}
void ReTrai(double SpeedM2){
	Motor_SetForward(MOTOR_2, SpeedM2);
	Motor_SetStopping(MOTOR_1);
	status_previous = 1;

}
void dithang(double SpeedM1){
	Motor_SetForward(MOTOR_1,SpeedM1);
	Motor_SetForward(MOTOR_2,SpeedM1);
}
uint16_t SensorRead(uint16_t pin){
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}

void oldstatus(){
	if (status_previous == 1)
		ReTrai(output);
	  
	else if (status_previous == 2)
		RePhai(output);

}
