/*
 * ADC.c
 *
 *  Created on: Jan 12, 2024
 *      Author: moktar
 */
#include "ADC.h"
#define ADC_EN_clk 		(1U<<8)
#define GPIOA_EN_clk 	(1U<<0)
#define ADC_CH1 		(1U<<0)
#define SR_EOC 			(1U<<1)

void init_ADC()
{

	/* GPIO configuration PA1 */
	// enable clock access to gpioA
	RCC->AHB1ENR |=GPIOA_EN_clk ;
	// PA1 as analog mode (MODER=11)
	GPIOA->MODER |= (1U<<2);  // pin_num*2
	GPIOA->MODER |= (1U<<3 ); // pin_num*2 +1
	/* ADC configuration*/
	// enable clock access
	RCC->APB2ENR |=ADC_EN_clk ;
	// conversion sequence start ( which channel to start)
	ADC1->SQR3 = ADC_CH1 ;
	// conversion squence length ( how many channel are there and theire sequence in conversion ( ch1 then ch3 then ch2 ... )
	ADC1->SQR1 = 0x00; // 1 conversion = 0000
	// set conversion mode (single conversion)  CONT
	ADC1->CR2 &= ~(1U<<1);
	// enable ADC Module  ADON
	ADC1->CR2  |= (1U<<0);


	return ;
}
uint32_t Read_ADC1()
{
	 while (!(ADC1->SR & SR_EOC)){}

	 return ADC1->DR ;

}
void Start_conversion()
{
	//ADC  start conversion: SWSTART
	ADC1->CR2 |= (1U<<30);
}


