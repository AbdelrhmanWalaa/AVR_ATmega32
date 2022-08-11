/*
 * TMR_Program.c
 *
 *   Created on: Jul 27, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Timers (TMR) functions' implementations, and ISR functions' prototypes and implementations.
 */

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TMR_Interface.h"
#include "TMR_Private.h"
#include "TMR_Config.h"

/* Declaration and Initialization */
/* Global Arrays of 3 Pointers to Functions ( because we have 3 Timers ), these functions ( in APP Layer ) which those 3 Pointers will hold their addresses; are having void input arguments and void return type. */
static void ( * TMR_ApfOVFInterruptsAction[3] ) ( void ) = { NULL, NULL, NULL };
static void ( * TMR_ApfCOMPInterruptsAction[3] ) ( void ) = { NULL, NULL, NULL };

/* Global Variables ( Flags ) to be altered when CTC Mode is selected in Timer 1, and depending on which Channel is selected. */
static u8 TMR_u8Timer1COMPAFlag = TMR_u8_FLAG_DOWN, TMR_u8Timer1COMPBFlag = TMR_u8_FLAG_DOWN;

/* 1.Function to Initialize TMR0 peripheral. */
void TMR_vdTMR0Initialization  ( void )
{
	/* Step 1: Select Waveform Generation Mode */
	switch( TMR_u8_TMR_0_MODE_SELECT )
	{
		/* Case 1: Waveform Generation Mode = Normal Mode */
		case TMR_u8_TMR_0_NORMAL_MODE			: CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM01_BIT ); break;
		/* Case 2: Waveform Generation Mode = PWM, Phase Correct Mode */
		case TMR_u8_TMR_0_PWM_PHASE_CORRECT_MODE: SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM01_BIT ); break;
		/* Case 3: Waveform Generation Mode = CTC Mode */
		case TMR_u8_TMR_0_CTC_MODE				: CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM01_BIT ); break;
		/* Case 4: Waveform Generation Mode = Fast PWM Mode */
		case TMR_u8_TMR_0_FAST_PWM_MODE			: SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_WGM01_BIT ); break;
	}

	/* Step 2: Select Compare Match Output Mode */
	switch( TMR_u8_TMR_0_COMP_OUTPUT_MODE )
	{
		/* Case 1: Normal port operation, OC0 disconnected */
		case TMR_u8_TMR_0_DISCONNECT_OC0_PIN: CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM01_BIT ); break;
		/* Case 2: Toggle OC0 on compare match */
		case TMR_u8_TMR_0_TOG_OC0_PIN		: SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM01_BIT ); break;
		/* Case 3: Clear OC0 on compare match ( PWM -> Non-Inverting Mode ) */
		case TMR_u8_TMR_0_CLR_OC0_PIN		: CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM01_BIT ); break;
		/* Case 4: Set OC0 on compare match ( PWM -> Inverting Mode ) */
		case TMR_u8_TMR_0_SET_OC0_PIN		: SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_COM01_BIT ); break;
	}

	/* Step 3: Select Interrupt Source */
	switch( TMR_u8_TMR_0_INTERRUPT_SELECT )
	{
		/* Case 1: Interrupt Source = No Interrupt ( i.e.: Interrupts are disabled, as in PWM two modes ) */
		case TMR_u8_TMR_0_NO_INTERRUPT  : CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE0_BIT ); CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_TOIE0_BIT ); break;
		/* Case 2: Interrupt Source = Compare Interrupt */
		case TMR_u8_TMR_0_COMP_INTERRUPT: SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE0_BIT ); break;
		/* Case 3: Interrupt Source = Overflow Interrupt */
		case TMR_u8_TMR_0_OVF_INTERRUPT : SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_TOIE0_BIT ); break;
	}

	/* Step 4: Set Compare Value and Preload Value */
	/* Compare Value */
	TMR_u8_OCR0_REG = TMR_u8_TMR_0_COMPARE_VALUE;
	/* Preload value */
	TMR_u8_TCNT0_REG = TMR_u8_TMR_0_PRELOAD_VALUE;

	/* Step 5: Select Clock Source ( i.e.: Start Counting ) */
	switch( TMR_u8_TMR_0_CLOCK_SELECT )
	{
		/* Case 1: Clock Source = No Clock Source (Timer/Counter0 stopped) */
		case TMR_u8_TMR_0_NO_CLOCK_SOURCE				 : CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
	    /* Case 2: Clock Source =  No Prescaler */
		case TMR_u8_TMR_0_NO_PRESCALER					 : SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
		/* Case 3: Clock Source = 8 Prescaler */
		case TMR_u8_TMR_0_8_PRESCALER					 : CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
		/* Case 4: Clock Source = 64 Prescaler */
		case TMR_u8_TMR_0_64_PRESCALER					 : SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
		/* Case 5: Clock Source = 256 Prescaler */
		case TMR_u8_TMR_0_256_PRESCALER					 : CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
		/* Case 6: Clock Source = 1024 Prescaler */
		case TMR_u8_TMR_0_1024_PRESCALER				 : SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
		/* Case 7: Clock Source = External Clock Source with Falling Edge, on Pin TO */
		case TMR_u8_TMR_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE: CLR_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
		/* Case 8: Clock Source = External Clock Source with Rising Edge, on Pin TO */
		case TMR_u8_TMR_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE: SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS00_BIT ); SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS01_BIT );
														   SET_BIT( TMR_u8_TCCR0_REG, TMR_u8_CS02_BIT ); break;
	}
}

