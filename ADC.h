/*
 * ADC.h
 *
 *  Created on: 27 oct 2019
 *      Author: pacas
 */

#ifndef ADC_H_
#define ADC_H_
#include <MK64F12.h>
#include "stdint.h"
#include "GPIO.h"
typedef enum {ADC_0,
			  ADC_1,
			  } adc_channel_t;

/* It enable the clock module of the ADC by modifying the SIM_SCGC6 bits */
void ADC_clk(adc_channel_t channel);

//** Modo de operacion, fuente de reloj, Divisor del Reloj y Low Power */
void ADC_conversion_mode(adc_channel_t channel);

//** Enable el Promediador por Hardware */
void ADC_calibration(adc_channel_t channel);

void ADC_input_channel_select(adc_channel_t chanel_select);

//** Como single ended */
void ADC_differential_mode_disable(adc_channel_t channel);

uint8_t ADC_result(adc_channel_t channel);




#endif /* ADC_H_ */
