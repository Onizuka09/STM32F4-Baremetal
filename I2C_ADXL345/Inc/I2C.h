/*
 * I2C.h
 *
 *  Created on: Jan 16, 2024
 *      Author: moktar
 */

#ifndef I2C_H_
#define I2C_H_
#include "stm32f4xx.h"

void I2C1_init();
void I2C_READ_Byte(char saddr, char maddr, char *data );
void I2C_burst_read(char saddr, char maddr,int n,  char *data);
void I2C_BurstWrite(char saddr,char maddr,int n,char *data);


#endif /* I2C_H_ */
