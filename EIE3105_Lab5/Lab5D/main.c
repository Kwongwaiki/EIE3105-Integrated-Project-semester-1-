#include "stm32f10x.h"                  // Device header

void delay(int t);

void delay(int t) 
{
	int i;
	for(i = 0; i < t; i++) GPIOA->BSRR |= 0x01; // do something to PA0
}

int main(void) {
	int state = -1;
		//Enable APB2 periphral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

		//GPIO set up for PA5 (on board LED)
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		//GPIO set up for PC13 (on board switch)
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStructure2.GPIO_Mode  = GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure2);
	
	while(1) {
		if ((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))==0)
			state = state * -1;
		delay(100);
		if (state == 1)
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		if (state == -1)
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		
		if ((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13))==0)
			state = state * -1;
		if (state == 1)
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		if (state == -1)
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
	}
}


