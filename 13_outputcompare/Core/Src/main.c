#include "stm32f0xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIO_A_EN	(1U<<17) //enable bit 17 in RCC AHB register for port A
#define PIN5		(1u<<5) //Pin 5 location in GPIO A Register
#define LED_PIN		PIN5

int main (void)
{
		tim3_PB4_output_compare();
		while(1)
		{

		}
}
