#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"


void RePhai(double SpeedM1){
	Motor_SetForward(MOTOR_1, SpeedM1);
 
	Motor_SetBackward(MOTOR_2, 25);
}
void ReTrai(double SpeedM2){
	Motor_SetForward(MOTOR_2, SpeedM2);

	Motor_SetBackward(MOTOR_1, 25);
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

uint16_t SensorRead(uint16_t pin);

int Converted_value[6];// mang luu giá tr? c?m bi?n sau khi chuy?n t? analog sang digital
int Sum = 0;
int old_sum = 0;


int Distance(int Converted_value[])
{
  int sum = 0;
  char i = 0;
  for (char k = 1; k <= 5; k++) // 8 sensor
  {
    if (Converted_value[k]==0)  //Black line
    {
      i++;
      sum = sum + k * 100;
    }
  }

  if ( (i > 0) && (i < 5) )
  {
    old_sum = sum / i;
    return old_sum;
  }
  else if (i == 5) // all line ?
  {
    return old_sum;
  }
  else            // no line ?
  {
    if ( (200 < old_sum ) && (old_sum < 400) )
      return 300;
    else
      return old_sum;
  }
}
void PID(uint16_t distance)
{
	int distance_error;

	distance_error = 300 - distance;

	// Motor control
	if (distance_error > 0 )
	{
			ReTrai(75);	
	}
	else if (distance_error < 0)
	{
			RePhai(75);		
	}
	else
	{
		if((Converted_value[1]==0 && Converted_value[2]==1 && Converted_value[3]==1 && Converted_value[4]==1 && Converted_value[5]==1)){
			RePhai(75);
		}
		else dithang(80);
	}
	
}
int main(void){
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();

	 while(1){
		Converted_value[1] = Sensor_Read(SENSOR_PIN1);
    Converted_value[2] = Sensor_Read(SENSOR_PIN2);
    Converted_value[3] = Sensor_Read(SENSOR_PIN3);
    Converted_value[4] = Sensor_Read(SENSOR_PIN4);
    Converted_value[5] = SensorRead(SENSOR_PIN5);
			
		Sum = Distance(Converted_value);	 								// return sum based on Converted_value
		PID(Sum);
	}
}
