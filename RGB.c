/*
 * RGB.c
 *
 *  Created on: 10 sep 2019
 *      Author: Ricardo Gonzalez Pacas/David Flores Ruiz
 */

#include "MK64F12.h"
#include "RGB.h"
#include <GPIO.h>
#include "bits.h"

#define ASCENDENTE_SW2  (0x02u) // Orden1 de FSM
#define DESCENDENTE_SW3 (0x01u)	// Orden2 de FSM

typedef enum {
	GREEN,		// 0
	BLUE,		// 1
	PURPLE,		// 2
	RED,		// 3
	YELLOW,		// 4
}State_name_t;

void RGB_init(void) {
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	GPIO_clock_gating(GPIO_B);	// led azul y rojo
	GPIO_clock_gating(GPIO_E);	// led verde

	gpio_pin_control_register_t led_config = GPIO_MUX1;	// 100 de GPIO
	/** OUTPUT: Configurar como LED RGB (GPIO) + safe value + como output */

	GPIO_pin_control_register(GPIO_B, bit_21, &led_config); // ledBlue  - pin 21 GPIO
	GPIO_pin_control_register(GPIO_B, bit_22, &led_config); // ledRed   - pin 22 GPIO
	GPIO_pin_control_register(GPIO_E, bit_26, &led_config); // ledGreen - pin 26 GPIO

	GPIO_set_pin(GPIO_B, bit_22);	// OFF - 1 RED
	GPIO_set_pin(GPIO_E, bit_26);	// OFF - 1 GREEN
	GPIO_set_pin(GPIO_B, bit_21);	// OFF - 1 BLUE

	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22); // OUTPUT - 1 RED
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26); // OUTPUT - 1 GREEN
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21); // OUTPUT - 1 BLUE

	GPIO_pin_control_register(GPIO_E, bit_24, &led_config); // GPIO - PTE_24 Debug del Input Capture

	GPIO_clear_pin(GPIO_E, bit_24);	// OFF
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_24);  // OUTPUT
	GPIO_clear_pin(GPIO_E, bit_24);	// OFF

}

void SW_init(void){
	GPIO_clock_gating( GPIO_A);	// sw3
	GPIO_clock_gating( GPIO_B);	// PTB2_B0 PTB3_B1 PTB10_B2 PB11_B3 PB18_B4 PB19_B5 PB20_B6
	GPIO_clock_gating( GPIO_C);	// sw2

	gpio_pin_control_register_t sw_config  = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;	// 103
	gpio_pin_control_register_t input_config = GPIO_MUX1 | INTR_FALLING_EDGE;	// 100 de GPIO

	GPIO_pin_control_register( GPIO_A, bit_4,  &sw_config );  //  sw3	  - pin  4
	GPIO_pin_control_register( GPIO_C, bit_6,  &sw_config );  //  sw2	  - pin  6

	GPIO_pin_control_register( GPIO_B, bit_2,  &input_config );//B0  	  - pin  2
	GPIO_pin_control_register( GPIO_B, bit_3,  &input_config );//B1	      - pin  3
	GPIO_pin_control_register( GPIO_B, bit_10, &input_config );//B2       - pin  10
	GPIO_pin_control_register( GPIO_B, bit_11, &input_config );//B3	      - pin  11
	GPIO_pin_control_register( GPIO_B, bit_18, &input_config );//B4	      - pin  11
	GPIO_pin_control_register( GPIO_B, bit_19, &input_config );//B5	      - pin  3
	GPIO_pin_control_register( GPIO_B, bit_20, &input_config );//B6	      - pin  2



	GPIO_data_direction_pin(GPIO_A,GPIO_INPUT, bit_4); // sw3
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, bit_6); // sw2

	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_2 );	// 7 sw´s externos
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_3 );
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_10);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_11);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_20);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_18);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_19);

}

uint8_t encender_LED(color_ON color_RGB) {
	switch (color_RGB) {
	case RED_ON:
		GPIO_clear_pin(GPIO_B, bit_22);	// ON - 0 RED
		break;
	case GREEN_ON:
		GPIO_clear_pin(GPIO_E, bit_26);	// ON - 0 GREEN
		break;
	case BLUE_ON:
		GPIO_clear_pin(GPIO_B, bit_21);	// ON - 0 BLUE
		break;
	case PURPLE_ON:
		GPIO_clear_pin(GPIO_B, bit_21);	// ON - 0 	BLUE +
		GPIO_clear_pin(GPIO_B, bit_22);	// ON - 0 	RED		= PURPLE
		break;
	case YELLOW_ON:
		GPIO_clear_pin(GPIO_B, bit_22);	// ON - 0 	RED +
		GPIO_clear_pin(GPIO_E, bit_26);	// ON - 0 	GREEN	= YELLOW
		break;
	default: /**If doesn't exist the option*/
		return (FALSE);
	}
	return (TRUE);
}

uint8_t apagar_LED(color_OFF color_RGB) {
	switch (color_RGB) {
	case RED_OFF:
		GPIO_set_pin( GPIO_B, bit_22);	// OFF - 1 RED
		break;
	case GREEN_OFF:
		GPIO_set_pin( GPIO_E, bit_26);	// OFF - 1 GREEN
		break;
	case BLUE_OFF:
		GPIO_set_pin( GPIO_B, bit_21);	// OFF - 1 BLUE
		break;
	case RGB_OFF:
		GPIO_set_pin( GPIO_B, bit_22);	// OFF - 1 RED	  +
		GPIO_set_pin( GPIO_E, bit_26);	// OFF - 1 GREEN  +
		GPIO_set_pin( GPIO_B, bit_21);	// OFF - 1 BLUE		=	RGB is OFF
		break;
	default: /**If doesn't exist the option*/
		return (FALSE);
	}
	return (TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void delay(uint16_t delay) {
	volatile uint16_t j, i;

	for (j = delay; j > 0; j--) {
		for (i = 0; i < 1000; ++i) {
			__asm("nop");
		}

	}
}
