/*
 * UARTdataProcess.c
 *
 * Created: 14-09-2024 12:35:45
 *  Author: kjeya
 */ 

#include "UARTdataProcess.h"

void uartProcessCommand(unsigned char receivedData){
	if (receivedData == 'L') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light1_ON();
		} else if (receivedData == '0') {
			light1_OFF();
		}
		eeprom_write(light1_address, lastState.lightState_1);
	}
	else if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light2_ON();
		} else if (receivedData == '0') {
			light2_OFF();
		}
		eeprom_write(light2_address, lastState.lightState_2);
	}
	else if (receivedData == 'N') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light3_ON();
		} else if (receivedData == '0') {
			light3_OFF();
		}
		eeprom_write(light3_address, lastState.lightState_3);
	}
	else if (receivedData == 'O') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light4_ON();
		} else if (receivedData == '0') {
			light4_OFF();
		}
		eeprom_write(light4_address, lastState.lightState_4);
	}
	else if (receivedData == 'P') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light5_ON();
		} else if (receivedData == '0') {
			light5_OFF();
		}
		eeprom_write(light5_address, lastState.lightState_5);
	}
	else if (receivedData == 'Q') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light6_ON();
		} else if (receivedData == '0') {
			light6_OFF();
		}
		eeprom_write(light6_address, lastState.lightState_6);
	}
	else if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			Total_ON();
			eeprom_write(light1_address, lastState.lightState_1);
			eeprom_write(light2_address, lastState.lightState_2);
			eeprom_write(light3_address, lastState.lightState_3);
			eeprom_write(light4_address, lastState.lightState_4);
			eeprom_write(light5_address, lastState.lightState_5);
			eeprom_write(light6_address, lastState.lightState_6);
		}
		else if(receivedData == '0'){
			Total_OFF();
			eeprom_write(light1_address, lastState.lightState_1);
			eeprom_write(light2_address, lastState.lightState_2);
			eeprom_write(light3_address, lastState.lightState_3);
			eeprom_write(light4_address, lastState.lightState_4);
			eeprom_write(light5_address, lastState.lightState_5);
			eeprom_write(light6_address, lastState.lightState_6);
		}
	}
	/*else if (receivedData == 'x'){
		wdt_enable(WDTO_15MS);
		while(1);
	}*/
}

