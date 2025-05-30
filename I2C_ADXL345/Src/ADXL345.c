/*
 * ADXL345.c
 *
 *  Created on: Jan 30, 2024
 *      Author: moktar
 */

#include "ADXL345.h"

char data;
uint8_t data_rec[6];
void ADXL_Read_ADRR(uint8_t reg)
{
	I2C_READ_Byte(DEVICE_addr, reg, &data);
}
void ADXL_Write(uint8_t reg, char value)
{
	char data[1];
	data[0]=value;
	I2C_BurstWrite(DEVICE_addr,reg, 1, data);
}
// read data registeers (X,Y,Z)
void ADXL_Read_values(uint8_t reg)
{
	I2C_burst_read(DEVICE_addr, reg, 6,(char*) data_rec);
}
void ADXL_init()
{
	// enable I2C
	I2C1_init();
	/* Read the DEVID shoudl return 0xE5*/
	ADXL_Read_ADRR(DEVID_R);

	// set the format range to +/- 4g
	ADXL_Write(DATA_Format_R, FOUR_G);
	// RESET all bits
	ADXL_Write(POWER_CTRL_R, RESET);
	// set power controll measure bit
	ADXL_Write(POWER_CTRL_R, SET_MEASURE_BIT);

}
