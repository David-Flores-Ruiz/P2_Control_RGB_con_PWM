/*
 * RGB_Secuencia.h
 *
 *  Created on: 28 oct 2019
 *      Author: pacas
 */

#ifndef RGB_SECUENCIA_H_
#define RGB_SECUENCIA_H_
#define SYSTEM_CLOCK (21000000U)

/*typedef struct{
	//GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
	uint8_t(*fptrSWs_status)( gpio_port_name_t , SWs_externos_t );
	uint32_t ON_OFF;
	uint32_t FTM_output_CH;
	void (*fptrFlexTimer_update_channel_value)( int16_t , FTM0_Specific_OutputChannel_t); //pit delay
	uint8_t next[2];
}State;*/
typedef enum {
	Guardar_secuencia,
	ejecutar_SW3,
	regresar_SW2,

} State_RGB_SECUENCIA_t;


void RGB_secuencia_save(void);
void RGB_secuencia_LED(void);
void RGB_secuencia_execute (void);




#endif /* RGB_SECUENCIA_H_ */
