/*
 * menu.c
 *
 *  Created on: 24 oct 2019
 *      Author: Lanix
 */

#include "menu.h"
#include "RGB.h"
#include "LCD_nokia.h"




void Menu_Inicial(void) {
	uint8_t string_1[]="1)RGB Manual"; /*! String to be printed in the LCD*/
	uint8_t string_2[]="2)RGB ADC"; /*! String to be printed in the LCD*/
	uint8_t string_3[]="3)RGB Secuen"; /*! String to be printed in the LCD*/
	uint8_t string_4[]="4)RGB Frecue"; /*! String to be printed in the LCD*/

	LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_1[0]); /*! It print a string stored in an array*/
	delay(50);
	LCD_nokia_goto_xy(0, 1);
	LCD_nokia_send_string(string_2); /*! It print a string stored in an array*/
	delay(50);
	LCD_nokia_goto_xy(0, 2);
	LCD_nokia_send_string(string_3); /*! It print a string stored in an array*/
	delay(50);
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(string_4); /*! It print a string stored in an array*/
}
void Menu_RGB_ADC(void) {
	uint8_t string_0[]="Volta "; /*! String to be printed in the LCD*/
	uint8_t string_1[6]="XX.YY";
	uint8_t string_2[]="SW3 = ";
	uint8_t string_3[]="SW2 = ";
	uint8_t string_4[3]="On";
	uint8_t string_5[4]="Off";
	LCD_nokia_goto_xy(0, 0); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_0[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_1[0]);
	delay(50);
	LCD_nokia_goto_xy(0, 2); /*! It establishes the position to print the messages in the LCD*/
	LCD_nokia_send_string(&string_2[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_4[0]); /*! It print a string stored in an array*/
	LCD_nokia_goto_xy(0, 3);
	LCD_nokia_send_string(&string_3[0]); /*! It print a string stored in an array*/
	LCD_nokia_send_string(&string_5[0]); /*! It print a string stored in an array*/
}
void Menu_RGB_secuencia(void) {
	uint8_t string_1[]="Z";
	uint8_t string_2[]="R";
	uint8_t string_3[]="V";
	uint8_t string_4[]="A";
	uint8_t string_5[]="M";
	uint8_t string_6[]="B";
}
