/*
 * i2c.c
 *
 * Created: 16-08-2024 14:11:25
 *  Author: kjeyabalan
 */ 

#include "i2c.h"
#include <util/twi.h>

void i2c_init(void) {
	TWSR0 = 0x00;
	TWBR0 = 0x48;
	TWCR0 = (1<<TWEN);
}

void i2c_start(void) {
	TWCR0 = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT);
	while (!(TWCR0 & (1<<TWINT)));
}

void i2c_stop(void) {
	TWCR0 = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT);
}

void i2c_write(uint8_t data) {
	TWDR0 = data;
	TWCR0 = (1<<TWEN) | (1<<TWINT);
	while (!(TWCR0 & (1<<TWINT)));
}

uint8_t i2c_read_ack(void) {
	TWCR0 = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
	while (!(TWCR0 & (1<<TWINT)));
	return TWDR0;
}

uint8_t i2c_read_nack(void) {
	TWCR0 = (1<<TWEN) | (1<<TWINT);
	while (!(TWCR0 & (1<<TWINT)));
	return TWDR0;
}
