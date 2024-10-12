/*
 * 3L1F_CONTROL_128A.c
 *
 * Created: 24-08-2024 08:41:41
 * Author : kjeyabalan
 */ 

#include "main.h"


typedef struct {
	volatile uint8_t *port;
	uint8_t pin;
} pin_map_t;

volatile states laststate = {0};
uint16_t light1_address = 0x0000;
uint16_t light2_address = 0x0001;
uint16_t light3_address = 0x0002;
uint16_t fan1_address = 0x0003;
uint8_t fan1_speed = 0;
volatile uint8_t timer_flag = 0;

int main(void)
{
    setup();
    readLastStatesFromEEPROM();
    retainLightStates();
    retainFanState();
    while (1) 
    {
    }
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

ISR(SPI_STC_vect) {
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
}

ISR(USART0_RX_vect){
	unsigned char receivedData = UDR0;
	UARTprocessCommand(receivedData);
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


void setup(void){
	sei(); // Enable global interrupts
	i2c_init();
	SPI_init_slave();
	timer1_init();
	USART_Init(MYUBRR);
	DDRD|=(1<<7)|(1<<5)|(1<<6)|(1<<4);
	DDRF|=(1<<4)|(1<<5)|(1<<6)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
	DDRC|=(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0)|(1<<6)|(1<<7);
}

void readLastStatesFromEEPROM(void){
	uint16_t addresses[] = {light1_address, light2_address, light3_address, fan1_address};
	uint8_t *state_ptr = (uint8_t *)&laststate;
	for (uint8_t i = 0; i < sizeof(laststate); i++) {
		state_ptr[i] = eeprom_read(addresses[i]);
	}
}

void retainLightStates(void){
	pin_map_t lightMapping[3][2] = {
		{{&PORTC, PC1}, {&PORTF, PF4}},  // light1state
		{{&PORTC, PC3}, {&PORTF, PF5}},  // light2state
		{{&PORTC, PC4}, {&PORTF, PF6}}  // light3state
	};

	volatile uint8_t *lightStates[3] = { &laststate.lightState_1, &laststate.lightState_2, &laststate.lightState_3};

	for(uint8_t i = 0; i < 3; i++) {
		if(*lightStates[i]) {
			*lightMapping[i][0].port ^= (1 << lightMapping[i][0].pin);
			*lightMapping[i][1].port ^= (1 << lightMapping[i][1].pin);
		}
	}
}

void retainFanState(void){
	switch(laststate.lastF1State){
		case 0: as0(); break;
		case 1: as1(); break;
		case 2: as2(); break;
		case 3: as3(); break;
		case 4: as4(); break;
		case 5: as5(); break;
		default:as0(); break;
	}
}

void handle_All_ON() {
	light1_ON();
	light2_ON();
	light3_ON();
	switch(laststate.lastF1State){
		case 1: as1(); USART_Transmit('A'); laststate.lastF1State = 1; fan1_speed = 1; break;
		case 2: as2(); USART_Transmit('C'); laststate.lastF1State = 2; fan1_speed = 2; break;
		case 3: as3(); USART_Transmit('D'); laststate.lastF1State = 3; fan1_speed = 3; break;
		case 4: as4(); USART_Transmit('E'); laststate.lastF1State = 4; fan1_speed = 4; break;
		case 5: as5(); USART_Transmit('F'); laststate.lastF1State = 5; fan1_speed = 5; break;
		default:
		switch(fan1_speed){
			case 1: as1(); USART_Transmit('A'); laststate.lastF1State = 1; fan1_speed = 1; break;
			case 2: as2(); USART_Transmit('C'); laststate.lastF1State = 2; fan1_speed = 2; break;
			case 3: as3(); USART_Transmit('D'); laststate.lastF1State = 3; fan1_speed = 3; break;
			case 4: as4(); USART_Transmit('E'); laststate.lastF1State = 4; fan1_speed = 4; break;
			case 5: as5(); USART_Transmit('F'); laststate.lastF1State = 5; fan1_speed = 5; break;
			default:as1(); USART_Transmit('A'); laststate.lastF1State = 1; fan1_speed = 1; break;
		}
		break;
	}
}

void handle_All_OFF() {
	light1_OFF();
	light2_OFF();
	light3_OFF();
	as0();
	laststate.lastF1State = 0;
}

void write_All_States_ToEEPROM(){
	uint16_t eeprom_addresses[] = {light1_address, light2_address, light3_address, fan1_address};
	uint8_t *state_ptr = (uint8_t *)&laststate;
	for (int i = 0; i < 4; i++) {
		eeprom_write(eeprom_addresses[i], state_ptr[i]);
	}
}