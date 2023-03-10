#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

int timestamp = 0;
//setup by connecting PA2 and PB4
int main (void)
{
		tim3_PB4_output_compare();
		tim15_PA2_input_capture();

		while(1)
		{
			//wait until edge is captured
			while(!(TIM15->SR & SR_CC_1_INTERRUPT_FLAG)){}
			//read captured value
			timestamp = TIM15->CCR1;
		}
}
