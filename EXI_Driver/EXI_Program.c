/*
 * EXI_Program.c
 *
 *   Created on: Apr 25, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all External Interrupt (EXI) functions' implementations, and ISR functions' prototypes and implementations.
 */
 
 /* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "EXI_Interface.h"
#include "EXI_Private.h"
#include "EXI_Config.h"

/* Declaration and Initialization */
/* Global Array of 3 Pointers to Functions ( because we have 3 External Interrupts ), these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( * EXI_ApfInterrupstAction[3] ) ( void ) = { NULL, NULL, NULL };

/* 1.Function to enable and configure Peripheral Interrupt Enable (PIE), by setting relevant bit for each interrupt in GICR register, then configuring Sense Control in MCUCR (case interrupt 0 or 1) or MCUCSR (case interrupt 2) registers. */
u8	 EXI_u8EnablePIE  ( u8 Copy_u8InterruptId, u8 Copy_u8SenseControl )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the InterruptId and the Sense Control are in the valid range */
	if( ( Copy_u8InterruptId <= EXI_u8_INT2 ) && ( Copy_u8SenseControl <= EXI_u8_SENSE_RISING_EDGE ) )
	{
		/* Check the Required Interrupt */
		switch( Copy_u8InterruptId )
		{
			case EXI_u8_INT0:
				/* Enable Interrupt 0 */
				SET_BIT( EXI_u8_GICR_REG, EXI_u8_INT0_BIT );

				/* Check the Required Sense Control */
				switch( Copy_u8SenseControl )
				{
					case EXI_u8_SENSE_LOW_LEVEL		: CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC00_BIT ); CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC01_BIT ); break;
					case EXI_u8_SENSE_LOGICAL_CHANGE: SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC00_BIT ); CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC01_BIT ); break;
					case EXI_u8_SENSE_FALLING_EDGE	: CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC00_BIT ); SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC01_BIT ); break;
					case EXI_u8_SENSE_RISING_EDGE	: SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC00_BIT ); SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC01_BIT ); break;
				}
			break;

			case EXI_u8_INT1:
				/* Enable Interrupt 1 */
				SET_BIT( EXI_u8_GICR_REG, EXI_u8_INT1_BIT );

				/* Check the Required Sense Control */
				switch( Copy_u8SenseControl)
				{
					case EXI_u8_SENSE_LOW_LEVEL		: CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC10_BIT ); CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC11_BIT ); break;
					case EXI_u8_SENSE_LOGICAL_CHANGE: SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC10_BIT ); CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC11_BIT ); break;
					case EXI_u8_SENSE_FALLING_EDGE	: CLR_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC10_BIT ); SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC11_BIT ); break;
					case EXI_u8_SENSE_RISING_EDGE	: SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC10_BIT ); SET_BIT( EXI_u8_MCUCR_REG, EXI_u8_ISC11_BIT ); break;

				}
			break;

			case EXI_u8_INT2:
				/* Enable Interrupt 2 */
				SET_BIT( EXI_u8_GICR_REG, EXI_u8_INT2_BIT );

				/* Check the Required Sense Control */
				switch( Copy_u8SenseControl )
				{
					case EXI_u8_SENSE_FALLING_EDGE: CLR_BIT( EXI_u8_MCUCSR_REG, EXI_u8_ISC2_BIT ); break;
					case EXI_u8_SENSE_RISING_EDGE :	SET_BIT( EXI_u8_MCUCSR_REG, EXI_u8_ISC2_BIT ); break;
				}
			break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong InterruptId or Sense Control! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 2.Function to disable Peripheral Interrupt Enable (PIE), by clearing relevant bit for each interrupt in GICR register. */
u8	 EXI_u8DisablePIE ( u8 Copy_u8InterruptId )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that InterruptId is in the valid range */
	if( Copy_u8InterruptId <= EXI_u8_INT2 )
	{
		/* Check the Required Interrupt */
		switch ( Copy_u8InterruptId )
		{
			case EXI_u8_INT0: CLR_BIT( EXI_u8_GICR_REG, EXI_u8_INT0_BIT ); break;
			case EXI_u8_INT1: CLR_BIT( EXI_u8_GICR_REG, EXI_u8_INT1_BIT ); break;
			case EXI_u8_INT2: CLR_BIT( EXI_u8_GICR_REG, EXI_u8_INT2_BIT ); break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong InterruptId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 3.Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Interrupt ( InterruptId ), the address is passed through a pointer to function ( InterruptAction ), and then pass this address to ISR function */
u8	 EXI_u8SetCallBack( u8 Copy_u8InterruptId, void ( * Copy_pfInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that InterruptId is in the valid range, and Pointer to Function is not equal to NULL */
	if( ( Copy_u8InterruptId <= EXI_u8_INT2 ) && ( Copy_pfInterruptAction != NULL ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( InterruptAction ) into Global Array of Pointers to Functions ( InterruptsAction ) in the passed index ( InterruptId ). */
		EXI_ApfInterrupstAction[Copy_u8InterruptId] = Copy_pfInterruptAction;
	}
	
	else
	{
		/* Update error state = NOK, wrong InterruptId, or Pointer to Function is NULL! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}


/* ISR functions' prototypes of INT0, INT1, and INT2 respectively */
void __vector_1( void )		__attribute__((signal));
void __vector_2( void )		__attribute__((signal));
void __vector_3( void )		__attribute__((signal));


/* ISR function implementation of INT0 */
void __vector_1( void )
{
	/* Make sure that INT0 index of the Global Array is not equal to NULL */
	if( EXI_ApfInterrupstAction[EXI_u8_INT0] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( InterruptsAction ) */
		EXI_ApfInterrupstAction[EXI_u8_INT0]();
	}	
}

/* ISR function implementation of INT1 */
void __vector_2( void )
{
	/* Make sure that INT1 index of the Global Array is not equal to NULL */
	if( EXI_ApfInterrupstAction[EXI_u8_INT1] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( InterruptsAction ) */
		EXI_ApfInterrupstAction[EXI_u8_INT1]();
	}	
}

/* ISR function implementation of INT2 */
void __vector_3( void )
{
	/* Make sure that INT2 index of the Global Array is not equal to NULL */
	if( EXI_ApfInterrupstAction[EXI_u8_INT2] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( InterruptsAction ) */
		EXI_ApfInterrupstAction[EXI_u8_INT2]();
	}	
}
