/*
 * light.c
 *
 * Created: 26-08-2024 10:22:20
 *  Author: kjeyabalan
 */ 

#include "light.h"

void light1_ON(){
	PORTD |= (1 << PD6);
	PORTF |= (1 << PF3);
	lastState.lightState_1 = 1;
	eeprom_write(light1_address, lastState.lightState_1);
}

void light1_OFF(){
	PORTD &= ~(1 << PD6);
	PORTF &= ~(1 << PF3);
	lastState.lightState_1 = 0;
	eeprom_write(light1_address, lastState.lightState_1);
}

void light2_ON(){
	PORTD |= (1 << PD5);
	PORTF |= (1 << PF4);
	lastState.lightState_2 = 1;
	eeprom_write(light2_address, lastState.lightState_2);
}

void light2_OFF(){
	PORTD &= ~(1 << PD5);
	PORTF &= ~(1 << PF4);
	lastState.lightState_2 = 0;
	eeprom_write(light2_address, lastState.lightState_2);
}

void light3_ON(){
	PORTD |= (1 << PD7);
	PORTF |= (1 << PF5);
	lastState.lightState_3 = 1;
	eeprom_write(light3_address, lastState.lightState_3);
}

void light3_OFF(){
	PORTD &= ~(1 << PD7);
	PORTF &= ~(1 << PF5);
	lastState.lightState_3 = 0;
	eeprom_write(light3_address, lastState.lightState_3);
}

void light4_ON(){
	PORTD |= (1 << PD4);
	PORTF |= (1 << PF6);
	lastState.lightState_4 = 1;
	eeprom_write(light4_address, lastState.lightState_4);
}

void light4_OFF(){
	PORTD &= ~(1 << PD4);
	PORTF &= ~(1 << PF6);
	lastState.lightState_4 = 0;
	eeprom_write(light4_address, lastState.lightState_4);
}