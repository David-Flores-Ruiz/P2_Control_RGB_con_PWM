/*
 * RGB_Secuencia.h
 *
 *  Created on: 28 oct 2019
 *      Author: Ricardo Gonzalez Pacas/David Flores Ruiz
 */

#ifndef RGB_SECUENCIA_H_
#define RGB_SECUENCIA_H_
#define SYSTEM_CLOCK (21000000U)
#define MAX 10
typedef enum {
	Guardar_secuencia,
	ejecutar_SW3,
	regresar_SW2,
} State_RGB_SECUENCIA_t;

/*Guarda la secuencia segun el boton externo y lo almacena en un arreglo de max 10*/
void RGB_secuencia_save(void);
/*Ejecua la secuencia leyendo cada posicion del arreglo*/
void RGB_secuencia_LED(void);
/*Maquina de estados de la secuencia toma la desicion sobre guardar secuencia ejecutar secuencia y salir a menu */
void RGB_secuencia_execute (void);




#endif /* RGB_SECUENCIA_H_ */
