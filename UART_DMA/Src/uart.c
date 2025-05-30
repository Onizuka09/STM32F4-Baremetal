/*
 * uart.c
 *
 *  Created on: Jan 10, 2024
 *      Author: moktar
 */
#include "uart.h"


#define USART2_en_clk (1U<<17)

#define CR1_TE (1U<<3)

#define CR1_RE (1U<<2)
#define CR1_USART_En (1U<<13)
#define  SR_TXE (1U<<7)  // transmit data register empty (status =>read)


#define APB1_CLK SYS_FREQ
#define SYS_FREQ 16000000


#define CR1_RXNEIE (1U<<5)



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
char USART_read(USART_TypeDef *USARTx)
{
	while  (! ( USART2->SR & SR_RXNE ) ) {} // returns 1 register not empty , 0 if register is empty

//	char data;
	return USARTx->DR;
}

void USART_read_string(USART_TypeDef *USARTx, char *buffer, uint32_t max_length)
{
    char received_char;
    uint32_t index = 0;

    while (index < (max_length - 1)) {
        // Wait until the receive buffer is not empty
        while (!(USARTx->SR & SR_RXNE)) {}

        // Read the received character
        received_char = USARTx->DR;

        // Check if the received character is a newline character
        if (received_char == '\n' || received_char == '\r') {
            break;  // Break the loop if newline character is received
        }

        // Store the received character in the buffer
        buffer[index++] = received_char;
    }

    // Null-terminate the string
    buffer[index] = '\0';

    return ;  // Return the number of characters received
}
void usart2_Rx_init_interrupt()
{
	/*********************** GPIO pin configuration ************************/
	// enable clock access to gpioa
	RCC->AHB1ENR |=GPIOA_en_clk ;
	// set PA3 to alternate function mode (moder = 10)
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7) ;
	// set alterante function type to usart tx (AF07=> 0111) see ref manual in alternate function register (11 10 9 8)
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);
	/*************************configure usart module  *********************************************/
//	 enable clock access to uart 2
	RCC->APB1ENR |= USART2_en_clk ;
//	configure baude rate
	usart_set_baudrate(USART2, APB1_CLK, USART2_BAUDRATE);
	// configure Receive  direction  (Rx) in usart control register 1 , RE: enable receiver
	// the abscence of or operator to set all the other configuration setting to 0 (default value )
 	USART2->CR1 = CR1_RE ;
 	// enable receiver interrupt
 	USART2->CR1 |=CR1_RXNEIE ;
 	// enavle usart2 in NVIC
 	NVIC_EnableIRQ(USART2_IRQn);

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
