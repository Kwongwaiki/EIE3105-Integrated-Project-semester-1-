#include "stm32f10x.h"                  // Device header

#define L1R GPIOA,GPIO_Pin_0
#define L1G GPIOA,GPIO_Pin_1
#define L2R GPIOA,GPIO_Pin_8
#define L2Y GPIOA,GPIO_Pin_9
#define L2G GPIOA,GPIO_Pin_4
#define L3R GPIOA,GPIO_Pin_5
#define L3Y GPIOA,GPIO_Pin_6
#define L3G GPIOA,GPIO_Pin_7

int times = 0;
int stage = 0;
int i = -1;

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		
	stage = stage + 1;
	if (stage == 81) {stage = 0;}
	times = stage / 5;
	if (times < 5) {times = 1;}
		else if (times < 6) {times = 2;}
			else if (times < 7) {times = 3;}
				else if (times < 8) {times = 4;}
					else if (times < 13) {times = 5;}
						else if (times < 14) {times = 6;}
							else if (times < 15) {times = 7;}
								else if (times < 16) {times = 8;}
	switch (times)
	{
		case 1:
			GPIO_WriteBit(L2R,0);
			GPIO_WriteBit(L2Y,0);
		
			GPIO_WriteBit(L1R,1);
			GPIO_WriteBit(L2G,1);
			GPIO_WriteBit(L3R,1);
			break;
		case 2:
			GPIO_WriteBit(L2G,0);
		
			GPIO_WriteBit(L1R,1);
			GPIO_WriteBit(L2Y,1);
			GPIO_WriteBit(L3R,1);
			break;
		case 3:
			GPIO_WriteBit(L2Y,0);
		
			GPIO_WriteBit(L1R,1);
			GPIO_WriteBit(L2R,1);
			GPIO_WriteBit(L3R,1);
			break;
		case 4:
			GPIO_WriteBit(L1R,1);
			GPIO_WriteBit(L2R,1);
			GPIO_WriteBit(L3R,1);
			GPIO_WriteBit(L3Y,1);
			break;
		case 5:
			GPIO_WriteBit(L1R,0);
			GPIO_WriteBit(L3R,0);
			GPIO_WriteBit(L3Y,0);
		
			GPIO_WriteBit(L1G,1);
			GPIO_WriteBit(L2R,1);
			GPIO_WriteBit(L3G,1);
			break;
		case 6:
			GPIO_WriteBit(L3G,0);
			
			i = i * -1;
			GPIO_WriteBit(L1G,((1+i)/2));
			GPIO_WriteBit(L2R,1);
			GPIO_WriteBit(L3Y,1);
			break;
		case 7:
			GPIO_WriteBit(L1G,0);
			GPIO_WriteBit(L3Y,0);
		
			GPIO_WriteBit(L1R,1);
			GPIO_WriteBit(L2R,1);
			GPIO_WriteBit(L3R,1);
			break;
		case 8:
			GPIO_WriteBit(L1R,1);
			GPIO_WriteBit(L2R,1);
			GPIO_WriteBit(L2Y,1);
			GPIO_WriteBit(L3R,1);
			break;
		default:
			break;
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(){
	//setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef LED_Init;
	LED_Init.GPIO_Pin = GPIO_Pin_All;
	LED_Init.GPIO_Speed = GPIO_Speed_2MHz;
	LED_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &LED_Init);
	//defind the GPIO pin
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
		TIM_TimeBaseInitTypeDef TIM2_Init;
		TIM2_Init.TIM_Prescaler	= 14400-1; // 72Mhz*0.2ms = 14400
		TIM2_Init.TIM_Period = 1000-1;	//0.2ms*1000=0.2s
		TIM2_Init.TIM_CounterMode = TIM_CounterMode_Up;
		TIM2_Init.TIM_ClockDivision = 0;
		TIM2_Init.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM2, &TIM2_Init);
		TIM_Cmd(TIM2, ENABLE);

	//Enable update event for Timer2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	while(1){}
}