/*
 * main.h
 *
 * Created: 29-08-2024 21:27:59
 *  Author: kjeya
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL  //CPU frequency
#include <avr/io.h>       
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>   
#include <avr/eeprom.h>
#include "fanSpeed.h"   
#include "uart.h"
#include "spiDataProcess.h"
#include "uartDataProcess.h"
#include "lights.h"

#define POLYNOMIAL 0x07  // CRC polynomial
#define INIT_CRC 0x00
// USART configuration
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#define EEPROM_LIGHT1_STATE_ADDR 0x00
#define EEPROM_LIGHT2_STATE_ADDR 0x01
#define EEPROM_LIGHT3_STATE_ADDR 0x02
#define EEPROM_FAN1_STATE_ADDR 0x03   

typedef struct{
	uint8_t lightState_1;
	uint8_t lightState_2;
	uint8_t lightState_3;
	uint8_t lastF1State;
}state;

extern volatile state lastState;
extern const char* command;
extern volatile uint8_t timer_flag;
extern uint8_t fan_speed;

void USART_Init(unsigned int ubrr);
void USART_Transmit(uint8_t data);
unsigned char USART_Receive(void);
void timer1_init();
void custom_delay_ms(uint16_t ms);
void SPI_init_slave();
void setup();
void readLastStatesFromEEPROM();
void retainLightStates();
void retainFanState();
void clearEEPROM();
uint8_t calculateCRC(uint8_t *data, size_t length);
void handle_All_OFF();
void handle_All_ON();


#endif /* MAIN_H_ */