/*
 * uart.h
 *
 *  Created on: Feb 9, 2023
 *      Author: Izzel
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include "stm32f0xx.h"
#include <stdint.h>

void uart2_rxtx_init(void);
char uart2_read(void);
void uart2_rxtx_interrupt_init(void);

#define UART_BAUDRATE 9600
#define CR1_TE		(1U<<3)
#define CR1_RE		(1U<<2)
#define CR1_RXNEIE	(1U<<5)
#define CR1_UART_EN	(1U<<0)
#define SR_TXE		(1U<<7)
#define SR_RXNE		(1U<<5)

#endif /* INC_UART_H_ */
