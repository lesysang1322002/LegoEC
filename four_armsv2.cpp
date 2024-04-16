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

void oldstatus();
uint16_t SensorRead(uint16_t pin);

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
	//Motor_SetForward(2,60);
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
		//	ReTrai(70);
			//if(SensorRead(SENSOR_PIN5)==1) ReTrai(70);
		switch ((sensor1 << 4) | (sensor2 << 3) | (sensor3 << 2) | (sensor4 << 1) | sensor5) {
			case 0b10011:
				ReTrai(30);
				break;
			case 0b00011:
				ReTrai(30);
				break;
			case 0b11101:
				RePhai(30);
				break;
			case 0b11000:
				RePhai(30);
				break;
			case 0b11011:
				dithang(30);
				break;
			case 0b11111:
				oldstatus();
				break;
			default:
		  
					break;
	}
	Delay_ms(300);

	}
}
void RePhai(double SpeedM1){
	Motor_SetForward(MOTOR_1, SpeedM1);
  Motor_SetStopping(MOTOR_2);
	status_previous = 4;
}
void ReTrai(double SpeedM2){
	Motor_SetForward(MOTOR_2, SpeedM2);
	Motor_SetStopping(MOTOR_1);
	status_previous = 3;

}
void dithang(double SpeedM1){
	Motor_SetForward(MOTOR_1,SpeedM1);
	Motor_SetForward(MOTOR_2,SpeedM1);
	status_previous = 2;
}
uint16_t SensorRead(uint16_t pin){
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}

void oldstatus(){
	if (status_previous == 2)
		dithang(30);
	else if (status_previous == 3)
		ReTrai(30);
	else if (status_previous == 4)
		RePhai(30);

}
