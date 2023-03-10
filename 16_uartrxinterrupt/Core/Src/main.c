#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define PIN5		(1u<<5) //Pin 5 location in GPIO A Register
#define LED_PIN		PIN5

static void exti_callback(void);
static void usart_callback(void);

int main (void)
{
		//Enable clock access to GPIOA
		RCC->AHBENR	|= GPIO_A_EN;
		//Set PA5 as output pin
		GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
		GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)
		//Initialize UART2 Interrupt
		uart2_rxtx_interrupt_init();
		//Initialize PC13 button as an interrupt
		PC13_exti_init();
		while(1)
		{
			printf("Wow 3 seconds have passed... \n\r");
			systickDelayMs(3000);
		}
}

static void exti_callback(void)
{
	printf("BTN Pressed... \n\r");
}

void EXTI4_15_IRQHandler(void)
{
	if ((EXTI->PR & LINE13)!=0) //then interrupt trigger request has occurred
	{
		//Clear PR flag to re-arm it
		EXTI->PR |= LINE13;
		//ISR function (do something...)
		exti_callback();
	}
}
static void usart_callback(void)
{
	int key = USART2->RDR;
	if (key == 'Y') //Constantly checks for the input to be Y even while code is running as opposed to using while and waiting until an input is received
	{
		GPIOA->ODR	^= LED_PIN;
		printf("LED TOGGLE! \n\r");
	}

}

void USART2_IRQHandler(void)
{
	//Check if RXNE is set (Interrupt Trigger)
	if(USART2->ISR & SR_RXNE)
	{
		//Do Interrupt Function
		usart_callback();

	}

}
