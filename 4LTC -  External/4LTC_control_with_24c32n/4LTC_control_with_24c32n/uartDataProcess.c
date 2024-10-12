/*
 * uartDataProcess.c
 *
 * Created: 27-08-2024 17:21:52
 *  Author: kjeyabalan
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
	}

	else if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light2_ON();
			}else if (receivedData == '0') {
			light2_OFF();
		}
	}
	else if (receivedData == 'N') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light3_ON();
			}else if (receivedData == '0') {
			light3_OFF();
		}
	}

	else if (receivedData == 'O') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light4_ON();
		}
		else if (receivedData == '0') {
			light4_OFF();
		}
	}
	
	else if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			light1_ON();
			light2_ON();
			light3_ON();
			light4_ON();
			eeprom_write(light1_address, lastState.lightState_1);
			eeprom_write(light2_address, lastState.lightState_2);
			eeprom_write(light3_address, lastState.lightState_3);
			eeprom_write(light4_address, lastState.lightState_4);
		}
		else if(receivedData == '0'){
			light1_OFF();
			light2_OFF();
			light3_OFF();
			light4_OFF();
			eeprom_write(light1_address, lastState.lightState_1);
			eeprom_write(light2_address, lastState.lightState_2);
			eeprom_write(light3_address, lastState.lightState_3);
			eeprom_write(light4_address, lastState.lightState_4);
		}
	}
	
	/*else if(receivedData == 'x'){
		wdt_enable(WDTO_15MS);
		while (1);
	}*/
}