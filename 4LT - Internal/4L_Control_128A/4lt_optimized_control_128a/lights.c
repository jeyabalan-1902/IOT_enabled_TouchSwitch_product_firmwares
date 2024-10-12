/*
 * lights.c
 *
 * Created: 31-08-2024 11:02:50
 *  Author: kjeya
 */ 


#include "lights.h"

void light1_ON(){
	PORTD |= (1 << PD6);
	PORTF |= (1 << PF3);
	lastState.lightState_1 = 1;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT1_STATE_ADDR, lastState.lightState_1);
}

void light1_OFF(){
	PORTD &= ~(1 << PD6);
	PORTF &= ~(1 << PF3);
	lastState.lightState_1 = 0;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT1_STATE_ADDR, lastState.lightState_1);
}

void light2_ON(){
	PORTD |= (1 << PD5);
	PORTF |= (1 << PF4);
	lastState.lightState_2 = 1;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT2_STATE_ADDR, lastState.lightState_2);
}

void light2_OFF(){
	PORTD &= ~(1 << PD5);
	PORTF &= ~(1 << PF4);
	lastState.lightState_2 = 0;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT2_STATE_ADDR, lastState.lightState_2);
}

void light3_ON(){
	PORTD |= (1 << PD7);
	PORTF |= (1 << PF5);
	lastState.lightState_3 = 1;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT3_STATE_ADDR, lastState.lightState_3);
}

void light3_OFF(){
	PORTD &= ~(1 << PD7);
	PORTF &= ~(1 << PF5);
	lastState.lightState_3 = 0;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT3_STATE_ADDR, lastState.lightState_3);
}

void light4_ON(){
	PORTD |= (1 << PD4);
	PORTF |= (1 << PF6);
	lastState.lightState_4 = 1;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT4_STATE_ADDR, lastState.lightState_4);
}

void light4_OFF(){
	PORTD &= ~(1 << PD4);
	PORTF &= ~(1 << PF6);
	lastState.lightState_4 = 0;
	eeprom_write_byte((uint8_t*)EEPROM_LIGHT4_STATE_ADDR, lastState.lightState_4);
}