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
#define TIM15EN	(1U<<16)
#define CR1_CEN	(1U<<0)
#define CH1_OUTPUT_ENABLE (1U<<0)
#define GPIO_B_ENABLE (1U<<18)
#define GPIO_A_ENABLE (1U<<17)
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
	GPIOB->MODER &= ~(1U<<8); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOB->MODER |= (1U<<9); //bitwise OR(|=) to set it to 1
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
void tim15_PA2_input_capture(void)
{
		//Enable clock access to GPIO A
		RCC->AHBENR |= GPIO_A_ENABLE;
		//Enable RCC to Timer 15
		RCC->APB2ENR |= TIM15EN;
		//Enable alternate function mode in PA2
		GPIOA->MODER &= ~(1U<<4); //bitwise AND(&=), NOT(~) to set it to 0
		GPIOA->MODER |= (1U<5); //bitwise OR(|=) to set it to 1
		//Set PA2 alternate function type to TIM15_CH1 (AF0) 0000:AF0 (index 0 for AFRL index 1 for AFRH)
		GPIOA->AFR[0] &= ~(1U<<8); //bitwise AND(&=), NOT(~) to set it to 0
		GPIOA->AFR[0] &= ~(1U<<9); //bitwise AND(&=), NOT(~) to set it to 0
		GPIOA->AFR[0] &= ~(1U<<10); //bitwise AND(&=), NOT(~) to set it to 0
		GPIOA->AFR[0] &= ~(1U<<11); //bitwise AND(&=), NOT(~) to set it to 0
		//Set Pre-scaler Value
		TIM15->PSC = 4800 - 1; // 8,000,0000/800 = 10,000
		//Set CH1 to input capture mode
		TIM15->CCMR1 &= ~(1U<<1); //0
		TIM15->CCMR1 |= (1U<<0); //1
		//set CH2 to capture at every rising edge
		//Enable timer 3 channel 2 in capture mode
		TIM15->CCER |= CH1_OUTPUT_ENABLE;
		//Enable Timer
		TIM15->CR1 |= CR1_CEN;

}
