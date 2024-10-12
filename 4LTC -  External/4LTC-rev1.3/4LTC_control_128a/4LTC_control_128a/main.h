/*
 * main.h
 *
 * Created: 18-09-2024 21:08:04
 *  Author: kjeya
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 16000000UL            //  CPU frequency
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <util/twi.h>
#include "i2c.h"
#include "eeprom.h"
#include "uart.h"
#include "light.h"
#include "spiDataProcess.h"
#include "uartDataProcess.h"

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
}states;

extern volatile states lastState;
extern uint16_t light1_address;
extern uint16_t light2_address;
extern uint16_t light3_address;
extern uint16_t light4_address;

void timer1_init();
void custom_delay_ms(uint16_t ms);
void SPI_init_slave();
void setup(void);
void readStatesFromEEPROM(void);
void retainLightStates(void);
void init_External_Interrupt(void);
void writeStatesToEEPROM(void);
void handle_External_interrupt(void);
void handle_SPI_interrupt(void);
void handle_UART_interrupt(void);
void init_watchdog_timer(void);
void handle_watchdog_event();





#endif /* MAIN_H_ */