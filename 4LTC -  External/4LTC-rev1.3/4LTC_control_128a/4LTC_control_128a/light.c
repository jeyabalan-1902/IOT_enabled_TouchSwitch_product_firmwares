/*
 * light.c
 *
 * Created: 18-09-2024 21:06:52
 *  Author: kjeya
 */ 


#include "light.h"

void light1_ON(){
	PORTD |= (1 << PD6);
	PORTF |= (1 << PF3);
	lastState.lightState_1 = 1;
}

void light1_OFF(){
	PORTD &= ~(1 << PD6);
	PORTF &= ~(1 << PF3);
	lastState.lightState_1 = 0;
}

void light2_ON(){
	PORTD |= (1 << PD5);
	PORTF |= (1 << PF4);
	lastState.lightState_2 = 1;
}

void light2_OFF(){
	PORTD &= ~(1 << PD5);
	PORTF &= ~(1 << PF4);
	lastState.lightState_2 = 0;
}

void light3_ON(){
	PORTD |= (1 << PD7);
	PORTF |= (1 << PF5);
	lastState.lightState_3 = 1;
}

void light3_OFF(){
	PORTD &= ~(1 << PD7);
	PORTF &= ~(1 << PF5);
	lastState.lightState_3 = 0;
}

void light4_ON(){
	PORTD |= (1 << PD4);
	PORTF |= (1 << PF6);
	lastState.lightState_4 = 1;
}

void light4_OFF(){
	PORTD &= ~(1 << PD4);
	PORTF &= ~(1 << PF6);
	lastState.lightState_4 = 0;
}

void Total_ON(){
	light1_ON();
	light2_ON();
	light3_ON();
	light4_ON();
}

void Total_OFF(){
	light1_OFF();
	light2_OFF();
	light3_OFF();
	light4_OFF();
}