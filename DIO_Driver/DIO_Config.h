/*
 * DIO_Config.h
 *
 *   Created on: Mar 31, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Digital Input Output (DIO) pre-build configurations, through which user can configure before using the DIO peripheral.
 */
 
#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_
 
/* Pinouts ATmega32(L): */
/*
					PDIP
				    -------------
		   (XCK/T0) PB0 -| 1		40 |- PA0 (ADC0)
		       (T1) PB1 -| 2		39 |- PA1 (ADC1)
	        (INT2/AIN0) PB2 -| 3		38 |- PA2 (ADC2)
	         (OC0/AIN1) PB3 -| 4		37 |- PA3 (ADC3)
		       (SS) PB4	-| 5		36 |- PA4 (ADC4)
		     (MOSI) PB5	-| 6		35 |- PA5 (ADC5)
		     (MISO) PB6	-| 7		34 |- PA6 (ADC6)
		      (SCK) PB7	-| 8		33 |- PA7 (ADC7)
			  RESET -| 9		32 |- AREF
			    VCC	-| 10		31 |- GND
			    GND	-| 11		30 |- AVCC
			  XTAL2	-| 12		29 |- PC0 (TOSC2)
			  XTAL1	-| 13		28 |- PC1 (TOSC1)
		      (RXD) PD0 -| 14		27 |- PC2 (TDI)
		      (TXD) PD1 -| 15		26 |- PC3 (TDO)
		     (INT0) PD2 -| 16		25 |- PC4 (TMS)
		     (INT1) PD3 -| 17		24 |- PC5 (TCK)
		     (OC1B) PD4 -| 18		23 |- PC6 (SDA)
		     (OC1A) PD5 -| 19		22 |- PC7 (SCL)
		      (ICP) PD6 -| 20		21 |- PD7 (OC2)
				    -------------
 */

/* DIO Configurations' Definitions */
/* Initial Pin Directions */
#define DIO_u8_INITIAL_INPUT				0
#define DIO_u8_INITIAL_OUTPUT				1

/* Initial Pin Values */
#define DIO_u8_INPUT_FLOATING				0
#define DIO_u8_INPUT_PULLUP_RESISTOR			1
#define DIO_u8_OUTPUT_LOW				0
#define DIO_u8_OUTPUT_HIGH				1
/* End of Configurations' Definitions */

/* DIO Configurations */
/* Initial Directions of all Pins */
/* Options: DIO_u8_INITIAL_INPUT
 *			DIO_u8_INITIAL_OUTPUT
 */

/* PORTA */
#define DIO_u8_PA0_INITIAL_DIRECTION	    DIO_u8_INITIAL_INPUT
#define DIO_u8_PA1_INITIAL_DIRECTION	    DIO_u8_INITIAL_INPUT
#define DIO_u8_PA2_INITIAL_DIRECTION	    DIO_u8_INITIAL_INPUT
#define DIO_u8_PA3_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PA4_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PA5_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PA6_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PA7_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT

/* PORTB */
#define DIO_u8_PB0_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB1_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB2_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB3_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB4_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB5_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB6_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PB7_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT

/* PORTC */
#define DIO_u8_PC0_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC1_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC2_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC3_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC4_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC5_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC6_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PC7_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT

/* PORTD */
#define DIO_u8_PD0_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD1_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD2_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD3_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD4_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD5_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD6_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT
#define DIO_u8_PD7_INITIAL_DIRECTION        DIO_u8_INITIAL_INPUT

/* Initial Values of all Pins */
/* Options: DIO_u8_INPUT_FLOATING
 *			DIO_u8_INPUT_PULLUP_RESISTOR
 *			DIO_u8_OUTPUT_LOW
 *			DIO_u8_OUTPUT_HIGH
 */

/* PORTA */
#define DIO_u8_PA0_INITIAL_VALUE		DIO_u8_INPUT_FLOATING
#define DIO_u8_PA1_INITIAL_VALUE		DIO_u8_INPUT_FLOATING
#define DIO_u8_PA2_INITIAL_VALUE		DIO_u8_INPUT_FLOATING
#define DIO_u8_PA3_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PA4_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PA5_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PA6_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PA7_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING

/* PORTB */
#define DIO_u8_PB0_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB1_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB2_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB3_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB4_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB5_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB6_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PB7_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING

/* PORTC */
#define DIO_u8_PC0_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC1_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC2_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC3_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC4_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC5_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC6_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PC7_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING

/* PORTD */
#define DIO_u8_PD0_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD1_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD2_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD3_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD4_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD5_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD6_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
#define DIO_u8_PD7_INITIAL_VALUE	        DIO_u8_INPUT_FLOATING
/* End of Configurations */

#endif /* DIO_CONFIG_H_ */
