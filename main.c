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
#include "NVIC.h"
#include "Bits.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include <stdint.h>
#include <stdio.h>
#include "RGB.h"
#include "menu.h"
#include "control.h"
#include "FlexTimer.h"
#include "RGB_Manual.h"
#include "RGB_ADC.h"
#include "RGB_Secuencia.h"
#include "RGB_frecuencia.h"
#include "ADC.h"
#include "PIT.h"

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

/** \brief This is the configuration structure to configure the 3 FTM.
 * Note that is constants and it is because is only a variable used for configuration*/
const FTM_config_t g_FTM0_config = {
					FTM_0,
					FTM_DISABLE_WPDIS,
					FTM_DISABLE_FTMEN,
					0x00FF,						// MOD = 255d para cuenta de Reinicio
					FTM_PWM_EdgeAligned_High,	// CnSC y CnV asigna a FTM0_CH0, FTM0_CH1, FTM0_CH2
					GPIO_MUX4,
					{GPIO_C, bit_1, bit_2, bit_3} }; 	// PTC1, PTC2, PTC3

const FTM_config_t g_FTM0_CH3_config = {
					FTM_0,
					FTM_DISABLE_WPDIS,
					FTM_DISABLE_FTMEN,
					0x00FF,						// MOD = 255d para tener un Ftof = (10.5MHz)/(128)*(255+1) = 320Hz
					FTM_InputCapture_Falling,	// enable CHIE y capture en Falling
					GPIO_MUX4,
					{GPIO_C, bit_4, bit_4, bit_4} };	// PTC4

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
//extern const uint8_t ITESO[504];

int main(void)
{
	RGB_init();
	SW_init();
	PIT_init();

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);

	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_9);	// sw3
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_9);	// sw2
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_9); // PIT_0

	/* PTB2_B0 PTB3_B1 PTB10_B2 PB11_B3 PB18_B4 PB19_B5 PB20_B6  */
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ,PRIORITY_9);	// 7sw´s externos
	NVIC_enable_interrupt_and_priotity(FTM0_IRQ, PRIORITY_9);	// Input Capture del FTM0_CH3 - PTC4
	NVIC_global_enable_interrupts;

	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */

	LCD_nokia_clear();

	/**Configuration function for FlexTimer for PWM: FTM0_ch0_ch1_ch2*/
	FlexTimer_Init(&g_FTM0_config);
	/**Configuration function for FlexTimer for Input Capture: FTM0_ch3*/
	FlexTimer_Init(&g_FTM0_CH3_config);

	/**Configuration function for ADC*/
	ADC_clk(ADC_0);
	ADC_conversion_mode(ADC_0);
	ADC_calibration(ADC_0);
	ADC_differential_mode_disable(ADC_0);

	for (;;)
	{
		GPIO_decode_intr_PORTB (GPIO_B);

		FSM_control();
			activateFSM_RGB_MANUAL();
			activateFSM_RGB_ADC();
			activateFSM_RGB_SECUENCIA();
			activateFSM_RGB_FRECUENCIA();

	}
	
	return 0;
}
