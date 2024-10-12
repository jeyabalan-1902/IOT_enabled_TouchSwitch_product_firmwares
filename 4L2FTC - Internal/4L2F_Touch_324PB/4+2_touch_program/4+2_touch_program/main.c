#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <atmel_start.h>
#include "touch.h"

#define F1_EEPROM_ADDR 0x00
#define F2_EEPROM_ADDR 0x01

#define POLYNOMIAL 0x07  // CRC polynomial
#define INIT_CRC 0x00


// Spi Communication Pins
#define SPI_SS_PIN PB4 // SS pin connected to PB4
#define SPI_MOSI_PIN PB5 // MOSI pin connected to PB5
#define SPI_MISO_PIN PB6 // MISO pin connected to PB6
#define SPI_SCK_PIN PB7 // SCK pin connected to PB7

// Function declarations
void touchpin1();
void touchpin2();
void touchpin3();
void touchpin4();
void touchpin5();
void touchpin6();
void touchpin7();
void touchpin8();
void touchpin9();
void touchpin10();
void SPI_MasterTransmitString(const char* str);
void timer1_init();
void loop();
void SPI_MasterTransmit(uint8_t data);
void SPI_MasterInit();
void retain_Last_Touch5_State(void);
void retain_Last_Touch8_State(void);

volatile uint16_t second_counter = 0;
volatile uint16_t second_counter_2 = 0;

// Declare previous key status and touch counter variables for all touch pins
extern volatile uint8_t measurement_done_touch;
uint8_t key_status_1 = 0;
uint8_t previous_key_status_1 = 0;
uint8_t touch_counter_1 = 0;
uint8_t key_status_2 = 0;
uint8_t previous_key_status_2 = 0;
uint8_t touch_counter_2 = 0;
uint8_t key_status_3 = 0;
uint8_t previous_key_status_3 = 0;
uint8_t touch_counter_3 = 0;
uint8_t key_status_4 = 0;
uint8_t previous_key_status_4 = 0;
uint8_t touch_counter_4 = 0;
uint8_t key_status_5 = 0;
uint8_t previous_key_status_5 = 0;
uint8_t touch_counter_5 = 0;
uint8_t key_status_6 = 0;
uint8_t previous_key_status_6 = 0;
uint8_t touch_counter_6 = 0;
uint8_t key_status_7 = 0;
uint8_t previous_key_status_7 = 0;
uint8_t touch_counter_7 = 0;
uint8_t key_status_8 = 0;
uint8_t previous_key_status_8 = 0;
uint8_t touch_counter_8 = 0;
uint8_t key_status_9 = 0;
uint8_t previous_key_status_9 = 0;
uint8_t touch_counter_9 = 0;
uint8_t key_status_10 = 0;
uint8_t previous_key_status_10 = 0;
uint8_t touch_counter_10 = 0;

