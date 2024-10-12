/*
 * uartDataProcess.c
 *
 * Created: 03-09-2024 17:02:26
 *  Author: kjeyabalan
 */ 

#include "uartDataProcess.h"

void UARTdataProcess(unsigned char receivedData){
	if(receivedData == 'L'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			PORTD |= (1 << PD3);
			laststate.switch1Status = 1;
		}
		else if(receivedData == '0'){
			PORTD &= ~(1 << PD3);
			laststate.switch1Status = 0;
		}
		eeprom_write(light1_address, laststate.switch1Status);
	}
	else if(receivedData == 'M'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			PORTD |= (1 << PD4);
			laststate.switch2Status = 1;
		}
		else if(receivedData == '0'){
			PORTD &= ~(1 << PD4);
			laststate.switch2Status = 0;
		}
		eeprom_write(light2_address, laststate.switch2Status);
	}
	else if(receivedData == 'N'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			PORTD |= (1 << PD5);
			laststate.switch3status = 1;
		}
		else if(receivedData == '0'){
			PORTD &= ~(1 << PD5);
			laststate.switch3status = 0;
		}
		eeprom_write(light3_address, laststate.switch3status);
	}
	if(receivedData == 'F'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			fanSpeed1();
			fan_speed = 1;
			laststate.fanSwitchStatus = 1;
			receivedData = USART_Receive();
			if(receivedData == 'U'){
				receivedData = USART_Receive();
				if(receivedData == '2'){
					fanSpeed2();
					fan_speed = 2;
					laststate.fanSwitchStatus = 2;
				}
				else if(receivedData == '3'){
					fanSpeed3();
					fan_speed = 3;
					laststate.fanSwitchStatus = 3;
				}
				else if(receivedData == '4'){
					fanSpeed4();
					fan_speed = 4;
					laststate.fanSwitchStatus = 4;
				}
				else if(receivedData == '5'){
					fanSpeed5();
					fan_speed = 5;
					laststate.fanSwitchStatus = 5;
				}
			}
			//laststate.fanSwitchStatus = 1;
			eeprom_write(fan1_address, laststate.fanSwitchStatus);
		}
		else if(receivedData == '0'){
			fanSpeed0();
			laststate.fanSwitchStatus = 0;
			eeprom_write(fan1_address, laststate.fanSwitchStatus);
		}
	}
	if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			turnAll_ON();
		}
		else if(receivedData == '0'){
			turnAll_OFF();
		}
		eeprom_write(light1_address, laststate.switch1Status);
		eeprom_write(light2_address, laststate.switch2Status);
		eeprom_write(light3_address, laststate.switch3status);
		eeprom_write(fan1_address, laststate.fanSwitchStatus);
	}
}