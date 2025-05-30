//#define STM32F401xE
#include "stm32f4xx.h"
#include <stdint.h>
#define GPIOA_en (1U<<0)//enable the clock source (set 1 at pos 0)

#define PIN5 (1U<<5)
#define LED_pin PIN5


int main(void)
{
	RCC->AHB1ENR |=GPIOA_en ;
	GPIOA->MODER |= (1U<< 10);
	GPIOA->MODER &= ~(1U<< 11);

	while (1)
		{
				GPIOA->BSRR = LED_pin ;// set pin 1
				for (int i=0;i<1000000;i++){}

				GPIOA->BSRR =  (1U<<21);// reset pin 0
				for (int i=0;i<1000000;i++){}
		}
return 0;
}
