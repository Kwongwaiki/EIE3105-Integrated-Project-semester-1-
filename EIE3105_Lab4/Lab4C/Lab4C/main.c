/*
 * Lab4C.c
 *
 * Created: 10/11/2021 9:52:31
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
	UBRR0L = 103; // 9600 = 16MHz/(16*(X+1)) >> X=103
	
	char ch[1] = "a";
	char temp;
	while(1)
	{
		while ((UCSR0A & (1<<UDRE0)) == 0); //USART sent data part
		UDR0 = ch[0];
		if ((UCSR0A & (1<<RXC0)) != 0)
		{
			temp = UDR0;
			for (int i = 0 ; i < 10 ; i++)
			{
				while ((UCSR0A & (1<<UDRE0)) == 0); //USART sent data part
				UDR0 = temp;
			}
			while (1)
			{
				while ((UCSR0A & (1<<RXC0)) == 0);
				if (UDR0 == temp) break;
			}
		}
	}
}