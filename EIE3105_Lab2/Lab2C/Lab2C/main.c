/*
 * Lab2C.c
 *
 * Created: 30/9/2021 2:43:48
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
void T1Delay_1();

int main(){
	unsigned int state, times;  //for looping
	DDRC = 0xFF; //PORTC output port
	DDRD = 0x00; //PORTD input port
	PORTC = 0x00;
	PORTD = 0x10;
	state = 0;
	times = 0;
	while(1){		
		T1Delay_1();
		PORTC = PORTC ^ (1<<PC0); //toggle PORTC.0
	}
}

void T1Delay_1(){
	OCR1A = 0x02;  
	TCCR1A = 0x00; //CTC mode
	TCCR1B = 0x0F; //CTC mode, External clock source on T1 pin. Clock on rising edge
	while((TIFR1 & (1<<OCF1A))==0);
	TCCR1B = 0; //stop timer1
	TIFR1 = 0x02;  //OCF0 = 1
	TIFR1 = (1<<OCF1A);
}
