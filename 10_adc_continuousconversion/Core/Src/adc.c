#include "stm32f0xx.h"
#include "adc.h"

#define ADC_EN_RCC	(1U<<9)
#define GPIOAEN	(1U<<17)
#define ADC_CH1 (1U<<1)
#define ADC_EN (1U<<0)
#define ADC_START (1U<<2)

#define ADC_EOC (1U<<2)
#define ADC_CONT (1U<<13)

//PA1 is ADC1 (channel 1)


void PA1_adc_init(void)
{
	//Configure ADC GPIO pin
	//Enable clock access to ADC GPIO A
	RCC->AHBENR	|= GPIOAEN;
	//set the mode to PA1 to analog
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);
	//configure ADC module
	//enable clock access to ADC
	RCC->APB2ENR |= ADC_EN_RCC;
	//configure ADC parameters
	//select the channel that needs to be converted
	ADC1->CHSELR |= ADC_CH1;
	//enable ADC
	ADC1->CR |= 	ADC_EN;
	//conversion sampling time adjustment register
	//ADC->SMPR
}

void start_conversion(void)
{
	//Enable continuous conversion mode
	ADC1->CFGR1 |= ADC_CONT;
	//Begin ADC conversion
	ADC1->CR |= ADC_START;
}

uint32_t adc_read(void)
{
	//wait for conversion to complete
	while(!(ADC1->ISR & ADC_EOC)){}

	return (ADC1->DR);
}