/* 2.Function to Initialize TMR1 peripheral. */
void TMR_vdTMR1Initialization  ( void )
{
	/* Step 1: Select Waveform Generation Mode */
	switch( TMR_u8_TMR_1_MODE_SELECT )
	{
		/* Case 1: Waveform Generation Mode = Normal Mode */
		case TMR_u8_TMR_1_NORMAL_MODE                       : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
		   	   	   	   	   	   	   	   	   	   	   	   	      break;
		/* Case 2: Waveform Generation Mode = PWM, Phase Correct, 8-bit Mode */
		case TMR_u8_TMR_1_PWM_PHASE_CORRECT_8_BIT_MODE      : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 3: Waveform Generation Mode = PWM, Phase Correct, 9-bit Mode */
		case TMR_u8_TMR_1_PWM_PHASE_CORRECT_9_BIT_MODE	    : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 4: Waveform Generation Mode = PWM, Phase Correct, 10-bit Mode */
		case TMR_u8_TMR_1_PWM_PHASE_CORRECT_10_BIT_MODE	    : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 5: Waveform Generation Mode = CTC, at OCR1A Register Value */
		case TMR_u8_TMR_1_CTC_OCR_TOP					    : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 6: Waveform Generation Mode = Fast PWM, 8-bit Mode */
		case TMR_u8_TMR_1_FAST_PWM_8_BIT_MODE			    : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 7: Waveform Generation Mode = Fast PWM, 9-bit Mode */
		case TMR_u8_TMR_1_FAST_PWM_9_BIT_MODE			    : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 8: Waveform Generation Mode = Fast PWM, 10-bit Mode */
		case TMR_u8_TMR_1_FAST_PWM_10_BIT_MODE			    : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 9: Waveform Generation Mode = PWM, Phase and Frequency Correct Mode, at ICR1 Register Value */
		case TMR_u8_TMR_1_PWM_PHASE_AND_FREQ_CORRECT_ICR_TOP: CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 10: Waveform Generation Mode = PWM, Phase and Frequency Correct Mode, at OCR1A Register Value */
		case TMR_u8_TMR_1_PWM_PHASE_AND_FREQ_CORRECT_OCR_TOP: SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 11: Waveform Generation Mode = PWM, Phase Correct Mode, at ICR1 Register Value */
		case TMR_u8_TMR_1_PWM_PHASE_CORRECT_ICR_TOP		    : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 12: Waveform Generation Mode = PWM, Phase Correct Mode, at OCR1A Register Value */
		case TMR_u8_TMR_1_PWM_PHASE_CORRECT_OCR_TOP		    : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
															  CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 13: Waveform Generation Mode = CTC Mode */
		case TMR_u8_TMR_1_CTC_ICR_TOP					    : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 14: Waveform Generation Mode = Fast PWM Mode, at ICR1 Register Value */
		case TMR_u8_TMR_1_FAST_PWM_ICR_TOP				    : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
		/* Case 15: Waveform Generation Mode = Fast PWM Mode, at OCR1A Register Value */
		case TMR_u8_TMR_1_FAST_PWM_OCR_TOP				    : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM10_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_WGM11_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM12_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_WGM13_BIT );
	   	   	   	   	   	     	 	 	 	 	 	 	 	  break;
	}

	/* Step 2: Select Compare Match Output Mode */
	/* Channel A */
	switch( TMR_u8_TMR_1_COMP_OUTPUT_MODE_A )
	{
		/* Case 1: Normal port operation, OC1A disconnected */
		case TMR_u8_TMR_1_DISCONNECT_OC1A_PIN: CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A0_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A1_BIT ); break;
		/* Case 2: Toggle OC1A on compare match */
		case TMR_u8_TMR_1_TOG_OC1A_PIN		 : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A0_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A1_BIT ); break;
		/* Case 3: Clear OC1A on compare match ( PWM -> Non-Inverting Mode ) */
		case TMR_u8_TMR_1_CLR_OC1A_PIN		 : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A0_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A1_BIT ); break;
		/* Case 4: Set OC1A on compare match ( PWM -> Inverting Mode ) */
		case TMR_u8_TMR_1_SET_OC1A_PIN		 : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A0_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1A1_BIT ); break;
	}

	/* Channel B */
	switch( TMR_u8_TMR_1_COMP_OUTPUT_MODE_B )
	{
		/* Case 1: Normal port operation, OC1B disconnected */
		case TMR_u8_TMR_1_DISCONNECT_OC1B_PIN: CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B0_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B1_BIT ); break;
		/* Case 2: Toggle OC1B on compare match */
		case TMR_u8_TMR_1_TOG_OC1B_PIN		 : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B0_BIT ); CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B1_BIT ); break;
		/* Case 3: Clear OC1B on compare match ( PWM -> Non-Inverting Mode ) */
		case TMR_u8_TMR_1_CLR_OC1B_PIN		 : CLR_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B0_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B1_BIT ); break;
		/* Case 4: Set OC1B on compare match ( PWM -> Inverting Mode ) */
		case TMR_u8_TMR_1_SET_OC1B_PIN		 : SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B0_BIT ); SET_BIT( TMR_u8_TCCR1A_REG, TMR_u8_COM1B1_BIT ); break;
	}

	/* Step 3: Select Interrupt Source */
	switch( TMR_u8_TMR_1_INTERRUPT_SELECT )
	{
		/* Case 1: Interrupt Source = No Interrupt ( i.e.: Interrupts are disabled, as in PWM modes ) */
		case TMR_u8_TMR_1_NO_INTERRUPT	  :	CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_TICIE1_BIT ); CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE1A_BIT );
											CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE1B_BIT );	CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_TOIE1_BIT  );	break;
		/* Case 2: Interrupt Source = Capture Event Interrupt */
		case TMR_u8_TMR_1_CAPT_INTERRUPT  : SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_TICIE1_BIT ); break;
		/* Case 3: Interrupt Source = Compare A Interrupt */
		case TMR_u8_TMR_1_COMP_A_INTERRUPT: SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE1A_BIT );	break;
		/* Case 4: Interrupt Source = Compare B Interrupt */
		case TMR_u8_TMR_1_COMP_B_INTERRUPT:	SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE1B_BIT );	break;
		/* Case 5: Interrupt Source = Overflow Interrupt */
		case TMR_u8_TMR_1_OVF_INTERRUPT   : SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_TOIE1_BIT  ); break;
	}

	/* Step 4: Set Compare Value in both Channels, Input Capture Value, and Preload Value  */
	/* Compare Value A */
	TMR_u16_OCR1A_REG = TMR_u16_TMR_1_COMPARE_VALUE_A;
	/* Compare Value B */
	TMR_u16_OCR1B_REG = TMR_u16_TMR_1_COMPARE_VALUE_B;
	/* Input Capture Value */
	TMR_u16_ICR1_REG  = TMR_u16_TMR_1_INPUT_CAPTURE_VALUE;
	/* Preload value */
	TMR_u16_TCNT1_REG = TMR_u16_TMR_1_PRELOAD_VALUE;

	/* Step 5: Select Clock Source ( i.e.: Start Counting ) */
	switch( TMR_u8_TMR_1_CLOCK_SELECT )
	{
		/* Case 1: Clock Source = No Clock Source (Timer/Counter1 stopped) */
		case TMR_u8_TMR_1_NO_CLOCK_SOURCE				 : CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 2: Clock Source =  No Prescaler */
		case TMR_u8_TMR_1_NO_PRESCALER					 : SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 3: Clock Source = 8 Prescaler */
		case TMR_u8_TMR_1_8_PRESCALER					 : CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 4: Clock Source = 64 Prescaler */
		case TMR_u8_TMR_1_64_PRESCALER					 : SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 5: Clock Source = 256 Prescaler */
		case TMR_u8_TMR_1_256_PRESCALER					 : CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 6: Clock Source = 1024 Prescaler */
		case TMR_u8_TMR_1_1024_PRESCALER				 : SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 7: Clock Source = External Clock Source with Falling Edge, on Pin T1 */
		case TMR_u8_TMR_1_EXTERNAL_CLOCK_SOURCE_FALL_EDGE: CLR_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
		/* Case 8: Clock Source = External Clock Source with Rising Edge, on Pin T1 */
		case TMR_u8_TMR_1_EXTERNAL_CLOCK_SOURCE_RISE_EDGE: SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS10_BIT ); SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS11_BIT );
														   SET_BIT( TMR_u8_TCCR1B_REG, TMR_u8_CS12_BIT ); break;
	}
}

