/*
 * lights.c
 *
 * Created: 29-08-2024 22:49:39
 *  Author: kjeya
 */ 

#include "lights.h"

void light1_ON(){
	PORTC |= (1 << PC1);
	PORTF |= (1 << PF4);
	lastState.lightState_1 = 1;
}

void light1_OFF(){
	PORTC &= ~(1 << PC1);
	PORTF &= ~(1 << PF4);
	lastState.lightState_1 = 0;
}

void light2_ON(){
	PORTC |= (1 << PC3);
	PORTF |= (1 << PF5);
	lastState.lightState_2 = 1;
}
void light2_OFF(){
	PORTC &= ~(1 << PC3);
	PORTF &= ~(1 << PF5);
	lastState.lightState_2 = 0;
}

void light3_ON(){
	PORTC |= (1 << PC4);
	PORTF |= (1 << PF6);
	lastState.lightState_3 = 1;
}

void light3_OFF(){
	PORTC &= ~(1 << PC4);
	PORTF &= ~(1 << PF6);
	lastState.lightState_3 = 0;
}

