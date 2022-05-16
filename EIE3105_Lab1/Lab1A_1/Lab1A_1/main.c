/*
 * Lab1A_1.c
 *
 * Created: 15/9/2021 8:56:53
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
int main(void)
{
	DDRD = 0xFF;
	while(1)
	{
		PORTD = 0x55;
	}
}

