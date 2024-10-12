/*
 * main.h
 *
 * Created: 16-08-2024 14:00:18
 *  Author: kjeyabalan
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "i2c.h"
#include "eeprom.h"
#include "uart.h"
#include "fanSpeed.h"
#include "uartDataProcess.h"

// USART configuration
#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define EEPROM_ADDR 0x50

typedef struct{
	uint8_t switch1Status;
	uint8_t switch2Status;
	uint8_t switch3status;
	uint8_t fanSwitchStatus;
}states;

extern volatile states laststate;
extern volatile uint8_t timer_flag;
extern uint16_t light1_address;
extern uint16_t light2_address;
extern uint16_t light3_address;
extern uint16_t fan1_address;
extern bool startup_Flag;
extern volatile uint8_t fan_speed;

uint8_t EXTERNAL_IRQ_0_init();
void setup();
void custom_delay_ms(uint16_t ms);
void clearEEPROM(void);
void readLastStatesFromEEPROM(void);
void retain_Lights_State_From_EEPROM(void);
void retain_Fan_State_From_EEPROM(void);
void turnAll_ON();
void turnAll_OFF();

#endif /* MAIN_H_ */