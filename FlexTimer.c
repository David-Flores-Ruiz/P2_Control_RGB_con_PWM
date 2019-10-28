/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	21/03/2019
	\todo
	    Add configuration structures.
 */



#include "FlexTimer.h"
#include "MK64F12.h"
#include "GPIO.h"


void FlexTimer_update_channel_value(int16_t channel_value, FTM0_Specific_OutputChannel_t FTM0_channel)
{
	if (FTM0_CH0 == FTM0_channel){
		/**Assigns a new value for the duty cycle*/
		FTM0->CONTROLS[0].CnV = channel_value;
	}

	if (FTM0_CH1 == FTM0_channel){
		/**Assigns a new value for the duty cycle*/
		FTM0->CONTROLS[1].CnV = channel_value;
	}

	if (FTM0_CH2 == FTM0_channel){
		/**Assigns a new value for the duty cycle*/
		FTM0->CONTROLS[2].CnV = channel_value;
	}

	if (FTM0_CH3 == FTM0_channel){
		///
	}

	if (FTM0_CH4 == FTM0_channel){
		///
	}

	if (FTM0_CH5 == FTM0_channel){
		///
	}

	if (FTM0_CH6 == FTM0_channel){
		///
	}

	if (FTM0_CH7 == FTM0_channel){
		///
	}
}


void FTM_clk(FTM_channel_t channel)
{
	if (FTM_0 == channel) {
		/**Clock gating for FlexTimer*/
		SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
	}
	if (FTM_1 == channel) {
		/**Clock gating for FlexTimer*/
		SIM->SCGC6 |= SIM_SCGC6_FTM1(1);
	}
	if (FTM_2 == channel) {
		/**Clock gating for FlexTimer*/
		SIM->SCGC6 |= SIM_SCGC6_FTM2(1);
	}
}

void FTM_WPDIS(FTM_channel_t channel, FTM_enable_WPDIS_t enable_or_disable)
{
	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
	* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/

	if (FTM_0 == channel) {
		if (FTM_ENABLE_WPDIS == enable_or_disable) {
			FTM0->MODE &= ~(FTM_MODE_WPDIS_MASK);	//** enabled (WPDIS = 0)  */
		}
		if (FTM_DISABLE_WPDIS == enable_or_disable) {
			FTM0->MODE |= FTM_MODE_WPDIS_MASK;		//** disabled (WPDIS = 1) */
		}
	}

	if (FTM_1 == channel) {
		if (FTM_ENABLE_WPDIS == enable_or_disable) {
			FTM1->MODE &= ~(FTM_MODE_WPDIS_MASK);	//** enabled (WPDIS = 0)  */
		}
		if (FTM_DISABLE_WPDIS == enable_or_disable) {
			FTM1->MODE |= FTM_MODE_WPDIS_MASK;		//** disabled (WPDIS = 1) */
		}
	}
	if (FTM_2 == channel) {
		if (FTM_ENABLE_WPDIS == enable_or_disable) {
			FTM2->MODE &= ~(FTM_MODE_WPDIS_MASK);	//** enabled (WPDIS = 0)  */
		}
		if (FTM_DISABLE_WPDIS == enable_or_disable) {
			FTM2->MODE |= FTM_MODE_WPDIS_MASK;		//** disabled (WPDIS = 1) */
		}
	}
}

void FTM_FTMEN(FTM_channel_t channel, FTM_enable_FTMEN_t enable_or_disable)
{	/** FTMEN - FTM Enable */
	if (FTM_0 == channel) {
		if (FTM_ENABLE_FTMEN == enable_or_disable) {
			FTM0->MODE |= FTM_MODE_FTMEN_MASK;		//** 0b1..All registers including the FTM-specific registers (second set of registers) are available for use with no restrictions. */
		}
		if (FTM_DISABLE_FTMEN == enable_or_disable) {
			FTM0->MODE &= ~ FTM_MODE_FTMEN_MASK;	//** 0b0..Only the TPM-compatible registers (first set of registers) can be used without any restriction. Do not use the FTM-specific registers. */
		}
	}
	if (FTM_1 == channel) {
		if (FTM_ENABLE_FTMEN == enable_or_disable) {
			FTM1->MODE |= FTM_MODE_FTMEN_MASK;		//** 0b1..All registers including the FTM-specific registers (second set of registers) are available for use with no restrictions. */
		}
		if (FTM_DISABLE_FTMEN == enable_or_disable) {
			FTM1->MODE &= ~ FTM_MODE_FTMEN_MASK;	//** 0b0..Only the TPM-compatible registers (first set of registers) can be used without any restriction. Do not use the FTM-specific registers. */
		}
	}
	if (FTM_2 == channel) {
		if (FTM_ENABLE_FTMEN == enable_or_disable) {
			FTM2->MODE |= FTM_MODE_FTMEN_MASK;		//** 0b1..All registers including the FTM-specific registers (second set of registers) are available for use with no restrictions. */
		}
		if (FTM_DISABLE_FTMEN == enable_or_disable) {
			FTM2->MODE &= ~ FTM_MODE_FTMEN_MASK;	//** 0b0..Only the TPM-compatible registers (first set of registers) can be used without any restriction. Do not use the FTM-specific registers. */
		}
	}
}

