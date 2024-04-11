/*
  ******************************************************************************
  * @file		stm32_gpio.h                                                              *
  * @author	Nguyen Minh Quan                                                *
  * @date		27/03/2024    
	* @ver 1.0                                                       *
  ******************************************************************************
*/
#include "TIMER2.h"

void timer_Init(void){
		TIM_TimeBaseInitTypeDef timer_init;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    timer_init.TIM_CounterMode = TIM_CounterMode_Up;
    timer_init.TIM_Period = 65535; // co the de gia tri max 
    timer_init.TIM_Prescaler = 2 - 1;
    timer_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&timer_init);
    TIM_Cmd(TIM2,ENABLE); // Enable Timer2
}
void Delay_1ms(void){
	// set gia tri dem cua timer
	TIM_Cmd(TIM2,ENABLE); // cho ph�p Timer2 ho?t d?ng
	TIM_SetCounter(TIM2,0); // d?t gi� tr? ban d?u cho Timer2
	while(TIM_GetCounter(TIM2)<36000); // l?p d?n khi gi� tr?
	TIM_Cmd(TIM2,DISABLE); // kh�ng cho ph�p Timer2 ho?t d?ng
}
void Delay_ms(unsigned int time){
	while(time--){
	Delay_1ms();
	}
}
void led_Init(void){
	GPIO_InitTypeDef led_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	led_init.GPIO_Mode = GPIO_Mode_Out_PP;
	led_init.GPIO_Pin = GPIO_Pin_13;
	led_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&led_init);
}
/********************************* END OF FILE ********************************/
/******************************************************************************/