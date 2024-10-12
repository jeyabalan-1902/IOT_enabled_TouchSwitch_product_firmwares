/*
 * uartDataProcess.c
 *
 * Created: 27-08-2024 15:08:38
 *  Author: kjeyabalan
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
		eeprom_write(light1_address, laststate.lightState_1);
	}
	
	else if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {        // light2 ON
			light2_ON();
		}
		else if (receivedData == '0') {       //light2 OFF
			light2_OFF();
		}
		eeprom_write(light2_address, laststate.lightState_2);
	}
	
	else if (receivedData == 'N') {
		receivedData = USART_Receive();
		if (receivedData == '1') {      //light3 ON
			light3_ON();
		}
		else if (receivedData == '0') {     //light3 OFF
			light3_OFF();
		}
		eeprom_write(light3_address, laststate.lightState_3);
	}
	else if (receivedData == 'F') {
		receivedData = USART_Receive();
		if (receivedData == '1') {     // fan1 ON
			as1();
			laststate.lastF1State = 1;
			fan1_speed = 1;
			receivedData = USART_Receive();
			if (receivedData == 'U') {
				receivedData = USART_Receive();      //fan1 speed increment and decrement
				if (receivedData == '2') {
					as2();
					laststate.lastF1State = 2;
					fan1_speed = 2;
				}
				else if (receivedData == '3') {
					as3();
					laststate.lastF1State = 3;
					fan1_speed = 3;
				}
				else if (receivedData == '4') {
					as4();
					laststate.lastF1State = 4;
					fan1_speed = 4;
				}
				else if (receivedData == '5') {
					as5();
					laststate.lastF1State = 5;
					fan1_speed = 5;
				}
			}
		}
		else if (receivedData == '0') {     // fan1 OFF
			as0();
			laststate.lastF1State = 0;
		}
		eeprom_write(fan1_address, laststate.lastF1State);
	}

	else if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			handle_All_ON();
			eeprom_write(light1_address, laststate.lightState_1);
			eeprom_write(light2_address, laststate.lightState_2);
			eeprom_write(light3_address, laststate.lightState_3);
			eeprom_write(fan1_address, laststate.lastF1State);
			
		}
		else if(receivedData == '0'){
			handle_All_OFF();
			eeprom_write(light1_address, laststate.lightState_1);
			eeprom_write(light2_address, laststate.lightState_2);
			eeprom_write(light3_address, laststate.lightState_3);
			eeprom_write(fan1_address, laststate.lastF1State);
		}	
	}
	
	/*else if(receivedData == 'x'){
		wdt_enable(WDTO_15MS);
		while (1);
	}*/
}