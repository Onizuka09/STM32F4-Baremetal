/*
 * I2C.c
 *
 *  Created on: Jan 16, 2024
 *      Author: moktar
 */
#include "I2C.h"


#define I2C1_en (1U<<21)
#define GPIOB_en (1U<<1)

#define I2C_100KHz 80
#define I2C_SM_MAX_RISE_TIME 17// standard mode maximum rise time (17)



#define CR1_SWRST (1U<<15)
#define CR1_PE (1U<<0) // peripheral Enable
#define SR2_BUSY (1U<<1)// bus busy
#define CR1_START (1U<<8)
#define SR1_SB (1U<<0)
#define SR1_ADDR (1U<<1)
#define SR1_TXE (1U<<7)
#define CR1_ACK (1U<<10)
#define SR1_RXNE (1U<<6)
#define CR1_Stop (1U<<9)
#define SR1_BTF (1U<<2)
/*
PB -- SCL
PB9 -- SDA
*/
void pin_GPIOB_config(int pin)
{
// set alternate function
	GPIOB->MODER &= ~(1U << (pin*2) ) ;
	GPIOB->MODER |= (1U << ( (pin*2) + 1) );
	//configure PB8  and PB9 to open drain (I2C requires this
	GPIOB->OTYPER |= (1U<< pin);
	// configure pin to pullup
	GPIOB->PUPDR |= (1U << (pin*2) ) ;
	GPIOB->PUPDR &= ~(1U << ( (pin*2) + 1) );


}
void I2C1_init()
{
	/*GPIO config  */
	// enable clock access to port B
	RCC->AHB1ENR |=GPIOB_en ;
	// configure PB8  and PB9 to AF
	pin_GPIOB_config(8);
	pin_GPIOB_config(9);
	// set alternate function 8 and 9 type AF4 (100)
	GPIOB->AFR[1] |= (4U<< 0) ;
	// set alternate function type AF4 (100)
	GPIOB->AFR[1] |= (4U<< 4);
	/*I2C config  */
	// enable clock access to I2C1
	RCC->APB1ENR |= I2C1_en ;
	// rest i2c
	I2C1->CR1 |=I2C_CR1_SWRST ;
	// disable rest mode
	I2C1->CR1 &=~I2C_CR1_SWRST ;
	// config the periph clock 16MHz
	I2C1->CR2 |= (1U<<4);
	// set the I2C mode ( standard or fast ) which depends on the periph clock: 100KHZ
	I2C1->CCR = I2C_100KHz ;
	//set maximum rise mode 17
	I2C1->TRISE = I2C_SM_MAX_RISE_TIME;
	// enable I2C
	I2C1->CR1 |= CR1_PE ;


}
// function reads a byte from slave device
/*
 *  arg1: slave_adr
 *  arg2: memory adr within the slave we won't to read from
 *  arg3: a ptr of a variable that stores the data to read
 *   */
// read
// first you need to set the address in memory in the slave you want to read from  ( I2C write operation)
// read from the address we specified

