/*
 * Lab4D_1.c
 *
 * Created: 14/11/2021 2:21:54
 * Author : Eric Kwong
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

char character[13] = "We Are Ready!";
char Hi[2] = "Hi";
char Bye[4] = "Bye!";
char temp;
int i = -1;
int k = 0;
int state = 0;

ISR(USART_UDRE_vect)
{
	if (state == 0)
	{
		i = i + 1;
		UDR0 = character[i];
		if (i == 12)
		{
			state = 1;
			i = -1;
		}
	}
	if (state == 2)
	{
		UDR0 = Bye[k];
		k = k + 1;
		if (k==4)
		{
			state = 1;
			k = 0;
		}
	}
}

ISR(USART_RX_vect)
{
	if (state == 1)
	{
		if (i>1) {i = -1;}
		i = i + 1;
		temp = UDR0;
		character[i] = temp;
		if (Hi[0] != character[0]) {i = -1;}
		if ((Hi[0] == character[0]) && ((Hi[1] == temp)&&(i = 1)))
		{
			i = -1;
			state = 2;
		}
	}
}


int main(void)
{
	UCSR0A = (0<<FE0) | (0<<DOR0) | (0<<UPE0);
	UCSR0B = (1<<RXEN0) | (1<<RXCIE0) | (1<<TXEN0) | (1<<UDRIE0); //enable USART receiver and transmitter
	UCSR0C = (0<<UPM01) | (0<<UPM00); //Parity: None
	UCSR0C = (0<<USBS0); //Stop bit: 0
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01) | (1<<UMSEL01); //Data: 8 bits
	UBRR0L = 207; // 4800 = 16MHz/(16*(X+1)) >> X=207
	
	sei();
	while(1){}
}





/*		i = i + 1;
UDR0 = character[i];
if (i == 12)
{
	state = 1;
	i = -1;
}
*/


