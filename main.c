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
#include "stdint.h"
#include "RGB.h"
#include "menu.h"
#include "control.h"
#include "FlexTimer.h"
#include "RGB_Manual.h"


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
const FTM_config_t g_FTM_config = {
					FTM_0,
					FTM_DISABLE_WPDIS,
					FTM_DISABLE_FTMEN,
					0x00FF,						// MOD
					FTM_PWM_EdgeAligned_High,	// CnSC y CnV asigna a FTM0_CH0, FTM0_CH1, FTM0_CH2
					GPIO_MUX4,
					{GPIO_C, bit_1, bit_2, bit_3} };

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
//extern const uint8_t ITESO[504];

int main(void)
{
	RGB_init();
	SW_init();

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);

	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_9);	// sw3
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_9);	// sw2

	/* PTB2_B0 PTB3_B1 PTB10_B2 PB11_B3 PB18_B4 PB19_B5 PB20_B6  */
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ,PRIORITY_9);	// 7sw´s externos
	NVIC_global_enable_interrupts;

	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */

//	uint8_t* ptr_array_ITESO = LCD_nokia_ITESO();

	LCD_nokia_clear();

//	uint8_t state_B0 = 0;
//	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0;
//	uint8_t state_B4 = 0, state_B5 = 0, state_B6 = 0;


	/**Configuration function for FlexTimer*/
	FlexTimer_Init(&g_FTM_config);


	for (;;)
	{
		//Menu_Inicial( );
		//Menu_RGB_ADC();

		GPIO_decode_intr_PORTB (GPIO_B);

		//FSM_control();

		FSM_RGB_Manual();

//		state_B0 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B0);
//		state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
//		state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
//		state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
//		state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);
//		state_B5 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B5);
//		state_B6 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B6);

//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B0);
//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B1);
//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B2);
//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B3);
//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B4);
//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B5);
//		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B6);

	}
	
	return 0;
}