void I2C_READ_Byte(char saddr, char maddr, char *data )
{
	volatile int tmp;
	// wait until bus not busy SR register
	while ( (I2C1->SR2 & SR2_BUSY )){}

		// generate  start condition in CR1
		I2C1->CR1 |=CR1_START ;
		// wait until start bit is set (
		while (( I2C1->SR1 & SR1_SB )==0){}

		// transmit slavle adress + write
		// the data register is 8 bit register: 7 bit for the adress, shift by , set the least bit to be write 1 or read mode 0
		I2C1->DR = saddr <<1; //
		// wait until address falg is set, a flag will be set the SR reg ADDR
		while (( I2C1->SR1 & SR1_ADDR )==0){}
		// clear the flag by reading by the SR2
//		tmp = I2C1->SR1 ;
		tmp = I2C1->SR2 ;
		// send memory address
		I2C1->DR = maddr;
		// wait  data is transferred
		while (( I2C1->SR1 & SR1_TXE )==0){}

		//  -- ---- READ ---
		// generated a restart condition
		I2C1->CR1 |=CR1_START ;
		// wait until start bit is set (
		while (( I2C1->SR1 & SR1_SB )==0){}
		// set slave address + READ
		I2C1->DR = saddr <<1 | 1;
		// wait until address falg is set, a flag will be set the SR reg ADDR
		while (( I2C1->SR1 & SR1_ADDR )==0){}
		//disable the ACK
		I2C1->CR1 &= ~CR1_ACK ;
		// clear addr flag
//		tmp = I2C1->SR1 ;
		tmp = I2C1->SR2 ;

// generate a stop after data received
		I2C1->CR1 |= CR1_Stop ;
		// wait until data is received
		while (( I2C1->SR1 & SR1_RXNE )==0){}
		// read data reg and stored
		*data++ = I2C1->DR;
}
// read multiple bytes
// n number of bytes to read
void I2C_burst_read(char saddr, char maddr,int n,  char *data)
{
	volatile int tmp;
	while ( (I2C1->SR2 & SR2_BUSY )){}

		// generate  start condition in CR1
		I2C1->CR1 |=CR1_START ;
		// wait until start bit is set (
		while (( I2C1->SR1 & SR1_SB )==0){}

		// transmit slavle adress + write
		I2C1->DR = saddr <<1; // address on 7 bit and MSB first somthon like that
		// wait until address falg is set, a flag will be set the SR reg ADDR
		while (( I2C1->SR1 & SR1_ADDR )==0){}
		// clear the flag by reading by the SR2
//		tmp = I2C1->SR1 ;
		tmp = I2C1->SR2 ;
		// send memory address
		I2C1->DR = maddr;
		// wait  data is transferred
		while (( I2C1->SR1 & SR1_TXE )==0){}

		//  -- ---- READ ---
		// generated a restart condition
		I2C1->CR1 |=CR1_START ;
		// wait until start bit is set (
		while (( I2C1->SR1 & SR1_SB )==0){}
		// set slave address + READ
		I2C1->DR = saddr <<1 | 1;
		// wait until address falg is set, a flag will be set the SR reg ADDR
		while (( I2C1->SR1 & SR1_ADDR )==0){}
		//clear the ADDR flag
//		tmp = I2C1->SR1 ;
		tmp = I2C1->SR2 ;
		//enable the ACK
		I2C1->CR1 |= CR1_ACK ;

		while (n>0U)
		{
			// check if n ==1
			if (n==1)
			{
				//disable the ACK
				I2C1->CR1 &= ~CR1_ACK ;
				// generate a stop after data received
				I2C1->CR1 |= CR1_Stop ;
				// wait until data is received
				while (( I2C1->SR1 & SR1_RXNE )==0){}
				// read data reg and stored
				*data++ = I2C1->DR;
				break;
			}
			else {
				// wait until data arrived
				while (( I2C1->SR1 & SR1_RXNE )==0){}
				// read data
				(*data++) = I2C1->DR;

				n--;
			}

		}
}
// function write byte from slave device
/*
 *  arg1: slave_adr
 *  arg2: memory adr within the slave we won't to read from
 *  arg3: a ptr of a variable that stores the data to read
 *  n: number of bytes to write
 *   */
void I2C_BurstWrite(char saddr,char maddr,int n,char *data)
{
	volatile int tmp;
	while ( (I2C1->SR2 & SR2_BUSY )){}

		// generate  start condition in CR1
		I2C1->CR1 |=CR1_START ;
		// wait until start bit is set (
		while (( I2C1->SR1 & SR1_SB )==0){}

		// transmit slavle adress + write
		I2C1->DR = saddr <<1; // address on 7 bit and MSB first somthon like that

		// wait until address falg is set, a flag will be set the SR reg ADDR
		while (( I2C1->SR1 & SR1_ADDR )==0){}

		// clear the flag by reading by the SR2
		tmp = I2C1->SR2 ;
		// send memory address
		I2C1->DR = maddr;
		// transmit all the bytes
		for (int i=0;i<n;++i)
		{
			// wait the dr register is empty
			while (( I2C1->SR1 & SR1_TXE )==0){}
			// stransmit data
			I2C1->DR = *data++ ; // data[i]
		}
		// wait until BTF is set (byte transfer finished
		while (( I2C1->SR1 & SR1_BTF )==0){}

		// generate a stop after data received
		I2C1->CR1 |= CR1_Stop ;

}
