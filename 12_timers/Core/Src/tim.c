/*
 * tim.c
 *
 *  Created on: Mar. 5, 2023
 *      Author: Izzel
 */

#include "stm32f0xx.h"
#include "tim.h"

//Timer 3 is in APB
#define TIM3EN	(1U<<1)
#define CR1_CEN	(1U<<0)
/*
 *
 *
 *
 * Update Event = Timer_Clock/(Prescaler+1)(Period+1)
 *
 *
 * Example: at
 * Clock 8MHz
 * Prescaler 800 - 1
 * Period 10000 - 1
 *
 * Update Event = 1Hz or occurs every one second
 *
 */
void tim3_1hz_init(void)
{
	//Enable RCC to Timer 3
	RCC->APB1ENR |= TIM3EN;
	//Set Pre-scaler Value
	TIM3->PSC = 800 - 1; // 8,000,0000/800 = 10,000
	//Set Auto-Reload Value (Period)
	TIM3->ARR = 50000 - 1;
	//Clear Counter
	TIM3->CNT = 0;
	//Enable Timer
	TIM3->CR1 |= CR1_CEN;

}
