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


 void USART_write (USART_TypeDef *USARTx, int ch);
void usart2_tx_init();

#endif /* UART_H_ */
