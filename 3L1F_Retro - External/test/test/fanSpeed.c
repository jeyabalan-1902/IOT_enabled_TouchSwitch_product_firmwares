/*
 * fanSpeed.c
 *
 * Created: 19-08-2024 10:32:03
 *  Author: kjeyabalan
 */ 

#include "main.h"
#include "fanSpeed.h"

void fanSpeed0(){
	PORTE &= ~(1 << PE3);
	PORTE &= ~(1 << PE2);
	PORTD &= ~(1 << PD7);
	PORTD &= ~(1 << PD6);
}

void fanSpeed1(){
	PORTE &= ~(1 << PE3);
	PORTE |= (1 << PE2);
	PORTD &= ~(1 << PD7);
	PORTD &= ~(1 << PD6);
}

void fanSpeed2(){
	PORTE |= (1 << PE3);
	PORTE &= ~(1 << PE2);
	PORTD |= (1 << PD7);
	PORTD &= ~(1 << PD6);
}

void fanSpeed3(){
	PORTE |= (1 << PE3);
	PORTE |= (1 << PE2);
	PORTD &= ~(1 << PD7);
	PORTD &= ~(1 << PD6);
}

void fanSpeed4(){
	PORTE &= ~(1 << PE3);
	PORTE |= (1 << PE2);
	PORTD |= (1 << PD7);
	PORTD &= ~(1 << PD6);
}

void fanSpeed5(){
	PORTE &= ~(1 << PE3);
	PORTE &= ~(1 << PE2);
	PORTD &= ~(1 << PD7);
	PORTD |= (1 << PD6);
}