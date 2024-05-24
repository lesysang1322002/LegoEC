#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
void RePhai(int SpeedM1,int SpeedM2){
	Motor_SetForward(MOTOR_1, SpeedM1);
  Motor_SetForward(MOTOR_2, SpeedM2);
}
void RePhai1(int SpeedM1,int SpeedM2){
	Motor_SetForward(MOTOR_1, SpeedM1);
  Motor_SetBackward(MOTOR_2, SpeedM2);
}
void ReTrai(int SpeedM1,int SpeedM2){
	Motor_SetForward(MOTOR_2, SpeedM1);
	Motor_SetForward(MOTOR_1,SpeedM2);
}
void ReTrai1(int SpeedM1,int SpeedM2){
	Motor_SetForward(MOTOR_2, SpeedM1);
	Motor_SetBackward(MOTOR_1,SpeedM2);
}
void dithang(int SpeedM1, int SpeedM2){
	Motor_SetForward(MOTOR_1,SpeedM1);
	Motor_SetForward(MOTOR_2,SpeedM2);
}
uint16_t SensorRead(uint16_t pin){
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}


uint8_t Sensor_v[5];
int main(void){
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	while(1){
	  uint8_t sensor1 = Sensor_Read(SENSOR_PIN1);
    uint8_t sensor2 = Sensor_Read(SENSOR_PIN2);
    uint8_t sensor3 = Sensor_Read(SENSOR_PIN3);
    uint8_t sensor4 = Sensor_Read(SENSOR_PIN4);
    uint16_t sensor5 = SensorRead(SENSOR_PIN5);
		uint8_t result=(sensor1 << 4) | (sensor2 << 3) | (sensor3 << 2) | (sensor4 << 1) | sensor5;
		switch (result) {
			case 0b00010:
				ReTrai(40,5);
				break;
			case 0b01100:
				ReTrai(40,5);
				break;
			case 0b01111:
			case 0b00111:
			case 0b01011:
				ReTrai1(50,10);
				break;
			case 0b11110:
			case 0b11010:
			case 0b11100:
				RePhai1(50,10);
				break;
			case 0b11000:
				RePhai(40,5);
				break;
			case 0b11011:
				dithang(50,50);
				break;
			case 0b10011:
				ReTrai(40,15);
				break;
			case 0b11001:
				RePhai(40,15);
				break;
			case 0b00011:
				ReTrai(50,5);
				break;
		}
	}
}
