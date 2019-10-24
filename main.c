/**
	\file 
	\brief 
		This is a starter file to use the Nokia 5510 LCD. 
		The LCD is connected as follows:
		RST-PDT5
		CE-PTD6
		DC-PTD4
		DIN-PTD2
		CLK-PTD1
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	19/09/2019
	    The SPI device driver needs to be completed.
 */

 
#include "SPI.h"
#include "GPIO.h"
#include "Bits.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include "stdint.h"
#include "RGB.h"


/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const spi_config_t g_spi_config = {
							SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2|GPIO_DSE,
							SPI_BAUD_RATE_8,
							SPI_FSIZE_8,
							{GPIO_D, bit_0, bit_1, bit_2, bit_3} };

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
//extern const uint8_t ITESO[504];
//extern const uint8_t PUMA [504];


int main(void)
{
	uint8_t string_1[]="ITESO"; /*! String to be printed in the LCD*/
	uint8_t string_2[]="Sistemas"; /*! String to be printed in the LCD*/
	uint8_t string_3[]="Embebidos I"; /*! String to be printed in the LCD*/
	uint8_t string_4[]="IE"; /*! String to be printed in the LCD*/

	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */

	uint8_t* ptr_array_PUMA = LCD_nokia_PUMA ();
	uint8_t* ptr_array_ITESO = LCD_nokia_ITESO();
	uint8_t* ptr_array_AME = LCD_nokia_AME();

	for (;;) {
		LCD_nokia_clear();/*! It clears the information printed in the LCD*/
		LCD_nokia_bitmap(ptr_array_PUMA); /*! It prints an array that hold an image, in this case is the initial picture*/
		delay(2500);
		LCD_nokia_clear();/*! It clears the information printed in the LCD*/
		LCD_nokia_bitmap(ptr_array_AME); /*! It prints an array that hold an image, in this case is the initial picture*/
		delay(2500);
		LCD_nokia_clear();/*! It clears the information printed in the LCD*/
		LCD_nokia_bitmap(ptr_array_ITESO); /*! It prints an array that hold an image, in this case is the initial picture*/
		delay(2500);
		LCD_nokia_clear();
		delay(2500);
		LCD_nokia_clear();
		LCD_nokia_goto_xy(20,0); /*! It establishes the position to print the messages in the LCD*/
		LCD_nokia_send_string(&string_1[0]); /*! It print a string stored in an array*/
		delay(2500);
		LCD_nokia_goto_xy(12,1);
		LCD_nokia_send_string(string_2); /*! It print a string stored in an array*/
		delay(2500);
		LCD_nokia_goto_xy(4,2);
		LCD_nokia_send_string(string_3); /*! It print a string stored in an array*/
		delay(2500);
		LCD_nokia_goto_xy(30,3);
		LCD_nokia_send_string(string_4); /*! It print a string stored in an array*/
		delay(2500);
		LCD_nokia_goto_xy(24,4);
		LCD_nokia_send_char('2'); /*! It prints a character*/
		LCD_nokia_send_char('0'); /*! It prints a character*/
		LCD_nokia_send_char('1'); /*! It prints a character*/
		LCD_nokia_send_char('9'); /*! It prints a character*/
		delay(2500);
	}
	
	return 0;
}

