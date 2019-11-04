/*
 * RGB_frecuencia.c
 *
 *  Created on: 3 nov 2019
 *      Author: Richard
 *
 */

#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "FlexTimer.h"
#include "PIT.h"
#include "ADC.h"
#include "RGB_Manual.h"
#include "RGB_ADC.h"
#include "RGB_Secuencia.h"
#include "RGB_frecuencia.h"
#include <stdio.h>

#define SIN_COLOR 0

#define STRING_FREC &string_valueFREC[0]	//Direccion del arreglo de Voltage

uint8_t g_decenas_Frec  = 0;
uint8_t g_unidades_Frec = 0;
uint8_t g_decimas_Frec    = 0;
uint8_t g_centesimas_Frec = 0;

uint8_t string_valueFREC[9]="XX.YYkHz";
uint8_t string_dummy_Frec[ ] = "";

void Float_to_String_2 (My_float_t flotante){
	g_decenas_Frec  = flotante / 10;
	g_unidades_Frec = ( flotante - (g_decenas_Frec*10) ) / 1;
	g_decimas_Frec  = ( flotante - (g_decenas_Frec*10 + g_unidades_Frec*1) ) / 0.1;
	g_centesimas_Frec = ( flotante - (g_decenas_Frec*10 + g_unidades_Frec*1 + g_decimas_Frec*0.1) ) / 0.01;

	string_valueFREC[0] = RGB_ADC_String(g_decenas_Frec);
	string_valueFREC[1] = RGB_ADC_String(g_unidades_Frec);

	string_valueFREC[3] = RGB_ADC_String(g_decimas_Frec);
	string_valueFREC[4] = RGB_ADC_String(g_centesimas_Frec);
}

uint8_t* Get_String_FREC (void) {
	uint8_t* ptr_String_FREC = STRING_FREC;
	return (ptr_String_FREC);
}

uint8_t RGB_FREC_String(uint8_t entero)
{
	switch (entero)
	{
		case CERO:
			string_dummy_Frec[0] = '0';
			break;
		case UNO:
			string_dummy_Frec[0] = '1';
			break;
		case DOS:
			string_dummy_Frec[0] = '2';
			break;
		case TRES:
			string_dummy_Frec[0] = '3';
			break;
		case CUATRO:
			string_dummy_Frec[0] = '4';
			break;
		case CINCO:
			string_dummy_Frec[0] = '5';
			break;
		case SEIS:
			string_dummy_Frec[0] = '6';
			break;
		case SIETE:
			string_dummy_Frec[0] = '7';
			break;
		case OCHO:
			string_dummy_Frec[0] = '8';
			break;
		case NUEVE:
			string_dummy_Frec[0] = '9';
			break;
		default:
			break;
		}
	return string_dummy_Frec[0];
}

