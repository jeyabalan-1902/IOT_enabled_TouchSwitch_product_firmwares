/*
 * spiDataProcess.h
 *
 * Created: 26-08-2024 12:59:57
 *  Author: kjeyabalan
 */ 


#ifndef SPIDATAPROCESS_H_
#define SPIDATAPROCESS_H_

#include <avr/io.h>
#include "main.h"

extern const char* command;
void SPIprocessCommand(const char* command);

#endif /* SPIDATAPROCESS_H_ */