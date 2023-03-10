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

#endif /* INC_UART_H_ */
