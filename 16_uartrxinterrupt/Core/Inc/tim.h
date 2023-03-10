/*
 * tim.h
 *
 *  Created on: Mar. 5, 2023
 *      Author: Izzel
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

void tim3_PB4_output_compare(void);
void tim15_PA2_input_capture(void);

#define SR_UIF (1U<<0)
#define SR_CC_1_INTERRUPT_FLAG (1U<<1)
#endif /* INC_TIM_H_ */
