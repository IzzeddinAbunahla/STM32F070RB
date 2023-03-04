#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"

int main (void)
{
		uar2_tx_init();
		while(1)
		{
			//uart2_write('Y');
			printf("Welcome from the STM32..\n\r");
		}
}



