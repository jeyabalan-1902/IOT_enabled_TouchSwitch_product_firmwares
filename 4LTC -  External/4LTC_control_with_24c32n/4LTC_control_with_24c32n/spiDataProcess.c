/*
 * spiDataProcess.c
 *
 * Created: 26-08-2024 13:04:22
 *  Author: kjeyabalan
 */ 

#include "spiDataProcess.h"

void SPIprocessCommand(const char* command) {                                         //SPI Received Data
	if (strcmp(command, "L1") == 0) {
		PORTD ^= (1 << PD6);
		PORTF ^= (1 << PF3);
		uint8_t newLightState_1 = (lastState.lightState_1 == 0) ? 1 : 0;
		if (newLightState_1 != lastState.lightState_1) {
			lastState.lightState_1 = newLightState_1;
			eeprom_write(light1_address, lastState.lightState_1);                 // Store the Light state 1 in EEPROM
			USART_Transmit(lastState.lightState_1 == 1 ? 'A' : 'B');
		}
	}
	/*else if(strcmp(command, "R1") == 0){                                        // ESP restart
		USART_Transmit('x');
	}*/
	else if (strcmp(command, "H1") == 0) {                                            //network hard reset
		USART_Transmit('R');
	}
	else if (strcmp(command, "L2") == 0) {
		PORTD ^= (1 << PD5);
		PORTF ^= (1 << PF4);
		uint8_t newLightState_2 = (lastState.lightState_2 == 0) ? 1 : 0;
		if(newLightState_2 != lastState.lightState_2){
			lastState.lightState_2 = newLightState_2;
			eeprom_write(light2_address, lastState.lightState_2);                 // Store the Light state 2 in EEPROM
			USART_Transmit(lastState.lightState_2 == 1 ? 'C' : 'D');
		}
	}
	else if (strcmp(command, "L3") == 0) {
		PORTD ^= (1 << PD7);
		PORTF ^= (1 << PF5);
		uint8_t newLightState_3 = (lastState.lightState_3 == 0) ? 1 : 0;
		if (newLightState_3 != lastState.lightState_3){
			lastState.lightState_3 = newLightState_3;
			eeprom_write(light3_address, lastState.lightState_3);                  //Store the Light state 3 in EEPROM
			USART_Transmit(lastState.lightState_3 == 1 ? 'E' : 'F');
		}
	}
	else if (strcmp(command, "L4") == 0) {
		PORTD ^= (1 << PD4);
		PORTF ^= (1 << PF6);
		uint8_t newLightState_4 = (lastState.lightState_4 == 0) ? 1 : 0;
		if(newLightState_4 != lastState.lightState_4){
			lastState.lightState_4 = newLightState_4;
			eeprom_write(light4_address, lastState.lightState_4);                  // Store the Light state 4 in EEPROM
			USART_Transmit(lastState.lightState_4 == 1 ? 'G' : 'H');
		}
	}
}