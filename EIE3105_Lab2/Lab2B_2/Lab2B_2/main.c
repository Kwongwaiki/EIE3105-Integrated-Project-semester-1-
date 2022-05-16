/*
 * Lab2B_2.c
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
			T1Delay(); //Timer 1, CTC mode (5 sec)
					

		PORTB = 0x11;
		T1Delay(); //Timer 1, CTC mode (1 sec)
		
		PORTB = 0x09;
		T1Delay(); //Timer 1, CTC mode (1 sec)
		
		PORTB = 0x0B;
		T1Delay(); //Timer 1, CTC mode (1 sec)
			
		PORTB = 0x0C;			
		PORTC = 0x20;
		for (i=0; i<5; i++)
			T1Delay(); //Timer 1, CTC mode (5 sec)
		
		PORTB = 0x0A;
		for (i=0; i<5; i++)
		{
			PORTC = PORTC ^ (1<<PC5); //toggle PORTC.5
			T1Delay_1(); //Timer 1, CTC mode (0.2 sec)
		}
		
		PORTB = 0x09;
		PORTC = 0x10;
		T1Delay(); //Timer 1, CTC mode (1 sec)
		
		PORTB = 0x19;
		T1Delay(); //Timer 1, CTC mode (1 sec)
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

void T1Delay_1(){
	OCR1A = 3124;  //3125 - 1  //1 for overflow
	TCCR1A = 0x00; //CTC mode
	TCCR1B = 0x0D; //CTC mode, Prescaler 1024
	while((TIFR1 & (1<<OCF1A))==0);
	TCCR1B = 0; //stop timer1
	TIFR1 = 0x02;  //OCF0 = 1
}
//Timer value = 16M * 0.2 / 1024 = 3,125 (delay 0.2 sec)

