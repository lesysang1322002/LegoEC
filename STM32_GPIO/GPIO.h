/*
  ******************************************************************************
  * @file		abc.h                                                              *
  * @author	Nguyen Quang Bien                                                  *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
	 
void Config(void);
void led_Blink(void);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/