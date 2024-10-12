/*
 * uartDataProcess.c
 *
 * Created: 29-08-2024 15:05:19
 *  Author: kjeyabalan
 */ 

#include "uartDataProcess.h"

void UARTprocessCommand(unsigned char receivedData){
	if (receivedData == 'L') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light1_ON();
		}
		else if (receivedData == '0') {
			light1_OFF();
		}
		eeprom_write(light1_address, lastStates_t.light1state);
	}
	else if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light2_ON();
		}
		else if (receivedData == '0') {
			light2_OFF();
		}
		eeprom_write(light2_address, lastStates_t.light2state);
	}
	else if (receivedData == 'N') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light3_ON();
		}
		else if (receivedData == '0') {
			light3_OFF();
		}
		eeprom_write(light3_address, lastStates_t.light3state);
	}
	else if (receivedData == 'P') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light4_ON();
		}
		else if (receivedData == '0') {
			light4_OFF();
		}
		eeprom_write(light4_address, lastStates_t.light4state);
	}
	else if (receivedData == 'F') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			as1();
			lastStates_t.lastF1state = 1;
			fan1_speed = 1;
			receivedData = USART_Receive();
			if (receivedData == 'U') {
				receivedData = USART_Receive();
				if (receivedData == '2') {
					as2();
					lastStates_t.lastF1state = 2;
					fan1_speed = 2;
				}
				else if (receivedData == '3') {
					as3();
					lastStates_t.lastF1state = 3;
					fan1_speed = 3;
				}
				else if (receivedData == '4') {
					as4();
					lastStates_t.lastF1state = 4;
					fan1_speed = 4;
				}
				else if (receivedData == '5') {
					as5();
					lastStates_t.lastF1state = 5;
					fan1_speed = 5;
				}
			}
			eeprom_write(fan1_address, lastStates_t.lastF1state);
		}
		else if (receivedData == '0') {
			as0();
			lastStates_t.lastF1state = 0;
			eeprom_write(fan1_address, lastStates_t.lastF1state);
		}
	}
	
	else if (receivedData == 'G') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			af1();
			lastStates_t.lastF2state = 1;
			fan2_speed = 1;
			receivedData = USART_Receive();
			if (receivedData == 'H') {
				receivedData = USART_Receive();
				if (receivedData == '2') {
					af2();
					lastStates_t.lastF2state = 2;
					fan2_speed = 2;
				}
				else if (receivedData == '3') {
					af3();
					lastStates_t.lastF2state = 3;
					fan2_speed = 3;
				}
				else if (receivedData == '4') {
					af4();
					lastStates_t.lastF2state = 4;
					fan2_speed = 4;
				}
				else if (receivedData == '5') {
					af5();
					lastStates_t.lastF2state = 5;
					fan2_speed = 5;
				}
			}
			eeprom_write(fan2_address, lastStates_t.lastF2state);
		}
		else if (receivedData == '0') {
			af0();
			lastStates_t.lastF2state = 0;
			eeprom_write(fan2_address, lastStates_t.lastF2state);
		}
	}
	else if (receivedData == 'Z') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			handle_All_ON();
		}else if (receivedData == '0') {
			handle_All_OFF();
		}
		write_All_States_ToEEPROM();
	}
	/*else if(receivedData == 'x'){
		wdt_enable(WDTO_15MS);
		while (1);
	}*/
}