#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;

int main (void)
{
	uart2_rxtx_init();
	PA1_adc_init();

		while(1)
		{
			start_conversion();
			sensor_value = adc_read();
			printf("Sensor Value :%d \n\r", (int)sensor_value);
		}
}
