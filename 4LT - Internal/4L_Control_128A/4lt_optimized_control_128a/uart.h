/*
 * uart.h
 *
 * Created: 31-08-2024 11:13:31
 *  Author: kjeya
 */ 


#ifndef UART_H_
#define UART_H_

#include "main.h"
void USART_Init(unsigned int ubrr);
void USART_Transmit(uint8_t data);
unsigned char USART_Receive(void);


#endif /* UART_H_ */