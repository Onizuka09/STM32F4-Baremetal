/*
 *this code interrupts the main function each 1 second  to toggole an led
 *
 *
 */
#include "systick.h"
#define GPIOA_en (1U<<0)//enable the clock source (set 1 at pos 0)

#define PIN5 (1U<<5)
#define LED5_pin PIN5
#define LED10_pin (1U<<10)

int main(void)
{
	RCC->AHB1ENR |=GPIOA_en ;
	GPIOA->MODER |= (1U<< 10);
	GPIOA->MODER &= ~(1U<< 11);
	// pin PA10 -> D2
	GPIOA->MODER |= (1U<< 20);
	GPIOA->MODER &= ~(1U<< 21);
	systick_it();
	while (1)
		{

		}
return 0;
}
void SysTick_Handler(void )
{
	GPIOA->ODR^= LED10_pin;

}