void FTM_MOD(FTM_channel_t channel, uint32_t default_value)
{
	/**Assigning a default value for modulo register*/
	if (FTM_0 == channel) {
		FTM0->MOD = default_value; 		//0x00FF
	}
	if (FTM_1 == channel) {
		FTM1->MOD = default_value; 		//0x00FF
	}
	if (FTM_2 == channel) {
		FTM2->MOD = default_value; 		//0x00FF
	}
}

void FTM_CnSC_OperationMode(FTM_channel_t channel, FTM_OpMode_t OpMode)
{
	if (FTM_0 == channel) {
		if (FTM_PWM_EdgeAligned_High == OpMode) {
			FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);	//** Selects the Edge-Aligned PWM mode: On High True pulses */
			FTM0->CONTROLS[1].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);	//** Selects the Edge-Aligned PWM mode: On High True pulses */
			FTM0->CONTROLS[2].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);	//** Selects the Edge-Aligned PWM mode: On High True pulses */
		}
		if (FTM_InputCapture_Falling == OpMode) {
			FTM0->CONTROLS[0].CnSC = FTM_CnSC_ELSB(1);		//** Selects the Input Capture mode: On Falling Edge */
		}
	}
	if (FTM_1 == channel) {
		if (FTM_PWM_EdgeAligned_High == OpMode) {
			FTM1->CONTROLS[0].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);	//** Selects the Edge-Aligned PWM mode: On High True pulses */
		}
		if (FTM_InputCapture_Falling == OpMode) {
			FTM1->CONTROLS[0].CnSC = FTM_CnSC_ELSB(1);		//** Selects the Input Capture mode: On Falling Edge */
		}
	}
	if (FTM_2 == channel) {
		if (FTM_PWM_EdgeAligned_High == OpMode) {
			FTM2->CONTROLS[0].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);	//** Selects the Edge-Aligned PWM mode: On High True pulses */
		}
		if (FTM_InputCapture_Falling == OpMode) {
			FTM2->CONTROLS[0].CnSC = FTM_CnSC_ELSB(1);		//** Selects the Input Capture mode: On Falling Edge */
		}
	}
}

void FTM_CnV_DutyCycle_50(FTM_channel_t channel)
{
	if (FTM_0 == channel) {
		/**Assign a duty cycle of 50%*/
		FTM0->CONTROLS[0].CnV = 0x00;
		FTM0->CONTROLS[1].CnV = 0x00;
		FTM0->CONTROLS[2].CnV = 0x00;
	}
	if (FTM_1 == channel) {
		/**Assign a duty cycle of 50%*/
		FTM1->CONTROLS[0].CnV = 0x00;
	}
	if (FTM_2 == channel) {
		/**Assign a duty cycle of 50%*/
		FTM2->CONTROLS[0].CnV = 0x00;
	}
}

void FTM_SC_ConfigTime(FTM_channel_t channel)
{
	if (FTM_0 == channel) {
		/**Configure the times*/
		FTM0->SC |= FTM_SC_CLKS(FLEX_TIMER_CLKS_1)| FTM_SC_PS(FLEX_TIMER_PS_128);
	}
	if (FTM_1 == channel) {
		/**Configure the times*/
		FTM1->SC |= FTM_SC_CLKS(FLEX_TIMER_CLKS_1)| FTM_SC_PS(FLEX_TIMER_PS_128);
	}
	if (FTM_2 == channel) {
		/**Configure the times*/
		FTM2->SC |= FTM_SC_CLKS(FLEX_TIMER_CLKS_1)| FTM_SC_PS(FLEX_TIMER_PS_128);
	}
}

void FlexTimer_Init(const FTM_config_t* config_struct)
{
	FTM_clk(config_struct->FTM_channel);
	GPIO_pin_control_register(config_struct->FTM_gpio_port.gpio_port_name, config_struct->FTM_gpio_port.FTM0_CH0, &(config_struct->pin_config));
	GPIO_pin_control_register(config_struct->FTM_gpio_port.gpio_port_name, config_struct->FTM_gpio_port.FTM0_CH1, &(config_struct->pin_config));
	GPIO_pin_control_register(config_struct->FTM_gpio_port.gpio_port_name, config_struct->FTM_gpio_port.FTM0_CH2, &(config_struct->pin_config));
	FTM_WPDIS(config_struct->FTM_channel, config_struct->FTM_WPDIS);
	FTM_FTMEN(config_struct->FTM_channel, config_struct->FTM_FTMEN);
	FTM_MOD(config_struct->FTM_channel, config_struct->defaultValue);
	FTM_CnSC_OperationMode(config_struct->FTM_channel, config_struct->OperationMode);
	FTM_CnV_DutyCycle_50(config_struct->FTM_channel);
	FTM_SC_ConfigTime(config_struct->FTM_channel);
}


