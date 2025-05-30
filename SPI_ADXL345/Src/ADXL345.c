/*
 * ADXL345.c
 *
 *  Created on: Jan 30, 2024
 *      Author: moktar
 */

#include "ADXL345.h"



void ADXL_Read(uint8_t adress,uint8_t* data_recv)
{
	uint8_t data[2];
	// set read operation
	adress |=READ_OPERATION;
	// enable multibyte operation
	adress |=MULTI_BYTE_EN;

	// enable salve
	CS_enbale();
	// transmit adress
	SPI_Transmit(&adress, 1);

	//receive data
	SPI_Receive(data_recv,6);

	// disable Slave
	CS_disable();




}
void ADXL_Write(uint8_t adress, uint8_t value)
{
	uint8_t data[2];
// enable multibyte place adress in to buffer
	data[0]= adress | MULTI_BYTE_EN ;
	// place data into buffer
	data[1]= value ;
	// pull CS line low to enable slave
	CS_enbale();
	// transmit data
	SPI_Transmit(data,2);
	// Pull cs line high to disable slave
	CS_disable();
}
// read data registeers (X,Y,Z)

void ADXL_init()
{
	// enable SPI GPIO
	SPI_GPIO_init();
	// config SPI
	SPI_init();

	// set the format range to +/- 4g
	ADXL_Write(DATA_Format_R, FOUR_G);
	// RESET all bits
	ADXL_Write(POWER_CTRL_R, RESET);
	// set power controll measure bit
	ADXL_Write(POWER_CTRL_R, SET_MEASURE_BIT);

}
