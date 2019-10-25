/*
 * memoria.c
 *
 *  Created on: 21 oct 2019
 *      Author: Lanix
 */


#include "memoria.h"
#include "LCD_nokia.h"
#include "GPIO.h"
#include "SPI.h"
#include "stdint.h"
#include "Bits.h"

/* Para mandar el comando Read a la memoria y después los 3 bytes de direcciones */
uint32_t full_address  = 0x00000000;
uint8_t  dirByte1	=  0x00;
uint8_t  dirByte2	=  0x00;
uint8_t  dirByte3	=  0x00;

uint8_t Img_1[MAX] = {0}; /* Led Zepellin */
uint32_t g_dir_Img1  = 0x00700000;


void memoria_READ_IMAGEN(const uint8_t bitmap[]){
	uint16_t index = 0;
  for (index = 0 ; index < MAX; index++)
	  memoria_READ_byte( LCD_CMD, 0x03, IMG_1);
}

void memoria_READ_byte(uint8_t data_or_command, uint8_t data, mem_Imagenes_t Image )
{
	uint8_t DATA_read;
	static uint16_t index = 0;
	static boolean_t flag_1 = FALSE;



	switch (Image)
	{
		case IMG_1:
			if (flag_1 == FALSE) {
				full_address = g_dir_Img1;
			}
			dirByte1 = (full_address >> 0 ) & (0xFF); // Byte LOW
			dirByte2 = (full_address >> 8 ) & (0xFF);
			dirByte3 = (full_address >> 16) & (0xFF); // Byte HIGH

			flag_1 = TRUE;
			break;	// end case IMG_1

		case IMG_2:
			break;

		case IMG_3:
			break;

		case IMG_4:
			break;

		case IMG_5:
			break;

		default:
			break;
	}	//end switch (Image)

	GPIO_clear_pin(GPIO_D, CS1);

	if(data_or_command)
		GPIO_set_pin(GPIO_D, DATA_OR_CMD_PIN);
	else
		GPIO_clear_pin(GPIO_D, DATA_OR_CMD_PIN);

	SPI_start_tranference(SPI_0);
	SPI_tranference(SPI_0, data);	// Comando READ
	SPI_tranference(SPI_0, dirByte1);	// 3 Bytes de direccion
	SPI_tranference(SPI_0, dirByte2);
	DATA_read = SPI_tranference(SPI_0, dirByte3);

	SPI_stop_tranference(SPI_0);

	//	GPIO_set_pin(GPIO_D, CS1);

	if ((index >= 0) && (index < MAX)) {
		Img_1[index] = DATA_read;
	}

	index++; //** Apuntar al siguiente elemento del arreglo de forma correspondiente */
	full_address++; //** Apuntar a la siguiente dirección de memoria */
}