/* 3.Function to Initialize TMR2 peripheral. */
void TMR_vdTMR2Initialization  ( void )
{
	/* Step 1: Select Waveform Generation Mode */
	switch( TMR_u8_TMR_2_MODE_SELECT )
	{
		/* Case 1: Waveform Generation Mode = Normal Mode */
		case TMR_u8_TMR_2_NORMAL_MODE			: CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM21_BIT ); break;
		/* Case 2: Waveform Generation Mode = PWM, Phase Correct Mode */
		case TMR_u8_TMR_2_PWM_PHASE_CORRECT_MODE: SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM21_BIT ); break;
		/* Case 3: Waveform Generation Mode = CTC Mode */
		case TMR_u8_TMR_2_CTC_MODE			    : CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM21_BIT ); break;
		/* Case 4: Waveform Generation Mode = Fast PWM Mode */
		case TMR_u8_TMR_2_FAST_PWM_MODE		    : SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_WGM21_BIT ); break;
	}

	/* Step 2: Select Compare Match Output Mode */
	switch( TMR_u8_TMR_2_COMP_OUTPUT_MODE )
	{
		/* Case 1: Normal port operation, OC2 disconnected */
		case TMR_u8_TMR_2_DISCONNECT_OC2_PIN: CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM21_BIT ); break;
		/* Case 2: Toggle OC2 on compare match */
		case TMR_u8_TMR_2_TOG_OC2_PIN		: SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM21_BIT ); break;
		/* Case 3: Clear OC2 on compare match ( PWM -> Non-Inverting Mode ) */
		case TMR_u8_TMR_2_CLR_OC2_PIN		: CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM21_BIT ); break;
		/* Case 4: Set OC2 on compare match ( PWM -> Inverting Mode ) */
		case TMR_u8_TMR_2_SET_OC2_PIN		: SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_COM21_BIT ); break;
	}

	/* Step 3: Select Interrupt Source */
	switch( TMR_u8_TMR_2_INTERRUPT_SELECT )
	{
		/* Case 1: Interrupt Source = No Interrupt ( i.e.: Interrupts are disabled, as in PWM two modes ) */
		case TMR_u8_TMR_2_NO_INTERRUPT  : CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE2_BIT ); CLR_BIT( TMR_u8_TIMSK_REG, TMR_u8_TOIE2_BIT );	break;
		/* Case 2: Interrupt Source = Compare Interrupt */
		case TMR_u8_TMR_2_COMP_INTERRUPT: SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_OCIE2_BIT ); break;
		/* Case 3: Interrupt Source = Overflow Interrupt */
		case TMR_u8_TMR_2_OVF_INTERRUPT : SET_BIT( TMR_u8_TIMSK_REG, TMR_u8_TOIE2_BIT ); break;
	}

	/* Step 4: Set Compare Value and Preload Value */
	/* Compare Value */
	TMR_u8_OCR2_REG = TMR_u8_TMR_2_COMPARE_VALUE;
	/* Set Preload value */
	TMR_u8_TCNT2_REG = TMR_u8_TMR_2_PRELOAD_VALUE;

	/* Step 5: Select Clock Source ( i.e.: Start Counting ) */
	switch( TMR_u8_TMR_2_CLOCK_SELECT )
	{
		/* Case 1: Clock Source = No Clock Source (Timer/Counter2 stopped) */
		case TMR_u8_TMR_2_NO_CLOCK_SOURCE: CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 2: Clock Source =  No Prescaler */
		case TMR_u8_TMR_2_NO_PRESCALER	 : SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 3: Clock Source = 8 Prescaler */
		case TMR_u8_TMR_2_8_PRESCALER	 : CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 4: Clock = 32 Prescaler */
		case TMR_u8_TMR_2_32_PRESCALER	 : SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
			 	 	 	 	 	 	 	   CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 5: Clock Source = 64 Prescaler */
		case TMR_u8_TMR_2_64_PRESCALER	 : CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 6: Clock Source = 128 Prescaler */
		case TMR_u8_TMR_2_128_PRESCALER	 : SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 7: Clock Source = 256 Prescaler */
		case TMR_u8_TMR_2_256_PRESCALER	 : CLR_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
		/* Case 8: Clock Source = 1024 Prescaler */
		case TMR_u8_TMR_2_1024_PRESCALER : SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS20_BIT ); SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS21_BIT );
										   SET_BIT( TMR_u8_TCCR2_REG, TMR_u8_CS22_BIT ); break;
	}
}

