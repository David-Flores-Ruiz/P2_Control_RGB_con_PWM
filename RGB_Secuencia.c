/*
 * RGB_Secuencia.c
 *
 *  Created on: 28 oct 2019
 *     Author: Ricardo Gonzalez Pacas/David Flores Ruiz
 */

#include "RGB_Secuencia.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "FlexTimer.h"
#include "PIT.h"
#include "LCD_nokia.h"
#include "RGB_Secuencia.h"
#include "LCD_nokia.h"

static uint8_t array[MAX] = { 0 };
static State_RGB_SECUENCIA_t current_state = Guardar_secuencia;

void RGB_secuencia_save(void){
	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0;
	uint8_t state_B4 = 0, state_B5 = 0, state_B6 = 0;

	static uint8_t contador_save = 0;

	state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
	state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
	state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
	state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);
	state_B5 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B5);
	state_B6 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B6);

	if (state_B1 | state_B2 | state_B3 | state_B4 | state_B5 | state_B6 | state_B1)
	{
		if (state_B1 == TRUE) {
			array[contador_save] = 'Z';
			contador_save++;
		}
		if (state_B2 == TRUE) {
			array[contador_save] = 'R';
			contador_save++;
		}
		if (state_B3 == TRUE) {
			array[contador_save] = 'V';
			contador_save++;
		}
		if (state_B4 == TRUE) {
			array[contador_save] = 'A';
			contador_save++;
		}
		if (state_B5 == TRUE) {
			array[contador_save] = 'M';
			contador_save++;
		}
		if (state_B6 == TRUE) {
			array[contador_save] = 'B';
			contador_save++;
		}
	}
	if(contador_save == MAX){
		contador_save=0;
	}

	GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B1);
	GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B2);
	GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B3);
	GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B4);
	GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B5);
	GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B6);
}
void RGB_secuencia_LED(void) {
	uint8_t estado = 0;
	uint8_t statusINT_sw2 = 0;
	static uint8_t contador_secuencia = 0;

	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
	GPIO_clear_irq_status(GPIO_C);

	switch (array[contador_secuencia]) {
	case 'Z':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			contador_secuencia++;
		}

		FlexTimer_update_channel_value(0xFF, FTM0_CH2);
		PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
		do {
			estado = PIT_get_irq_flag_status(PIT_0);
		} while (estado == FALSE);
		FlexTimer_update_channel_value(0, FTM0_CH2);
		PIT_clear_irq_flag_status(PIT_0);
		break;
	case 'R':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			contador_secuencia++;
		}

		FlexTimer_update_channel_value(0xFF, FTM0_CH0);
		PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
		do {
			estado = PIT_get_irq_flag_status(PIT_0);
		} while (estado == FALSE);
		FlexTimer_update_channel_value(0, FTM0_CH0);
		PIT_clear_irq_flag_status(PIT_0);
		break;
	case 'V':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			contador_secuencia++;
		}

		FlexTimer_update_channel_value(0xFF, FTM0_CH1);
		PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
		do {
			estado = PIT_get_irq_flag_status(PIT_0);
		} while (estado == FALSE);
		FlexTimer_update_channel_value(0, FTM0_CH1);
		PIT_clear_irq_flag_status(PIT_0);

		break;
	case 'A':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			contador_secuencia++;
		}
		FlexTimer_update_channel_value(0xFF, FTM0_CH0);
		FlexTimer_update_channel_value(0xFF, FTM0_CH1);
		PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
		do {
			estado = PIT_get_irq_flag_status(PIT_0);
		} while (estado == FALSE);
		FlexTimer_update_channel_value(0, FTM0_CH0);
		FlexTimer_update_channel_value(0, FTM0_CH1);
		PIT_clear_irq_flag_status(PIT_0);

		break;
	case 'M':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			contador_secuencia++;
		}
		FlexTimer_update_channel_value(0xFF, FTM0_CH0);
		FlexTimer_update_channel_value(0xFF, FTM0_CH2);
		PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
		do {
			estado = PIT_get_irq_flag_status(PIT_0);
		} while (estado == FALSE);

		FlexTimer_update_channel_value(0, FTM0_CH0);
		FlexTimer_update_channel_value(0, FTM0_CH2);
		PIT_clear_irq_flag_status(PIT_0);
		break;
	case 'B':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			contador_secuencia++;
		}
		FlexTimer_update_channel_value(0xFF, FTM0_CH0);
		FlexTimer_update_channel_value(0xFF, FTM0_CH1);
		FlexTimer_update_channel_value(0xFF, FTM0_CH2);
		PIT_delayInteger(PIT_0, SYSTEM_CLOCK, 2);
		do {
			estado = PIT_get_irq_flag_status(PIT_0);
		} while (estado == FALSE);
		FlexTimer_update_channel_value(0x00, FTM0_CH0);
				FlexTimer_update_channel_value(0x00, FTM0_CH1);
				FlexTimer_update_channel_value(0x00, FTM0_CH2);
		break;
	}
}

void RGB_secuencia_execute (void){

	uint8_t statusINT_sw3 = 0;
	uint8_t statusINT_sw2 = 0;

	statusINT_sw3 = GPIO_get_irq_status(GPIO_A);
	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);

	if (statusINT_sw3 == TRUE) {
		current_state = ejecutar_SW3;
		GPIO_clear_irq_status(GPIO_A);	// Limpia flag de SW
	}
	if(statusINT_sw2 == TRUE){
		current_state = regresar_SW2;
	}

	switch (current_state)
	{
		case Guardar_secuencia:
			LCD_nokia_clear();/*! It clears the information printed in the LCD*/
			RGB_secuencia_save();
			break;
		case ejecutar_SW3:
			if (statusINT_sw3) {
				LCD_nokia_clear();
				LCD_nokia_send_string(array);
				statusINT_sw3 = FALSE;
			}
			RGB_secuencia_LED();
			break;
		case regresar_SW2:
			FlexTimer_update_channel_value(0x00, FTM0_CH0);
			FlexTimer_update_channel_value(0x00, FTM0_CH1);
			FlexTimer_update_channel_value(0x00, FTM0_CH2);
			break;
	}
}
