#include "stm32f4xx.h"
#include <stdint.h>

#include "uart.h"

#define PIN5 (1U<<5)
#define LED_pin PIN5
#define MAX_STRING_LENGTH 50

char received_string[MAX_STRING_LENGTH];
void config_led_pa5()
{
	RCC->AHB1ENR |= GPIOA_en_clk ;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}
int main(void)
{
	config_led_pa5();
	usart2_Rx_init_interrupt();
	while (1)
		{

//		USART_read_string(USART2, received_string , MAX_STRING_LENGTH);
		}

return 0;
}

static void USART2_Callback(void )

{
	char key;
	key = USART2->DR ;
	if (key == '1')
	{
		GPIOA->ODR |= LED_pin ;
	}
	else if (key =='0' )
	{
		GPIOA->ODR &= ~LED_pin;
	}

}

void USART2_IRQHandler(void)
{
	if   ( ( USART2->SR & SR_RXNE ) ) {

		USART2_Callback();
	}
}
