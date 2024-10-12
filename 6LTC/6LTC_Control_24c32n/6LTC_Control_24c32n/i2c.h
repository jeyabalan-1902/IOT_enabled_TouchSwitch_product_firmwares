/*
 * i2c.h
 *
 * Created: 13-09-2024 17:03:09
 *  Author: kjeya
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "main.h"
uint8_t i2c_read_nack(void);
uint8_t i2c_read_ack(void);
void i2c_write(uint8_t data) ;
void i2c_stop(void);
void i2c_start(void);
void i2c_init(void);





#endif /* I2C_H_ */