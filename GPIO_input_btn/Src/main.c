#include "stm32f4xx.h"
#include <stdint.h>

#define PIN5 (1U<<5)
#define LED_pin PIN5
#define GPIO_PIN_8 (1U<<8)

int main(void)
{
    RCC->AHB1ENR |= (1U<<0);        // Enable GPIOA clock

    // Configure GPIOA pin 5 as output
    GPIOA->MODER |= (1U << 10);
    GPIOA->MODER &= ~(1U << 11);

    // Configure GPIOA pin 8 as input
    GPIOA->MODER &= ~(1U << 16);
    GPIOA->MODER &= ~(1U << 17);

    // Set pin 8 as pull-down
    GPIOA->PUPDR &= ~(1U << 16);
    GPIOA->PUPDR |= (1U << 17);

    while (1)
    {
        if ((GPIOA->IDR & GPIO_PIN_8) == 0)
        {
            // Button not pressed
            GPIOA->BSRR = LED_pin<<16; // Turn on LED
        }
        else
        {
            // Button n pressed
            GPIOA->BSRR = LED_pin ; // Turn off LED
        }
    }

    return 0;
}
