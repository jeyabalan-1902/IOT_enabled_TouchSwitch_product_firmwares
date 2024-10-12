/*
 * eeprom.h
 *
 * Created: 18-09-2024 21:05:04
 *  Author: kjeya
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "i2c.h"
#include <avr/io.h>


void eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);



#endif /* EEPROM_H_ */