/*
 * uart.c
 *
 *  Created on: Jan 10, 2024
 *      Author: moktar
 */
#include "uart.h"


#define GPIOA_en_clk (1U<<0)//enable the clock source (set 1 at pos 0)
#define USART2_en_clk (1U<<17)
#define DMA1_en_clk (1U<<21)
#define DMA1_DIR (1U<<6)


// DMA definition

#define DMA1_S_EN (1U<<0) // stream enable/disable
#define DMA1_MEM_INC (1U<<10)
#define DMA1_CR_TCIE (1U<<4)
#define DMA1_Direct_mode (1U<<2)




// USART definotion
#define CR1_TE (1U<<3)
#define CR1_USART_En (1U<<13)
#define  SR_TXE (1U<<7)  // transmit data register empty (status =>read)
#define USART_CR3_DMAT (1U<<7)

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

void dma1_stream6_ini(uint32_t src,uint32_t dst,uint32_t len)
{
	// enable clk access to DMA
	RCC->AHB1ENR |= DMA1_en_clk;

	// Disable DMA1 Stream6
	DMA1_Stream6->CR =0; // init the CR regsiter
	DMA1_Stream6->CR &=~DMA1_S_EN;
	// Clear all interrupt flags of stream6
	DMA1->HIFCR |= (1U<<16);//CFEIF6
	DMA1->HIFCR |= (1U<<18);//CDMEIF6
	DMA1->HIFCR |= (1U<<19);//CTEIF6
	DMA1->HIFCR |= (1U<<20);//CHTIF6
	DMA1->HIFCR |= (1U<<21);//CTCIF6
	// set the destinatoion buff USART
	DMA1_Stream6->PAR = dst;

	// set the src buff Memroy
	DMA1_Stream6->M0AR = src;
	// set length
	DMA1_Stream6->NDTR = len ;
	// select stream6 CH4
	DMA1_Stream6->CR = (4U << 25);
	// enable memory increlment
	DMA1_Stream6->CR |=DMA1_MEM_INC;
	// configure transfer direct ion memory->peripheral
	DMA1_Stream6->CR |=DMA1_DIR;

	// enable interrutp transfer complete
	DMA1_Stream6->CR |= DMA1_CR_TCIE;
	// Enable Direct mode, Disable FIFO
	DMA1_Stream6->FCR &=~ DMA1_Direct_mode;
	// enable circular mode
	DMA1_Stream6->CR |= (1U<<8);
	// enable DMA1 Steam6
	DMA1_Stream6->CR |=DMA1_S_EN;

	// Enable USART2 transmitter DMA
	USART2->CR3 |=USART_CR3_DMAT;
	// enable INterrupt requet for DMA in NVIC
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
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
