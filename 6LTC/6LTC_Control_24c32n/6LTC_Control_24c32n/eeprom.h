/*
 * eeprom.h
 *
 * Created: 14-09-2024 10:39:18
 *  Author: kjeya
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"
#include "i2c.h"



uint8_t eeprom_read(uint16_t address);
void eeprom_write(uint16_t address, uint8_t data);
//void eeprom_write_states(uint16_t address, states *lastState);


#endif /* EEPROM_H_ */