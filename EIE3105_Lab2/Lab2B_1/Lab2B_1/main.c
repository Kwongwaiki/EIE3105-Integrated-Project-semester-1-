/*
 * Lab2B_1.c
 *
 * Created: 29/9/2021 9:08:42
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
void T1Delay();
void T1Delay_1();

int main(){
	unsigned int i;  //for looping
	DDRB = 0xFF; //PORTB output port
	DDRC = 0xFF; //PORTC output port
	PORTB = 0x00;
	PORTC = 0x00;
	while(1){
		PORTB = 0x21;
		PORTC = 0x10;
		for (i=0; i<5; i++)
			T1Delay(); //Timer 1, Normal mode (5 sec)
					

		PORTB = 0x11;
		T1Delay(); //Timer 1, Normal mode (1 sec)
		
		PORTB = 0x09;
		T1Delay(); //Timer 1, Normal mode (1 sec)
		
		PORTB = 0x0B;
		T1Delay(); //Timer 1, Normal mode (1 sec)
			
		PORTB = 0x0C;			
		PORTC = 0x20;
		for (i=0; i<5; i++)
			T1Delay(); //Timer 1, Normal mode (5 sec)
		
		PORTB = 0x0A;
		for (i=0; i<5; i++)
		{
			PORTC = PORTC ^ (1<<PC5); //toggle PORTC.5
			T1Delay_1(); //Timer 1, Normal mode (0.2 sec)
		}
		
		PORTB = 0x09;
		PORTC = 0x10;
		T1Delay(); //Timer 1, Normal mode (1 sec)
		
		PORTB = 0x19;
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

void T1Delay_1(){
	TCNT1H = 0xF3; //TCNT1 = 0xF3CB
	TCNT1L = 0xCB;
	TCCR1A = 0x00; //Normal mode
	TCCR1B = 0x05; //Normal mode, Prescaler 1024
	while ((TIFR1 &(1<<TOV1))==0); //wait for TOV1 to roll over
	TCCR1B = 0; //turn off Timer 1
	TIFR1 = 0x1<<TOV1; //clear TOV1
}
//Timer value = 16M * 0.2 / 1024 = 3,125 (delay 0.2 sec)
//TCNT1 = 65,536 ¡V 3,125 = 62,411 = 0xF3CB





