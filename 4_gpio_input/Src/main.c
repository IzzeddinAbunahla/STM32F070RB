#include "stm32f0xx.h"

#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define GPIO_C_EN	(1U<<19) //enable bit 19 in RCC AHB register for port C
#define PIN5		(1u<<5) //Pin 5 location in GPIO A Register
#define PIN13		(1U<<13) //Pin 13 location in GPIO C Register
#define LED_PIN		PIN5
#define BTN_PIN		PIN13

int main (void)
{
	/* 1.Enable clock access to GPIOA*/
		RCC->AHBENR	|= GPIO_A_EN;
		RCC->AHBENR	|= GPIO_C_EN;
	/* 2. Set PA5 as output pin*/
		GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
		GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)
	/* 3. Set PC13 as input pin*/
		GPIOC->MODER &= ~(1U<<26); //bitwise OR(|=)
		GPIOC->MODER &= ~(1U<<27); //bitwise AND(&=), NOT(~)
		while(1)
		{
			//when button is not pressed it is at HIGH
			if(GPIOC->IDR & BTN_PIN)
			{
				GPIOA->BSRR	= LED_PIN; //bit set BS5 turns on led
			}
			else //When button is pressed it is at LOW
			{
				GPIOA->BSRR	= (1U<<21); //bit reset BR5 turns off led
			}
		}
}
