/*
 * 4LTC_control_128a_PFD.c
 *
 * Created: 18-09-2024 16:13:41
 * Author : kjeyabalan
 */ 

#include "main.h"

typedef enum {
	EVENT_NONE = 0,
	EVENT_SPI,
	EVENT_UART,
	EVENT_ANOMALY
} event_t;

typedef struct {
	event_t event;
} event_process_t;

#define MAX_EVENT_PROCESS_SIZE 10
volatile event_process_t event_process[MAX_EVENT_PROCESS_SIZE];
volatile uint8_t event_process_head = 0;
volatile uint8_t event_process_tail = 0;

typedef struct {
	volatile uint8_t *port;
	uint8_t pin;
} pin_map_t;

uint16_t light1_address = 0x0000;
uint16_t light2_address = 0x0001;
uint16_t light3_address = 0x0002;
uint16_t light4_address = 0x0003;
volatile states lastState = {0};
	
void add_event_to_process(event_t event);

int main(void) {
	setup();
	readStatesFromEEPROM();
	retainLightStates();
	init_watchdog_timer();
	while (1) {
		wdt_reset();
		
		if (event_process_head != event_process_tail) {
			event_t current_event = event_process[event_process_tail].event;
			event_process_tail = (event_process_tail + 1) % MAX_EVENT_PROCESS_SIZE;

			switch (current_event) {
				case EVENT_SPI:
				handle_SPI_interrupt();
				break;
				case EVENT_UART:
				handle_UART_interrupt();
				break;
				case EVENT_ANOMALY:
				handle_watchdog_event();
				break;
				default:
				break;
			}
		}
	}
	return 0;
}

void add_event_to_process(event_t event) {
	event_process[event_process_head].event = event;
	event_process_head = (event_process_head + 1) % MAX_EVENT_PROCESS_SIZE;
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

ISR(SPI_STC_vect) {
	add_event_to_process(EVENT_SPI);
}

ISR(USART0_RX_vect){
	 add_event_to_process(EVENT_UART);
}

void trigger_anomaly_event() {
	add_event_to_process(EVENT_ANOMALY);
}

void handle_SPI_interrupt(void){
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

void handle_UART_interrupt(void){
	unsigned char receivedData = UDR0;
	UARTprocessCommand(receivedData);
}

void handle_watchdog_event() {
	while(1);  
}

void setup(void){
	i2c_init();
	SPI_init_slave();
	USART_Init(MYUBRR);
    sei();
	DDRD|=(1<<7)|(1<<5)|(1<<6)|(1<<4);
	DDRF|=(1<<4)|(1<<5)|(1<<6)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
}

void writeStatesToEEPROM(void){
	uint16_t eeprom_addresses[] = {light1_address, light2_address, light3_address, light4_address};
	uint8_t *last_lights_state = (uint8_t*)&lastState;
	for (int i = 0; i < 4; i++) {
		eeprom_write(eeprom_addresses[i], last_lights_state[i]);
	}
}

void readStatesFromEEPROM(void){
	uint16_t addresses[] = {light1_address, light2_address, light3_address, light4_address};
	volatile uint8_t *state_ptr = (uint8_t *)&lastState;
	for (uint8_t i = 0; i < sizeof(lastState); i++) {
		state_ptr[i] = eeprom_read(addresses[i]);
	}
}

void retainLightStates(void){
	pin_map_t lightMapping[4][2] = {
		{{&PORTD, PD6}, {&PORTF, PF3}},  // light1state
		{{&PORTD, PD5}, {&PORTF, PF4}},  // light2state
		{{&PORTD, PD7}, {&PORTF, PF5}},  // light3state
		{{&PORTD, PD4}, {&PORTF, PF6}}   // light4state
	};

	volatile uint8_t *lightStates[4] = {&lastState.lightState_1, &lastState.lightState_2, &lastState.lightState_3, &lastState.lightState_4};

	for(uint8_t i = 0; i < 4; i++) {
		if(*lightStates[i]) {
			*lightMapping[i][0].port ^= (1 << lightMapping[i][0].pin);
			*lightMapping[i][1].port ^= (1 << lightMapping[i][1].pin);
		}
	}
}


void init_watchdog_timer(void) {
	wdt_enable(WDTO_2S);
}