void FSM_RGB_Frecuencia(void) {
	My_float_t float_to_string = 0;
	static State_RGB_ADC_t current_state = IDLE_2;
	int16_t duty_cycle_BLUE  = 0x0000;
	int16_t duty_cycle_RED   = 0x0000;
	int16_t duty_cycle_GREEN = 0x0000;
	uint8_t statusINT_sw2 = 0;
	uint8_t statusINT_sw3 = 0;
	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
	statusINT_sw3 = GPIO_get_irq_status(GPIO_A);

	float_to_string = Return_FrecuenceValue(FTM_0);
	Float_to_String_2(float_to_string/1000);


		switch (current_state) {
		case IDLE_2:
			if (statusINT_sw3 == TRUE) {
				current_state = Input_Capture_each_10ms;
				GPIO_clear_irq_status(GPIO_A);	// Limpia flg de SW
			}
			break;

		case Input_Capture_each_10ms:
			if ((0 <= float_to_string) && (float_to_string<=1700)) {
				current_state = ph1;	//** Transicion al siguiente estado */
			} else if ((1700 < float_to_string) && (float_to_string <= 2400)) {
				current_state = ph2;	//** Transicion al siguiente estado */
			} else if ((2400 < float_to_string) && (float_to_string <= 3100)) {
				current_state = ph3;	//** Transicion al siguiente estado */
			} else if ((3100 < float_to_string) && (float_to_string <= 3800)) {
				current_state = ph4;	//** Transicion al siguiente estado */
			} else if ((3800 < float_to_string) && (float_to_string <= 4500)) {
				current_state = ph5;	//** Transicion al siguiente estado */
			} else if ((4500 < float_to_string) && (float_to_string <= 5200)) {
				current_state = ph6;	//** Transicion al siguiente estado */
			} else if ((5200 < float_to_string) && (float_to_string <= 5900)) {
				current_state = ph7;	//** Transicion al siguiente estado */
			} else if ((5900 < float_to_string) && (float_to_string <= 6600)) {
				current_state = ph8;	//** Transicion al siguiente estado */
			} else if ((6600 < float_to_string) && (float_to_string <= 7300)) {
				current_state = ph9;	//** Transicion al siguiente estado */
			} else if ((7300 < float_to_string) && (float_to_string <= 8000)) {
				current_state = ph10;	//** Transicion al siguiente estado */
			} else if ((8000 < float_to_string) && (float_to_string <= 8700)) {
				current_state = ph11;	//** Transicion al siguiente estado */
			} else if ((8700 < float_to_string) && (float_to_string <= 9400)) {
				current_state = ph12;	//** Transicion al siguiente estado */
			} else if ((9400 < float_to_string) && (float_to_string <= 10000)) {
				current_state = ph13;	//** Transicion al siguiente estado */
			} else {
				current_state = ph14;	//** No cambia */
			}
			break;

			//** RED =  CH0			RED_base   = 128
			//** FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);

			//** GREEN = CH1		GREEN_base = 128
			//** FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);

			//** BLUE = CH2			BLUE_base  = 128
			//** FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

		case ph1:							//**		 ROJO 		*/
			duty_cycle_RED = 0x7F;
			duty_cycle_GREEN = 0x08;
			duty_cycle_BLUE = 0x00;

			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph2:							//**	 Color Marron 	*/
			duty_cycle_RED = 0x6D;
			duty_cycle_GREEN = 0x25;
			duty_cycle_BLUE = SIN_COLOR;

			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph3:							//**	 Color Naranja	*/
			duty_cycle_RED = 0x5B;
			duty_cycle_GREEN = 0x37;
			duty_cycle_BLUE = SIN_COLOR;

			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph4:							//**	 AMARILLO	*/
			duty_cycle_RED = 0x49;
			duty_cycle_GREEN = 0x49;
			duty_cycle_BLUE = SIN_COLOR;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph5:							//**	 Color Aguamarina 	*/
			duty_cycle_RED = 0x37;
			duty_cycle_GREEN = 0x5B;
			duty_cycle_BLUE = SIN_COLOR;
			duty_cycle_GREEN = duty_cycle_GREEN + 25;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph6:							//**	 Color Pantanoso 		*/
			duty_cycle_RED = 0x25;
			duty_cycle_GREEN = 0x6D;
			duty_cycle_BLUE = SIN_COLOR;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph7:							//**	 VERDE			*/
			duty_cycle_RED = SIN_COLOR;
			duty_cycle_GREEN = 0x7F;
			duty_cycle_BLUE = SIN_COLOR;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph8:							//**	 Color verde pera 	*/
			duty_cycle_RED = SIN_COLOR;
			duty_cycle_GREEN = 0x66;
			duty_cycle_BLUE = 0x02;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph9:							//**	 Color azul neon 	*/
			duty_cycle_RED = SIN_COLOR;
			duty_cycle_GREEN = 0x4D;
			duty_cycle_BLUE = 0x1B;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph10:							//**	 Color azul cielo 	*/
			duty_cycle_RED = SIN_COLOR;
			duty_cycle_GREEN = 0x34;
			duty_cycle_BLUE = 0x34;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph11:							//**	Color azul bajito  	*/
			duty_cycle_RED = SIN_COLOR;
			duty_cycle_GREEN = 0x1B;
			duty_cycle_BLUE = 0x4D;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph12:							//**	AZUL	*/
			duty_cycle_RED = SIN_COLOR;
			duty_cycle_GREEN = 0x02;
			duty_cycle_BLUE = 0x66;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph13:							//**	Color violeta 	*/
			duty_cycle_RED = 0x5B;
			duty_cycle_GREEN = SIN_COLOR;
			duty_cycle_BLUE = 0x66;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		case ph14:							//**	 MORADO	 	 	*/
			duty_cycle_RED = 0x7F;
			duty_cycle_GREEN = SIN_COLOR;
			duty_cycle_BLUE = 0x7F;
			FlexTimer_update_channel_value(duty_cycle_RED, FTM0_CH0);
			FlexTimer_update_channel_value(duty_cycle_GREEN, FTM0_CH1);
			FlexTimer_update_channel_value(duty_cycle_BLUE, FTM0_CH2);

			current_state = Input_Capture_each_10ms;
			break;

		default:
			break;

		} //end switch(current state)

}



