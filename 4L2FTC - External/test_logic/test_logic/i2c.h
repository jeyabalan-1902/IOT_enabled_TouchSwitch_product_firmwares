/*
 * i2c.h
 *
 * Created: 14-08-2024 22:22:55
 *  Author: kjeyabalan
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/twi.h>

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);



#endif /* I2C_H_ */