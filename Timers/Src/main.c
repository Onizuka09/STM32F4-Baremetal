//#define STM32F401xE
/*
 * This code will toggle the LED each 1s
 *
 *
 */
#include "stm32f4xx.h"
#include <stdint.h>
#include "timer.h"

#define GPIOA_en (1U<<0)//enable the clock source (set 1 at pos 0)

#define PIN5 (1U<<5)
#define LED_pin PIN5

void configure_PA5_Output()
{
	RCC->AHB1ENR |=GPIOA_en ;
		GPIOA->MODER |= (1U<< 10);
		GPIOA->MODER &= ~(1U<< 11);
}
void toggle_LED(void)
{
	GPIOA->ODR^= LED_pin;

}
int time_stamp=0;
int main(void){
//configure_PA5_Output();
//	tim2_1hrz_init();
configure_PA5_AF();
//configure_PA6_AF();
//time2_PA5_output_compare_1hrz();
//time3_PA6_input_captrue_rising_edge();
	while (1)
		{
		//			timeout_event(3, toggle_LED);
//		time_stamp = capture_value();
		tim2_PA5_pwm_generation(0);
		}
return 0;
}
