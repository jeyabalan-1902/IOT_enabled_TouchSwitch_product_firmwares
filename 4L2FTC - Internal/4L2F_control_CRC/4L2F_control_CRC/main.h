/*
 * main.h
 *
 * Created: 31-08-2024 13:53:34
 *  Author: kjeya
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <string.h>
#include "fans_control.h"
#include "lights.h"
#include "uart.h"
#include "spiDataProcess.h"
#include "uartDataProcess.h"

// uSart configuration
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

#define POLYNOMIAL 0x07  // CRC polynomial
#define INIT_CRC 0x00

//EEPROM address definition
#define light1_State_Address 0x00
#define light2_State_Address 0x01
#define light3_State_Address 0x02
#define light4_state_Address 0x03
#define fan1_State_Address 0x04
#define fan2_State_Address 0x05

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



#endif /* MAIN_H_ */