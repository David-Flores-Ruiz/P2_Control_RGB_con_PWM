/*
 * @file:			FSMcontrol.h
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "MK64F12.h"

#define SYSTEM_CLOCK (21000000U)
#define Delay_Password 1		 /** Para blink de los leds */


typedef enum {
	FONDO_PANTALLA,
	MENU_INICIAL,
	RGB_MANUAL, RGB_ADC, RGB_SECUENCIA, RGB_FRECUENCIA,
} State_t;

//** Para saltar al código de la máquina de estado */
//** Si es la segunda vez o número par que presiona B0 es para regresar a Fondo de Pantalla */
typedef struct {
	uint8_t flag_RGB_MANUAL :1;
	uint8_t flag_RGB_ADC	:1;
	uint8_t flag_RGB_SECUENCIA	:1;
	uint8_t flag_RGB_FRECUENCIA	:1;
	uint8_t primer_acceso :1;
	uint8_t imparOn 	  :1;
} FSM_flags_t;

void activateFSM_RGB_MANUAL();

void Wait_1_second(); //** Para el blink de los leds */

void FSM_control();	//** Máquina de estados general */

#endif /* CONTROL_H_ */
