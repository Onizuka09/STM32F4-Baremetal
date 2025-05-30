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
#define ADC_CH3         (1U<<2)
#define ADC_CH5			(1U<<4)
#define SR_EOC 			(1U<<1)

void init_GPIO(uint8_t Pin)
{

	/* GPIO configuration PA1 */
	// enable clock access to gpioA
	RCC->AHB1ENR |=GPIOA_EN_clk ;
	// PA1 as analog mode (MODER=11)
	GPIOA->MODER |= (1U<<Pin*2);  // pin_num*2
	GPIOA->MODER |= (1U<<((Pin*2) +1) ); // pin_num*2 +1

	/* ADC configuration*/
return ;
}
void init_ADC()
{
	// enable clock access
	RCC->APB2ENR |=ADC_EN_clk ;
	//sequence ch3 , ch5 ch1
	// conversion sequence start ( which channel to start)

	//SQ1 ch3 11
	ADC1->SQR3 |= (1U<<0);

	ADC1->SQR3 |= (1U<<1);
	//SQ2 ch5 101
	ADC1->SQR3 |= (1U<<5);
	ADC1->SQR3 &= ~(1U<<6);
	ADC1->SQR3 |= (1U<<7);
	//SQ3 ch1
	ADC1->SQR3 |= (1U<<10);
	// conversion sequence length ( 3)
	ADC1->SQR1 |= (1U<<20);
	ADC1->SQR1 |= (1U<<21);



	return ;
}
uint32_t Read_ADC1()
{
	 while (!(ADC1->SR & SR_EOC)){}

	 return ADC1->DR ;

}
void Start_conversion()
{
	// set conversion mode (continues conversion)  CONT
	ADC1->CR2 |= (1U<<1);
	// enable ADC Module  ADON
	ADC1->CR2  |= (1U<<0);
	//ADC  start conversion: SWSTART
	ADC1->CR2 |= (1U<<30);
}


