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
#define CH1_OUTPUT_ENABLE (1U<<0)
#define CH2_OUTPUT_ENABLE (1U<<4)
#define GPIO_B_ENABLE (1U<<18)
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

//Output compare is the ability to trigger an output based on a time stamp in memory, without interrupting the execution of code by a processor or MCU.
void tim3_PB4_output_compare(void)
{
	//RCC for GPIOB
	RCC->AHBENR |= GPIO_B_ENABLE;
	//Enable alternate function mode in PB4
	GPIOB->MODER &= ~(1U<<8); //bitwise OR(|=) to set it to 1
	GPIOB->MODER |= (1U<<9); //bitwise AND(&=), NOT(~) to set it to 0
	//Set PB4 alternate function type to TIM3_CH1 (AF1) 0001:AF1 (index 0 for AFRL index 1 for AFRH)
	GPIOB->AFR[0] |= (1U<<16); //bitwise OR(|=) to set it to 1
	GPIOB->AFR[0] &= ~(1U<<17); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOB->AFR[0] &= ~(1U<<18); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOB->AFR[0] &= ~(1U<<19); //bitwise AND(&=), NOT(~) to set it to 0
	//Enable RCC to Timer 3
	RCC->APB1ENR |= TIM3EN;
	//Set Pre-scaler Value
	TIM3->PSC = 800 - 1; // 8,000,0000/800 = 10,000
	//Set Auto-Reload Value (Period)
	TIM3->ARR = 10000 - 1;
	//Set output compare toggle mode
	TIM3->CCMR1 |= (1U<<4);
	TIM3->CCMR1 |= (1U<<5);
	//Enable timer 3 channel 1 in compare mode
	TIM3->CCER |= CH1_OUTPUT_ENABLE;
	//Clear Counter
	TIM3->CNT = 0;
	//Enable Timer
	TIM3->CR1 |= CR1_CEN;

}
