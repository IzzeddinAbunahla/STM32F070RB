/*
 * systick.c
 *
 *  Created on: Mar. 4, 2023
 *      Author: Izzel
 */
#include "stm32f0xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VALUE 8000 //since our clock is 8MHz (cycles per sec)
#define SYSTICK_ENABLE (1U<<0) //to set the enable bit to 1
#define SYSTICK_CLKSRC (1U<<2) //to set the clock source bit to 1 to use internal clock
#define SYSTICK_COUNTFLAG (1U<<16) //countflag bit at 1

void systickDelayMs(int delay)
{
	//Reload with number of clocks per milisecond in reload value register
	SysTick->LOAD = SYSTICK_LOAD_VALUE;
	//Clear Systick current value register
	SysTick->VAL = 0;
	//Enable Systick and select internal processor clock in control and status register
	SysTick->CTRL = SYSTICK_ENABLE | SYSTICK_CLKSRC;

	for(int i=0;i<delay;i++)
	{
		//wait until the count flag returns 1 if timer counted to 0 since the last read of this register.
		while((SysTick->CTRL & SYSTICK_COUNTFLAG) == 0){}
		//Software can use COUNTFLAG to determine if SysTick has ever counted to zero. 1 = counter enabled. When ENABLE is set to 1, the counter loads the RELOAD value from the SYST_RVR register and then counts down. On reaching 0, it sets the COUNTFLAG to 1
		//it counts down from 8000 every time then when it reaches 0 countflag is set to 1 and this breaks the while loop
	}

	SysTick->CTRL = 0;
}
