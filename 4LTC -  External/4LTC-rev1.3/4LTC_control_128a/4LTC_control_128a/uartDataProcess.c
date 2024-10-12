/*
 * uartDataProcess.c
 *
 * Created: 18-09-2024 21:12:00
 *  Author: kjeya
 */ 

#include "uartDataProcess.h"

void UARTprocessCommand(unsigned char receivedData){
	if (receivedData == 'L') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light1_ON();
			}else if (receivedData == '0') {
			light1_OFF();
		}
		eeprom_write(light1_address, lastState.lightState_1);
	}

	if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light2_ON();
			}else if (receivedData == '0') {
			light2_OFF();
		}
		eeprom_write(light2_address, lastState.lightState_2);
	}
	if (receivedData == 'N') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light3_ON();
			}else if (receivedData == '0') {
			light3_OFF();
		}
		eeprom_write(light3_address, lastState.lightState_3);
	}

	if (receivedData == 'O') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light4_ON();
		}
		else if (receivedData == '0') {
			light4_OFF();
		}
		eeprom_write(light4_address, lastState.lightState_4);
	}
	
	if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			Total_ON();
			writeStatesToEEPROM();
		}
		else if(receivedData == '0'){
			Total_OFF();
			writeStatesToEEPROM();
		}
	}
}