/*
 * RGB_Manual.c
 *
 *  Created on: 27 oct 2019
 *      Author: Lanix
 */

#include "RGB_Manual.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "FlexTimer.h"


void FSM_RGB_Manual(void) {
	static State_RGB_MANUAL_t current_state = IDLE;
	static int16_t duty_cycle_BLUE  = 0x0000;
	static int16_t duty_cycle_RED   = 0x0000;
	static int16_t duty_cycle_GREEN = 0x0000;

	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0;
	uint8_t state_B4 = 0, state_B5 = 0, state_B6 = 0, estado = 0;

	uint8_t statusINT_sw2 = 0;
	uint8_t statusINT_sw3 = 0;

	state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
	state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
	state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
	state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);
	state_B5 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B5);
	state_B6 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B6);

	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
	statusINT_sw3 = GPIO_get_irq_status(GPIO_A);
	if (statusINT_sw2 == TRUE) {
		current_state = IDLE;
		GPIO_clear_irq_status(GPIO_C);	// Limpia flag de SW
	}

	switch (current_state)
	{
		case IDLE:
			if (statusINT_sw3 == TRUE) {
				current_state = Wait_BOTON;
				GPIO_clear_irq_status(GPIO_A);	// Limpia flg de SW
			}
			break;

		case Wait_BOTON:
			if (state_B1 == TRUE) {
				current_state = B1;			//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B1);
			} else if (state_B2 == TRUE) {
				current_state = B2;			//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B2);
			} else if (state_B3 == TRUE) {
				current_state = B3;			//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B3);
			} else if (state_B4 == TRUE) {
				current_state = B4;			//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B4);
			} else if (state_B5 == TRUE) {
				current_state = B5;			//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B5);
			} else if (state_B6 == TRUE) {
				current_state = B6;			//** Transicion al siguiente estado */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B6);
			} else {
				current_state = Wait_BOTON;	//** No cambia */
				GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B0);
			}
			break;

		case B1:							//**	 Azul + 	*/
			duty_cycle_BLUE = duty_cycle_BLUE + 25;
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);
			current_state = Wait_BOTON;
			break;

		case B2:							//**	 Azul - 	*/
			duty_cycle_BLUE = duty_cycle_BLUE - 25;
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);
			current_state = Wait_BOTON;
			break;

		case B3:							//**	 Rojo + 	*/
			duty_cycle_RED = duty_cycle_RED + 25;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			current_state = Wait_BOTON;
			break;

		case B4:							//**	 Rojo - 	*/
			duty_cycle_RED = duty_cycle_RED - 25;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			current_state = Wait_BOTON;
			break;

		case B5:							//**	 Verde + 	*/
			duty_cycle_GREEN = duty_cycle_GREEN + 25;
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			current_state = Wait_BOTON;
			break;

		case B6:							//**	 Verde - 	*/
			duty_cycle_GREEN = duty_cycle_GREEN - 25;
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			current_state = Wait_BOTON;
			break;

		default:
			break;

	} //end switch(current state)
}
