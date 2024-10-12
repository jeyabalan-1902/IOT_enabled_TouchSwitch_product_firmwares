/*
 * uartDataProcess.c
 *
 * Created: 31-08-2024 11:15:39
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
	}

	if (receivedData == 'M') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light2_ON();
			}else if (receivedData == '0') {
			light2_OFF();
		}
	}
	if (receivedData == 'N') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light3_ON();
			}else if (receivedData == '0') {
			light3_OFF();
		}
	}

	if (receivedData == 'O') {
		receivedData = USART_Receive();
		if (receivedData == '1') {
			light4_ON();
		}
		else if (receivedData == '0') {
			light4_OFF();
		}
	}
	
	if(receivedData == 'Z'){
		receivedData = USART_Receive();
		if(receivedData == '1'){
			light1_ON();
			light2_ON();
			light3_ON();
			light4_ON();
		}
		else if(receivedData == '0'){
			light1_OFF();
			light2_OFF();
			light3_OFF();
			light4_OFF();
		}
	}
}