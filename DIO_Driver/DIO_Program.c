/*
 * DIO_Program.c
 *
 *   Created on: Mar 31, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Digital Input Output (DIO) functions' implementations.
 */

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "DIO_Config.h"

/* 1.Function to Initialize DIO peripheral. */
void DIO_vdInitialization  ( void )
{
	/* Set Initial Port Direction */
	/* PORTA */
	DIO_u8_DDRA_REG = DIO_u8_CONC( DIO_u8_PA7_INITIAL_DIRECTION, DIO_u8_PA6_INITIAL_DIRECTION, DIO_u8_PA5_INITIAL_DIRECTION, DIO_u8_PA4_INITIAL_DIRECTION, DIO_u8_PA3_INITIAL_DIRECTION, DIO_u8_PA2_INITIAL_DIRECTION, DIO_u8_PA1_INITIAL_DIRECTION, DIO_u8_PA0_INITIAL_DIRECTION );
	/* PORTB */
	DIO_u8_DDRB_REG = DIO_u8_CONC( DIO_u8_PB7_INITIAL_DIRECTION, DIO_u8_PB6_INITIAL_DIRECTION, DIO_u8_PB5_INITIAL_DIRECTION, DIO_u8_PB4_INITIAL_DIRECTION, DIO_u8_PB3_INITIAL_DIRECTION, DIO_u8_PB2_INITIAL_DIRECTION, DIO_u8_PB1_INITIAL_DIRECTION, DIO_u8_PB0_INITIAL_DIRECTION );
	/* PORTC */
	DIO_u8_DDRC_REG = DIO_u8_CONC( DIO_u8_PC7_INITIAL_DIRECTION, DIO_u8_PC6_INITIAL_DIRECTION, DIO_u8_PC5_INITIAL_DIRECTION, DIO_u8_PC4_INITIAL_DIRECTION, DIO_u8_PC3_INITIAL_DIRECTION, DIO_u8_PC2_INITIAL_DIRECTION, DIO_u8_PC1_INITIAL_DIRECTION, DIO_u8_PC0_INITIAL_DIRECTION );
	/* PORTD */
	DIO_u8_DDRD_REG = DIO_u8_CONC( DIO_u8_PD7_INITIAL_DIRECTION, DIO_u8_PD6_INITIAL_DIRECTION, DIO_u8_PD5_INITIAL_DIRECTION, DIO_u8_PD4_INITIAL_DIRECTION, DIO_u8_PD3_INITIAL_DIRECTION, DIO_u8_PD2_INITIAL_DIRECTION, DIO_u8_PD1_INITIAL_DIRECTION, DIO_u8_PD0_INITIAL_DIRECTION );
	
	/* Set Initial Port Value */
	/* PORTA */
	DIO_u8_PORTA_REG = DIO_u8_CONC( DIO_u8_PA7_INITIAL_VALUE, DIO_u8_PA6_INITIAL_VALUE, DIO_u8_PA5_INITIAL_VALUE, DIO_u8_PA4_INITIAL_VALUE, DIO_u8_PA3_INITIAL_VALUE, DIO_u8_PA2_INITIAL_VALUE, DIO_u8_PA1_INITIAL_VALUE, DIO_u8_PA0_INITIAL_VALUE );
	/* PORTB */
	DIO_u8_PORTB_REG = DIO_u8_CONC( DIO_u8_PB7_INITIAL_VALUE, DIO_u8_PB6_INITIAL_VALUE, DIO_u8_PB5_INITIAL_VALUE, DIO_u8_PB4_INITIAL_VALUE, DIO_u8_PB3_INITIAL_VALUE, DIO_u8_PB2_INITIAL_VALUE, DIO_u8_PB1_INITIAL_VALUE, DIO_u8_PB0_INITIAL_VALUE );
	/* PORTC */
	DIO_u8_PORTC_REG = DIO_u8_CONC( DIO_u8_PC7_INITIAL_VALUE, DIO_u8_PC6_INITIAL_VALUE, DIO_u8_PC5_INITIAL_VALUE, DIO_u8_PC4_INITIAL_VALUE, DIO_u8_PC3_INITIAL_VALUE, DIO_u8_PC2_INITIAL_VALUE, DIO_u8_PC1_INITIAL_VALUE, DIO_u8_PC0_INITIAL_VALUE );
	/* PORTD */
	DIO_u8_PORTD_REG = DIO_u8_CONC( DIO_u8_PD7_INITIAL_VALUE, DIO_u8_PD6_INITIAL_VALUE, DIO_u8_PD5_INITIAL_VALUE, DIO_u8_PD4_INITIAL_VALUE, DIO_u8_PD3_INITIAL_VALUE, DIO_u8_PD2_INITIAL_VALUE, DIO_u8_PD1_INITIAL_VALUE, DIO_u8_PD0_INITIAL_VALUE );
}

