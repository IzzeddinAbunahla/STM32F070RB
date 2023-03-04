
#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"

#define GPIOAEN	(1U<<17)
#define GPIOA_5	(1U<<5)

#define LED_PIN	GPIOA_5
char key;

int main (void)
{
	/* 1.Enable clock access to GPIOA*/
	RCC->AHBENR	|= GPIOAEN;

	/* 2. Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
	GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)

	uart2_rxtx_init();

		while(1)
		{
			key = uart2_read();
			if (key == '1')
			{
				printf("Correct!\n\r");
				GPIOA->ODR	|= LED_PIN;
			}
			else
			{
				printf("Incorrect!\n\r");
				GPIOA->ODR	&= ~LED_PIN;
			}
		}
}
