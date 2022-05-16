/*
 * Lab4B.c
 *
 * Created: 10/11/2021 8:50:59
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
	UBRR0L = 207; // 4800 = 16MHz/(16*(X+1)) >> X=207
	
	char character[] = "We Are Ready!";
	char Hi[2] = "Hi";
	char Bye[4] = "Bye!";
	char temp;
	int i = -1;
	while(1)
	{
		i = i + 1;
		while ((UCSR0A & (1<<UDRE0)) == 0); //USART sent data part
		temp = character[i];
		UDR0 = temp;
		if (i==12) break;
	}
	while (1)
	{
		if (i>1) i = -1;
		i = i + 1;
		while((UCSR0A & (1<<RXC0)) == 0); //USART receive data part
		temp = UDR0;
		character[i] = temp;
		if (Hi[0] != character[0]) i = -1;
		if ((Hi[0] == character[0]) && ((Hi[1] == temp)&&(i = 1)))	
		{
			i = -1;
			while (1)
			{
				i = i + 1;
				while ((UCSR0A & (1<<UDRE0)) == 0); //USART sent data part
				temp = Bye[i];
				UDR0 = temp;
				if (i==3) break;
			}
		}
	}
	return 0;
}

