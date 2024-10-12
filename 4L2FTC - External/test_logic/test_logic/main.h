/*
 * main.h
 *
 * Created: 14-08-2024 22:04:25
 *  Author: kjeyabalan
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <string.h>
#include "fans_control.h"
#include "lights.h"
#include "eeprom.h"
#include "i2c.h"
#include "uart.h"
#include "spiDataProcess.h"
#include "uartDataProcess.h"

// USART configuration
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define EEPROM_ADDR 0x50 // EEPROM address
#define POLYNOMIAL 0x07  // CRC polynomial
#define INIT_CRC 0x00

typedef struct
{
	uint8_t light1state;
	uint8_t light2state;
	uint8_t light3state;
	uint8_t light4state;
	uint8_t lastF1state;
	uint8_t lastF2state;
} states_t;

extern volatile states_t lastStates_t;
extern volatile uint8_t timer_flag;
extern const char* command;
extern uint8_t fan1_speed;
extern uint8_t fan2_speed;

extern uint16_t light1_address;
extern uint16_t light2_address; 
extern uint16_t light3_address;
extern uint16_t light4_address;
extern uint16_t fan1_address;
extern uint16_t fan2_address;

// Function prototypes
void timer1_init(void);
void custom_delay_ms(uint16_t ms);
void SPI_init_slave(void);
void processCommand(const char* command);
void readLastStatesFromEEPROM(void);
void clearEEPROM(void);
void retain_Lights_State_From_EEPROM(void);
void retain_Fan1_State_From_EEPROM();
void retain_Fan2_State_From_EEPROM();
void setup();
void handle_Light(uint8_t light, uint8_t state);
void handle_Fan(uint8_t fan, uint8_t speed);
void handle_Fan_Speed_Control(uint8_t fan);
void handle_All_ON();
void handle_All_OFF();
void handle_SPI_interrupt(void);
void handle_UART_interrupt(void);
void init_watchdog_timer(void);
void handle_watchdog_event();
void handle_TIMER_interrupt();
void write_All_States_ToEEPROM();

#endif /* MAIN_H_ */