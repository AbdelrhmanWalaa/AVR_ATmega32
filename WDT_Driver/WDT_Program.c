/*
 * WDT_Program.c
 *
 *   Created on: Aug 5, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Watch Dog Timer (WDT) functions' implementations.
 */

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "WDT_Interface.h"
#include "WDT_Private.h"
#include "WDT_Config.h"

/* 1.Function to enable and configure WDT. */
u8	 WDT_u8Enable ( u8 Copy_u8Prescaler )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that the Prescaler is in the valid range */
	if( Copy_u8Prescaler <= WDT_u8_2048K_PRESCALER )
	{
		/* Step 1: Check the Required Prescaler */
		switch( Copy_u8Prescaler )
		{
			/* Case 1: Prescaler = 16K */
			case WDT_u8_16K_PRESCALER  : CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
									   	 CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 2: Prescaler = 32K */
			case WDT_u8_32K_PRESCALER  : SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
									     CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 3: Prescaler = 64K */
			case WDT_u8_64K_PRESCALER  : CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
									     CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 4: Prescaler = 128K */
			case WDT_u8_128K_PRESCALER : SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
									   	 CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 5: Prescaler = 256K */
			case WDT_u8_256K_PRESCALER : CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
										 SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 6: Prescaler = 512K */
			case WDT_u8_512K_PRESCALER : SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
										 SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 7: Prescaler = 1024K */
			case WDT_u8_1024K_PRESCALER: CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
										 SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
			/* Case 8: Prescaler = 2048K */
			case WDT_u8_2048K_PRESCALER: SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP0_BIT ); SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP1_BIT );
										 SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDP2_BIT ); break;
		}

		/* Step 2: Enable WDT */
		SET_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDE_BIT );
	}

	else
	{
		/* Update error state = NOK, wrong Prescaler! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/* 2.Function to disable WDT. */
void WDT_vdDisable( void )
{
	/* To disable an enabled Watchdog Timer, the following procedure must be followed: */
	/* 1. In the same operation, write a logic one to WDTOE and WDE. A logic one must be written to WDE even though it is set to one before the disable operation starts. */
	WDT_u8_WDTCR_REG |= ( 1 << WDT_u8_WDTOE_BIT ) | ( 1 << WDT_u8_WDE_BIT );

	/* 2. Within the next four clock cycles, write a logic 0 to WDE. This disables the Watchdog. */
	CLR_BIT( WDT_u8_WDTCR_REG, WDT_u8_WDE_BIT );
}