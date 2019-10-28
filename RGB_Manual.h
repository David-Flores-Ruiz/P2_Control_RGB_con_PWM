/*
 * RGB_Manual.h
 *
 *  Created on: 27 oct 2019
 *      Author: Lanix
 */

#ifndef RGB_MANUAL_H_
#define RGB_MANUAL_H_

typedef enum {
	IDLE,
	Wait_BOTON,
	B0, B1,	B2,	B3,	B4,	B5, B6,
} State_RGB_MANUAL_t;


void FSM_RGB_Manual(void);



#endif /* RGB_MANUAL_H_ */
