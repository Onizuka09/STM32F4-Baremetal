/*
 * timer.c
 *
 *  Created on: Jan 14, 2024
 *      Author: moktar
 */

#include "stm32f4xx.h"

#define TIMER2EN (1U<<0)
#define TIMER3EN (1u<<1)
#define CR1_CEN (1U<<0)// enable timer2
#define APB_freq  16000000
#define SR_UIF (1U<<0)

#define OC1M_toggle (3U<<4)//(1U<<4) | (1U<<5)
#define CC1E_compare_capture (1U<<0)

#define SR_CC1IF (1u<<1)


#define CCR1_CC1S_IC (1U<<0)
//enable the clock source (set 1 at pos 0)
#define GPIOA_en (1U<<0)

#define OC1M_pwm (6U<<4)




// a function that generate a timeout each 1 second
void tim2_1hrz_init (void )

{
	//enable clock access to timer2
	RCC->APB1ENR |=TIMER2EN ;
	//set prescaler value
    TIM2->PSC = 1600 -1 ;  // 16 MHz / 1600 = 10,000 Hz
	//set auto reload value
    TIM2->ARR = 10000 -1 ;// 10,000 Hz / 10,000  = 1 Hz (1 s)
	//clear counter
    TIM2->CNT = 0;

	//enable timer
	TIM2->CR1 |= CR1_CEN ;

}


// this is a function expects a pointer to function and it will create a timeout based on the user input( timeout)

void timeout_event(int timeout,void (*func_ptr)(void))
{

	for (int t=0;t<timeout;t++)
	{
		while ( (TIM2->SR & SR_UIF)==0) {}
		TIM2->SR &= ~SR_UIF ;
	}

	func_ptr();



}

// configure PINA5 to AF timer2 channel 1
void configure_PA5_AF(){
// enable clock acces to GPIOA
	RCC->AHB1ENR |=GPIOA_en ;
	// set PA5 to ALternate fucntion
	GPIOA->MODER &= ~(1U<< 10);
	GPIOA ->MODER |= (1U<< 11);
	// set alternate function type to AF01 == AF1 low AFRL 5
	GPIOA->AFR[0] |=(1U<<20);  // pin 5*4
	GPIOA->AFR[0] &=~(1U<<21);  // 5*4 +1
	GPIOA->AFR[0] &=~(1U<<22);  // 5*4 +2
	GPIOA->AFR[0] &=~(1U<<23);  // 5*4 +3

}
// generate a toogle signle when a pereiod of 1 second is done using ouput compare mode
void time2_PA5_output_compare_1hrz() // 1 second
{

	/* timer2 configuration  */
	//enable clock access to timer2
	RCC->APB1ENR |=TIMER2EN ;
	//set prescaler value
    TIM2->PSC = 1600 -1 ;  // 16 MHz / 1600 = 10,000 Hz
	//set auto reload value
    TIM2->ARR = 10000 -1 ;// 10,000 Hz / 10,000  = 1 Hz (1 s)


	// set output compare toggle mode
	TIM2->CCMR1 |= OC1M_toggle ;
	// enable compare mode in tim2_ch1
	TIM2->CCER |= CC1E_compare_capture ;

	//enable timer
	TIM2->CR1 |= CR1_CEN ;

}


void configure_PA6_AF(){
// enable clock acces to GPIOA
	RCC->AHB1ENR |=GPIOA_en ;
	// set PA6 to ALternate fucntion
	GPIOA->MODER &= ~(1U<< 12);
	GPIOA ->MODER |= (1U<< 13);
	// set alternate function type to AF02 == AF1 low AFRL 6
	GPIOA->AFR[0] &=~(1U<<24);  // pin 6*4
	GPIOA->AFR[0] |= (1U<<25);  // 6*4 +1
	GPIOA->AFR[0] &=~(1U<<26);  // 6*4 +2
	GPIOA->AFR[0] &=~(1U<<27);  // 6*4 +3

}
void time3_PA6_input_captrue_rising_edge() // 1 second
{

	/* timer2 configuration  */
	//enable clock access to timer2
	RCC->APB1ENR |=TIMER3EN ;
	//set prescaler value
    TIM3->PSC = 16000 -1 ;  // 16 MHz / 16000 = 1,000 Hz

	// set CH1 input capture
	TIM3->CCMR1 |= CCR1_CC1S_IC ;
	// set ch1 to capture at rising edge
	TIM3->CCER |= CC1E_compare_capture ;


	//enable timer
	TIM3->CR1 |= CR1_CEN ;

}
int capture_value(){
	// wait until edge is captured
	while( ( TIM3->SR & SR_CC1IF) == 0){}
	return TIM3->CCR1 ;

}

// pwm generation on PA
void tim2_PA5_pwm_generation(int duty_percent)
{


	/* timer2 configuration  */
	//enable clock access to timer2
	RCC->APB1ENR |=TIMER2EN ;
	//set prescaler value
    TIM2->PSC = 1600 -1 ;  // 16 MHz / 1600 = 10,000 Hz
	//set auto reload value
    TIM2->ARR = 10000 -1 ;// 10,000 Hz / 10,000  = 1 Hz (1 s)
    // reset counter value
    TIM2->CNT = 0;
	// set pwm mode ( mode 1) 110 to
	TIM2->CCMR1 |= OC1M_pwm ;
	// set duty cycle to 1/3 of the period (10000 /3)
	TIM2->CCR1= 1000-1 ;
	// enable compare mode in tim2_ch1
	TIM2->CCER |= CC1E_compare_capture ;
	//enable timer
	TIM2->CR1 |= CR1_CEN ;



}
