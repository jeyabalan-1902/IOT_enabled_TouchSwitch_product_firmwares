/*
 * uart.h
 *
 * Created: 14-08-2024 22:41:32
 *  Author: kjeyabalan
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void USART_Init(unsigned int ubrr);
void USART_Transmit(uint8_t data);
unsigned char USART_Receive(void);



#endif /* UART_H_ */