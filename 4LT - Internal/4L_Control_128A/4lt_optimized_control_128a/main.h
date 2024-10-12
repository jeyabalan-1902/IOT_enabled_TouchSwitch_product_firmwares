/*
 * main.h
 *
 * Created: 31-08-2024 10:50:22
 *  Author: kjeya
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL            //  CPU frequency
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <util/twi.h>
#include "uart.h"
#include "lights.h"
#include "spiDataProcess.h"
#include "uartDataProcess.h"


#define POLYNOMIAL 0x07  // CRC polynomial
#define INIT_CRC 0x00

#define EEPROM_LIGHT1_STATE_ADDR 0x00       //EEPROM Address
#define EEPROM_LIGHT2_STATE_ADDR 0x01
#define EEPROM_LIGHT3_STATE_ADDR 0x02
#define EEPROM_LIGHT4_STATE_ADDR 0x03

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
extern volatile uint8_t timer_flag;
void timer1_init();
void custom_delay_ms(uint16_t ms);
void SPI_init_slave();
void setup(void);
void readStatesFromEEPROM(void);
void retainLightStates(void);
void clearEEPROM(void);



#endif /* MAIN_H_ */