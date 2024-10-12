/*
 * 4L2F_control_CRC.c
 *
 * Created: 31-08-2024 12:34:45
 * Author : kjeya
 */ 

#include "main.h"

typedef struct {
	volatile uint8_t *port;
	uint8_t pin;
} pin_map_t;

volatile states_t lastStates_t = {0};
volatile uint8_t timer_flag = 0;
const char* command;
uint8_t fan1_speed = 0;
uint8_t fan2_speed = 0;

uint16_t light1_address = 0x0000;
uint16_t light2_address = 0x0001;
uint16_t light3_address = 0x0002;
uint16_t light4_address = 0x0003;
uint16_t fan1_address   = 0x0004;
uint16_t fan2_address   = 0x0005;

int main(void){
	setup();
	readLastStatesFromEEPROM();
	retain_Lights_State_From_EEPROM();
	retain_Fan1_State_From_EEPROM();
	retain_Fan2_State_From_EEPROM();
	sei(); // global interrupt
	while (1) {
	}
	return 0;
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

void timer1_init() {
	TCCR1B |= (1 << WGM12);
	OCR1A = 3624;
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << CS12) | (1 << CS10);
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
			counter = 0;
		}
	}
}

void SPI_init_slave() {
	DDRB |= (1 << DDB4);
	SPCR |= (1 << SPE);
	SPCR |= (1 << SPIE);
}

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

ISR(USART0_RX_vect) {
	unsigned char receivedData = UDR0;
	UARTprocessCommand(receivedData);
}

void readLastStatesFromEEPROM(void) {
	uint16_t addresses[] = {light1_State_Address, light2_State_Address, light3_State_Address, light4_state_Address, fan1_State_Address, fan2_State_Address};
	uint8_t *state_ptr = (uint8_t *)&lastStates_t;
	for (uint8_t i = 0; i < sizeof(lastStates_t); i++) {
		state_ptr[i] = eeprom_read_byte((uint8_t*) addresses[i]);
	}
}


void retain_Lights_State_From_EEPROM(void){
	pin_map_t lightMapping[4][2] = {
		{{&PORTD, PD7}, {&PORTC, PC5}},  // light1state
		{{&PORTC, PC3}, {&PORTC, PC6}},  // light2state
		{{&PORTD, PD6}, {&PORTA, PA5}},  // light3state
		{{&PORTC, PC4}, {&PORTA, PA4}}   // light4state
	};

	volatile uint8_t *lightStates[4] = {
		&lastStates_t.light1state,
		&lastStates_t.light2state,
		&lastStates_t.light3state,
		&lastStates_t.light4state
	};

	for(uint8_t i = 0; i < 4; i++) {
		if(*lightStates[i]) {
			*lightMapping[i][0].port ^= (1 << lightMapping[i][0].pin);
			*lightMapping[i][1].port ^= (1 << lightMapping[i][1].pin);
		}
	}
}

void retain_Fan1_State_From_EEPROM(){
	switch(lastStates_t.lastF1state){
		case 0: as0(); lastStates_t.lastF1state = 0; break;
		case 1: as1(); lastStates_t.lastF1state = 1; break;
		case 2: as2(); lastStates_t.lastF1state = 2; break;
		case 3: as3(); lastStates_t.lastF1state = 3; break;
		case 4: as4(); lastStates_t.lastF1state = 4; break;
		case 5: as5(); lastStates_t.lastF1state = 5; break;
		default:as0(); lastStates_t.lastF1state = 0; break;
	}
}

void retain_Fan2_State_From_EEPROM(){
	switch(lastStates_t.lastF2state){
		case 0: af0(); lastStates_t.lastF2state = 0; break;
		case 1: af1(); lastStates_t.lastF2state = 1; break;
		case 2: af2(); lastStates_t.lastF2state = 2; break;
		case 3: af3(); lastStates_t.lastF2state = 3; break;
		case 4: af4(); lastStates_t.lastF2state = 4; break;
		case 5: af5(); lastStates_t.lastF2state = 5; break;
		default:af0(); lastStates_t.lastF2state = 0; break;
	}
}

