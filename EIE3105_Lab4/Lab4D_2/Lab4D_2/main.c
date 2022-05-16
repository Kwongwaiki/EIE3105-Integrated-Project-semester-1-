/*
 * Lab4D_2.c
 *
 * Created: 17/11/2021 1:14:56
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

char ch[1] = "a";
char temp;
char temp2;
int i = 0;
int state = 0;

ISR(USART_UDRE_vect)
{
	if (state == 0) UDR0 =  ch[0];
	if ((state == 1) && (i < 10))
	{
		i++;
		UDR0 = temp;
	}
	if (i == 10) 
	{
		i = 0;
		state = 2;
	}
}

ISR(USART_RX_vect)
{
	if ((i == 0) && (state != 2))
	{
		temp = UDR0;
		state = 1;	
	}
	if ((state == 2) && (UDR0 == temp))
	{
		temp = UDR0;
		state = 0;
	}
}

int main(void)
{
	UCSR0A = (0<<FE0) | (0<<DOR0) | (0<<UPE0);
	UCSR0B = (1<<RXEN0) | (1<<RXCIE0) | (1<<TXEN0) | (1<<UDRIE0); //enable USART receiver and transmitter
	UCSR0C = (0<<UPM01) | (0<<UPM00); //Parity: None
	UCSR0C = (0<<USBS0); //Stop bit: 0
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01) | (1<<UMSEL01); //Data: 8 bits
	UBRR0L = 103; // 9600 = 16MHz/(16*(X+1)) >> X=103

	sei();
	while(1){}
}

