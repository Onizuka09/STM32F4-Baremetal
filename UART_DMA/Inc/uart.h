/*
 * uart.h
 *
 *  Created on: Jan 10, 2024
 *      Author: moktar
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#define USART2_BAUDRATE 9600
#define GPIOA_en_clk (1U<<0)//enable the clock source (set 1 at pos 0)
#define SR_RXNE (1U<<5) // receive data reg is not empty



 void USART_write (USART_TypeDef *USARTx, int ch);
void usart2_Rx_init_interrupt();
char USART_read(USART_TypeDef *USARTx) ;
void USART_read_string(USART_TypeDef *USARTx, char *buffer, uint32_t max_length);
#endif /* UART_H_ */
