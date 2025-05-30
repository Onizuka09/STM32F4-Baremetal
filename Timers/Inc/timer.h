/*
 * timer.h
 *
 *  Created on: Jan 14, 2024
 *      Author: moktar
 */

#ifndef TIMER_H_
#define TIMER_H_

#define GPIOA_en (1U<<0)
#define SR_CC1IF (1u<<1)

void tim2_1hrz_init (void );
void timeout_event(int timeout,void (*func_ptr)(void));

// oupytr comapre
void time2_PA5_output_compare_1hrz();
void configure_PA5_AF();

// input capture
void time3_PA6_input_captrue_rising_edge();
void configure_PA6_AF();
int capture_value();


// pwm generation using ouput compare timer 2
void tim2_PA5_pwm_generation(int duty_percent);


#endif /* TIMER_H_ */
