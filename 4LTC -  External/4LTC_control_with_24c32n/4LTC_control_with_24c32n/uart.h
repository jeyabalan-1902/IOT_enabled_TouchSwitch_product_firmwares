/*
 * uart.h
 *
 * Created: 26-08-2024 09:45:58
 *  Author: kjeyabalan 
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void USART_Init(unsigned int ubrr);
void USART_Transmit(uint8_t data);
unsigned char USART_Receive(void);

#endif /* UART_H_ */