/* 2.Function to set Pin direction. */
u8	 DIO_u8SetPinDirection ( u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinDirection )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId and PinId are in the valid range */
	if( ( Copy_u8PortId <= DIO_u8_PORTD ) && ( Copy_u8PinId <= DIO_u8_PIN7 ) )
	{
		if( Copy_u8PinDirection == DIO_u8_PIN_INPUT )
		{
			/* Check the required PortId */
			switch( Copy_u8PortId )
			{
				case DIO_u8_PORTA: CLR_BIT( DIO_u8_DDRA_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTB: CLR_BIT( DIO_u8_DDRB_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTC: CLR_BIT( DIO_u8_DDRC_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTD: CLR_BIT( DIO_u8_DDRD_REG, Copy_u8PinId ); break;
			}
		}

		else if( Copy_u8PinDirection == DIO_u8_PIN_OUTPUT )
		{
			/* Check the required PortId */
			switch( Copy_u8PortId )
			{
				case DIO_u8_PORTA: SET_BIT( DIO_u8_DDRA_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTB: SET_BIT( DIO_u8_DDRB_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTC: SET_BIT( DIO_u8_DDRC_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTD: SET_BIT( DIO_u8_DDRD_REG, Copy_u8PinId ); break;
			}
		}

		else
		{
			/* Update error state = NOK, wrong PinDirection! */
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}

	else
	{
		/* Update error state = NOK, wrong PortId or PinId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 3.Function to set Pin value. */
u8	 DIO_u8SetPinValue     ( u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinValue )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId and PinId are in the valid range */
	if( ( Copy_u8PortId <= DIO_u8_PORTD ) && ( Copy_u8PinId <= DIO_u8_PIN7 ) )
	{
		if( Copy_u8PinValue == DIO_u8_PIN_LOW )
		{
			/* Check the required PortId */
			switch( Copy_u8PortId )
			{
				case DIO_u8_PORTA: CLR_BIT( DIO_u8_PORTA_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTB: CLR_BIT( DIO_u8_PORTB_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTC: CLR_BIT( DIO_u8_PORTC_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTD: CLR_BIT( DIO_u8_PORTD_REG, Copy_u8PinId ); break;
			}
		}

		else if( Copy_u8PinValue == DIO_u8_PIN_HIGH )
		{
			/* Check the required PortId */
			switch( Copy_u8PortId )
			{
				case DIO_u8_PORTA: SET_BIT( DIO_u8_PORTA_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTB: SET_BIT( DIO_u8_PORTB_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTC: SET_BIT( DIO_u8_PORTC_REG, Copy_u8PinId ); break;
				case DIO_u8_PORTD: SET_BIT( DIO_u8_PORTD_REG, Copy_u8PinId ); break;
			}
		}

		else
		{
			/* Update error state = NOK, wrong PinValue! */
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}

	else
	{
		/* Update error state = NOK, wrong PortId or PinId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 4.Function to get Pin value. */
u8	 DIO_u8GetPinValue 	   ( u8 Copy_u8PortId, u8 Copy_u8PinId, u8 * Copy_pu8ReturnedPinValue )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId and PinId are in the valid range, and Pointer is not equal to NULL */
	if( ( Copy_u8PortId <= DIO_u8_PORTD ) && ( Copy_u8PinId <= DIO_u8_PIN7 ) && ( Copy_pu8ReturnedPinValue != NULL ) )
	{
		/* Define local variable to put the value of PIN register in it, incase DIO_u8_PIN_LOW or DIO_u8_PIN_HIGH values are changed */
		u8 Local_u8PinValue;
	
		/* Check the Required PORT Number */
		switch( Copy_u8PortId )
		{
			case DIO_u8_PORTA:
			
				Local_u8PinValue = GET_BIT( DIO_u8_PINA_REG, Copy_u8PinId ); 
				
				if( Local_u8PinValue == 0 )
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_LOW;
				}
				
				else
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_HIGH;
				}					
			break;
			
			case DIO_u8_PORTB:
			
				Local_u8PinValue = GET_BIT( DIO_u8_PINB_REG, Copy_u8PinId );

				if( Local_u8PinValue == 0 )
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_LOW;
				}
				
				else
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_HIGH;
				}					
			break;
				
			case DIO_u8_PORTC:

				Local_u8PinValue = GET_BIT( DIO_u8_PINC_REG, Copy_u8PinId ); 
				
				if( Local_u8PinValue == 0 )
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_LOW;
				}
				
				else
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_HIGH;
				}	
			break;
								
			case DIO_u8_PORTD:

				Local_u8PinValue = GET_BIT( DIO_u8_PIND_REG, Copy_u8PinId ); 
			
				if( Local_u8PinValue == 0 )
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_LOW;
				}
				
				else
				{
					* Copy_pu8ReturnedPinValue = DIO_u8_PIN_HIGH;
				}	
			break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong PortId, PinId, or Pointer is NULL! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/* 5.Function to toggle Pin value. */
u8	 DIO_u8TogglePinValue  ( u8 Copy_u8PortId, u8 Copy_u8PinId )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId and PinId are in the valid range */
	if( ( Copy_u8PortId <= DIO_u8_PORTD ) && ( Copy_u8PinId <= DIO_u8_PIN7 ) )
	{
		/* Check the Required PORT Number */
		switch( Copy_u8PortId )
		{
			case DIO_u8_PORTA: TOG_BIT( DIO_u8_PORTA_REG, Copy_u8PinId ); break;
			case DIO_u8_PORTB: TOG_BIT( DIO_u8_PORTB_REG, Copy_u8PinId ); break;
			case DIO_u8_PORTC: TOG_BIT( DIO_u8_PORTC_REG, Copy_u8PinId ); break;
			case DIO_u8_PORTD: TOG_BIT( DIO_u8_PORTD_REG, Copy_u8PinId ); break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong PortId or PinId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 6.Function to set Port direction. */
u8	 DIO_u8SetPortDirection( u8 Copy_u8PortId, u8 Copy_u8PortDirection )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId is in the valid range */
	if( Copy_u8PortId <= DIO_u8_PORTD )
	{		
		/* Check the required PortId */
		switch( Copy_u8PortId )
		{
			case DIO_u8_PORTA: DIO_u8_DDRA_REG = Copy_u8PortDirection; break;
			case DIO_u8_PORTB: DIO_u8_DDRB_REG = Copy_u8PortDirection; break;
			case DIO_u8_PORTC: DIO_u8_DDRC_REG = Copy_u8PortDirection; break;
			case DIO_u8_PORTD: DIO_u8_DDRD_REG = Copy_u8PortDirection; break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong PortId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 7.Function to set Port value. */
u8 	 DIO_u8SetPortValue	   ( u8 Copy_u8PortId, u8 Copy_u8PortValue )
{
	/* Define Local Variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId is in the valid range */
	if( Copy_u8PortId <= DIO_u8_PORTD )
	{
		/* Check the required PortId */
		switch( Copy_u8PortId )
		{
			case DIO_u8_PORTA: DIO_u8_PORTA_REG = Copy_u8PortValue;	break;
			case DIO_u8_PORTB: DIO_u8_PORTB_REG = Copy_u8PortValue;	break;
			case DIO_u8_PORTC: DIO_u8_PORTC_REG = Copy_u8PortValue;	break;
			case DIO_u8_PORTD: DIO_u8_PORTD_REG = Copy_u8PortValue;	break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong PortId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}

/* 8.Function to get Port value. */
u8 	 DIO_u8GetPortValue	   ( u8 Copy_u8PortId, u8 * Copy_pu8ReturnedPortValue )
{
	/* Define Local Variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Make sure that the PortId is in the valid range, and Pointer is not equal to NULL */
	if( ( Copy_u8PortId <= DIO_u8_PORTD ) && ( Copy_pu8ReturnedPortValue != NULL ) )
	{
		/* Check the required PortId */
		switch( Copy_u8PortId )
		{
			case DIO_u8_PORTA: * Copy_pu8ReturnedPortValue = DIO_u8_PINA_REG; break;
			case DIO_u8_PORTB: * Copy_pu8ReturnedPortValue = DIO_u8_PINB_REG; break;
			case DIO_u8_PORTC: * Copy_pu8ReturnedPortValue = DIO_u8_PINC_REG; break;
			case DIO_u8_PORTD: * Copy_pu8ReturnedPortValue = DIO_u8_PIND_REG; break;
		}		
	}
	
	else
	{
		/* Update error state = NOK, wrong PortId, or Pointer is NULL! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
}