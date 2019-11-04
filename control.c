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
#include "menu.h"
#include "RGB.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include "RGB_Manual.h"
#include "RGB_ADC.h"
#include "RGB_Secuencia.h"
#include "FlexTimer.h"

#define DEBUG_ON				/* Para proposito de DEBUG */

static FSM_flags_t g_FSM_status_flags = {0};	//** Banderas de activacion de cada submenu */
int8_t readArray[4] = { '0', '0', '0', '0' };

void activateFSM_RGB_MANUAL() {
	if (g_FSM_status_flags.flag_RGB_MANUAL == TRUE) {
		//Menu_RGB_MANUAL();
		FSM_RGB_Manual();
	}
	if(g_FSM_status_flags.flag_RGB_MANUAL == FALSE) {
		// Stop FSM
	}
}

void activateFSM_RGB_ADC() {
	if (g_FSM_status_flags.flag_RGB_ADC == TRUE) {
		//Menu_RGB_ADC();
		FSM_RGB_ADC();
	}
	if(g_FSM_status_flags.flag_RGB_ADC == FALSE) {
		// Stop FSM
	}
}

void activateFSM_RGB_SECUENCIA() {
	if (g_FSM_status_flags.flag_RGB_SECUENCIA == TRUE) {
		//Menu_RGB_SECUENCIA();
		RGB_secuencia_execute();
	}
	if(g_FSM_status_flags.flag_RGB_SECUENCIA == FALSE) {
		// Stop FSM
	}
}

void activateFSM_RGB_FRECUENCIA() {
	if (g_FSM_status_flags.flag_RGB_FRECUENCIA == TRUE) {
		FSM_RGB_Frecuencia();
		//Menu_RGB_FRECUENCIA();
		//RGB_();
	}
	if(g_FSM_status_flags.flag_RGB_FRECUENCIA == FALSE) {
		// Stop FSM
	}
}

void FSM_control() {
	static State_t current_state = FONDO_PANTALLA; //** Estado Inicial del Sistema */
	static State_inicio_t current_state_inicio = RED_inicio;
	uint8_t state_B0 = 0;
	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0, state_B4 = 0;
	static uint8_t incioRGB = 1;
	uint8_t estado = 0;
	uint8_t statusINT_sw2 = 0;
	uint8_t statusINT_sw3 = 0;

	uint8_t* ptr_array_PUMA = LCD_nokia_PUMA ();

	if (g_FSM_status_flags.flag_RGB_MANUAL == FALSE)
	{
		state_B0 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B0);
		state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
		state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
		state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
		state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);

		statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
		statusINT_sw3 = GPIO_get_irq_status(GPIO_A);
	}
	if (incioRGB) {
		switch (current_state_inicio)
		{
			case RED_inicio:
				FlexTimer_update_channel_value(0xFF, FTM0_CH0);
				PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
				estado = PIT_get_irq_flag_status(PIT_0);
				if (estado) {
					FlexTimer_update_channel_value(0x00, FTM0_CH0);
					current_state_inicio = GREEN_inicio;
					estado = 0;
					PIT_clear_irq_flag_status(PIT_0);
					PIT_stop(PIT_0);
				}
				break;

			case GREEN_inicio:
				FlexTimer_update_channel_value(0xFF, FTM0_CH1);
				PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
				estado = PIT_get_irq_flag_status(PIT_0);
				if (estado) {
					FlexTimer_update_channel_value(0x00, FTM0_CH1);
					current_state_inicio = BLUE_inicio;
					PIT_clear_irq_flag_status(PIT_0);
					estado = 0;
					PIT_stop(PIT_0);
				}
				break;

			case BLUE_inicio:
				FlexTimer_update_channel_value(0xFF, FTM0_CH2);
				PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
				estado = PIT_get_irq_flag_status(PIT_0);
				if (estado) {
					FlexTimer_update_channel_value(0x00, FTM0_CH2);
					incioRGB = 0;
					PIT_clear_irq_flag_status(PIT_0);
					PIT_stop(PIT_0);
				}
				break;

		} // end switch (current_state_inicio)
	} //end if incioRGB


	switch (current_state)
	{
		case FONDO_PANTALLA:

			LCD_nokia_bitmap(ptr_array_PUMA); /*! It prints an array that hold an image, in this case is the initial picture*/
			if (state_B0 == TRUE) {
				current_state = MENU_INICIAL; //** Transicion al siguiente estado */
				LCD_nokia_clear(); //** Limpia al cambio de pantalla 1 sola vez */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B0);
			} else {
				current_state = FONDO_PANTALLA; //** No cambia */
			}
			break; // end case FONDO_PANTALLA

		case MENU_INICIAL:
			Menu_Inicial( );	//** Mostramos en LCD el Menu principal */

			if (state_B0 == TRUE) {
				current_state = FONDO_PANTALLA;	//** Transicion al siguiente estado */
				LCD_nokia_clear(); //** Limpia al cambio de pantalla 1 sola vez */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B0);
			} else if (state_B1 == TRUE){
				current_state = RGB_MANUAL;		//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B1);
			} else if (state_B2 == TRUE){
				current_state = RGB_ADC;		//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B2);
			} else if (state_B3 == TRUE){
				current_state = RGB_SECUENCIA;	//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B3);
			} else if (state_B4 == TRUE){
				current_state = RGB_FRECUENCIA;	//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B4);
			} else {
				current_state = MENU_INICIAL;	//** No cambia */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B5);
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B6);
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
			//LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			//Menu_RGB_SECUENCIA();
			RGB_secuencia_execute();

				g_FSM_status_flags.flag_RGB_SECUENCIA = TRUE;
				current_state = RGB_SECUENCIA;

//			if ( statusINT_sw2 == TRUE ) {
//				g_FSM_status_flags.flag_RGB_SECUENCIA = FALSE;
//				current_state = MENU_INICIAL;
//			}

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
