/*
 * Lab3B.c
 *
 * Created: 27/10/2021 8:42:23
 * Author : Eric Kwong
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int stage = -1;
unsigned int times = 0;
unsigned int button = -1;
int cnt = 0;
void lab2b();
void lab2b_1();

int main(){
	DDRB = 0xFF; //PORTB output port
	DDRC = 0xFF; //PORTC output port
	DDRD = 0x00; //PORTD input port
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x07;
	
	EIMSK = 0x01; //enable external interrupt 0
	EICRA = 0x03;
	lab2b();
	sei ();	//enable interrupts
	while(1);
}


void lab2b_1()
{
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
			PORTB = 0x21;
			if (button == 1) PORTC = 0x11;
				else PORTC = 0x10;
			break;
		case 2:
			PORTB = 0x11;
			break;
		case 3:
			PORTB = 0x09;
			break;
		case 4:
			PORTB = 0x0B;
			break;
		case 5:
			PORTB = 0x0C;
			if (button == 1) PORTC = 0x21;
				else PORTC = 0x20;
			break;
		case 6:
			PORTB = 0x0A;
			PORTC = PORTC ^ (1<<PC5); //toggle PORTC.5
			break;
		case 7:
			PORTB = 0x09;
			if (button == 1) PORTC = 0x11;
				else PORTC = 0x10;
			break;
		case 8:
			PORTB = 0x19;
			break;
		default:
			break;
	}
}

void lab2b()
{
	OCR1A = 3124;  //3125 - 1  //1 for overflow
	TCCR1A = 0x00; //CTC mode
	TCCR1B = 0x0D; //CTC mode, Prescaler 1024
	TIMSK1 = (1<<OCIE1A); //enable Timer1 compare match int.
}


ISR (TIMER1_COMPA_vect) //ISR for Timer1 compare match
{
	OCR1A = 3124;
	lab2b_1();
}	//Timer value = 16M * 0.2 / 1024 = 3,125 (delay 0.2 sec)

ISR (INT0_vect) //ISR for external interrupt 0
{
	cnt = cnt +1;
	if (cnt == 3) {
		PORTC = PORTC ^ (1<< PC0); //toggle PORTC.0
		cnt = 0;
		button = button * -1;
	}
}