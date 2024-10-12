/*
 * main.h
 *
 * Created: 13-09-2024 16:43:17
 *  Author: kjeya
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL            //  CPU frequency
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <string.h>
#include <util/delay.h>
#include <util/twi.h>
#include "i2c.h"
#include "eeprom.h"
#include "SPIdataProcess.h"
#include "UARTdataProcess.h"
#include "uart.h"
#include "light.h"

#define EEPROM_ADDR 0x50

#define POLYNOMIAL 0x07  // CRC polynomial
#define INIT_CRC 0x00

#define FOSC 16000000                       // UART
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

typedef struct{
	uint8_t lightState_1;
	uint8_t lightState_2;
	uint8_t lightState_3;
	uint8_t lightState_4;
	uint8_t lightState_5;
	uint8_t lightState_6;
}states;

extern volatile states lastState;
//extern const char* command;
extern volatile uint8_t timer_flag;
extern uint16_t light1_address;
extern uint16_t light2_address;
extern uint16_t light3_address;
extern uint16_t light4_address;
extern uint16_t light5_address;
extern uint16_t light6_address;

void timer1_init();
void custom_delay_ms(uint16_t ms);
void SPI_init_slave();
void setup(void);
void retainLightStates(void);
void readStatesFromEEPROM(void);
void write_all_States_ToEEPROM();


#endif /* MAIN_H_ */