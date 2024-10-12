#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <atmel_start.h>
#include <avr/eeprom.h>
#include "touch.h"

#define SPI_SS_PIN PB4     // SS pin connected to PB4
#define SPI_MOSI_PIN PB5   // MOSI pin connected to PB5
#define SPI_MISO_PIN PB6   // MISO pin connected to PB6
#define SPI_SCK_PIN PB7    // SCK pin connected to PB7

#define EEPROM_ADDR 0x00    //EEPROM address

#define POLYNOMIAL 0x07  // CRC polynomial 
#define INIT_CRC 0x00

// Function declarations
void touchpin1();
void touchpin2();
void touchpin3();
void touchpin4();
void touchpin5();
void touchpin6();
void SPI_MasterTransmitString(const char* dataTosendend);
void timer1_init();
void loop();
void SPI_MasterTransmit(uint8_t data);
void SPI_MasterInit();
uint8_t calculateCRC(uint8_t *data, size_t length);
void retain_fanTouch_sensor_state(void);

// Declare previous key status and touch counter variables for all touch pins
extern volatile uint8_t measurement_done_touch;
uint8_t key_status_1 = 0, previous_key_status_1 = 0, touch_counter_1 = 0;
uint8_t key_status_2 = 0, previous_key_status_2 = 0, touch_counter_2 = 0;
uint8_t key_status_3 = 0, previous_key_status_3 = 0, touch_counter_3 = 0;
uint8_t key_status_4 = 0, previous_key_status_4 = 0, touch_counter_4 = 0;
uint8_t key_status_5 = 0, previous_key_status_5 = 0, touch_counter_5 = 0;
uint8_t key_status_6 = 0, previous_key_status_6 = 0, touch_counter_6 = 0;
volatile uint16_t second_counter = 0;
volatile uint16_t second_counter_2 = 0;

int main(void)
{
	atmel_start_init();
	cpu_irq_enable();
	SPI_MasterInit();
	retain_fanTouch_sensor_state();
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
	if (measurement_done_touch == 1)
	{
		measurement_done_touch = 0;
		touchpin1();
		touchpin2();
		touchpin3();
		touchpin4();
		touchpin5();
		touchpin6();
		if (second_counter >= 200 && second_counter_2 >= 200) {
			uint8_t dataToSend[3] = {'H', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);
			SPI_MasterTransmit(crc);
			second_counter = 0;
			second_counter_2 = 0;
			touch_counter_5 = 0;
			touch_counter_6 = 0;
		}
	}
}

void touchpin1() {
	previous_key_status_1 = key_status_1;
	key_status_1 = get_sensor_state(0) & 0x80;
	if (key_status_1 && !previous_key_status_1) {
		touch_counter_1++;  
        if(touch_counter_1 == 1){
			uint8_t dataToSend[3] = {'L', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                     // Transmits "L1"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
		}
		else if(touch_counter_1 == 2){
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
	key_status_2 = get_sensor_state(1) & 0x80;
	if (key_status_2&& !previous_key_status_2) {
		touch_counter_2++;
		if (touch_counter_2 == 1) {
			char dataToSend[3] = {'L', '2'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L2"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
		}
		else if(touch_counter_2 == 2){
			char dataToSend[3] = {'L', '2'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L2"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
			touch_counter_2 = 0;
		}
	}
}

void touchpin3() {
	previous_key_status_3 = key_status_3;
	key_status_3 = get_sensor_state(2) & 0x80;
	if (key_status_3 && !previous_key_status_3) {
		touch_counter_3++;
		if (touch_counter_3 == 1) {
			uint8_t dataToSend[3] = {'L', '3'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L3"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
		}
		else if (touch_counter_3 == 2) {
			uint8_t dataToSend[3] = {'L', '3'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "L3"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
			touch_counter_3 = 0;
		}
	}
}
void touchpin4()
{
	previous_key_status_4 = key_status_4;
	key_status_4 = get_sensor_state(3) & 0x80;
	if (key_status_4 && !previous_key_status_4) {
		touch_counter_4++;
		if (touch_counter_4 == 1)
		{
			uint8_t dataToSend[3] = {'F', '0'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "F0"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
			touch_counter_4 = 1;
			eeprom_write_byte((uint8_t*)EEPROM_ADDR, touch_counter_4);
		}
		
		else if (touch_counter_4 == 2) {
			uint8_t dataToSend[3] = {'F', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "F1"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
			touch_counter_4 = 0;
			eeprom_write_byte((uint8_t*)EEPROM_ADDR, touch_counter_4);
		}
	}
}

void touchpin5()
{
	previous_key_status_5 = key_status_5;
	key_status_5 = get_sensor_state(4) & 0x80;
	if (key_status_5 && !previous_key_status_5) {
		second_counter = 0;
		touch_counter_5 = 1;
	}
	if(key_status_5){
		second_counter++;
	}
	else if(!key_status_5 && previous_key_status_5){
		if(second_counter > 0 && second_counter < 200 && touch_counter_5 == 1){
			uint8_t dataToSend[3] = {'U', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "U1"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
		}
		second_counter = 0;
		touch_counter_5 = 0;
	}		
}

void touchpin6()
{
	previous_key_status_6 = key_status_6;
	key_status_6 = get_sensor_state(5) & 0x80;
	if (key_status_6 && !previous_key_status_6)
	{
		second_counter_2 = 0;
		touch_counter_6 = 1;	
	}
	if(key_status_6){
		second_counter_2++;
	}
	else if(!key_status_6 && previous_key_status_6){
		if(second_counter_2 > 0 && second_counter_2 < 200 && touch_counter_6 == 1){
			uint8_t dataToSend[3] = {'D', '1'};
			uint8_t crc = calculateCRC(dataToSend, 2);
			SPI_MasterTransmitString(dataToSend);                      // Transmits "D1"
			SPI_MasterTransmit(crc);                                   // Transmits the CRC
		}
		second_counter_2 = 0;
		touch_counter_6 = 0;
	}
}

void SPI_MasterTransmitString(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		SPI_MasterTransmit(str[i]);
		_delay_ms(100);
	}
}

ISR(TIMER1_COMPA_vect) {
	second_counter++;
	second_counter_2++;
}

void retain_fanTouch_sensor_state(void){
	touch_counter_4 = eeprom_read_byte((uint8_t*)EEPROM_ADDR);
	if(touch_counter_4 == 1){
		touch_counter_4 = 1;
		}else{
		touch_counter_4 = 0;
	}
	
	if(touch_counter_4 == 0xFF){
		eeprom_write_byte((uint8_t*)EEPROM_ADDR, 0x00);
	}
}