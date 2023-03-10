/*
 * uart.c
 *
 *  Created on: Feb 9, 2023
 *      Author: Izzel
 */
#include "uart.h"
#include "stm32f0xx.h"

#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define UART2EN		(1U<<17)

#define SYS_FREQ	8000000
#define APB1_CLK	SYS_FREQ

#define UART_BAUDRATE 9600
#define CR1_TE		(1U<<3)
#define CR1_RE		(1U<<2)
#define CR1_RXNEIE	(1U<<5)
#define CR1_UART_EN	(1U<<0)
#define SR_TXE		(1U<<7)
#define SR_RXNE		(1U<<5)
#define AHB_DMAEN	(1U<<0)
#define DMA_CCR_ENABLE	(1U<<0)
#define DMA_IF_CGIF4 (1u<<12)
#define DMA_IF_CTCIF4 (1u<<13)
#define DMA_IF_CHTIF4 (1u<<14)
#define DMA_IF_CTEIF4 (1u<<15)
#define DMA_PSIZE	(1U<<9)
#define DMA_MSIZE	(1U<<11)
#define DMA_MINC	(1U<<7)
#define DMA_DIR_MEM_READ		(1U<<4)
#define DMA_TCIE	(1U<<0)
#define DMAT	(1U<<7)

//Function prototypes;
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_BD(uint32_t PeriphClk, uint32_t Baudrate);

void uart2_write(int ch);


int __io_putchar(int ch) //for redirecting printf
{
	uart2_write(ch);
	return ch;
}

void dma_usart2_init(uint32_t src, uint32_t dst, uint32_t len)
{
	//enable clock access to DMA
	RCC->AHBENR |= AHB_DMAEN;
	//Disable DMA for USART (Channel 4)
	DMA1_Channel4->CCR &= ~DMA_CCR_ENABLE;
	//wait until DMA1 stream 6 is disabled
	while(DMA1_Channel4->CCR & DMA_CCR_ENABLE){}
	//Clear all interrupt for USART DMA channel 4
	DMA1->IFCR |= DMA_IF_CGIF4;
	DMA1->IFCR &= ~DMA_IF_CGIF4;
	//set peripheral address register size to 32 bit
	//DMA1_Channel4->CCR |= DMA_PSIZE;
	//set destination buffer
	DMA1_Channel4->CPAR = dst;
	//Set memory size to 32 bit
	//DMA1_Channel4->CCR |= DMA_MSIZE;
	//set the source buffer
	DMA1_Channel4->CMAR = src;
	//set length
	DMA1_Channel4->CNDTR = len;
	//Enable memory increment
	DMA1_Channel4->CCR |= DMA_MINC;
	//Configure transfer direction (memory to peripheral or peripheral to memory or memeory to memory)
	DMA1_Channel4->CCR |= DMA_DIR_MEM_READ;
	//Enable Transfer Complete Interrupt
	DMA1_Channel4->CCR |= DMA_TCIE;
	//Direct mode is the reset state for the DMA so it does not change
	//Enable DMA USART (Channel 4)
	DMA1_Channel4->CCR |= DMA_CCR_ENABLE;
	//Enable USART2 TX DMA
	USART2->CR3 |= DMAT;
	//NVIC enable IRQ for DMA
	NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);
}
void uart2_rxtx_interrupt_init(void)
{
	/*Configure UART2 GPIO pins*/
	//Enable clock access to GPIOA
	RCC->AHBENR	|= GPIO_A_EN;
	//set TX pin (PA2) mode to alternate function mode
	GPIOA->MODER &= ~(1U<<4); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->MODER |= (1U<<5); //bitwise OR(|=) to set it to 1
	//set RX pin (PA3) mode to alternate function mode
	GPIOA->MODER &= ~(1U<<6); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->MODER |= (1U<<7); //bitwise OR(|=) to set it to 1
	//set PA2 alternate function type to UART2_TX (AF1) 0001:AF1 (index 0 for AFRL index 1 for AFRH)
	GPIOA->AFR[0] |= (1U<<8); //bitwise OR(|=) to set it to 1
	GPIOA->AFR[0] &= ~(1U<<9); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<10); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<11); //bitwise AND(&=), NOT(~) to set it to 0
	//set PA3 alternate function type to UART2_RX (AF1) 0001:AF1 (index 0 for AFRL index 1 for AFRH)
	GPIOA->AFR[0] |= (1U<<12); //bitwise OR(|=) to set it to 1
	GPIOA->AFR[0] &= ~(1U<<13); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<14); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<15); //bitwise AND(&=), NOT(~) to set it to 0
	/*Configure UART GPIO pin*/
	//Enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure UART2 baud-rate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	//Configure the transfer direction
	USART2->CR1 |= CR1_TE;
	USART2->CR1 |= CR1_RE;
	//interrupt setup
		//Enable RXNEIE (RX interrupt)
		USART2->CR1 |= CR1_RXNEIE;
		//Enable USART 2 Interrupt in NVIC
		NVIC_EnableIRQ(USART2_IRQn);
	//Enable UART module in control register 1
	USART2->CR1 |= CR1_UART_EN;
}

void uart2_rxtx_init(void)
{
	/*Configure UART2 GPIO pins*/
	//Enable clock access to GPIOA
	RCC->AHBENR	|= GPIO_A_EN;
	//set TX pin (PA2) mode to alternate function mode
	GPIOA->MODER &= ~(1U<<4); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->MODER |= (1U<<5); //bitwise OR(|=) to set it to 1
	//set RX pin (PA3) mode to alternate function mode
	GPIOA->MODER &= ~(1U<<6); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->MODER |= (1U<<7); //bitwise OR(|=) to set it to 1
	//set PA2 alternate function type to UART2_TX (AF1) 0001:AF1 (index 0 for AFRL index 1 for AFRH)
	GPIOA->AFR[0] |= (1U<<8); //bitwise OR(|=) to set it to 1
	GPIOA->AFR[0] &= ~(1U<<9); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<10); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<11); //bitwise AND(&=), NOT(~) to set it to 0
	//set PA3 alternate function type to UART2_RX (AF1) 0001:AF1 (index 0 for AFRL index 1 for AFRH)
	GPIOA->AFR[0] |= (1U<<12); //bitwise OR(|=) to set it to 1
	GPIOA->AFR[0] &= ~(1U<<13); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<14); //bitwise AND(&=), NOT(~) to set it to 0
	GPIOA->AFR[0] &= ~(1U<<15); //bitwise AND(&=), NOT(~) to set it to 0
	/*Configure UART GPIO pin*/
	//Enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure UART2 baud-rate
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	//Configure the transfer direction
	USART2->CR1 |= CR1_TE;
	USART2->CR1 |= CR1_RE;
	//Enable UART module in control register 1
	USART2->CR1 |= CR1_UART_EN;
}

char uart2_read(void)
{
	/*wait until the receive data register is not empty*/
	while(!(USART2->ISR & SR_RXNE)){}

	/*read data*/
	return USART2->RDR;
}
void uart2_write(int ch)
{
	/*wait until the transmit data register is not empty*/
	while(!(USART2->ISR & SR_TXE)){}
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
