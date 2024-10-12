/*
 * light.c
 *
 * Created: 14-09-2024 12:44:00
 *  Author: kjeyabalan
 */ 

#include "light.h"

void light1_ON(){
	PORTD |= (1 << PD6);
	PORTF |= (1 << PF1);
	lastState.lightState_1 = 1;
}

void light1_OFF(){
	PORTD &= ~(1 << PD6);
	PORTF &= ~(1 << PF1);
	lastState.lightState_1 = 0;
}

void light2_ON(){
	PORTD |= (1 << PD5);
	PORTF |= (1 << PF2);
	lastState.lightState_2 = 1;
}

void light2_OFF(){
	PORTD &= ~(1 << PD5);
	PORTF &= ~(1 << PF2);
	lastState.lightState_2 = 0;
}

void light3_ON(){
	PORTD |= (1 << PD7);
	PORTF |= (1 << PF3);
	lastState.lightState_3 = 1;
}

void light3_OFF(){
	PORTD &= ~(1 << PD7);
	PORTF &= ~(1 << PF3);
	lastState.lightState_3 = 0;
}

void light4_ON(){
	PORTD |= (1 << PD4);
	PORTF |= (1 << PF4);
	lastState.lightState_4 = 1;
}

void light4_OFF(){
	PORTD &= ~(1 << PD4);
	PORTF &= ~(1 << PF4);
	lastState.lightState_4 = 0;
}

void light5_ON(){
	PORTD |= (1 << PD3);
	PORTF |= (1 << PF5);
	lastState.lightState_5 = 1;
}

void light5_OFF(){
	PORTD &= ~(1 << PD3);
	PORTF &= ~(1 << PF5);
	lastState.lightState_5 = 0;
}

void light6_ON(){
	PORTD |= (1 << PD2);
	PORTF |= (1 << PF6);
	lastState.lightState_6 = 1;
}

void light6_OFF(){
	PORTD &= ~(1 << PD2);
	PORTF &= ~(1 << PF6);
	lastState.lightState_6 = 0;
}

void Total_ON(){
	light1_ON();
	light2_ON();
	light3_ON();
	light4_ON();
	light5_ON();
	light6_ON();
}

void Total_OFF(){
	light1_OFF();
	light2_OFF();
	light3_OFF();
	light4_OFF();
	light5_OFF();
	light6_OFF();
}