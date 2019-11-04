/*
 * menu.c
 *
 *  Created on: 24 oct 2019
 *      Author: Lanix
 */

#include "menu.h"
#include "RGB.h"
#include "LCD_nokia.h"
#include "RGB_ADC.h"
#include "RGB_frecuencia.h"



void Menu_Inicial(void) {
	uint8_t string_1[]="1)RGB Manual"; /*! String to be printed in the LCD*/
	uint8_t string_2[]="2)RGB ADC"; /*! String to be printed in the LCD*/
	uint8_t string_3[]="3)RGB Secuen"; /*! String to be printed in the LCD*/
	uint8_t string_4[]="4)RGB Frecue"; /*! String to be printed in the LCD*/

	LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_1[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 1);
	LCD_nokia_send_string(string_2); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(string_3); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(string_4); /*! It print a string stored in an array*/
}

void Menu_RGB_MANUAL(void) {
	uint8_t string_1[]= "1) RGB"; /*! String to be printed in the LCD*/
	uint8_t string_2[]= "   MANUAL";
	uint8_t string_3[]= "SW3 = ";
	uint8_t string_5[]= "On";
	uint8_t string_4[]= "SW2 = ";
	uint8_t string_6[]= "Off";
	LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_1[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 1); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_2[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&string_3[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_5[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 4);
	LCD_nokia_send_string(&string_4[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_6[0]); /*! It print a string stored in an array*/
}

void Menu_RGB_ADC(void) {
	uint8_t string_0[] ="Volta "; /*! String to be printed in the LCD*/
	uint8_t string_1[6]="XX.YY";
	uint8_t string_2[] ="SW3 = ";
	uint8_t string_4[] ="On";
	uint8_t string_3[] ="SW2 = ";
	uint8_t string_5[] ="Off";

	uint8_t* ptr_string_POT = Get_String_POT();

	uint16_t index=0;
	for (index = 0 ; index < (6-1) ; index++){
	  string_1[index] = *(string_1 + index);
	}

	LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_0[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(ptr_string_POT);
	LCD_nokia_goto_xy(0, 2); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_2[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_4[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&string_3[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_5[0]); /*! It print a string stored in an array*/
}

void Menu_RGB_SECUENCIA(void) {
	uint8_t string_1[]= "X,";
	uint8_t string_2[]= "X,";
	uint8_t string_3[]= "X,";
	uint8_t string_4[]= "X,";
	uint8_t string_5[]= "X";
	uint8_t string_6[]= "X,";
	uint8_t string_7[]= "X,";
	uint8_t string_8[]= "X,";
	uint8_t string_9[]= "X,";
	uint8_t string_10[]="X";

	LCD_nokia_goto_xy(0, 1); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_1[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_2[0]);
	LCD_nokia_send_string(&string_3[0]);
	LCD_nokia_send_string(&string_4[0]);
	LCD_nokia_send_string(&string_5[0]);
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&string_6[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_7[0]);
	LCD_nokia_send_string(&string_8[0]);
	LCD_nokia_send_string(&string_9[0]);
	LCD_nokia_send_string(&string_10[0]);
}

void Menu_RGB_FRECUENCIA(void){
	uint8_t string_0[] ="Fre "; /*! String to be printed in the LCD*/
	uint8_t string_1[9]="XX.YYkHz";
	uint8_t string_2[] ="SW3 = ";
	uint8_t string_4[] ="On";
	uint8_t string_3[] ="SW2 = ";
	uint8_t string_5[] ="Off";

	uint8_t* ptr_string_FREC = Get_String_FREC();

	uint16_t index=0;
	for (index = 0 ; index < (6-1) ; index++){
	  string_1[index] = *(string_1 + index);
	}

	LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_0[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(ptr_string_FREC);
	LCD_nokia_goto_xy(0, 2); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_2[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_4[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&string_3[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_5[0]); /*! It print a string stored in an array*/
}


