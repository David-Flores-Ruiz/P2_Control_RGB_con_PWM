/*
 * SPI.c
 *
 *  Created on: 17 oct 2019
 *      Author: Lanix
 */

 #include "SPI.h"

void SPI_clk(spi_channel_t channel)
{
	if (SPI_0 == channel) {
		SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK; /* Bit_12 - 0x1000*/
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_enable(spi_channel_t channel)
{
	if (SPI_0 == channel) {
		SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);	/* MDIS Bit_14 0b0.. Enables the module clocks */
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
{
	if (SPI_0 == channel) {
		if (SPI_MASTER == master_or_slave) {
			SPI0->MCR |= SPI_MCR_MSTR_MASK; /*MSTR bit_31: 0b1..Enables Master mode */
		}
		if (SPI_SLAVE == master_or_slave) {
			SPI0->MCR &= ~(SPI_MCR_MSTR_MASK); /* MSTR bit_31: 0b0..Enables Slave mode */
		}
	}

	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
{
	if (SPI_0 == channel) {
		if (SPI_ENABLE_FIFO == enable_or_disable) {
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK); /* DIS_TXF bit_13: 0b0..TX FIFO is enabled. */
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK); /* DIS_RXF bit_12: 0b0..RX FIFO is enabled. */
		}
		if (SPI_DISABLE_FIFO == enable_or_disable) {
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; /* DIS_TXF bit_13: 0b1..TX FIFO is disabled. */
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK; /* DIS_RXF bit_12: 0b1..RX FIFO is disabled. */
		}
	}

	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
{	/* Existen 2 CPOL en Master Mode: pp 1455 y en Slave Mode: pp 1459 */
	if (SPI_0 == channel) {
		if (SPI_LOW_POLARITY == cpol) {
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPOL_MASK); /* CPOL bit_26: 0b0..The inactive state value of SCK is low. */
		}
		if (SPI_HIGH_POLARITY == cpol) {
			SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPOL_MASK; /* CPOL bit_26: 0b1..The inactive state value of SCK is high. */
		}
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
{
	if (SPI_0 == channel) {
		if (SPI_LOW_PHASE == cpha) {
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_CPHA_MASK); /* CPHA bit_25: 0b0..Data is captured on the leading edge of SCK and changed on the following edge. */
		}
		if (SPI_HIGH_PHASE == cpha) {
			SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_CPHA_MASK; /* CPHA bit_25: 0b1..Data is changed on the leading edge of SCK and captured on the following edge. */
		}
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate)
{
	if (SPI_0 == channel) {
		SPI0->CTAR[SPI_CTAR_0] |= (baud_rate & SPI_CTAR_BR_MASK); /* BR bit_3-0: 0x03 = SPI_BAUD_RATE_8 */
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
{
	if (SPI_0 == channel) {
		if (SPI_MSB == msb) {
			SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_LSBFE_MASK); /* LSBFE bit_24: 0b0..Data is transferred MSB first. */
		}
		if (SPI_LSM == msb) {
			SPI0->CTAR[SPI_CTAR_0] |= SPI_CTAR_LSBFE_MASK; /* LSBFE bit_24: 0b1..Data is transferred LSB first. */
		}
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_frame_size(spi_channel_t channel, uint32_t frame_size)
{

	if (SPI_0 == channel) {
		SPI0->CTAR[SPI_CTAR_0] &= ~(SPI_CTAR_FMSZ_MASK); // Borramos FMSZ valores por default.
		SPI0->CTAR[SPI_CTAR_0] |= (frame_size & SPI_CTAR_FMSZ_MASK); /* FMSZ bit_30-27: 1 byte = SPI_FSIZE_8 */
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_start_tranference(spi_channel_t channel)
 {
	if (SPI_0 == channel) {
		SPI0->MCR &= ~(SPI_MCR_HALT_MASK); /* HALT bit_1: 0b0..Start transfers. */
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

void SPI_stop_tranference(spi_channel_t channel)
{
	if (SPI_0 == channel) {
		SPI0->MCR |= SPI_MCR_HALT_MASK; /* HALT bit_1: 0b1..Stop transfers. */
	}
	if (SPI_1 == channel) {
		////
	}
	if (SPI_2 == channel) {
		////
	}
}

uint8_t SPI_tranference(spi_channel_t channel, uint8_t data)
{
	SPI0->PUSHR = (data) | SPI_PUSHR_EOQ_MASK; /* Dato a transmitir = 1 byte, inicia transmision y generacion de reloj */
	while (0 == (SPI0->SR & SPI_SR_TCF_MASK)) /* Cuando TCF cambia de 0 a 1 la transmision ha terminado correctamente */
		;
	SPI0->SR |= SPI_SR_TCF_MASK; /* Se limpia bandera de TCF escribiendo un 1 en el bit_31 */

	uint8_t received_data = 0x00;
	received_data = SPI0->POPR & 0xFF;

	return (received_data);
}

void SPI_init(const spi_config_t* config_struct)
{
	SPI_clk(config_struct->spi_channel);
	GPIO_clock_gating(config_struct->spi_gpio_port.gpio_port_name);
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_clk,  &(config_struct->pin_config));
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_sout, &(config_struct->pin_config));
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name, config_struct->spi_gpio_port.spi_sin,  &(config_struct->pin_config)); /* Para leer de memoria */
	SPI_set_master(config_struct->spi_channel, config_struct->spi_master);
	SPI_fifo(config_struct->spi_channel, config_struct->spi_enable_fifo);
	SPI_enable(config_struct->spi_channel);
	SPI_clock_polarity(config_struct->spi_channel, config_struct->spi_polarity);
	SPI_frame_size(config_struct->spi_channel, config_struct->spi_frame_size);
	SPI_clock_phase(config_struct->spi_channel, config_struct->spi_phase);
	SPI_baud_rate(config_struct->spi_channel, config_struct->spi_baudrate);
	SPI_msb_first(config_struct->spi_channel, config_struct->spi_lsb_or_msb);
}
