/*
 * 6LTC_Control_24c32n.c
 *
 * Created: 05-08-2024 22:31:47
 * Author : kjeyabalan
 */ 

#include "main.h"

typedef struct {
	volatile uint8_t *port;
	uint8_t pin;
} pin_map_t;

volatile states lastState = {0};
	
volatile uint8_t timer_flag = 0;
uint16_t light1_address = 0x0000;
uint16_t light2_address = 0x0001;
uint16_t light3_address = 0x0002;
uint16_t light4_address = 0x0003;
uint16_t light5_address = 0x0004;
uint16_t light6_address = 0x0005;


int main(void) {
	setup();
	readStatesFromEEPROM();
	retainLightStates();
	while (1) {		
	}
	return 0;
}

void timer1_init() {
	TCCR1B |= (1 << WGM12);
	OCR1A = 3624;
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

uint8_t calculateCRC(uint8_t *data, size_t length) {
	uint8_t crc = INIT_CRC;
	for (size_t i = 0; i < length; i++) {
		crc ^= data[i];
		for (uint8_t j = 0; j < 8; j++) {
			if (crc & 0x80) {
				crc = (crc << 1) ^ POLYNOMIAL;
				} else {
				crc <<= 1;
			}
		}
	}
	return crc;
}

ISR(TIMER1_COMPA_vect) {
	timer_flag = 1;
}

void custom_delay_ms(uint16_t ms) {
	static uint16_t counter = 0;
	if (timer_flag) {
		timer_flag = 0;
		counter++;
		if (counter >= ms) {
			counter = 0;                       // Reset the counter
		}
	}
}

void SPI_init_slave() {
	DDRB |= (1 << DDB4);
	SPCR |= (1 << SPE);
	SPCR |= (1 << SPIE);                       // Enable SPI interrupt
}

/*ISR(SPI_STC_vect) {
	uint8_t receivedSPIData = SPDR;
	static char receivedBytes[2];
	static uint8_t receivedCRC = 0;
	static uint8_t byteIndex = 0;

	if (byteIndex < 2) {
		receivedBytes[byteIndex] = receivedSPIData;
		byteIndex++;
		} else if (byteIndex == 2) {
		receivedCRC = receivedSPIData;
		byteIndex++;
	}

	if (byteIndex == 3) {
		uint8_t calculatedCRC = calculateCRC((uint8_t *)receivedBytes, 2);
		if (calculatedCRC == receivedCRC) {
			receivedBytes[2] = '\0';
			SPIprocessCommand(receivedBytes);
		}
		byteIndex = 0;
	}
	SPSR |= (1 << SPIF);
}*/

ISR(SPI_STC_vect) {
	uint8_t receivedData = SPDR;                    // Read received data from SPI data register
	static char receivedBytes[3];
	static uint8_t byteIndex = 0;
	if (byteIndex < 2) {
		receivedBytes[byteIndex] = receivedData;
		byteIndex++;
		if (byteIndex == 2) {
			receivedBytes[2] = '\0';
			SPIprocessCommand(receivedBytes);          // Process the received command
			byteIndex = 0;
		}
	}
	SPSR |= (1 << SPIF);
}

ISR (USART0_RX_vect){
	unsigned char receivedData = UDR0;
	uartProcessCommand(receivedData);
}

void setup(void){
	sei();
	i2c_init();
	SPI_init_slave();                   
	timer1_init();
	USART_Init(MYUBRR);                 
	DDRD|=(1<<7)|(1<<5)|(1<<6)|(1<<4)|(1<<3)|(1<<2);
	DDRF|=(1<<4)|(1<<5)|(1<<6)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
}

void write_all_States_ToEEPROM(){
	uint16_t addresses[] = {light1_address, light2_address, light3_address,light4_address, light5_address, light6_address};
	uint8_t *state_ptr = (uint8_t*)&lastState;
	for(uint8_t i = 0; i < 6; i++){
		eeprom_write(addresses[i], state_ptr[i]);
	}
}

void readStatesFromEEPROM(void){
	uint16_t addresses[] = {light1_address, light2_address, light3_address, light4_address, light5_address, light6_address};
	uint8_t *state_ptr = (uint8_t *)&lastState;
	for(uint8_t i = 0; i < sizeof(lastState); i++){
		state_ptr[i] = eeprom_read(addresses[i]);
	}
}

void retainLightStates(void){
	pin_map_t lightMapping[6][2] = {
		{{&PORTD, PD6}, {&PORTF, PF1}},   // light1state
		{{&PORTD, PD5}, {&PORTF, PF2}},   // light2state
		{{&PORTD, PD7}, {&PORTF, PF3}},   // light3state
		{{&PORTD, PD4}, {&PORTF, PF4}},   // light4state
		{{&PORTD, PD3}, {&PORTF, PF5}},   // light5state
		{{&PORTD, PD2}, {&PORTF, PF6}}    // light6state
		};

	volatile uint8_t *lightStates[6] = {&lastState.lightState_1, &lastState.lightState_2, &lastState.lightState_3, &lastState.lightState_4, &lastState.lightState_5, &lastState.lightState_6};

	for(uint8_t i = 0; i < 6; i++) {
		if(*lightStates[i]) {
			*lightMapping[i][0].port ^= (1 << lightMapping[i][0].pin);
			*lightMapping[i][1].port ^= (1 << lightMapping[i][1].pin);
		}
	}
}



