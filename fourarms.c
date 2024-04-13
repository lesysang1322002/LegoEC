#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

#define maxSpeed  80
#define baseSpeed 60
#define turnSpeed 20

int count = 0;
int buttonState = 0;
int lastButtonState = 0;

void Sensor_Read_All();
void Read_Button();
void Turn_Left(int Speed_M_1, int Speed_M_2);
void Turn_Right(int Speed_M_1, int Speed_M_2);
void ForWard(int Speed);
void BackWard(int Speed);
void Run();

int Status_Robot = 0;
int Sensors[5];

int main(void)
{
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	while (1)
	{
		Read_Button();
		Sensor_Read_All();
		Delay_ms(50);
		if (Status_Robot == 1)
		{
			Run();
		}
	}
}
void Run()
{
    int S = Sensors[0] * 16 + Sensors[1] * 8 + Sensors[2] * 4 + Sensors[3] * 2 + Sensors[4];

    switch (S)
    {
    case 0b11011:
        ForWard(maxSpeed);
        break;
    case 0b01111:
        Turn_Left(baseSpeed, baseSpeed + turnSpeed);
        break;
    case 0b11110:
        Turn_Right(baseSpeed + turnSpeed, baseSpeed);
        break;
    case 0b10111:
        Turn_Left(baseSpeed, baseSpeed - turnSpeed);
        break;
    case 0b11101:
        Turn_Right(baseSpeed - turnSpeed, baseSpeed);
        break;
    case 0b00111:
        Turn_Left(baseSpeed, baseSpeed);
        break;
    case 0b11100:
        Turn_Right(baseSpeed, baseSpeed);
        break;
    default:
        BackWard(baseSpeed);
        break;
    }
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
			if (buttonState == 0)
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
	for(int i = 0; i < 5; i++)
	{
		Sensors[i] = Sensor_Read(SENSOR_PIN1 + i);
	}
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

