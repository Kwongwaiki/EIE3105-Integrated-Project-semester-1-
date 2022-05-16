/*
 * Lab2A_1.c
 *
 * Created: 29/9/2021 9:08:42
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
void T1Delay();

int main(){
	DDRB = 0xFF; //PORTB output port
	PORTB = 0x00;
	while(1){
		PORTB = PORTB ^ (1<<PB0); //toggle PORTB.5
		T1Delay(); //Timer 1, Normal mode (1 sec)
	}
}

void T1Delay(){  
	TCNT1H = 0xC2; //TCNT1 = 0xC2F7
	TCNT1L = 0xF7;
	TCCR1A = 0x00; //Normal mode
	TCCR1B = 0x05; //Normal mode, Prescaler 1024
	while ((TIFR1 &(1<<TOV1))==0); //wait for TOV1 to roll over
	TCCR1B = 0; //turn off Timer 1
	TIFR1 = 0x1<<TOV1; //clear TOV1
} 
//Timer value = 16M * 1 / 1024 = 15,625 (delay 1 sec)
//TCNT1 = 65,536 ¡V 15,625 = 49,911 = 0xC2F7

