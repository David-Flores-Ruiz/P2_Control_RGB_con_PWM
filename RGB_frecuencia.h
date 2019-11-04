/*
 * RGB_frecuencia.h
 *
 *  Created on: 3 nov 2019
 *      Author: Richard
 */

#ifndef RGB_FRECUENCIA_H_
#define RGB_FRECUENCIA_H_

#include "PIT.h"

//* For print in LCD the string of the Voltage value */
void Float_to_String_2 (My_float_t flotante);

//* Get the char of the respect number of the frecuency */
uint8_t RGB_FREC_String(uint8_t entero);

uint8_t* Get_String_FREC (void);

void FSM_RGB_Frecuencia(void);


#endif /* RGB_FRECUENCIA_H_ */
