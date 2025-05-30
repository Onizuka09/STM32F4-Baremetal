/*
 * uart.c
 *
 *  Created on: Jan 10, 2024
 *      Author: moktar
 */
#include "uart.h"


#define GPIOA_en_clk (1U<<0)//enable the clock source (set 1 at pos 0)
#define USART2_en_clk (1U<<17)

#define CR1_TE (1U<<3)
#define CR1_USART_En (1U<<13)
#define  SR_TXE (1U<<7)  // transmit data register empty (status =>read)

#define APB1_CLK SYS_FREQ
#define SYS_FREQ 16000000



#define PIN5 (1U<<5)
#define LED_pin PIN5


static void usart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t Baudrate );
static uint16_t compute_uart_bd( uint32_t PeriphClk, uint32_t Baudrate );

// this function is used to implement the printf
int __io_putchar(int ch)
{
	USART_write(USART2, ch);
	return ch;
}


void USART_write (USART_TypeDef *USARTx,int ch)
{
	// make sure the transmit data register is empty
	while  (! ( USART2->SR & SR_TXE ) ) {} // returns 0 register not empty , 1 if register is empty
	// write to the transmit data register
	USARTx->DR = (ch & 0xFF); // the DR register is 16 bit 0XFF to make sure to take only the lower 16 bit from the int
	return ;
}
void usart2_tx_init()
{
	/*********************** GPIO pin configuration for tx  ************************/
	// enable clock access to gpioa
	RCC->AHB1ENR |=GPIOA_en_clk ;
	// set PA2 to alternate function mode (moder = 10)
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5) ;
	// set alterante function type to usart tx (AF07=> 0111) see ref manual in alternate function register (11 10 9 8)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	/*************************configure usart module  *********************************************/
	// enable clock access to uart 2
	RCC->APB1ENR |= USART2_en_clk ;
	//configure baude rate
	usart_set_baudrate(USART2, APB1_CLK, USART2_BAUDRATE);
	// configure transfer direction  (Tx) in usart control register 1 , TE: enable tranmitter


	// the abscence of or operator to set all the other configuration setting to 0 (default value )
 	USART2->CR1 = CR1_TE ;
	// enable uart module
	USART2->CR1 |= CR1_USART_En;
}
static void usart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t Baudrate )
{
	USARTx->BRR = compute_uart_bd(PeriphClk,Baudrate);
	return;
}

// funtion that takes bus frequency and baudrate value and calculate a value to be set to the register
static uint16_t compute_uart_bd( uint32_t PeriphClk, uint32_t Baudrate )
		{
			return ((PeriphClk + (Baudrate/2U)) /Baudrate);

		}
