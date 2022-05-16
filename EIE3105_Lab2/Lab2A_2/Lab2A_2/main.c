/*
 * Lab2A_2.c
 *
 * Created: 29/9/2021 9:08:42
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
void T1Delay();

int main(){
	DDRB |= 1<<0; //PORTB output port
	PORTB &= ~(1<<0);
	while (1)
	{
		T1Delay();
		PORTB = PORTB ^ (1<<PB0); //toggle PORTB.0
	}
}

void T1Delay(){
	OCR1A = 15624;  //15,625 - 1  //1 for overflow
	TCCR1A = 0x00; //CTC mode
	TCCR1B = 0x0D; //CTC mode, Prescaler 1024
	while((TIFR1 & (1<<OCF1A))==0);
	TCCR1B = 0; //stop timer1
	TIFR1 = 0x02;  //OCF0 = 1
}
//Timer value = 16M * 1 / 1024 = 15,625 (delay 1 sec)