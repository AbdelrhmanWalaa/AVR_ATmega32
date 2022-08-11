/*
 * ADC_Program.c
 *
 *   Created on: Apr 28, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) functions' implementations.
 */

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

/* 1.Function to Initialize ADC peripheral. */
void ADC_vdInitialization ( void )
{
	/* Step 1: Select Voltage Reference (Vref)  */
	/* Case 1: Vref = AREF */
	#if( ADC_u8_VREF_SELECT == ADC_u8_AREF_VOLT )
		CLR_BIT( ADC_u8_ADMUX_REG, ADC_u8_REFS0_BIT );
		CLR_BIT( ADC_u8_ADMUX_REG, ADC_u8_REFS1_BIT );

	/* Case 2: Vref = AVCC */
	#elif( ADC_u8_VREF_SELECT == ADC_u8_AVCC_VOLT )
		SET_BIT( ADC_u8_ADMUX_REG, ADC_u8_REFS0_BIT );
		CLR_BIT( ADC_u8_ADMUX_REG, ADC_u8_REFS1_BIT );

	/* Case 3: Vref = Internal ( 2.56 volts )  */
	#elif( ADC_u8_VREF_SELECT == ADC_u8_INTERNAL_VOLT )
		SET_BIT( ADC_u8_ADMUX_REG, ADC_u8_REFS0_BIT );
		SET_BIT( ADC_u8_ADMUX_REG, ADC_u8_REFS1_BIT );

	#endif
	/* End of Step 1 */

	/* Step 2: Select Right or Left Adjust */
	/* Case 1: Right Adjust */
	#if( ADC_u8_RESULT_ADJUST == ADC_u8_RIGHT_ADJUST )
		CLR_BIT( ADC_u8_ADMUX_REG, ADC_u8_ADLAR_BIT );

	/* Case 2: LEFT Adjust */
	#elif( ADC_u8_RESULT_ADJUST == ADC_u8_LEFT_ADJUST )
		SET_BIT( ADC_u8_ADMUX_REG, ADC_u8_ADLAR_BIT );

	#endif
	/* End of Step 2 */

	/* Step 3: Enable or Disable Auto Trigger */
	/* Case 1: Disable Auto Trigger */
	#if( ADC_u8_AUTO_TRIGGER_SELECT == ADC_u8_AUTO_TRIGGER_DISABLE )
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADATE_BIT );

	/* Case 2: Enable Auto Trigger */
	#elif( ADC_u8_AUTO_TRIGGER_SELECT == ADC_u8_AUTO_TRIGGER_ENABLE )
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADATE_BIT );

	#endif

	/* Note: Case Auto Trigger is Disabled, This Selection will have no effect. */
	/* Select Auto Trigger Source */
	/* Case 1: Trigger Source -> Free Running mode */
	#if( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_FREE_RUNNING_MODE )
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 2: Trigger Source -> Analog Comparator */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_ANALOG_COMPARATOR )
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 3: Trigger Source -> External Interrupt Request 0 */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_EXI_REQUEST_0 )
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 4: Trigger Source -> Timer/Counter0 Compare Match */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_TMR_0_COMPARE_MATCH )
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 5: Trigger Source -> Timer/Counter0 Overflow */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_TMR_0_OVERFLOW )
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 6: Trigger Source -> Timer/Counter Compare Match B */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_TMR_COMPARE_MATCH_B )
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 7: Trigger Source -> Timer/Counter1 Overflow */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_TMR_1_OVERFLOW )
		CLR_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	/* Case 8: Trigger Source -> Timer/Counter1 Capture Event */
	#elif( ADC_u8_AUTO_TRIGGER_SOURCE == ADC_u8_TMR_1_CAPTURE_EVENT )
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS0_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS1_BIT );
		SET_BIT( ADC_u8_SFIOR_REG, ADC_u8_ADTS2_BIT );

	#endif
	/* End of Step 3 */

	/* Step 4: Select Prescalar */
	/* Note: By default, the successive approximation circuitry requires an input clock frequency between 50 kHz and 200 kHz to get maximum resolution. Therefore, to get this frequency: FCPU / Prescalar -> 8 MHz / 64 = 125 kHz */
	/* Case 1: Division Factor = 2 */
	#if( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_2 )
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	/* Case 2: Division Factor = 4 */
	#elif( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_4 )
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	/* Case 3: Division Factor = 8 */
	#elif( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_8 )
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	/* Case 4: Division Factor = 16 */
	#elif( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_16 )
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	/* Case 5: Division Factor = 32 */
	#elif( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_32 )
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	/* Case 6: Division Factor = 64 */
	#elif( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_64 )
		CLR_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	/* Case 7: Division Factor = 128 */
	#elif( ADC_u8_PRESCALER_SELECT == ADC_u8_DIVISION_FACTOR_128 )
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS0_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS1_BIT );
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADPS2_BIT );

	#endif
	/* End of Step 4 */

	/* Step 5: Enable ADC */
	SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADEN_BIT );
	/* End of Step 5 */
}

/* 2.Function to start Analog to Digital conversion and passes the Digital value back. */
u8	 ADC_u8GetDigitalValue( u8 Copy_u8ChannelId, u16 * Copy_pu16DigitalValue )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that the ChannelId is in the valid range, and Pointer is not equal to NULL */
	if( ( Copy_u8ChannelId <= ADC_u8_CHANNEL_31 ) && ( Copy_pu16DigitalValue != NULL ) )
	{
		/* Step 1: Place the passed Channel into the ADMUX register in the 5 LSBs ( MUX4:0 ) */
		/* Important Note 1: In order to place the right channel in the ADMUX register, we have to clear the 5 LSBs ( MUX4:0 ) and reserve the 3 MSBs by using logical AND */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Important Note 2: In order to avoid altering the 3 MSBs, and since the ChannelId is passed in 8 bits not 5 bits, we have to use logical OR. */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelId;

		/* Step 2: Start Conversion */
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADSC_BIT );

		/* Step 3: Wait ( Poll ) until the conversion ends ( i.e. until flag (ADIF) = 1 ) */
		while( !GET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADIF_BIT ) );

		/* Step 4: Clear the flag (ADIF) by writing logical one, because this is Polling method. */
		SET_BIT( ADC_u8_ADCSRA_REG, ADC_u8_ADIF_BIT );

		/* Step 5: Get the digital value from the ADC register -> ( ADCH register + ADCL register ). */
		* Copy_pu16DigitalValue = ADC_u16_ADC_REG;
	}

	else
	{
		/* Update error state = NOK, wrong ChannelId, or Pointer is NULL! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}