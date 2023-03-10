#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
static void adc_callback(void);

int main (void)
{
	uart2_rxtx_init();
	PA1_adc_interrupt_init();
	start_conversion();
		while(1)
		{

		}
}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor Value :%d \n\r", (int)sensor_value);
}

void ADC1_IRQHandler(void)
{
	//Check if the End of Conversion flag is raised (Interrupt Trigger)
	if((ADC1->ISR & ADC_EOC) != 0)
	{
		//Clear EOC flag
		ADC1->ISR &= ~ADC_EOC;

		//Function
		adc_callback();
	}
}
