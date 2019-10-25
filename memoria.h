/*
 * memoria.h
 *
 *  Created on: 21 oct 2019
 *      Author: Lanix
 */

#ifndef MEMORIA_H_
#define MEMORIA_H_

#include "stdint.h"

#define CS1 0
#define MAX 504

typedef enum {
	IMG_1,
	IMG_2,
	IMG_3,
	IMG_4,
	IMG_5,
} mem_Imagenes_t;

void memoria_READ_byte(uint8_t data_or_command, uint8_t data, mem_Imagenes_t Image );

#endif /* MEMORIA_H_ */
