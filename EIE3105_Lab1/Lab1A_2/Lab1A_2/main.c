/*
 * Lab1A_2.c
 *
 * Created: 9/15/2021 10:35:11 AM
 * Author : 19030979D
 */ 

#include <avr/io.h>

int main(void) 
{
  unsigned int i,j;
  DDRD = 0xFF;
  while(1)
  {
	for (i = 0; i < 2000; i++){
		for (j = 0; j < 2000; j++){}};
	PORTD = 0x55;

	for (i = 0; i < 2000; i++){
		for (j = 0; j < 2000; j++){}};
	PORTD = 0xAA;
  }
}



