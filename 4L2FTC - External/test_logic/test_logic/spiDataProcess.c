/*
 * spiDataProcess.c
 *
 * Created: 29-08-2024 14:55:33
 *  Author: kjeyabalan
 */ 


#include "spiDataProcess.h"

void SPI_init_slave() {
	DDRB |= (1 << DDB4);
	SPCR |= (1 << SPE);
	SPCR |= (1 << SPIE);
}

void SPIprocessCommand(const char* command){
	
	if(strcmp(command, "P1") == 0){     //Network Hard Reset
		USART_Transmit('Q');
	}
	
	/*else if(strcmp(command, "R1") == 0){
		USART_Transmit('x');             //ESP Restart
	}*/
	
	else if(strcmp(command, "L1") == 0){      // Light 1
		PORTD ^= (1 << PD7);
		PORTC ^= (1 << PC5);   
		uint8_t newLightState_1 = (lastStates_t.light1state == 0) ? 1 : 0;
		if(newLightState_1 != lastStates_t.light1state){
			lastStates_t.light1state = newLightState_1;
			eeprom_write(light1_address, lastStates_t.light1state);
			USART_Transmit(lastStates_t.light1state == 1 ? 'S' : 's'); 
		}
	}
	
	else if(strcmp(command, "L2") == 0){      //Light 2
		PORTC ^= (1 << PC3);
		PORTC ^= (1 << PC6);
		uint8_t newLightState_2 = ( lastStates_t.light2state == 0) ? 1 : 0;
		if(newLightState_2 != lastStates_t.light2state){
			lastStates_t.light2state = newLightState_2;
			eeprom_write(light2_address, lastStates_t.light2state);
			USART_Transmit(lastStates_t.light2state == 1 ? 'P' : 'p');
		}
	}
	
	else if (strcmp(command, "L3") == 0) {     //Light 3
		PORTD ^= (1 << PD6);
		PORTA ^= (1 << PA5);
		uint8_t newLightState_3 = (lastStates_t.light3state == 0) ? 1 : 0;
		if (newLightState_3 != lastStates_t.light3state){
			lastStates_t.light3state = newLightState_3;
			eeprom_write(light3_address, lastStates_t.light3state);
			USART_Transmit(lastStates_t.light3state == 1 ? 'R' : 'r');
		}
	}
	
	else if (strcmp(command, "L4") == 0) {    //Light 4
		PORTC ^= (1 << PC4);
		PORTA ^= (1 << PA4); 
		uint8_t newLightState_4 = (lastStates_t.light4state == 0) ? 1 : 0;
		if (newLightState_4 != lastStates_t.light4state){
			lastStates_t.light4state = newLightState_4;
			eeprom_write(light4_address, lastStates_t.light4state);
			USART_Transmit(lastStates_t.light4state == 1 ? 'G' : 'g');
		}
	}
	
	else if (strcmp(command, "F0") == 0) {      // Fan 1 ON
		switch(lastStates_t.lastF1state){
			case 1: as1(); USART_Transmit('A'); lastStates_t.lastF1state = 1; break;
			case 2: as2(); USART_Transmit('C'); lastStates_t.lastF1state = 2; break;
			case 3: as3(); USART_Transmit('D'); lastStates_t.lastF1state = 3; break;
			case 4: as4(); USART_Transmit('E'); lastStates_t.lastF1state = 4; break;
			case 5: as5(); USART_Transmit('F'); lastStates_t.lastF1state = 5; break;
			default:
			switch(fan1_speed){
				case 1: as1(); USART_Transmit('A'); lastStates_t.lastF1state = 1; break;
				case 2: as2(); USART_Transmit('C'); lastStates_t.lastF1state = 2; break;
				case 3: as3(); USART_Transmit('D'); lastStates_t.lastF1state = 3; break;
				case 4: as4(); USART_Transmit('E'); lastStates_t.lastF1state = 4; break;
				case 5: as5(); USART_Transmit('F'); lastStates_t.lastF1state = 5; break;
				default:as1(); USART_Transmit('A'); lastStates_t.lastF1state = 1; break;
			}
			break;
		}
		eeprom_write(fan1_address, lastStates_t.lastF1state);
	}
	else if (strcmp(command, "F1") == 0) {      //Fan 1 OFF
		USART_Transmit('B');
		as0();
		eeprom_write(fan1_address, 0);
	}
	else if (strcmp(command, "F2") == 0) {         // Fan 2 ON
		switch(lastStates_t.lastF2state){
			case 1: af1(); USART_Transmit('K'); lastStates_t.lastF2state = 1; break;
			case 2: af2(); USART_Transmit('Z'); lastStates_t.lastF2state = 2; break;
			case 3: af3(); USART_Transmit('X'); lastStates_t.lastF2state = 3; break;
			case 4: af4(); USART_Transmit('I'); lastStates_t.lastF2state = 4; break;
			case 5: af5(); USART_Transmit('J'); lastStates_t.lastF2state = 5; break;
			default:
			switch(fan2_speed){
				case 1: af1(); USART_Transmit('K'); lastStates_t.lastF2state = 1; break;
				case 2: af2(); USART_Transmit('Z'); lastStates_t.lastF2state = 2; break;
				case 3: af3(); USART_Transmit('X'); lastStates_t.lastF2state = 3; break;
				case 4: af4(); USART_Transmit('I'); lastStates_t.lastF2state = 4; break;
				case 5: af5(); USART_Transmit('J'); lastStates_t.lastF2state = 5; break;
				default: af1();USART_Transmit('K'); lastStates_t.lastF2state = 1; break;
			}
			break;
		}
		eeprom_write(fan2_address, lastStates_t.lastF2state);
	}
	
	else if (strcmp(command, "F3") == 0) {     //Fan 2 OFF
		USART_Transmit('W');
		af0();
		eeprom_write(fan2_address, 0);
	}
	
	else if (strcmp(command, "U1") == 0) {     //Fan 1 Increment
		if ((PORTC & (1 << PC2)) == 0) {
			USART_Transmit('A');
			as1();
			lastStates_t.lastF1state = 1;
		}
		else if ((PORTC & (1 << PC1)) == 0) {
			USART_Transmit('C');
			as2();
			lastStates_t.lastF1state = 2;
		}
		else if ((PORTC & (1 << PC0)) == 0) {
			USART_Transmit('D');
			as3();
			lastStates_t.lastF1state = 3;
		}
		else if ((PORTG & (1 << PG1)) == 0) {
			USART_Transmit('E');
			as4();
			lastStates_t.lastF1state = 4;
		}
		else if ((PORTG & (1 << PG0)) == 0) {
			USART_Transmit('F');
			as5();
			lastStates_t.lastF1state = 5;
		}
		eeprom_write(fan1_address, lastStates_t.lastF1state);
	}
	
	else if (strcmp(command, "U2") == 0) {        // Fan 2 Increment
		if ((PORTD & (1 << PD5)) == 0) {
			USART_Transmit('K');
			af1();
			lastStates_t.lastF2state = 1;
		}
		else if ((PORTD & (1 << PD4)) == 0) {
			USART_Transmit('Z');
			af2();
			lastStates_t.lastF2state = 2;
		}
		
		else if ((PORTD & (1 << PD3)) == 0) {
			USART_Transmit('X');
			af3();
			lastStates_t.lastF2state = 3;
		}
		else if ((PORTD & (1 << PD2)) == 0) {
			USART_Transmit('I');
			af4();
			lastStates_t.lastF2state = 4;
		}
		
		else if ((PORTG & (1 << PG4)) == 0) {
			USART_Transmit('J');
			af5();
			lastStates_t.lastF2state = 5;
		}
		eeprom_write(fan2_address, lastStates_t.lastF2state);
	}
	
	else if (strcmp(command, "D1") == 0) {    // Fan 1 Decrement
		if ((PORTG & (1 << PG0)) != 0) {
			USART_Transmit('E');
			as4();
			lastStates_t.lastF1state = 4;
		}
		else if ((PORTG & (1 << PG1)) != 0) {
			USART_Transmit('D');
			as3();
			lastStates_t.lastF1state = 3;
		}
		else if ((PORTC & (1 << PC0)) != 0) {
			USART_Transmit('C');
			as2();
			lastStates_t.lastF1state = 2;
		}
		else if ((PORTC & (1 << PC1)) != 0) {
			USART_Transmit('A');
			as1();
			lastStates_t.lastF1state = 1;
		}
		eeprom_write(fan1_address,lastStates_t.lastF1state);
	}
	
	else if (strcmp(command, "D2") == 0) {  //Fan 2 Decrement
		if ((PORTG & (1 << PG4)) != 0) {
			USART_Transmit('I');
			af4();
			lastStates_t.lastF2state = 4;
		}
		else if ((PORTD & (1 << PD2)) != 0) {
			USART_Transmit('X');
			af3();
			lastStates_t.lastF2state = 3;
		}
		else if ((PORTD & (1 << PD3)) != 0) {
			USART_Transmit('Z');
			af2();
			lastStates_t.lastF2state = 2;
		}
		else if ((PORTD & (1 << PD4)) != 0) {
			USART_Transmit('K');
			af1();
			lastStates_t.lastF2state = 1;
		}
		eeprom_write(fan2_address,lastStates_t.lastF2state);
	}
}
