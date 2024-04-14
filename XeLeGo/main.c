#include "stm32f10x.h"
#include "LED.h"
#include "DELAY.h"
int main(void){
	Led_Init();
	Delay_Init();
	while(1){		
		Led_Off(GPIO_Pin_13);
		Delay_ms(1000);

		Led_On(GPIO_Pin_13);	
		Delay_ms(1000);
	}
}


