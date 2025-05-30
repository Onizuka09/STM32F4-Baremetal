/*
 * SPI.h
 *
 *  Created on: Jan 16, 2024
 *      Author: moktar
 */

#ifndef SPI_H_
#define SPI_H_
#include "stm32f4xx.h"

void SPI_GPIO_init();
void SPI_init();
void SPI_Transmit (uint8_t* data, uint8_t size );

void SPI_Receive (uint8_t* data, uint8_t size );
void CS_enbale (void);
void CS_disable (void );

#endif /* SPI_H_ */
