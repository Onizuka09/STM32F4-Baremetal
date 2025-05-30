/*
 * ADXL345.h
 *
 *  Created on: Jan 30, 2024
 *      Author: moktar
 */

#ifndef ADXL345_H_
#define ADXL345_H_
#include "I2C.h"

#define DEVID_R 			0x00
#define DEVICE_addr 		0x53
#define DATA_Format_R 		0x31
#define POWER_CTRL_R 		0x2D
#define DATA_START_ADDR 	0x32

// constants
#define FOUR_G 				0x01 // set the data format to + or - 4g
#define RESET 				0x00
#define SET_MEASURE_BIT 	0x08 // 0b 00001000

// 4g scale fcator


void ADXL_init();
void ADXL_Read_values(uint8_t reg);

#endif /* ADXL345_H_ */
