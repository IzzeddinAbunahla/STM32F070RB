#include "stm32f0xx.h"
#include <stdint.h>

#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define UART2EN		(1U<<17)

#define SYS_FREQ	8000000 //Clock speed of the STM32F070RB MCU
#define APB1_CLK	SYS_FREQ

#define UART_BAUDRATE 9600 //Baud rate or bits per second
#define CR1_TE		(1U<<3)
#define CR1_UART_EN	(1U<<0)
#define SR_TXE		(1U<<7)

//Function prototypes;
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_BD(uint32_t PeriphClk, uint32_t Baudrate);
void uart2_write(int ch);
void uar2_tx_init(void);

int main (void)
{
		uar2_tx_init(); //Initialize TX of the MCU
		while(1)
		{
			uart2_write('Y'); //Send this character via UART serial
		}
}

void uar2_tx_init(void)
{
	/*Configure UART GPIO pin*/
	//Enable clock access to GPIOA
	RCC->AHBENR	|= GPIO_A_EN;
	//set TX pin (PA2) mode to alternate function mode
	GPIOA->MODER &= ~(1U<<4); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->MODER |= (1U<<5); //bitwise OR(|=) to set it to 1
	//set PA2 alternate function type to UART_TX (AF1) 0001:AF1 (index 0 for AFRL index 1 for AFRH)
	GPIOA->AFR[0] |= (1U<<8); //bitwise OR(|=) to set it to 1
	GPIOA->AFR[0] &= ~(1U<<9); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<10); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<11); //bitwise AND(&=), NOT(~) to set it to 0
	/*Configure UART GPIO pin*/
	//Enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure UART baud-rate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	//Configure the transfer direction
	USART2->CR1 = CR1_TE;
	//Enable UART module
	USART2->CR1 |= CR1_UART_EN;
}
void uart2_write(int ch)
{
	/*Make sure the transmit data register is empty*/
	while(!(USART2->ISR & SR_TXE))
	{}
	/*Write to transmit data register*/
	USART2->TDR = (ch & 0xFF); //we perform AND operation because we want to transmit eight bits
/*“& 0xff” effectively masks the variable so it leaves only the value in the last 8 bits, and ignores all the rest of the bits*/
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate)
{
	USARTx->BRR = compute_uart_BD(PeriphClk, Baudrate);
}
static uint16_t compute_uart_BD(uint32_t PeriphClk, uint32_t Baudrate)
{
	return ((PeriphClk + (Baudrate/2U))/Baudrate);
}
