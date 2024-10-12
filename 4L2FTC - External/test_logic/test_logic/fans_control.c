/*
 * fans_control.c
 *
 * Created: 14-08-2024 22:12:30
 *  Author: kjeyabalan
 */ 

#include "main.h"
#include "fans_control.h"

void as0() {                     // Fan1 Speed 0
	PORTC &= ~(1 << PC2);
	PORTC &= ~(1 << PC1);
	PORTC &= ~(1 << PC0);     // Led Pins
	PORTG &= ~(1 << PG1);
	PORTG &= ~(1 << PG0);

	PORTC &= ~(1 << PC7);     //Relay Pins
	custom_delay_ms(200);
	PORTG &= ~(1 << PG2);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA7);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA6);
	custom_delay_ms(200);
}

void as1() {
	PORTC |= (1 << PC2);
	
	PORTC &= ~(1 << PC1);
	PORTC &= ~(1 << PC0);     // Led Pins FAN1 Speed1
	PORTG &= ~(1 << PG1);
	PORTG &= ~(1 << PG0);
	
	PORTC &= ~(1 << PC7);
	custom_delay_ms(200);
	PORTG &=~ (1 << PG2);
	custom_delay_ms(200);
	PORTA |= (1 << PA7);      //2.2K
	custom_delay_ms(200);
	PORTA &= ~(1 << PA6);
	custom_delay_ms(200);
	
}

void as2() {
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC1);

	PORTC &= ~(1 << PC0);     // Led Pins FAN1 Speed2
	PORTG &= ~(1 << PG1);
	PORTG &= ~(1 << PG0);

	PORTC &= ~(1 << PC7);
	custom_delay_ms(200);
	PORTG &= ~(1 << PG2);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA7);
	custom_delay_ms(200);
	PORTA |= (1 << PA6);    //3.3k
	custom_delay_ms(200);
}

void as3() {
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC1);
	PORTC |= (1 << PC0);    // Fan1  Speed 3
	
	PORTG &= ~(1 << PG1);
	PORTG &= ~(1 << PG0);

	PORTC &= ~(1 << PC7);
	custom_delay_ms(200);
	PORTG |= (1 << PG2);      // 4.3K
	custom_delay_ms(200);
	PORTA &= ~(1 << PA7);
	custom_delay_ms(200);
	
	PORTA |= (1 << PA6);
	custom_delay_ms(200);
}

void as4() {
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC1);
	PORTC |= (1 << PC0);    // Fan1  Speed 4
	PORTG |= (1 << PG1);

	PORTG &= ~(1 << PG0);

	PORTC &= ~(1 << PC7);
	custom_delay_ms(200);
	PORTG &= ~(1 << PG2);
	custom_delay_ms(200);
	PORTA |= (1 << PA7);   //5.5K
	custom_delay_ms(200);
	PORTA |= (1 << PA6);
	custom_delay_ms(200);
}

void as5() {
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC1);
	PORTC |= (1 << PC0);    // Fan1  Speed 5
	PORTG |= (1 << PG1);
	PORTG |= (1 << PG0);


	PORTC |= (1 << PC7);     //Direct
	custom_delay_ms(200);
	PORTG &= ~(1 << PG2);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA7);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA6);
	custom_delay_ms(200);
	
}

//fan2 speed function

void af0() {
	PORTD &=~ (1 << PD5);
	PORTD &= ~(1 << PD4);
	PORTD &= ~(1 << PD3);    /// Fan2  Speed 0
	PORTD &= ~(1 << PD2);
	PORTG &= ~(1 << PG4);

	PORTA &=~ (1 << PA3);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA2);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA1);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA0);
	custom_delay_ms(200);
}

void af1() {
	PORTD |= (1 << PD5);

	PORTD &= ~(1 << PD4);
	PORTD &= ~(1 << PD3);    /// Fan2  Speed 1
	PORTD &= ~(1 << PD2);
	PORTG &= ~(1 << PG4);
	
	PORTA &=~ (1 << PA3);
	custom_delay_ms(200);
	PORTA &=~ (1 << PA2);
	custom_delay_ms(200);
	PORTA |= (1 << PA1);    //2.2K
	custom_delay_ms(200);
	PORTA &= ~(1 << PA0);
	custom_delay_ms(200);
}

void af2() {
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD4);    // Fan2  Speed 2
	
	PORTD &= ~(1 << PD3);
	PORTD &= ~(1 << PD2);
	PORTG &= ~(1 << PG4);
	
	PORTA &= ~(1 << PA3);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA2);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA1);
	custom_delay_ms(200);
	PORTA |= (1 << PA0);   //3.3K
	custom_delay_ms(200);
}

void af3() {
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD3);      // Fan2  Speed 3
	
	PORTD &= ~(1 << PD2);
	PORTG &= ~(1 << PG4);

	PORTA &= ~(1 << PA3);
	custom_delay_ms(200);
	PORTA |= (1 << PA2);  //1K+3.3K = 4.3K
	custom_delay_ms(200);
	PORTA &= ~(1 << PA1);
	custom_delay_ms(200);
	PORTA |= (1 << PA0);
	custom_delay_ms(200);
}

void af4() {
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD3);      // Fan2  Speed 4
	PORTD |= (1 << PD2);

	PORTG &= ~(1 << PG4);
	
	PORTA &=~ (1 << PA3);
	custom_delay_ms(200);
	PORTA &=~ (1 << PA2);
	custom_delay_ms(200);
	PORTA |= (1 << PA1);  //2.2K +3.3K = 5.5K
	custom_delay_ms(200);
	PORTA |= (1 << PA0);
	custom_delay_ms(200);
}

void af5() {
	PORTD |= (1 << PD5);
	PORTD |= (1 << PD4);
	PORTD |= (1 << PD3);      // Fan2  Speed 5
	PORTD |= (1 << PD2);
	PORTG |= (1 << PG4);

	PORTA |= (1 << PA3);
	custom_delay_ms(200);     //Direct
	PORTA &= ~(1 << PA2);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA1);
	custom_delay_ms(200);
	PORTA &= ~(1 << PA0);
	custom_delay_ms(200);
}