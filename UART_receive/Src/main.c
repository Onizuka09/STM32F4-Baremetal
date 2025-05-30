#include "stm32f4xx.h"
#include <stdint.h>

#include "uart.h"

#define PIN5 (1U<<5)
#define LED_pin PIN5
#define MAX_STRING_LENGTH 50

char key;
char received_string[MAX_STRING_LENGTH];
int main(void)
{
	usart2_Rx_init();
	RCC->AHB1ENR |= GPIOA_en_clk ;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	while (1)
		{
//		key = USART_read(USART2);
//		if (key == '1')
//		{
//			GPIOA->ODR |= LED_pin ;
//		}
//		else if (key =='0' )
//		{
//			GPIOA->ODR &= ~LED_pin;
//		}
		USART_read_string(USART2, received_string , MAX_STRING_LENGTH);
		}

return 0;
}



