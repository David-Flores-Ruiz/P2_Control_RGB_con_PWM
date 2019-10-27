/*
 * @file:			FSMcontrol.c
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "control.h"
#include "MK64F12.h"
#include "bits.h"
#include <stdio.h>
#include "GPIO.h"
#include "PIT.h"
#include "LCD_nokia.h"

#define DEBUG_ON				/* Para proposito de DEBUG */

static FSM_flags_t g_FSM_status_flags = {0};	//** Banderas de activacion de cada submenu */
int8_t readArray[4] = { '0', '0', '0', '0' };

void FSM_control() {
	static State_t current_state = FONDO_PANTALLA; //** Estado Inicial del Sistema */
	uint8_t state_B0 = 0;
	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0, state_B4 = 0;

	uint8_t statusINT_sw2 = 0;
	uint8_t statusINT_sw3 = 0;

	uint8_t* ptr_array_PUMA = LCD_nokia_PUMA ();

	state_B0 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B0);
	state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
	state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
	state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
	state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);

	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
	statusINT_sw3 = GPIO_get_irq_status(GPIO_A);

	switch (current_state)
	{
		case FONDO_PANTALLA:
			LCD_nokia_bitmap(ptr_array_PUMA); /*! It prints an array that hold an image, in this case is the initial picture*/
			delay(1500);

			if (state_B0 == TRUE) {
				current_state = MENU_INICIAL; //** Transicion al siguiente estado */
			} else {
				current_state = FONDO_PANTALLA; //** No cambia */
			}
			break; // end case FONDO_PANTALLA

		case MENU_INICIAL:

			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			Menu_Inicial( );	//** Mostramos en LCD el Menu principal */

			if (state_B0 == TRUE) {
				current_state = FONDO_PANTALLA;	//** Transicion al siguiente estado */
			} else if (state_B1 == TRUE){
				current_state = RGB_MANUAL;		//** Transicion al siguiente estado */
			} else if (state_B2 == TRUE){
				current_state = RGB_ADC;		//** Transicion al siguiente estado */
			} else if (state_B3 == TRUE){
				current_state = RGB_SECUENCIA;	//** Transicion al siguiente estado */
			} else if (state_B4 == TRUE){
				current_state = RGB_FRECUENCIA;	//** Transicion al siguiente estado */
			} else {
				current_state = MENU_INICIAL;	//** No cambia */
			}

			break; // end case MENU_INICIAL

		case RGB_MANUAL:
			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			Menu_RGB_MANUAL();

			if ( statusINT_sw3 == TRUE) {
				g_FSM_status_flags.flag_RGB_MANUAL = TRUE;
				current_state = RGB_MANUAL;
			}
			if ( statusINT_sw2 == TRUE ) {
				g_FSM_status_flags.flag_RGB_MANUAL = FALSE;
				current_state = MENU_INICIAL;
			}
			break; // end case RGB_MANUAL

		case RGB_ADC:
			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			Menu_RGB_ADC();

			if ( statusINT_sw3 == TRUE){
				g_FSM_status_flags.flag_RGB_ADC = TRUE;
				current_state = RGB_ADC;
			}
			if ( statusINT_sw2 == TRUE ) {
				g_FSM_status_flags.flag_RGB_ADC = FALSE;
				current_state = MENU_INICIAL;
			}
			break;// end case RGB_ADC

		case RGB_SECUENCIA:
			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			Menu_RGB_SECUENCIA();

			if ( statusINT_sw3 == TRUE){
				g_FSM_status_flags.flag_RGB_SECUENCIA = TRUE;
				current_state = RGB_SECUENCIA;
			}
			if ( statusINT_sw2 == TRUE ) {
				g_FSM_status_flags.flag_RGB_SECUENCIA = FALSE;
				current_state = MENU_INICIAL;
			}
			break;// end case RGB_SECUENCIA

		case RGB_FRECUENCIA:
			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			Menu_RGB_FRECUENCIA();

			if ( statusINT_sw3 == TRUE){
				g_FSM_status_flags.flag_RGB_FRECUENCIA = TRUE;
				current_state = RGB_FRECUENCIA;
			}
			if ( statusINT_sw2 == TRUE ) {
				g_FSM_status_flags.flag_RGB_FRECUENCIA = FALSE;
				current_state = MENU_INICIAL;
			}
			break;// end case RGB_SECUENCIA

		default:
			break;
	} //end switch(current state)
} //end FSM_control
