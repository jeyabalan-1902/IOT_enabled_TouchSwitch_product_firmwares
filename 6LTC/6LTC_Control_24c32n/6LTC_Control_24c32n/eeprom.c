/*
 * eeprom.c
 *
 * Created: 14-09-2024 10:38:35
 *  Author: kjeya
 */ 

#include "eeprom.h"

void eeprom_write(uint16_t address, uint8_t data) {
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) | 0);
	i2c_write((address >> 8) & 0xFF);
	i2c_write(address & 0xFF);
	i2c_write(data);
	i2c_stop();
}

uint8_t eeprom_read(uint16_t address) {
	uint8_t data;
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) | 0);
	i2c_write((address >> 8) & 0xFF);
	i2c_write(address & 0xFF);
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) | 1);
	data = i2c_read_nack();
	i2c_stop();
	return data;
}

/*void eeprom_write_states(uint16_t address, states *lastState) {
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) | 0); // Write mode
	i2c_write((address >> 8) & 0xFF);  // High byte of address
	i2c_write(address & 0xFF);         // Low byte of address
	
	uint8_t *dataPtr = (uint8_t*)lastState; // Pointer to the structure
	for (uint8_t i = 0; i < sizeof(states); i++) {
		i2c_write(dataPtr[i]); // Write each byte of the structure
	}
	
	i2c_stop();
}*/


