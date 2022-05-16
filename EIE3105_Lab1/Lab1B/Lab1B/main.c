/*
 * Lab1B.c
 *
 * Created: 29/9/2021 1:20:19
 * Author : Eric Kwong
 */ 

#include <avr/io.h>


int main(void)
{
	unsigned int state;
    DDRD = 0xFF;
	DDRB = 0x00;
	PORTB = 0x01;
	PORTD = 0x00;
	state = 0;
	while(1)
	{
		if (state == 0 && ((PINB & (1 << 0))))
		{
			PORTD = 0xFF;
			state = 1;
		} else
		if (state == 1 && ((PINB & (1 << 0))))
		{
			PORTD = 0x00;
			state = 0;
		}
	}
}

