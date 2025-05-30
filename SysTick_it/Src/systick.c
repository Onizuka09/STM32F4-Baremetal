/*
 * systick.c
 *
 *  Created on: Jan 13, 2024
 *      Author: moktar
 */

#include "systick.h"
#define SYS_CLK 16000000 // default clokc source 16Mhz => devided by 1000 to get ms
#define CTRL_en (1U<<0)
#define CTRL_CLK_SRC (1U<<2) // use system clock 1 // external clk is 0
#define CTRL_COUNTFLAG (1U<<16)

void systick_delay_MS(int delay)
{
	// configure systick
	// reload with number of clock per milliseconds
	SysTick->LOAD = (int)(SYS_CLK/1000) ;

	// clear current systeick value register
	SysTick->VAL = 0;
	// enable systik
	SysTick->CTRL |= CTRL_en ;
	// select internal clock source
	SysTick->CTRL |= CTRL_CLK_SRC ;
	// waits for 1ms * delay
	for (int d = 0 ; d<delay ; d ++)
	{
		// waits for on 1m
		while ((SysTick->CTRL & CTRL_COUNTFLAG)== 0) {}

	}
	// disable Systick
	SysTick->CTRL = 0;

	return ;
}


