/*
 * lights.c
 *
 * Created: 16-08-2024 11:04:03
 *  Author: kjeyabalan
 */ 

#include "main.h"
#include "lights.h"

void light1_ON(){
	PORTD |= (1 << PD7);
	PORTC |= (1 << PC5);
	lastStates_t.light1state = 1;
}
  
void light1_OFF(){
	PORTD &= ~(1 << PD7);
	PORTC &= ~(1 << PC5);
	lastStates_t.light1state = 0;
}

void light2_ON(){
	PORTC |= (1 << PC3);
	PORTC |= (1 << PC6);
	lastStates_t.light2state = 1;
}

void light2_OFF(){
	PORTC &= ~(1 << PC3);
	PORTC &= ~(1 << PC6);
	lastStates_t.light2state = 0;
}

void light3_ON(){
	PORTD |= (1 << PD6);
	PORTA |= (1 << PA5);
	lastStates_t.light3state = 1;
}

void light3_OFF(){
	PORTD &= ~(1 << PD6);
	PORTA &= ~(1 << PA5);
	lastStates_t.light3state = 0;
}

void light4_ON(){
	PORTC |= (1 << PC4);
	PORTA |= (1 << PA4);
	lastStates_t.light4state = 1;
}

void light4_OFF(){
	PORTC &= ~(1 << PC4);
	PORTA &= ~(1 << PA4);
	lastStates_t.light4state = 0;
}
