/*
 * eeprom.h
 *
 * Created: 16-08-2024 14:41:47
 *  Author: kjeyabalan
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

void eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);



#endif /* EEPROM_H_ */