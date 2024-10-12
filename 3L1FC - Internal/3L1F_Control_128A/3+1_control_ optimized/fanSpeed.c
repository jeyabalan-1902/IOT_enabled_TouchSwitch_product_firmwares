/*
 * fanSpeed.c
 *
 * Created: 29-08-2024 21:52:32
 *  Author: kjeyabalan
 */ 

#include "fanSpeed.h"

void as0() {

	PORTC &= ~(1 << PC2);
	
	PORTD &= ~(1 << PD4);
	PORTD &= ~(1 << PD5);
	PORTD &= ~(1 << PD6);
	PORTD &= ~(1 << PD7);
	PORTC &= ~(1 << PC0);

	PORTF &= ~(1 << PF0);
	custom_delay_ms(200);
	PORTF &= ~(1 << PF1);
	custom_delay_ms(200);
	PORTF &= ~(1 << PF2);
	custom_delay_ms(200);
	PORTF &= ~(1 << PF3);
	custom_delay_ms(200);
}

void as1() {

	PORTC |= (1 << PC2);

	PORTD |= (1 << PD4);
	PORTD &= ~(1 << PD5);
	PORTD &= ~(1 << PD6);
	PORTD &= ~(1 << PD7);
	PORTC &= ~(1 << PC0);
	//relay Pins
	PORTF &= ~ (1 << PF0);
	custom_delay_ms(200);
	PORTF |= (1 << PF1);   //2.2k
	custom_delay_ms(200);
	PORTF &= ~(1 << PF2);
	custom_delay_ms(200);
	PORTF &= ~(1 << PF3);
	custom_delay_ms(200);
}

void as2() {   // fan Speed 2

	PORTC |= (1 << PC2); //Fan on led
	
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD5);
	PORTD &= ~(1 << PD6);     // Led Pins
	PORTD &= ~(1 << PD7);
	PORTC &= ~(1 << PC0);

	PORTF |=  (1 << PF0);     //Relay Pins
	custom_delay_ms(200);
	PORTF |= (1 << PF1);
	custom_delay_ms(200);
	PORTF &= ~ (1 << PF2);     //3.3k
	custom_delay_ms(200);
	PORTF &= ~(1 << PF3);
	custom_delay_ms(200);
}

void as3() {   //Fan speed 3

	PORTC |= (1 << PC2); //fan on led
	
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD6);     // Led Pins
	PORTD &= ~(1 << PD7);
	PORTC &= ~(1 << PC0);

	PORTF |= (1 << PF0);     //Relay Pins
	custom_delay_ms(200);
	PORTF &= ~(1 << PF1);
	custom_delay_ms(200);
	PORTF |= (1 << PF2);    //4.3k
	custom_delay_ms(200);
	PORTF &= ~(1 << PF3);
	custom_delay_ms(200);
}

void as4() {     //Fan speed 4
	
	PORTC |= (1 << PC2); //fan on led
	
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD6);     // Led Pins
	PORTD |= (1 << PD7);
	PORTC &= ~(1 << PC0);

	PORTF &= ~(1 << PF0);     //Relay Pins
	custom_delay_ms(200);
	PORTF |= (1 << PF1);
	custom_delay_ms(200);
	PORTF |= (1 << PF2);      //5.5k
	custom_delay_ms(200);
	PORTF &= ~(1 << PF3);
	custom_delay_ms(200);
}

void as5() {       // fan speed 5
	
	PORTC |= (1 << PC2);  // fan on led
	
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD6);     // Led Pins
	PORTD |= (1 << PD7);
	PORTC |= (1 << PC0);
	

	PORTF &= ~(1 << PF0);     //Relay Pins
	custom_delay_ms(200);
	PORTF &= ~(1 << PF1);
	custom_delay_ms(200);
	PORTF &= ~(1 << PF2);
	custom_delay_ms(200);
	PORTF |= (1 << PF3);       //direct
	custom_delay_ms(200);
}