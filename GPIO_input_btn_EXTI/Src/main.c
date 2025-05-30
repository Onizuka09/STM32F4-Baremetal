//#define STM32F401xE
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>
#define PIN5 (1U<<5)
#define LED_pin PIN5
#define GPIO_PIN_8 (1U<<8)
#define GPIOA_en (1U<<0)

#define SYSCFG_en (1U<<14)

#define EXTI_IMR8 (1U<<8)
#define EXTI_FSTR8 (1U<<8)


void configure_led_pa5()
{

	RCC->AHB1ENR |=GPIOA_en ;
	// set pin 5 as output
	GPIOA->MODER |= (1U<< 10);
	GPIOA->MODER &= ~(1U<< 11);

}




// external btn
void configure_btn_pa8()
{

	RCC->AHB1ENR |=GPIOA_en;

	// set pin 8 as input
    GPIOA->MODER &= ~(1U << 16);
    GPIOA->MODER &= ~(1U << 17);

    // Set pin 8 as pull-down
    GPIOA->PUPDR &= ~(1U << 16);
    GPIOA->PUPDR |= (1U << 17);

}
void pa8_exti_init()
 {
	  // disable global interrupt (good practise)
	 __disable_irq();
	// EXTI is part of SYSCFG , enable clock acces to SYSCFG
	 RCC->AHB2ENR|= SYSCFG_en ;
	 // coneect EXTI line with PA8
	 SYSCFG->EXTICR[2] &= ~(0x0F << 0); // Clear the bits first
	 SYSCFG->EXTICR[2] |= (0x00 << 0);  // Connect EXTI line 8 to PA8
	 // unmask EXTI13
	 EXTI->IMR |=EXTI_IMR8 ;
	 // select falling edge trigger for (interrupt) : 0 for falling trigger , 1: rising trigger
	 EXTI->FTSR |= EXTI_FSTR8 ;
	 // enable EXTI13 line in NVIC
	 NVIC_EnableIRQ(EXTI9_5_IRQn);
	 // enable global intyerrupt
	 __enable_irq();
 }

volatile bool flag= false  ;
int main(void)
{
//configure_btn_pc13();
configure_led_pa5();
configure_btn_pa8();
pa8_exti_init();

while (1)
		{

if (flag )
{
    GPIOA->ODR ^= LED_pin;
flag=false ;
}

		}
return 0;
}

void EXTI9_5_IRQHandler (void)
{
	// check in the pending register which EXTI form 10 to 15 is pending (we need 13)
    if (EXTI->PR & (1U << 8)) {  // Check if EXTI line 8 triggered the interrupt
        EXTI->PR |= (1U << 8);    // Clear the pending bit
        flag= true;
    }
return;
}