void setup(){
	timer1_init();
	SPI_init_slave(); // Initialize SPI as a slave
	USART_Init(MYUBRR); //Initialize Uart
	
	DDRD |= (1 << PD1) |(1 << PD2) |(1 << PD3) |(1 << PD4) |(1 << PD5) |(1 << PD6) |(1 << PD7);              // Set PORTD pins as output
	DDRG |= (1 << PG0) | (1 << PG1)| (1 << PG2)|(1 << PG4);                                                             // Set PORTG pins 0 and 1 as output for LEDs
	DDRC |= (1 << PC5) | (1 << PC6)| (1 << PC7)| (1 << PC0)| (1 << PC1)| (1 << PC2)| (1 << PC3)| (1 << PC4); // Set PORTC pins as output
	DDRA |= (1 << PA5) | (1 << PA4)|(1 << PA7) | (1 << PA6)| (1 << PA3)|(1 << PA2) | (1 << PA1)| (1 << PA0); // Set PORTA pins as output
}

void handle_All_ON() {
	light1_ON();
	light2_ON();
	light3_ON();
	light4_ON();
	switch(lastStates_t.lastF1state){
		case 1: as1(); USART_Transmit('A'); lastStates_t.lastF1state = 1; fan1_speed = 1; break;
		case 2: as2(); USART_Transmit('C'); lastStates_t.lastF1state = 2; fan1_speed = 2; break;
		case 3: as3(); USART_Transmit('D'); lastStates_t.lastF1state = 3; fan1_speed = 3; break;
		case 4: as4(); USART_Transmit('E'); lastStates_t.lastF1state = 4; fan1_speed = 4; break;
		case 5: as5(); USART_Transmit('F'); lastStates_t.lastF1state = 5; fan1_speed = 5; break;
		default:
		switch(fan1_speed){
			case 1: as1(); USART_Transmit('A'); lastStates_t.lastF1state = 1; fan1_speed = 1; break;
			case 2: as2(); USART_Transmit('C'); lastStates_t.lastF1state = 2; fan1_speed = 2; break;
			case 3: as3(); USART_Transmit('D'); lastStates_t.lastF1state = 3; fan1_speed = 3; break;
			case 4: as4(); USART_Transmit('E'); lastStates_t.lastF1state = 4; fan1_speed = 4; break;
			case 5: as5(); USART_Transmit('F'); lastStates_t.lastF1state = 5; fan1_speed = 5; break;
			default:as1(); USART_Transmit('A'); lastStates_t.lastF1state = 1; fan1_speed = 1; break;
		}
		break;
	}
	switch(lastStates_t.lastF2state){
		case 1: af1(); USART_Transmit('K'); lastStates_t.lastF2state = 1; fan2_speed = 1; break;
		case 2: af2(); USART_Transmit('Z'); lastStates_t.lastF2state = 2; fan2_speed = 2; break;
		case 3: af3(); USART_Transmit('X'); lastStates_t.lastF2state = 3; fan2_speed = 3; break;
		case 4: af4(); USART_Transmit('I'); lastStates_t.lastF2state = 4; fan2_speed = 4; break;
		case 5: af5(); USART_Transmit('J'); lastStates_t.lastF2state = 5; fan2_speed = 5; break;
		default:
		switch(fan2_speed){
			case 1: af1(); USART_Transmit('K'); lastStates_t.lastF2state = 1; fan2_speed = 1; break;
			case 2: af2(); USART_Transmit('Z'); lastStates_t.lastF2state = 2; fan2_speed = 2; break;
			case 3: af3(); USART_Transmit('X'); lastStates_t.lastF2state = 3; fan2_speed = 3; break;
			case 4: af4(); USART_Transmit('I'); lastStates_t.lastF2state = 4; fan2_speed = 4; break;
			case 5: af5(); USART_Transmit('J'); lastStates_t.lastF2state = 5; fan2_speed = 5; break;
			default: af1();USART_Transmit('K'); lastStates_t.lastF2state = 1; fan2_speed = 1; break;
		}
		break;
	}
}

void handle_All_OFF() {
	light1_OFF();
	light2_OFF();
	light3_OFF();
	light4_OFF();
	as0();
	af0();
	lastStates_t.lastF1state = 0;
	lastStates_t.lastF2state = 0;
}


