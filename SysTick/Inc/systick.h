/*
 * systick.h
 *
 *  Created on: Jan 13, 2024
 *      Author: moktar
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx.h"
#include <stdint.h>

void systick_delay_MS(int delay);
void systick_it(void);
#endif /* SYSTICK_H_ */
