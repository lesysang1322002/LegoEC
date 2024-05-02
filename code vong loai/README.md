# Four_Arm
## TỔNG HỢP CODE TỪ VÒNG LOẠI ROBOT
- Code 1:
```
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
uint16_t SensorRead(uint16_t pin){                         // hàm đọc riêng cho sensor 5
	if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
		return SENSOR_ON;
	else
		return SENSOR_OFF;
}

uint16_t SensorRead(uint16_t pin);

int Converted_value[6];
int Sum = 0;
int old_sum = 0;


int Distance(int Converted_value[])          // hàm xác định khoảng cách giữa line và sensor trung tâm (sensor 3)
{
  int sum = 0;
  char i = 0;
  for (char k = 1; k <= 5; k++) // 5 sensor
  {
    if (Converted_value[k]==0)  // tức line đen
    {
      i++;
      sum = sum + k * 100;       // khi có sensor dính vào line thì ta sẽ tiến hành tính tổng các giá trị {100,200,300,400,500} tương ứng với các sensor {1,2,3,4,5}
    }
  }

  if ( (i > 0) && (i < 5) )     
  {
    old_sum = sum / i;			// tính giá trị old_sum trả về giá trị trung bình để xác định độ lệch giữa sensor 3 với line
    return old_sum;
  }
  else if (i == 5) // 
  {
    return old_sum;             // nếu cả 5 sensor đều dính line thì trả về giá trị nhớ trước đó
  }
  else           // nếu xe out line 
  {
    if ( (200 < old_sum ) && (old_sum < 400) )
      return 300;
    else
      return old_sum;
  }
}
void PID(uint16_t distance)
{
	int distance_error;  // sai số lệch line

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
		dithang(80);
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
			
		Sum = Distance(Converted_value);	 								
		PID(Sum);
	}
}
```
- Code 2:
```
#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

int speedMax = 80;
int speed3 = 0.8*speedMax
int speed2 = 0.4*speedMax;
int speed1 = 0.2*speedMax;

void RePhai(int motor1, int motor2){
    Motor_SetForward(MOTOR_1, motor1);
    Motor_SetForward(MOTOR_2, motor2);
}

void ReTrai(int motor1, int motor2){
    Motor_SetForward(MOTOR_2, motor2);
    Motor_SetForkward(MOTOR_1, motor1);
}

void diThang(int motor1, int motor 2){
    Motor_SetForward(MOTOR_1, motor1);
    Motor_SetForward(MOTOR_2, motor2);
}

uint16_t SensorRead(uint16_t pin){
    if(GPIO_ReadInputDataBit(SENSOR_PORT, pin) == Bit_SET)
        return SENSOR_ON;
    else
        return SENSOR_OFF;
}

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
        int line_state = (sensor1 << 4) | (sensor2 << 3) | (sensor3 << 2) | (sensor4 << 1) | sensor5;

            switch(line_state) {
                case 0b11011: 
                    diThang(speedMax,speedMax);
                    break;
								case 0b11101:
                    ReTrai(speed3,speedMax);
                    break;
								case 0b11110:
									  ReTrai(speed2,speedMax);
                    break;
								case 0b11000:
										RePhai(speedMax,speed1);
										break;
								case 0b10111:
										RePhai(speedMax,speed3);
                    break;
								case 0b01111:
										RePhai(speedMax,speed2);
                    break;
								case 0b00011:
										ReTrai(speed1,speedMax);
                    break;
								default:
										break;
            }
    }
}
```
