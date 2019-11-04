/*
 * RGB_Secuencia.c
 *
 *  Created on: 28 oct 2019
 *      Author: pacas
 */

#include "RGB_Secuencia.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "FlexTimer.h"
#include "PIT.h"
#include "LCD_nokia.h"
#include "RGB_Secuencia.h"

static uint8_t array[10] = { 0 };
static State_RGB_SECUENCIA_t current_state = Guardar_secuencia;

void RGB_secuencia_save(void){
	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0;
	uint8_t state_B4 = 0, state_B5 = 0, state_B6 = 0;

	static uint8_t i = 0;

	state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
	state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
	state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
	state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);
	state_B5 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B5);
	state_B6 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B6);

	if (state_B1 | state_B2 | state_B3 | state_B4 | state_B5 | state_B6 | state_B1)
	{
		if (state_B1 == TRUE) {
			array[i] = 'Z';
			i++;
		}
		if (state_B2 == TRUE) {
			array[i] = 'R';
			i++;
		}
		if (state_B3 == TRUE) {
			array[i] = 'V';
			i++;
		}
		if (state_B4 == TRUE) {
			array[i] = 'A';
			i++;
		}
		if (state_B5 == TRUE) {
			array[i] = 'M';
			i++;
		}
		if (state_B6 == TRUE) {
			array[i] = 'B';
			i++;
		}
	}
	if(i == 10){
		i=0;
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
	static uint8_t a = 0;
	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
	GPIO_clear_irq_status(GPIO_C);
	switch (array[a]) {
	case 'Z':
		if (statusINT_sw2) {
			current_state=regresar_SW2;
			break;
		} else {
			a++;
		}
		//LCD_nokia_send_char('Z');
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
			a++;
		}
		//LCD_nokia_send_char('R');
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
			a++;
		}
		//LCD_nokia_send_char('V');
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
			a++;
		}
		//LCD_nokia_send_char('A');
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
			a++;
		}
		//LCD_nokia_send_char('M');
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
			a++;
		}
		//LCD_nokia_send_char('B');
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

	//CH0=RED
	//CH1=GREEN
	//CH2=BLUE

	statusINT_sw3 = GPIO_get_irq_status(GPIO_A);
	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);

	if (statusINT_sw3 == TRUE) {
		current_state = ejecutar_SW3;
		GPIO_clear_irq_status(GPIO_A);	// Limpia flag de SW
	}
	if(statusINT_sw2 == TRUE){
		current_state = regresar_SW2;
		GPIO_clear_irq_status(GPIO_C);	// Limpia flag de SW
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
