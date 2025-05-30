/*
 * SPI.c
 *
 *  Created on: Jan 16, 2024
 *      Author: moktar
 */


#include "SPI.h"

#include "stm32f4xx.h"
#define SPI1_en (1U<<12)
#define GPIOA_en (1U<<0)
#define CR1_BR (1U<<3)

#define SR_TXE (1U<<1)
#define SR_BUSY (1U<<7)

#define SR_RXNE (1U<<0)

/*
SPI1_MOSI: PA7
smpi1_Miso : PA6

SPI1_SCK : PA5
SPI1_SS : PA9

*/
void Config_GPIOA_pin(int pin)
{

	// set alternate function
	GPIOA->MODER &= ~(1U << (pin*2) ) ;
	GPIOA->MODER |= (1U << ( (pin*2) + 1) );

	// set alternate function type AF5 (101)
	GPIOA->AFR[0] |= (5U<< (pin*4) );

}
void SPI_GPIO_init()
{

	// enable GPIOA clk
	RCC->AHB1ENR |=GPIOA_en;

	// config pinA9 as OUPUT
	GPIOA->MODER |= (1U << 18 ) ;
	GPIOA->MODER &= ~(1U << 19);

	// set PA5
	Config_GPIOA_pin(5);
	// set PA6
	Config_GPIOA_pin(6);
	// set PA7
	Config_GPIOA_pin(7);
}
void SPI_init()
{
	//enable CLK SPI
	RCC->APB2ENR |= SPI1_en;
	// set SPI clock baude rate conftrol by setting a prescaler ( 4)
	SPI1->CR1  |= (1U<<3);
	SPI1->CR1  &= ~(1U<<4);
	SPI1->CR1  &= ~(1U<<5);
	// set CPOL to 1 and set CPHA to 1
	SPI1->CR1  |= (1U<<0);
	SPI1->CR1  |= (1U<<1);
	// enable full duplex , RXONLY
	SPI1->CR1  &= ~(1U<<10);
	// set MSB first
	SPI1->CR1 &= ~ (1U<<7);
	// set SPI as master mode MSTR
	SPI1->CR1  |= (1U<<2);
	// set data size DFF data frame 8 bit mode
	SPI1->CR1  &= ~(1U<<11);
	// set software slave mabnagement
	// enable SSM bit , set  SSi
	SPI1->CR1  |= (1U<<8);
	SPI1->CR1  |= (1U<<9);
// enable SPI mode SPIE
	SPI1->CR1  |= (1U<<6);

}
/*
 * uint8_t data : buffer that has the data
 * uint8_t size: size of buffer
 */



void SPI_Transmit (uint8_t* data, uint8_t size )
{

	uint32_t i=0;
	uint8_t tmp =0;
	while (i<size)
	{
		// wait until tranmit bus is mepty , TXE
		while ( ( SPI1->SR & SR_TXE) == 0 ) {}

		// write data
		SPI1->DR = data[i];
		i++;
	}
	// wait until tranmit bus is mepty , TXE
			while ( ( SPI1->SR & SR_TXE) == 0 ) {}
	// wait for BUSY flag is set
while ( ( SPI1->SR & SR_BUSY) ) {}
	// clear overflow flag by reading  DR and SR regist
	tmp = SPI1->DR ;
	tmp = SPI1->SR ;


}

/*
 * uint8_t data : buffer to store the data
 * uint8_t size: size of buffer
 */


void SPI_Receive (uint8_t* data, uint8_t size )
{

	while (size)
	{
		// send dummy data
		SPI1->DR = 0;

		// wait for RXNE to be set
		while ( ( SPI1->SR & SR_RXNE)==0 ) {}
		// read the data from dr
		*data++ = SPI1->DR ;
		size -- ;
	}
	}

void CS_enbale (void )
{
	GPIOA->ODR &= ~(1U<<9);
}

void CS_disable (void )
{
	GPIOA->ODR |= (1U<<9);
}
