/*
 * adc.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Izzel
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_
#include <stdio.h>
void PA1_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);

#endif /* INC_ADC_H_ */