int main(void)
{
	atmel_start_init();
	cpu_irq_enable();
	SPI_MasterInit();
	retain_Last_Touch5_State();
	retain_Last_Touch8_State();
	while (1)
	{
		loop();
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
	OCR1A = 79997;  
	TIMSK1 |= (1 << OCIE1A); 
	TCCR1B |= (1 << CS12) | (1 << CS10); 
}


void SPI_MasterInit()
{
	DDRB |= (1 << SPI_SS_PIN) | (1 << SPI_MOSI_PIN) | (1 << SPI_SCK_PIN);
	SPCR0 = (1 << SPE) | (1 << MSTR);
	PORTB |= (1 << SPI_SS_PIN);
}
void SPI_MasterTransmit(uint8_t data)
{
	PORTB &= ~(1 << SPI_SS_PIN);
	SPDR0 = data;
	while (!(SPSR0 & (1 << SPIF)))
	{
		
	}
	PORTB |= (1 << SPI_SS_PIN);
}
void loop()
{
	touch_process();
	// Check if touch measurement is done
	if (measurement_done_touch == 1)
	{
		measurement_done_touch = 0;
		touchpin1();
		touchpin2();
		touchpin3();
		touchpin4();
		touchpin5();
		touchpin6();
		touchpin7();
		touchpin8();
		touchpin9();
		touchpin10();

		// Check if both touchpin6 (second_counter) and touchpin7 (second_counter_2) have been pressed for 10 seconds
		if (second_counter >= 200 && second_counter_2 >= 200) {
			uint8_t dataToSend[3] = {'P', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);
			SPI_MasterTransmit(crc);
			second_counter = 0;
			second_counter_2 = 0;
			touch_counter_1 = 0;
			touch_counter_2 = 0;
		}
		
	}
}

void touchpin1() {
	previous_key_status_1 = key_status_1;
	key_status_1 = get_sensor_state(0) & 0x80;
	if (key_status_1 && !previous_key_status_1) {
		touch_counter_1++;
		if (touch_counter_1 == 1) {
			uint8_t dataToSend[3] = {'L', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                     // Transmits "L1"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
		}
		else if (touch_counter_1 == 2) {
			SPI_MasterTransmitString("L1");
			uint8_t dataToSend[3] = {'L', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                     // Transmits "L1"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
			touch_counter_1 = 0;
		}
	}
}
void touchpin2() {
	previous_key_status_2 = key_status_2;
	key_status_2= get_sensor_state(2) & 0x80;
	if (key_status_2 && !previous_key_status_2) {
		touch_counter_2++;
		if (touch_counter_2 == 1) {
			char dataToSend[3] = {'L', '2'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L2"
			SPI_MasterTransmit(crc);
		}
		else if (touch_counter_2 == 2) {
			char dataToSend[3] = {'L', '2'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L2"
			SPI_MasterTransmit(crc);
			touch_counter_2 = 0;
		}
	}
}
void touchpin3() {
	previous_key_status_3 = key_status_3;
	key_status_3 = get_sensor_state(1) & 0x80;
	if (key_status_3 && !previous_key_status_3) {
		touch_counter_3++;
		if (touch_counter_3 == 1) {
			uint8_t dataToSend[3] = {'L', '3'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L3"
			SPI_MasterTransmit(crc);
		}
		else if (touch_counter_3 == 2) {
			uint8_t dataToSend[3] = {'L', '3'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L3"
			SPI_MasterTransmit(crc);
			touch_counter_3 = 0;
		}
	}
}
void touchpin4() {
	previous_key_status_4 = key_status_4;
	key_status_4 = get_sensor_state(3) & 0x80;
	if (key_status_4 && !previous_key_status_4) {
		touch_counter_4++;
		if (touch_counter_4 == 1) {
			uint8_t dataToSend[3] = {'L', '4'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L4"
			SPI_MasterTransmit(crc);
		}
		else if (touch_counter_4 == 2) {
			uint8_t dataToSend[3] = {'L', '4'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L4"
			SPI_MasterTransmit(crc);
			touch_counter_4 = 0;
		}
	}
}
void touchpin5()
{
	previous_key_status_5 = key_status_5;
	key_status_5 = get_sensor_state(4) & 0x80;

	if (key_status_5 && !previous_key_status_5) {
		touch_counter_5++;
		if (touch_counter_5 == 1)
		{
			uint8_t dataToSend[3] = {'F', '0'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "F0"
			SPI_MasterTransmit(crc);
			touch_counter_5 = 1;
			eeprom_write_byte((uint8_t*)F1_EEPROM_ADDR, touch_counter_5);
		}
		
		else if (touch_counter_5 == 2) {
			uint8_t dataToSend[3] = {'F', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "F1"
			SPI_MasterTransmit(crc);
			touch_counter_5 = 0;
			eeprom_write_byte((uint8_t*)F1_EEPROM_ADDR, touch_counter_5);
		}
	}
}



void touchpin6() {
	previous_key_status_6 = key_status_6;
	key_status_6 = get_sensor_state(5) & 0x80;

	if (key_status_6 && !previous_key_status_6) {
		second_counter = 0;
		touch_counter_6 = 1;  
	}
	if (key_status_6) {
		second_counter++;
	}
	else if (!key_status_6 && previous_key_status_6) {
		if (second_counter > 0 && second_counter < 200 && touch_counter_6 == 1) {
			uint8_t dataToSend[3] = {'U', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "U1"
			SPI_MasterTransmit(crc);
		}
		second_counter = 0; 
		touch_counter_6 = 0; 
	}
}


void touchpin7() {
	previous_key_status_7 = key_status_7;
	key_status_7 = get_sensor_state(6) & 0x80;

	if (key_status_7 && !previous_key_status_7) {
		second_counter_2 = 0;
		touch_counter_7 = 1;
	}
	if (key_status_7) {
		second_counter_2++;
	}
	else if (!key_status_7 && previous_key_status_7) {
		
		if (second_counter_2 > 0 && second_counter_2 < 200 && touch_counter_7 == 1) {
			uint8_t dataToSend[3] = {'D', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "D1"
			SPI_MasterTransmit(crc);
		}
		second_counter_2 = 0;
		touch_counter_7 = 0;
	}
}

void touchpin8()
{
	previous_key_status_8 = key_status_8;
	key_status_8 = get_sensor_state(7) & 0x80;
	if (key_status_8 && !previous_key_status_8) {
		touch_counter_8++;
		if (touch_counter_8 == 1)
		{
			uint8_t dataToSend[3] = {'F', '2'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "F2"
			SPI_MasterTransmit(crc);
			touch_counter_8 = 1;
			eeprom_write_byte((uint8_t*)F2_EEPROM_ADDR, touch_counter_8);
		}
		else if (touch_counter_8 == 2) {
			uint8_t dataToSend[3] = {'F', '3'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "F3"
			SPI_MasterTransmit(crc);
			touch_counter_8 = 0;
			eeprom_write_byte((uint8_t*)F2_EEPROM_ADDR, touch_counter_8);
		}
	}
}

void touchpin9()
{
	previous_key_status_9 = key_status_9;
	key_status_9 = get_sensor_state(8) & 0x80;
	
	if (key_status_9 && !previous_key_status_9) {
		touch_counter_9++;
		uint8_t dataToSend[3] = {'U', '2'};
		uint8_t crc = calculateCRC(dataToSend, 2);
		SPI_MasterTransmitString(dataToSend);                      // Transmits "U2"
		SPI_MasterTransmit(crc);
	}
	
}


void touchpin10()
{
	previous_key_status_10 = key_status_10;
	key_status_10 = get_sensor_state(9) & 0x80;

	if (key_status_10 && !previous_key_status_10) {
		touch_counter_10++;
		uint8_t dataToSend[3] = {'D', '2'};
		uint8_t crc = calculateCRC(dataToSend, 2);
		SPI_MasterTransmitString(dataToSend);                      // Transmits "D2"
		SPI_MasterTransmit(crc);
	}	
}

void SPI_MasterTransmitString(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		SPI_MasterTransmit(str[i]);
		_delay_ms(100);
	}
}

void retain_Last_Touch5_State(void){
	touch_counter_5 = eeprom_read_byte((uint8_t*)F1_EEPROM_ADDR);
	if(touch_counter_5 == 1){
		touch_counter_5 = 1;
		}else{
		touch_counter_5 = 0;
	}
	
	if(touch_counter_5 == 0xFF){
		eeprom_write_byte((uint8_t*)F1_EEPROM_ADDR, 0x00);
	}
}

void retain_Last_Touch8_State(void){
	touch_counter_8 = eeprom_read_byte((uint8_t*)F2_EEPROM_ADDR);
	if(touch_counter_8 == 1){
		touch_counter_8 = 1;
		}else{
		touch_counter_8 = 0;
	}
	
	if(touch_counter_8 == 0xFF){
		eeprom_write_byte((uint8_t*)F2_EEPROM_ADDR, 0x00);
	}
}