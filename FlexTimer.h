/**
	\file
	\brief
		This is the header file for the FlexTimer divice driver.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	21/03/2019
	\todo
	    Add configuration structures.
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_


#include "MK64F12.h"

#define FLEX_TIMER_CLKS_0  (0U)
#define FLEX_TIMER_CLKS_1  (1U)
#define FLEX_TIMER_CLKS_2  (2U)
#define FLEX_TIMER_CLKS_3  (3U)


#define FLEX_TIMER_PS_1    (0U)
#define FLEX_TIMER_PS_2    (1U)
#define FLEX_TIMER_PS_4    (2U)
#define FLEX_TIMER_PS_8    (3U)
#define FLEX_TIMER_PS_16    (4U)
#define FLEX_TIMER_PS_32    (5U)
#define FLEX_TIMER_PS_64    (6U)
#define FLEX_TIMER_PS_128    (7U)


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80


/*Type for FTM modules*/
typedef enum {FTM_0,
			  FTM_1,
			  FTM_2
			  } FTM_channel_t;

/*Type for WPDIS configuration*/
typedef enum {FTM_DISABLE_WPDIS, FTM_ENABLE_WPDIS} FTM_enable_WPDIS_t;

/*Type for FTMEN configuration*/
typedef enum {FTM_DISABLE_FTMEN, FTM_ENABLE_FTMEN} FTM_enable_FTMEN_t;

/*Type for Operation Mode configuration*/
typedef enum {FTM_PWM_EdgeAligned_High, FTM_InputCapture_Falling} FTM_OpMode_t;

/*Type that is used for FTM configuration, It contains all the information needed for a SPI module*/
typedef struct
{
	FTM_channel_t FTM_channel;
	FTM_enable_WPDIS_t FTM_WPDIS;
	FTM_enable_FTMEN_t FTM_FTMEN;
	uint32_t defaultValue;
	FTM_OpMode_t OperationMode;
} FTM_config_t;


void FlexTimer_update_channel_value(int16_t channel_value);

void FTM_clk (FTM_channel_t channel);

void FTM_WPDIS(FTM_channel_t channel, FTM_enable_WPDIS_t enable_or_disable);

void FTM_FTMEN(FTM_channel_t channel, FTM_enable_FTMEN_t enable_or_disable);

void FTM_MOD(FTM_channel_t channel, uint32_t default_value);

void FTM_CnSC_OperationMode(FTM_channel_t channel, FTM_OpMode_t OpMode);

void FTM_CnV_DutyCycle_50(FTM_channel_t channel);

void FTM_SC_ConfigTime(FTM_channel_t channel);

/*It configures the FTM, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void FlexTimer_Init(const FTM_config_t* config_struct);

#endif /* FLEXTIMER_H_ */