/* 4.Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Timer ( TimerId ), the address is passed through a pointer to function ( OVFInterruptAction ), and then pass this address to ISR function. */
u8	 TMR_u8OVFSetCallBack	   ( u8 Copy_u8TimerId, void ( * Copy_pfOVFInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that TimertId is in the valid range, and Pointer to Function is not equal to NULL */
	if( ( Copy_u8TimerId <= TMR_u8_TMR2 ) && ( Copy_pfOVFInterruptAction != NULL ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function ( OVFInterruptAction ) into Global Array of Pointers to Functions ( OVFInterruptsAction ) in the passed index ( TimerId ). */
		TMR_ApfOVFInterruptsAction[Copy_u8TimerId] = Copy_pfOVFInterruptAction;
	}

	else
	{
		/* Update error state = NOK, wrong TimertId or Pointer to Function is NULL! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/* 5.Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Timer ( TimerId ), the address is passed through a pointer to function ( COMPInterruptAction ), and then pass this address to ISR function. */
u8	 TMR_u8COMPSetCallBack	   ( u8 Copy_u8TimerId, u8 Copy_u8Timer1ChannelId, void ( * Copy_pfCOMPInterruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that TimertId and Timer1ChannelId are in the valid range, and Pointer to Function is not equal to NULL */
	if( ( Copy_u8TimerId <= TMR_u8_TMR2 ) && ( Copy_u8Timer1ChannelId <= TMR_u8_TMR_1_CHANNEL_B ) && ( Copy_pfCOMPInterruptAction != NULL ) )
	{
		/* Check the required Timer1ChannelId */
		switch( Copy_u8Timer1ChannelId )
		{
			case TMR_u8_NO_CHANNEL	   : 										 break;
			case TMR_u8_TMR_1_CHANNEL_A: TMR_u8Timer1COMPAFlag = TMR_u8_FLAG_UP; break;
			case TMR_u8_TMR_1_CHANNEL_B: TMR_u8Timer1COMPBFlag = TMR_u8_FLAG_UP; break;
		}

		/* Store the passed address of function ( in APP Layer ) through pointer to function ( COMPInterruptAction ) into Global Array of Pointers to Functions ( COMPInterruptsAction ) in the passed index ( TimerId ). */
		TMR_ApfCOMPInterruptsAction[Copy_u8TimerId] = Copy_pfCOMPInterruptAction;
	}

	else
	{
		/* Update error state = NOK, wrong TimertId or Timer1ChannelId, or Pointer to Function is NULL! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/* 6.Function to Get Counter Value from TCNTn Register. */
u8	 TMR_u8GetCounterValue	   ( u8 Copy_u8TimerId, u16 * Copy_pu16CounterValue )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that TimertId is in the valid range, and Pointer is not equal to NULL  */
	if( ( Copy_u8TimerId <= TMR_u8_TMR2 ) && ( Copy_pu16CounterValue != NULL ) )
	{
		/* Check the required TimerId */
		switch( Copy_u8TimerId )
		{
			case TMR_u8_TMR0: * Copy_pu16CounterValue = ( u16 ) TMR_u8_TCNT0_REG; break;
			case TMR_u8_TMR1: * Copy_pu16CounterValue = TMR_u16_TCNT1_REG; 		  break;
			case TMR_u8_TMR2: * Copy_pu16CounterValue = ( u16 ) TMR_u8_TCNT2_REG; break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong TimertId or Pointer is NULL!! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/* 7.Function to Set Compare Match Value in OCRn Register. */
u8	 TMR_u8SetCompareMatchValue( u8 Copy_u8TimerId, u8 Copy_u8Timer1ChannelId, u16 Copy_u16CompareMatchValue )
{
	/* Define local variable to set the error state = OK */
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Make sure that TimertId and Timer1ChannelId are in the valid range */
	if( ( Copy_u8TimerId <= TMR_u8_TMR2 ) && ( Copy_u8Timer1ChannelId <= TMR_u8_TMR_1_CHANNEL_B ) )
	{
		/* Check the required TimerId */
		switch( Copy_u8TimerId )
		{
			case TMR_u8_TMR0: TMR_u8_OCR0_REG = ( u8 ) Copy_u16CompareMatchValue; break;

			case TMR_u8_TMR1:
				/* Check the required Timer1ChannelId */
				switch( Copy_u8Timer1ChannelId )
				{
					case TMR_u8_NO_CHANNEL	   : 												break;
					case TMR_u8_TMR_1_CHANNEL_A: TMR_u16_OCR1A_REG = Copy_u16CompareMatchValue; break;
					case TMR_u8_TMR_1_CHANNEL_B: TMR_u16_OCR1A_REG = Copy_u16CompareMatchValue; break;
				}
			break;

			case TMR_u8_TMR2: TMR_u8_OCR2_REG = ( u8 ) Copy_u16CompareMatchValue; break;
		}
	}

	else
	{
		/* Update error state = NOK, wrong TimertId or Timer1ChannelId! */
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/* 8.Function to Set Input Capture Value in ICR1 Register ( in TMR1 only ). */
void TMR_u8SetInputCaptureValue( u16 Copy_u16InputCaptureValue )
{
	TMR_u16_ICR1_REG = Copy_u16InputCaptureValue;
}


/*
 *  8-bit Timer/Counter2 ISR
 */
/* ISR functions' prototypes of TMR2 Compare Match (COMP), and TMR2 Overflow (OVF) respectively */
void __vector_4( void )		__attribute__((signal));
void __vector_5( void )		__attribute__((signal));

/* ISR function implementation of TMR2 COMP */
void __vector_4( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer2 counting register ( TCNT2 = 8 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterCOMP = 0;

	/* Increment the COMP Counter after every Overflow in Timer2 counting register */
	Local_u16CounterCOMP++;

	/* Check whether the COMP Counter reached the desired number of Overflows  */
	if( Local_u16CounterCOMP == TMR_u16_TMR_2_NUM_OF_OVERFLOWS )
	{
		/* Reset the COMP Counter to 0 */
		Local_u16CounterCOMP = 0;

		/* Make sure that TMR2 index of the Global Array is not equal to NULL */
		if( TMR_ApfCOMPInterruptsAction[TMR_u8_TMR2] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( COMPInterruptsAction ) */
			TMR_ApfCOMPInterruptsAction[TMR_u8_TMR2]();
		}
	}
}

/* ISR function implementation of TMR2 OVF */
void __vector_5( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer2 counting register ( TCNT2 = 8 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterOVF = 0;

	/* Increment the OVF Counter after every Overflow in Timer2 counting register */
	Local_u16CounterOVF++;

	/* Check whether the OVF Counter reached the desired number of Overflows  */
	if( Local_u16CounterOVF == TMR_u16_TMR_2_NUM_OF_OVERFLOWS )
	{
		/* Reset Preload Value */
		TMR_u8_TCNT2_REG = TMR_u8_TMR_2_PRELOAD_VALUE;

		/* Reset the OVF Counter to 0 */
		Local_u16CounterOVF = 0;

		/* Make sure that TMR2 index of the Global Array is not equal to NULL */
		if( TMR_ApfOVFInterruptsAction[TMR_u8_TMR2] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( OVFInterruptsAction ) */
			TMR_ApfOVFInterruptsAction[TMR_u8_TMR2]();
		}
	}
}

/*
 * 16-bit Timer/Counter1 ISR
 */
/* ISR functions' prototypes of TMR1 Capture Event (CAPT), TMR1 Compare Match A (COMPA), TMR1 Compare Match B (COMPB), and TMR1 Overflow (OVF) respectively */
void __vector_6( void )		__attribute__((signal));
void __vector_7( void )		__attribute__((signal));
void __vector_8( void )		__attribute__((signal));
void __vector_9( void )		__attribute__((signal));

/* ISR function implementation of TMR1 CAPT */
void __vector_6( void )
{

}

/* ISR function implementation of TMR1 COMPA */
void __vector_7( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer1 counting register ( TCNT1 = 16 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterCOMP = 0;

	/* Increment the COMP Counter after every Overflow in Timer1 counting register */
	Local_u16CounterCOMP++;

	/* Check whether the COMP Counter reached the desired number of Overflows  */
	if( Local_u16CounterCOMP == TMR_u16_TMR_1_NUM_OF_OVERFLOWS )
	{
		/* Reset the COMP Counter to 0 */
		Local_u16CounterCOMP = 0;

		/* Make sure that TMR1 index of the Global Array is not equal to NULL, and Channel A COMPFlag is raised */
		if( ( TMR_ApfCOMPInterruptsAction[TMR_u8_TMR1] != NULL ) && ( TMR_u8Timer1COMPAFlag != TMR_u8_FLAG_DOWN ) )
		{
			/* Reset Channel A COMPFlag to 0 */
			TMR_u8Timer1COMPAFlag = TMR_u8_FLAG_DOWN;

			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( COMPInterruptsAction ) */
			TMR_ApfCOMPInterruptsAction[TMR_u8_TMR1]();
		}
	}
}

/* ISR function implementation of TMR1 COMPB */
void __vector_8( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer1 counting register ( TCNT1 = 16 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterCOMP = 0;

	/* Increment the COMP Counter after every Overflow in Timer1 counting register */
	Local_u16CounterCOMP++;

	/* Check whether the COMP Counter reached the desired number of Overflows  */
	if( Local_u16CounterCOMP == TMR_u16_TMR_1_NUM_OF_OVERFLOWS )
	{
		/* Reset the COMP Counter to 0 */
		Local_u16CounterCOMP = 0;

		/* Make sure that TMR1 index of the Global Array is not equal to NULL, and Channel B COMPFlag is raised */
		if( ( TMR_ApfCOMPInterruptsAction[TMR_u8_TMR1] != NULL ) && ( TMR_u8Timer1COMPBFlag != TMR_u8_FLAG_DOWN ) )
		{
			/* Reset Channel B COMPFlag to 0 */
			TMR_u8Timer1COMPBFlag = TMR_u8_FLAG_DOWN;

			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( COMPInterruptsAction ) */
			TMR_ApfCOMPInterruptsAction[TMR_u8_TMR1]();
		}
	}
}

/* ISR function implementation of TMR1 OVF */
void __vector_9( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer1 counting register ( TCNT1 = 16 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterOVF = 0;

	/* Increment the OVF Counter after every Overflow in Timer1 counting register */
	Local_u16CounterOVF++;

	/* Check whether the OVF Counter reached the desired number of Overflows  */
	if( Local_u16CounterOVF == TMR_u16_TMR_1_NUM_OF_OVERFLOWS )
	{
		/* Reset Preload Value */
		TMR_u16_TCNT1_REG = TMR_u16_TMR_1_PRELOAD_VALUE;

		/* Reset the OVF Counter to 0 */
		Local_u16CounterOVF = 0;

		/* Make sure that TMR1 index of the Global Array is not equal to NULL */
		if( TMR_ApfOVFInterruptsAction[TMR_u8_TMR1] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( OVFInterruptsAction ) */
			TMR_ApfOVFInterruptsAction[TMR_u8_TMR1]();
		}
	}
}

/*
 *  8-bit Timer/Counter0 ISR
 */
/* ISR functions' prototypes of TMR0 Compare Match (COMP), and TMR0 Overflow (OVF) respectively */
void __vector_10( void )		__attribute__((signal));
void __vector_11( void )		__attribute__((signal));

/* ISR function implementation of TMR0 COMP */
void __vector_10( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer0 counting register ( TCNT0 = 8 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterCOMP = 0;

	/* Increment the COMP Counter after every Overflow in Timer0 counting register */
	Local_u16CounterCOMP++;

	/* Check whether the COMP Counter reached the desired number of Overflows  */
	if( Local_u16CounterCOMP == TMR_u16_TMR_0_NUM_OF_OVERFLOWS )
	{
		/* Reset the COMP Counter to 0 */
		Local_u16CounterCOMP = 0;

		/* Make sure that TMR0 index of the Global Array is not equal to NULL */
		if( TMR_ApfCOMPInterruptsAction[TMR_u8_TMR0] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( COMPInterruptsAction ) */
			TMR_ApfCOMPInterruptsAction[TMR_u8_TMR0]();
		}
	}
}

/* ISR function implementation of TMR0 OVF */
void __vector_11( void )
{
	/* Static Counter, in case the desired time to be counted; is more than Timer0 counting register ( TCNT0 = 8 bits ), i.e.: to count the number of Overflows  */
	static u16 Local_u16CounterOVF = 0;

	/* Increment the OVF Counter after every Overflow in Timer0 counting register */
	Local_u16CounterOVF++;

	/* Check whether the OVF Counter reached the desired number of Overflows  */
	if( Local_u16CounterOVF == TMR_u16_TMR_0_NUM_OF_OVERFLOWS )
	{
		/* Reset Preload Value */
		TMR_u8_TCNT0_REG = TMR_u8_TMR_0_PRELOAD_VALUE;

		/* Reset the OVF Counter to 0 */
		Local_u16CounterOVF = 0;

		/* Make sure that TMR0 index of the Global Array is not equal to NULL */
		if( TMR_ApfOVFInterruptsAction[TMR_u8_TMR0] != NULL )
		{
			/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( OVFInterruptsAction ) */
			TMR_ApfOVFInterruptsAction[TMR_u8_TMR0]();
		}
	}
}