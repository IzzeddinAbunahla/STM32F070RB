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
static void exti_callback(void);

int main (void)
{
		char message[8] = "Hi Frend";

		//Enable clock access to GPIOA
		RCC->AHBENR	|= GPIO_A_EN;
		//Set PA5 as output pin
		GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
		GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)
		//Initialize UART2
		uart2_rxtx_init();
		//Initialize DMA on USART2
		dma_usart2_init((uint32_t)message,(uint32_t)(&USART2->TDR),8);
		while(1)
		{

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

static void dma_callback(void)
{
	GPIOA->ODR	^= LED_PIN;
}

void DMA1_Channel4_5_IRQHandler(void) //Not Working
{
	//Check the transfer complete flag (interrupt trigger)
	if(DMA1->ISR & DMA_TCIF4)
	{
		//clear flag
		DMA1->IFCR |= DMA_IF_CTCIF4;
		//function
		dma_callback();
	}
}
