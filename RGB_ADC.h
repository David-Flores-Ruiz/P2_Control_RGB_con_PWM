/*
 * RGB_ADC.h
 *
 *  Created on: 27 oct 2019
 *      Author: Lanix
 */

#ifndef RGB_ADC_H_
#define RGB_ADC_H_

#include "PIT.h"

#define SYSTEM_CLOCK (21000000U)
typedef enum {
	IDLE_2,
	Input_Capture_each_10ms,
	ph1, ph2, ph3,  ph4,  ph5,  ph6,  ph7,
	ph8, ph9, ph10, ph11, ph12, ph13, ph14,
} State_RGB_ADC_t;

typedef enum {
	CERO,  UNO,  DOS,   TRES, CUATRO,
	CINCO, SEIS, SIETE, OCHO, NUEVE,
} Index_array_t;



//* For print in LCD the string of the Voltage value */
void Float_to_String (My_float_t flotante);

//* Get the char of the respect number of the frecuency */
uint8_t RGB_ADC_String(uint8_t entero);

uint8_t* Get_String_POT (void);

void FSM_RGB_ADC(void);



#endif /* RGB_ADC_H_ */
