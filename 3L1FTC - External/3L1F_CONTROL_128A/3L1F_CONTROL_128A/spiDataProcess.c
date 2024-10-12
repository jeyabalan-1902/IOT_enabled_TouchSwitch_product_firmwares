/*
 * spiDataProcess.c
 *
 * Created: 27-08-2024 14:15:20
 *  Author: kjeyabalan
 */ 

#include "spiDataProcess.h"
const char* command;

void SPIprocessCommand(const char* command) {
	
	if (strcmp(command, "H1") == 0) {        //Network Reset
		USART_Transmit('G');
	}
	
	/*else if(strcmp(command, "R1") == 0){     // ESP restart
		USART_Transmit('x');
	}*/
	
	else if (strcmp(command, "L1") == 0) {
		PORTC ^= (1 << PC1);               //LIGHT 1
		PORTF ^= (1 << PF4);
		uint8_t newLightState_1 = (laststate.lightState_1 == 0) ? 1 : 0;
		if (newLightState_1 != laststate.lightState_1) {
			laststate.lightState_1 = newLightState_1;
			eeprom_write(light1_address, laststate.lightState_1);                
			USART_Transmit(laststate.lightState_1 == 1 ? 'P' : 'Q');
		}
	}

	else if (strcmp(command, "L2") == 0) {    //light 2
		PORTC ^= (1 << PC3);
		PORTF ^= (1 << PF5);
		uint8_t newLightState_2 = (laststate.lightState_2 == 0) ? 1 : 0;
		if(newLightState_2 != laststate.lightState_2){
			laststate.lightState_2 = newLightState_2;
			eeprom_write(light2_address, laststate.lightState_2);                
			USART_Transmit(laststate.lightState_2 == 1 ? 'R' : 'S');
		}
	}
	
	
	else if (strcmp(command, "L3") == 0) {  //light 3
		PORTC ^= (1 << PC4);
		PORTF ^= (1 << PF6);
		uint8_t newLightState_3 = (laststate.lightState_3 == 0) ? 1 : 0;
		if (newLightState_3 != laststate.lightState_3){
			laststate.lightState_3 = newLightState_3;
			eeprom_write(light3_address, laststate.lightState_3);                  
			USART_Transmit(laststate.lightState_3 == 1 ? 'T' : 'U');
		}
	}
	
	else if (strcmp(command, "F0") == 0) {                                  // Fan1 ON state
		switch(laststate.lastF1State){
			case 1: as1(); USART_Transmit('A'); laststate.lastF1State = 1; break;
			case 2: as2(); USART_Transmit('C'); laststate.lastF1State = 2; break;
			case 3: as3(); USART_Transmit('D'); laststate.lastF1State = 3; break;
			case 4: as4(); USART_Transmit('E'); laststate.lastF1State = 4; break;
			case 5: as5(); USART_Transmit('F'); laststate.lastF1State = 5; break;
			default: 
			switch(fan1_speed){
				case 1: as1(); USART_Transmit('A'); laststate.lastF1State = 1; break;
				case 2: as2(); USART_Transmit('C'); laststate.lastF1State = 2; break;
				case 3: as3(); USART_Transmit('D'); laststate.lastF1State = 3; break;
				case 4: as4(); USART_Transmit('E'); laststate.lastF1State = 4; break;
				case 5: as5(); USART_Transmit('F'); laststate.lastF1State = 5; break;
				default:as1(); USART_Transmit('A'); laststate.lastF1State = 1; break;
			}
			break;
		}
		eeprom_write(fan1_address, laststate.lastF1State);
	}
	
	else if (strcmp(command, "F1") == 0) {                                    // fan1 off state
		USART_Transmit('B');
		as0();
		eeprom_write(fan1_address, 0);
	}
	
	else if (strcmp(command, "U1") == 0) {                                   //fan increment
		if((PORTD & (1 << PD4)) == 0) {
			USART_Transmit('A');
			as1();
			laststate.lastF1State = 1;
		}
		else if ((PORTD & (1 << PD5)) == 0) {
			USART_Transmit('C');
			as2();
			laststate.lastF1State = 2;
		}
		else if ((PORTD & (1 << PD6)) == 0) {
			USART_Transmit('D');
			as3();
			laststate.lastF1State = 3;
		}
		else if ((PORTD & (1 << PD7)) == 0) {
			USART_Transmit('E');
			as4();
			laststate.lastF1State = 4;
		}
		else if ((PORTC & (1 << PC0)) == 0) {
			USART_Transmit('F');
			as5();
			laststate.lastF1State = 5;
		}
		eeprom_write(fan1_address, laststate.lastF1State);
	}
	
	
	else if (strcmp(command, "D1") == 0) {                               // fan1 decrement
		if ((PORTC & (1 << PC0)) != 0) {
			USART_Transmit('E');
			as4();
			laststate.lastF1State = 4;
		}
		else if ((PORTD & (1 << PD7)) != 0) {
			USART_Transmit('D');
			as3();
			laststate.lastF1State = 3;
		}
		else if ((PORTD & (1 << PD6)) != 0) {
			USART_Transmit('C');
			as2();
			laststate.lastF1State = 2;
		}
		else if ((PORTD & (1 << PD5)) != 0) {
			USART_Transmit('A');
			as1();
			laststate.lastF1State = 1;
		}
		eeprom_write(fan1_address, laststate.lastF1State);
	}
}

