# PINK_PANTHERS
# TỔNG HỢP CODE
## 1. CODE 1
```stm32
#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"
#include "uart.h"

void PID(uint16_t distance);
uint16_t SensorRead(uint16_t pin);
int Distance(int Converted_value[]);
void RePhai_Lui(double SpeedM1, double SpeedM2); // 1 sensor tien, 1 lui
void ReTrai_Lui(double SpeedM1, double SpeedM2);
void RePhai(double SpeedM2, double SpeedM1); // 2 sensor tien
void ReTrai(double SpeedM2, double SpeedM1);
void dithang(double SpeedM1); // cac ham re trai, phai, di thang hien tai tam khong su dung

int Converted_value[6];
int Sum = 0;
int old_sum = 0;

int main(void)
{
	Delay_Init();
	Led_Init();
	Motor_Init();
	Button_Init();
	Sensor_Init();
	USART_config();
	GPIO_Config_TX_RX();
	UARTPrintf_Number(20);
	uint16_t i = 0;
	// Motor_SetForward(1 ,30);
	while (1)
	{
		Converted_value[1] = Sensor_Read(SENSOR_PIN1);
		Converted_value[2] = Sensor_Read(SENSOR_PIN2);
		Converted_value[3] = Sensor_Read(SENSOR_PIN3);
		Converted_value[4] = Sensor_Read(SENSOR_PIN4);
		Converted_value[5] = SensorRead(SENSOR_PIN5);

		Sum = Distance(Converted_value); // return sum based on Converted_value
		PID(Sum);
	}
}
void PID(uint16_t distance)
{
	int distance_error;
	switch (distance)
	{
	case 100: // s1 tat
		Motor_SetBackward(MOTOR_1, 25);
		Motor_SetForward(MOTOR_2, 60);
		break;
	case 200: // s2 tat
		Motor_SetForward(MOTOR_2, 60);
		Motor_SetForward(MOTOR_1, 25);
		break;
	case 300: // s3 tat
		dithang(80);
		break;
	case 400: // s4 tat
		Motor_SetBackward(MOTOR_2, 25);
		break;
	case 500: // s5 tat
		Motor_SetForward(MOTOR_1, 60);
		Motor_SetBackward(MOTOR_2, 25);
		break;
	case 150: // s1,2 tat
		Motor_SetBackward(MOTOR_1, 25);
		Motor_SetForward(MOTOR_2, 60);
		break;
	case 250:						   // s2,3 tat
		Motor_SetForward(MOTOR_2, 60); // ben phai  // k dc thif ve 50
		Motor_SetForward(MOTOR_1, 25); // trai
		break;
	case 350:						   // s3,4 tat
		Motor_SetForward(MOTOR_1, 60); // k dc thif ve 50
		Motor_SetForward(MOTOR_2, 25);
		break;
	case 450: // s4,5 tatS
		Motor_SetForward(MOTOR_1, 60);
		Motor_SetBackward(MOTOR_2, 25);
		break;
	default:
		break;
	}
}

int Distance(int Converted_value[]) // tinh muc hien thi sensor
{
	int sum = 0;
	char i = 0;
	for (char k = 1; k <= 5; k++) // 5 sensor
	{
		if (Converted_value[k] == 0) // Black line
		{
			i++;
			sum = sum + k * 100; // tinh tong gia tri sensor
		}
	}

	if ((i > 0) && (i < 5))
	{
		old_sum = sum / i; // , sau do tinh gia tri trung binh de ra muc hien thi sensor
		return old_sum;	   // vi du: 00100 -> 300 , 01100 -> 250
	}
	else if (i == 5) // tat ca den sensor deu tat
	{
		return old_sum; // tra ve trang thai truoc do
	}
	else // tat ca den sensor deu bat
	{
		//    if ( (200 < old_sum ) && (old_sum < 400) )
		//      return 300;
		//    else
		return old_sum; // tra ve trang thai truoc do
	}
}

void RePhai_Lui(double SpeedM1, double SpeedM2)
{
	Motor_SetForward(MOTOR_1, SpeedM1);
	// Motor_SetStopping(MOTOR_2);
	Motor_SetBackward(MOTOR_2, SpeedM2);
}
void ReTrai_Lui(double SpeedM1, double SpeedM2)
{
	Motor_SetForward(MOTOR_2, SpeedM2);
	// Motor_SetStopping(MOTOR_1);
	Motor_SetBackward(MOTOR_1, SpeedM1);
}
void RePhai(double SpeedM2, double SpeedM1)
{
	Motor_SetBackward(MOTOR_1, SpeedM1);
	// Motor_SetStopping(MOTOR_2);
	Motor_SetBackward(MOTOR_2, 15);
}
void ReTrai(double SpeedM2, double SpeedM1)
{
	Motor_SetBackward(MOTOR_2, SpeedM2);
	// Motor_SetStopping(MOTOR_1);
	Motor_SetBackward(MOTOR_1, SpeedM1);
}
void dithang(double SpeedM1)
{
	Motor_SetForward(MOTOR_1, SpeedM1);
	Motor_SetForward(MOTOR_2, SpeedM1);
}
uint16_t SensorRead(uint16_t pin)
{
	if (GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}
```

## 2. CODE 2
```stm32
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
void Previous();

int status_previous = 0, sensors_previous = 0, status_previous_flag = 0;

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
        // Read_Button();

        Sensor_Read_All();
        // Run();
        //		if (Status_Robot == ON)
        //		{
        Run();
        //}
    }
}
void Run()
{
    int S = S1 * 10000 + S2 * 1000 + S3 * 100 + S4 * 10 + S5;
    switch (S)
    {
    case 11011:
        ForWard(baseSpeed); // 60
        break;
    case 11001:
        ForWard(baseSpeed);
        break;
    case 10011:
        ForWard(baseSpeed);
        break;
    case 1111: // 01111
        Turn_Left(80, 25);
        break;
    case 11110:
        Turn_Right(25, 80);
        break;
    case 1011: // 01011
        Turn_Left(70, 15);
        break;
    case 11010:
        Turn_Right(15, 70);
        break;
    case 10111:
        Turn_Left(80, 10);
        break;
    case 11101:
        Turn_Right(10, 80);
        break;
    case 111: // 00111
        Turn_Left(80, 15);
        break;
    case 11100:
        Turn_Right(15, 80);
        break;
    case 11: // 00011
        Turn_Left(80, 10);
        break;
    case 11000:
        Turn_Right(10, 80);
        break;
    case 11111: // cac truong hop full line, outline, va cac truong hop khac se quay ve trang thai truoc do
        Previous();
    case 00000:
        Previous();
    default:
        Previous();
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
    status_previous = 2;
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
    status_previous = 3;
}
void Turn_Right(int Speed_M_1, int Speed_M_2)
{
    Motor_SetBackward(MOTOR_1, Speed_M_1);
    Motor_SetForward(MOTOR_2, Speed_M_2);
    status_previous = 4;
}
void Stop()
{
    Motor_SetStopping(MOTOR_1);
    Motor_SetStopping(MOTOR_2);
}
void Previous()
{

    if (status_previous == 2)
        ForWard(80);
    else if (status_previous == 3)
        Turn_Left(40, 4);
    else if (status_previous == 4)
        Turn_Right(4, 40);
}

```
