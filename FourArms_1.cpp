#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
#define KP 1.0
#define KI 0.1
#define KD 0.01
double previous_error = 0;
double integral = 0;

void ReTrai(double SpeedM1);
void RePhai(double SpeedM2);	
void dithang(double SpeedM1, double SpeedM2);
uint16_t SensorRead(uint16_t pin);
int  a=0;
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
		
		double error = (sensor1 - sensor5) * 1 + (sensor2 - sensor5) * 0.5 + (sensor3 - sensor5) * 0 + (sensor4 - sensor5) * (-0.5);
		double output = KP * error + KI * integral + KD * (error - previous_error);
		//Motor_SetForward(2,output);
		switch ((sensor1 << 4) | (sensor2 << 3) | (sensor3 << 2) | (sensor4 << 1) | sensor5) {
    case 0b11100:
        ReTrai(70);
      // Delay_ms(2000);
        break;
    case 0b00111:
        RePhai(70);
       //Delay_ms(2000);
        break;
    case 0b00100:
        dithang(80,80);
        break;
    default:
  
        break;
	}
		previous_error = error;
    integral += error;
		Delay_ms(100);
/*	if(sensor5==SENSOR_ON){
		a++;
		Delay_ms(2000);
	}*/
	}
}
void RePhai(double SpeedM1){
	Motor_SetForward(MOTOR_1, SpeedM1);
  Motor_SetStopping(MOTOR_2);
}
void ReTrai(double SpeedM2){
	  Motor_SetForward(MOTOR_2, SpeedM2);
		Motor_SetStopping(MOTOR_1);

}
void dithang(double SpeedM1, double SpeedM2){
	Motor_SetForward(MOTOR_1,SpeedM1);
	Motor_SetForward(MOTOR_2,SpeedM2);
}
uint16_t SensorRead(uint16_t pin){
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}

