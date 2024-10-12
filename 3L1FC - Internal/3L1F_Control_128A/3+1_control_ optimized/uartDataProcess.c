/*
 * uartDataProcess.c
 *
 * Created: 29-08-2024 22:20:57
 *  Author: kjeya
 */ 

#include "uartDataProcess.h"

void UARTprocessCommand(unsigned char receivedData){
	if (receivedData == 'L') {
		receivedData = USART_Receive();
		if (receivedData == '1') {	    // light1 ON
			light1_ON();
		}
		else if (receivedData == '0') {   //light1 OFF
			light1_OFF();
		}
		eeprom_write_byte((uint8_t*)EEPROM_LIGHT1_STATE_ADDR, lastState.lightState_1); // Store the Light1 state in EEPROM
	}
	
	if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {        // light2 ON
			light2_ON();
		}
		else if (receivedData == '0') {       //light2 OFF
			light2_OFF();
		}
		eeprom_write_byte((uint8_t*)EEPROM_LIGHT2_STATE_ADDR, lastState.lightState_2); // Store the Light2 state in EEPROM
	}
	
	if (receivedData == 'N') {
		
		receivedData = USART_Receive();
		if (receivedData == '1') {      //light3 ON
			light3_ON();
		}
		else if (receivedData == '0') {     //light3 OFF
			light3_OFF();
		}
		eeprom_write_byte((uint8_t*)EEPROM_LIGHT3_STATE_ADDR, lastState.lightState_3); // Store the Light state 3 in EEPROM
	}
	
	if (receivedData == 'F') {
		receivedData = USART_Receive();
		if (receivedData == '1') {     // fan1 ON
			as1();
			lastState.lastF1State = 1;
			fan_speed = 1;
			receivedData = USART_Receive();
			if (receivedData == 'U') {
				receivedData = USART_Receive();      //fan1 speed increment and decrement
				if (receivedData == '2') {
					as2();
					lastState.lastF1State = 2;
					fan_speed = 2;
				}
				else if (receivedData == '3') {
					as3();
					lastState.lastF1State = 3;
					fan_speed = 3;
				}
				else if (receivedData == '4') {
					as4();
					lastState.lastF1State = 4;
					fan_speed = 4;
				}
				else if (receivedData == '5') {
					as5();
					lastState.lastF1State = 5;
					fan_speed = 5;
				}
				eeprom_write_byte((uint8_t*)EEPROM_FAN1_STATE_ADDR, lastState.lastF1State);
			}
		}
		
		else if (receivedData == '0') {     // fan1 OFF
			as0();
			lastState.lastF1State = 0;
		}
		eeprom_write_byte((uint8_t*)EEPROM_FAN1_STATE_ADDR, lastState.lastF1State);
	}

	if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			handle_All_ON();
			eeprom_write_byte((uint8_t*)EEPROM_LIGHT1_STATE_ADDR, lastState.lightState_1);
			eeprom_write_byte((uint8_t*)EEPROM_LIGHT2_STATE_ADDR, lastState.lightState_2);
			eeprom_write_byte((uint8_t*)EEPROM_LIGHT3_STATE_ADDR, lastState.lightState_3);
			eeprom_write_byte((uint8_t*)EEPROM_FAN1_STATE_ADDR, lastState.lastF1State);
		}
		else if(receivedData == '0'){
			handle_All_OFF();
			eeprom_write_byte((uint8_t*)EEPROM_LIGHT1_STATE_ADDR, lastState.lightState_1);
			eeprom_write_byte((uint8_t*)EEPROM_LIGHT2_STATE_ADDR, lastState.lightState_2);
			eeprom_write_byte((uint8_t*)EEPROM_LIGHT3_STATE_ADDR, lastState.lightState_3);
			eeprom_write_byte((uint8_t*)EEPROM_FAN1_STATE_ADDR, 0);
		}
	}
}