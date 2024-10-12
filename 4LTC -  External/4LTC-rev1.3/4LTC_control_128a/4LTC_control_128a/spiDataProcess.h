/*
 * spiDataProcess.h
 *
 * Created: 18-09-2024 21:09:44
 *  Author: kjeya
 */ 


#ifndef SPIDATAPROCESS_H_
#define SPIDATAPROCESS_H_


#include <avr/io.h>
#include "main.h"

void SPI_init_slave();
extern const char* command;
void SPIprocessCommand(const char* command);



#endif /* SPIDATAPROCESS_H_ */