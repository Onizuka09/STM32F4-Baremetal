/*
 * ADC.h
 *
 *  Created on: Jan 12, 2024
 *      Author: moktar
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

#include "stm32f4xx.h"
#define SR_EOC 			(1U<<1)

void init_ADC_it();
uint32_t Read_ADC1();
void Start_conversion();

#endif /* ADC_H_ */
