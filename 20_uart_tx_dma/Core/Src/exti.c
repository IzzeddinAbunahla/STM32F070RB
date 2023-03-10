/*
 * exti.c
 *
 *  Created on: Mar. 6, 2023
 *      Author: Izzel
 */
#include "exti.h"
#include "stm32f0xx.h"

#define GPIO_C_EN	(1U<<19)
#define SYSCFG_EN	(1U<<0)
#define IM13		(1U<<13)
#define FT13		(1U<<13)

void PC13_exti_init(void)
{
	// OPTIONAL (GOOD PRACTICE) Disable global interrupts
	__disable_irq(); //comes with cortexm0.h
	//Enable Clock Access For GPIO C
	RCC->AHBENR |= GPIO_C_EN;
	//EXTI is part of the SYSCONFIG module and we need to give it clock access
	RCC->APB2ENR |= SYSCFG_EN;
	//Set PC13 as input
	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27);
	//Select Port C for EXTI13 (SYSCFG external interrupt configuration register 4)
	SYSCFG->EXTICR[3] &= ~(1<<4); //0
	SYSCFG->EXTICR[3] |= (1<<5); //1
	SYSCFG->EXTICR[3] &= ~(1<<6); //0
	//Un-mask EXTI13 (unmask means uncovered they are covered by default)
	EXTI->IMR |= IM13;
	//Select falling edge trigger (can also be rising edge if you want)
	EXTI->FTSR |= FT13;
	//Enable EXTI line in NVIC
	NVIC_EnableIRQ(EXTI4_15_IRQn); //check Reference manual for location
	//comes with cortexm0.h
	//Enable Global Interrupts
	__enable_irq(); //comes with cortexm0.h
}

