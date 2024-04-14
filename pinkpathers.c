#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

#define ON 1
#define OFF 0
#define baseSpeed 60
#define turnSpeed 20

int count = 0;
int buttonState = OFF;
int lastButtonState = OFF;

void Sensor_Read_All();
void Read_Button();
void Turn_Left(int Speed_M_1, int Speed_M_2);
void Turn_Right(int Speed_M_1, int Speed_M_2);
void ForWard(int Speed);
void BackWard(int Speed);
void Run();
void Stop();

int Status_Robot = 0;
int S1, S2, S3, S4, S5;

int main(void)
{
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	while (1)
	{
		//		Read_Button();
		Sensor_Read_All();
		//		Delay_ms(50);
		//		if (Status_Robot == ON)
		//		{
		Run();
	}
}
void Run()
{
	// em đang quay lại với if else vì switch case không hoạt động với S1=0, vì nó đang là kiểu int
	// em đang viết lại hàm này vì if else này rắc rối quá
	if (S1 == 1 && S2 == 1 && S3 == 0 && S4 == 1 && S5 == 1)
		ForWard(baseSpeed + turnSpeed);
	else if (S1 == 1 && S2 == 1 && S3 == 0 && S4 == 0 && S5 == 1)
		ForWard(baseSpeed + turnSpeed);
	else if (S1 == 1 && S2 == 0 && S3 == 0 && S4 == 1 && S5 == 1)
		ForWard(baseSpeed + turnSpeed);
	else if (S1 == 0 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1)
		Turn_Left(40, 4);
	else if (S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 0)
		Turn_Right(4, 40);
	else if (S1 == 1 && S2 == 1 && S3 == 0 && S4 == 1 && S5 == 0)
		Turn_Right(4, 40);
	else if (S1 == 1 && S2 == 0 && S3 == 1 && S4 == 1 && S5 == 1)
		Turn_Left(40, 4);
	else if (S1 == 1 && S2 == 1 && S3 == 1 && S4 == 0 && S5 == 1)
		Turn_Right(4, 40);
	else if (S1 == 0 && S2 == 0 && S3 == 1 && S4 == 1 && S5 == 1)
		Turn_Left(40, 4);
	else if (S1 == 1 && S2 == 1 && S3 == 1 && S4 == 0 && S5 == 0)
		Turn_Right(4, 40);
	else if (S1 == 0 && S2 == 0 && S3 == 0 && S4 == 1 && S5 == 1)
		Turn_Left(40, 4);
	else if (S1 == 1 && S2 == 1 && S3 == 0 && S4 == 0 && S5 == 0)
		Turn_Right(4, 40);
	else if (S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1)
		BackWard(60);
	else
		Stop();
}
void Read_Button()
{
	int reading = Button_Read(BUTTON_ONOFF);
	if (reading != lastButtonState)
	{
		Delay_ms(200);
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == OFF)
			{
				count++;
				count %= 2;
				Status_Robot = count;
			}
		}
	}
	lastButtonState = reading;
}
void Sensor_Read_All()
{
	S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0;
	S1 = Sensor_Read(SENSOR_PIN1);
	S2 = Sensor_Read(SENSOR_PIN2);
	S3 = Sensor_Read(SENSOR_PIN3);
	S4 = Sensor_Read(SENSOR_PIN4);
	S5 = Sensor_Read(SENSOR_PIN5);
}
void ForWard(int Speed)
{
	Motor_SetForward(MOTOR_1, Speed);
	Motor_SetForward(MOTOR_2, Speed);
}
void BackWard(int Speed)
{
	Motor_SetBackward(MOTOR_1, Speed);
	Motor_SetBackward(MOTOR_2, Speed);
}
void Turn_Left(int Speed_M_1, int Speed_M_2)
{
	Motor_SetForward(MOTOR_1, Speed_M_1);
	Motor_SetBackward(MOTOR_2, Speed_M_2);
}
void Turn_Right(int Speed_M_1, int Speed_M_2)
{
	Motor_SetBackward(MOTOR_1, Speed_M_1);
	Motor_SetForward(MOTOR_2, Speed_M_2);
}
void Stop()
{
	Motor_SetStopping(MOTOR_1);
	Motor_SetStopping(MOTOR_2);
}