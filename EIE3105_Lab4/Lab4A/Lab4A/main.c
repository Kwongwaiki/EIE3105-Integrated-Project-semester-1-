/*
 * Lab4A.c
 *
 * Created: 10/11/2021 3:24:59
 * Author : Eric Kwong
 */ 

#include <avr/io.h>

int main(void)
{
	UCSR0A = (0<<FE0) | (0<<DOR0) | (0<<UPE0);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0); //enable USART receiver and transmitter
	UCSR0C = (0<<UPM01) | (0<<UPM00); //Parity: None
	UCSR0C = (0<<USBS0); //Stop bit: 0
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01); //Data: 8 bits
	UCSR0C = (1<<UMSEL01); //Register select: UBRRH
	UBRR0L = 207; // 4800 = 16MHz/(16*(X+1)) >> X=207
	UBRR0H = 0;
	
	unsigned char character;	
	while(1)
	{	
		while((UCSR0A & (1<<RXC0)) == 0); //USART receive data part
		character = UDR0;
		while ((UCSR0A & (1<<UDRE0)) == 0); //USART sent data part
		UDR0 = character;
	}
	return 0;
}

