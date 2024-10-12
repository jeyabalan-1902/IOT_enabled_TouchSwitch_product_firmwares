/*
 * uart.h
 *
 * Created: 19-08-2024 09:56:06
 *  Author: kjeyabalan
 */ 


#ifndef UART_H_
#define UART_H_

unsigned char USART_Receive( void );
void USART_Init(unsigned int ubrr);
void USART_Transmit( unsigned char data );

#endif /* UART_H_ */