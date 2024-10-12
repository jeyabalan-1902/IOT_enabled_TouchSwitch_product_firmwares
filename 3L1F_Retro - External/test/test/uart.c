/*
 * uart.c
 *
 * Created: 19-08-2024 09:57:02
 *  Author: kjeyabalan
 */ 

#include <avr/io.h>
#include "uart.h"
#include "main.h"

void USART_Transmit( unsigned char data )
{
	while ( !( UCSR0A & (1<<UDRE)) );
	UDR0 = data;
}
void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);  // Enable receiver and transmitter
	UCSR0C = (1 << UCSZ1) | (1 << UCSZ0);               // 8-bit data, 1 stop bit
}


unsigned char USART_Receive( void )
{
	while ( !(UCSR0A & (1<<RXC)) );
	return UDR0;
}