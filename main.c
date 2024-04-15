#include "led.h"
#include "delay.h"
#include "motor.h"
#include "button.h"
#include "sensor.h"

#define MOTOR_MEAN 50


char readSensors() {
    char sensor[3] = {'0', '0', '0'};
    if(Sensor_Read(SENSOR_PIN2) == SENSOR_ON)
        sensor[0] = '1';
    if(Sensor_Read(SENSOR_PIN3) == SENSOR_ON)
        sensor[1] = '1';
    if(Sensor_Read(SENSOR_PIN4) == SENSOR_ON)
        sensor[2] = '1';
    char result = sensor[0] + sensor[1] + sensor[2];
    return result;
}

void TurnLeft() {
    Motor_SetForward(MOTOR_2, MOTOR_MAX);
    Motor_SetBackward(MOTOR_1, MOTOR_MEAN);
}

void TurnRight() {
    Motor_SetForward(MOTOR_1, MOTOR_MAX);
    Motor_SetBackward(MOTOR_2, MOTOR_MEAN);
}

void MoveForward() {
    Motor_SetForward(MOTOR_1, MOTOR_MAX);
    Motor_SetForward(MOTOR_2, MOTOR_MAX);
}

void TurnLeft90() {
    Motor_SetForward(MOTOR_2, MOTOR_MAX);
    Motor_SetBackward(MOTOR_1, MOTOR_MIN);
}

void TurnRight90() {
    Motor_SetForward(MOTOR_1, MOTOR_MAX);
    Motor_SetBackward(MOTOR_2, MOTOR_MIN);
}


int main(void) {
    Delay_Init();
    Led_Init();
    Motor_Init();
    Button_Init();
    Sensor_Init();

    while (1) {
        if(Button_Read(BUTTON_RUN) == Press){
        char sensorResult = readSensors();
        switch(sensorResult){
            case 100:
                TurnLeft();
                break;
            case 001:
                TurnRight();
                break;
            case 011:
                TurnRight90();
                break;
            case 110:
                TurnLeft90();
                break;
            default:
                MoveForward();
                break;
        }
        }
    }
}

