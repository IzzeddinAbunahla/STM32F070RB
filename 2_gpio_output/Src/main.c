#include "stm32f0xx.h"

#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define PIN5		(1u<<5) //Pin 5 location in GPIO A Register
#define LED_PIN		PIN5


int main (void)
{
	/* 1.Enable clock access to GPIOA*/
		RCC->AHBENR	|= GPIO_A_EN;

		/* 2. Set PA5 as output pin*/
		GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
		GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)
		while(1)
		{
			//3.Toggle PA5
				GPIOA->ODR	^= LED_PIN;
				for(int n=0;n<100000;n++){}
			}
}
