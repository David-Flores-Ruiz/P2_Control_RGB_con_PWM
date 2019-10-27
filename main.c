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
					0x00FF,
					FTM_PWM_EdgeAligned_High };

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

	uint8_t* ptr_array_ITESO = LCD_nokia_ITESO();

	LCD_nokia_clear();

	uint8_t state_B0 = 0;
	uint8_t state_B1 = 0, state_B2 = 0, state_B3 = 0;
	uint8_t state_B4 = 0, state_B5 = 0, state_B6 = 0;

// MAIN FLEX TIMER	para debug...
	int16_t duty_cycle = 0x00FF / 2;
	uint8_t input_port_a = 0, input_port_c = 0;
	gpio_pin_control_register_t pcr_pin_a_4 = GPIO_MUX1 | GPIO_PE | GPIO_PS;
	gpio_pin_control_register_t pcr_pin_a_6 = GPIO_MUX1 | GPIO_PE | GPIO_PS;
	/**Clock gating for port A and C*/
	SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA | GPIO_CLOCK_GATING_PORTC;
	PORTC->PCR[1] = PORT_PCR_MUX(0x4);
	/**Pin control register configuration for GPIO*/
	PORTA->PCR[bit_4] = pcr_pin_a_4;
	PORTC->PCR[bit_6] = pcr_pin_a_6;
	/**Pin 4 and pin 6 of port A and C, respectively as inputs*/
	GPIOA->PDDR &= ~(bit_4);
	GPIOC->PDDR &= ~(bit_6);
	/**Configuration function for FlexTimer*/
	FlexTimer_Init(&g_FTM_config);
//




	for (;;)
	{
		//Menu_Inicial( );
		//Menu_RGB_ADC();

		FSM_control();

		GPIO_decode_intr_PORTB (GPIO_B);
		state_B0 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B0);
		state_B1 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B1);
		state_B2 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B2);
		state_B3 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B3);
		state_B4 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B4);
		state_B5 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B5);
		state_B6 = GPIO_get_PORTB_SWs_status(GPIO_B, sw_B6);

		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B0);
		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B1);
		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B2);
		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B3);
		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B4);
		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B5);
		GPIO_clear_PORTB_SWs_status(GPIO_B, sw_B6);

		/**Reading the input ports for port A and C*/
		input_port_c = GPIOC->PDIR;
		input_port_c &= (0x40);
		input_port_c = input_port_c >> 6;
		input_port_a = GPIOA->PDIR;
		input_port_a &= (0x10);
		input_port_a = input_port_a >> 4;

// FLEX TIMER Ciclo infinito del Profe para debug:
		if(0 == input_port_a)
		{
			duty_cycle = duty_cycle + 10;
			FlexTimer_update_channel_value(duty_cycle);
			delay(20000);
		}
		if(0 == input_port_c)
		{
			duty_cycle = duty_cycle - 10;
			FlexTimer_update_channel_value(duty_cycle);
			delay(20000);
		}

//



	}
	
	return 0;
}
