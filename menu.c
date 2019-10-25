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
