#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"


#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define PIN5		(1u<<5) //Pin 5 location in GPIO A Register
#define LED_PIN		PIN5

int main (void)
{
		//Enable clock access to GPIOA
		RCC->AHBENR	|= GPIO_A_EN;
		//Set PA5 as output pin
		GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
		GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)
		//Initialize UART
		uart2_rxtx_init();

		while(1)
		{
				printf("5 seconds has passed... \n\r");
				GPIOA->ODR	^= LED_PIN;
				systickDelayMs(5000);

		}
}
