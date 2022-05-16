#include "stm32f10x.h"                  // Device header

#define L1R GPIOA,GPIO_Pin_0
#define L1G GPIOA,GPIO_Pin_1
#define L2R GPIOA,GPIO_Pin_8
#define L2Y GPIOA,GPIO_Pin_9
#define L2G GPIOA,GPIO_Pin_4
#define L3R GPIOA,GPIO_Pin_5
#define L3Y GPIOA,GPIO_Pin_6
#define L3G GPIOA,GPIO_Pin_7

//PC13
#define BUTTON_RCC_GPIO   RCC_APB2Periph_GPIOC
#define BUTTON_GPIO	      GPIOC
#define BUTTON_GPIO_PIN   GPIO_Pin_13
#define BUTTON_EXTI_LINE     EXTI_Line13
#define BUTTON_GPIO_PORTSOURCE GPIO_PortSourceGPIOC
#define BUTTON_GPIO_PINSOURCE  GPIO_PinSource13

int times = 0;
int stage = 0;
int state = -1;
int i = -1;

void EXTI15_10_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line13) != RESET) {				
				state = state * (-1);
      	EXTI_ClearITPendingBit(EXTI_Line13);
    }
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
	if (state == 1){	
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
		}
	if (state == -1) 
	{
		GPIO_WriteBit(L1R,0);
		GPIO_WriteBit(L1G,0);
		GPIO_WriteBit(L2R,0);
		GPIO_WriteBit(L2Y,0);
		GPIO_WriteBit(L2G,0);
		GPIO_WriteBit(L3R,0);
		GPIO_WriteBit(L3Y,0);
		GPIO_WriteBit(L3G,0);
	}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

int main(){
	//setup
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(BUTTON_RCC_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
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
	
	
		// Configure I/O for EXTI13
	GPIO_InitStruct.GPIO_Pin = BUTTON_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BUTTON_GPIO, &GPIO_InitStruct);
	
	// EXTI Configuration
	GPIO_EXTILineConfig(BUTTON_GPIO_PORTSOURCE, BUTTON_GPIO_PINSOURCE);
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = BUTTON_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	// Enable Interrupt
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_Init(&NVIC_InitStruct);
	
	while(1){}
}