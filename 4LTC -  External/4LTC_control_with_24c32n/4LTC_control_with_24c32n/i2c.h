/*
 * i2c.h
 *
 * Created: 26-08-2024 09:59:40
 *  Author: kjeyabalan
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/twi.h>

uint8_t i2c_read_nack(void);
uint8_t i2c_read_ack(void);
void i2c_write(uint8_t data);
void i2c_stop(void);
void i2c_start(void);
void i2c_init(void);

#endif /* I2C_H_ */