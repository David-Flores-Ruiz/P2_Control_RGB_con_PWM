/*
 * RGB_ADC.c
 *
 *  Created on: 27 oct 2019
 *      Author: Lanix
 */

#include "RGB_ADC.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "FlexTimer.h"
#include "PIT.h"
#include "ADC.h"
#include <stdio.h>

#define RED_base 128
#define GREEN_base 128
#define BLUE_base 128
#define SIN_COLOR 0

#define STRING_POT &string_valuePOT[0]	//Direccion del arreglo de Voltage

uint8_t g_decenas  = 0;
uint8_t g_unidades = 0;
uint8_t g_decimas    = 0;
uint8_t g_centesimas = 0;

uint8_t string_valuePOT[6]="XX.YY";
uint8_t string_dummy[ ] = "";

void Float_to_String (My_float_t flotante){
	g_decenas  = flotante / 10;
	g_unidades = ( flotante - (g_decenas*10) ) / 1;
	g_decimas  = ( flotante - (g_decenas*10 + g_unidades*1) ) / 0.1;
	g_centesimas = ( flotante - (g_decenas*10 + g_unidades*1 + g_decimas*0.1) ) / 0.01;

	string_valuePOT[0] = RGB_ADC_String(g_decenas);
	string_valuePOT[1] = RGB_ADC_String(g_unidades);

	string_valuePOT[3] = RGB_ADC_String(g_decimas);
	string_valuePOT[4] = RGB_ADC_String(g_centesimas);
}

uint8_t* Get_String_POT (void) {
	uint8_t* ptr_String_POT = STRING_POT;
	return (ptr_String_POT);
}

uint8_t RGB_ADC_String(uint8_t entero)
{
	switch (entero)
	{
		case CERO:
			string_dummy[0] = '0';
			break;
		case UNO:
			string_dummy[0] = '1';
			break;
		case DOS:
			string_dummy[0] = '2';
			break;
		case TRES:
			string_dummy[0] = '3';
			break;
		case CUATRO:
			string_dummy[0] = '4';
			break;
		case CINCO:
			string_dummy[0] = '5';
			break;
		case SEIS:
			string_dummy[0] = '6';
			break;
		case SIETE:
			string_dummy[0] = '7';
			break;
		case OCHO:
			string_dummy[0] = '8';
			break;
		case NUEVE:
			string_dummy[0] = '9';
			break;
		default:
			break;
		}
	return string_dummy[0];
}

void FSM_RGB_ADC(void) {
	static State_RGB_ADC_t current_state = IDLE_2;
	int16_t duty_cycle_BLUE  = 0x0000;
	int16_t duty_cycle_RED   = 0x0000;
	int16_t duty_cycle_GREEN = 0x0000;

	uint8_t statusINT_sw2 = 0;
	uint8_t statusINT_sw3 = 0;

	statusINT_sw2 = GPIO_get_irq_status(GPIO_C);
	statusINT_sw3 = GPIO_get_irq_status(GPIO_A);


	// Modulo que lee el ADC:
	static uint8_t POT_voltage[10] = {0};
	static uint8_t contador=0;
	uint32_t prom = 0;
	uint8_t estado = 0;
	My_float_t Map_voltage = 0;


	PIT_delayFloat( PIT_0, SYSTEM_CLOCK, .02);
	estado = PIT_get_irq_flag_status( PIT_0 );
	if (estado) {
		POT_voltage[contador] = ADC_result(ADC_0);
		contador++;
		PIT_clear_irq_flag_status(PIT_0);	// Limpiamos bandera de Software
	}

		if (contador == 10) {
		prom = prom + POT_voltage[0];
		prom = prom + POT_voltage[1];
		prom = prom + POT_voltage[2];
		prom = prom + POT_voltage[3];
		prom = prom + POT_voltage[4];
		prom = prom + POT_voltage[5];
		prom = prom + POT_voltage[6];
		prom = prom + POT_voltage[7];
		prom = prom + POT_voltage[8];
		prom = prom + POT_voltage[9];
		prom = prom / 10;

		Map_voltage = (prom*3.10) / 240;
		Float_to_String (Map_voltage);
		//	printf("Voltage to LCD: %u  \n", (uint8_t)Map_voltage);
	}

	if (contador == 10) {
		contador=0;
		switch (current_state) {
		case IDLE_2:
			if (statusINT_sw3 == TRUE) {
				current_state = Input_Capture_each_10ms;
				GPIO_clear_irq_status(GPIO_A);	// Limpia flg de SW
			}
			break;

		case Input_Capture_each_10ms:
			if ((0 <= prom) && (prom<=18)) {
				current_state = ph1;	//** Transicion al siguiente estado */
			} else if ((18 < prom) && (prom <= 36)) {
				current_state = ph2;	//** Transicion al siguiente estado */
			} else if ((36 < prom) && (prom <= 54)) {
				current_state = ph3;	//** Transicion al siguiente estado */
			} else if ((54 < prom) && (prom <= 72)) {
				current_state = ph4;	//** Transicion al siguiente estado */
			} else if ((72 < prom) && (prom <= 90)) {
				current_state = ph5;	//** Transicion al siguiente estado */
			} else if ((90 < prom) && (prom <= 108)) {
				current_state = ph6;	//** Transicion al siguiente estado */
			} else if ((108 < prom) && (prom <= 126)) {
				current_state = ph7;	//** Transicion al siguiente estado */
			} else if ((126 < prom) && (prom <= 144)) {
				current_state = ph8;	//** Transicion al siguiente estado */
			} else if ((144 < prom) && (prom <= 162)) {
				current_state = ph9;	//** Transicion al siguiente estado */
			} else if ((162 < prom) && (prom <= 180)) {
				current_state = ph10;	//** Transicion al siguiente estado */
			} else if ((180 < prom) && (prom <= 198)) {
				current_state = ph11;	//** Transicion al siguiente estado */
			} else if ((198 < prom) && (prom <= 216)) {
				current_state = ph12;	//** Transicion al siguiente estado */
			} else if ((216 < prom) && (prom <= 234)) {
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
			duty_cycle_BLUE = SIN_COLOR;

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
	} //end if(contador==10)
}

