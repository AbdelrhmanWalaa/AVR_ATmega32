/*
 * ADC_Config.h
 *
 *   Created on: Apr 28, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) pre-build configurations, through which user can configure before using the SAADC peripheral.
 */
 
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/* ADC Configurations Definitions */
/* Voltage Reference Selections for ADC */
#define ADC_u8_AREF_VOLT				0
#define ADC_u8_AVCC_VOLT				1
#define ADC_u8_INTERNAL_VOLT 			2

/* Presentation of the ADC Conversion Result */
#define	ADC_u8_RIGHT_ADJUST				0
#define ADC_u8_LEFT_ADJUST				1

/* Auto Trigger Disable/Enable */
#define	ADC_u8_AUTO_TRIGGER_DISABLE		0
#define ADC_u8_AUTO_TRIGGER_ENABLE		1

/* Auto Trigger Source Selections for ADC */
#define	ADC_u8_FREE_RUNNING_MODE		0
#define ADC_u8_ANALOG_COMPARATOR		1
#define ADC_u8_EXI_REQUEST_0			2
#define ADC_u8_TMR_0_COMPARE_MATCH		3
#define ADC_u8_TMR_0_OVERFLOW			4
#define ADC_u8_TMR_COMPARE_MATCH_B		5
#define ADC_u8_TMR_1_OVERFLOW			6
#define ADC_u8_TMR_1_CAPTURE_EVENT		7

/* Prescaler Selections for ADC */
#define	ADC_u8_DIVISION_FACTOR_2		0
#define ADC_u8_DIVISION_FACTOR_4		1
#define ADC_u8_DIVISION_FACTOR_8		2
#define ADC_u8_DIVISION_FACTOR_16		3
#define ADC_u8_DIVISION_FACTOR_32		4
#define ADC_u8_DIVISION_FACTOR_64		5
#define ADC_u8_DIVISION_FACTOR_128		6
/* End of Configurations Definitions */

/* ADC Configurations */
/* Voltage Reference Selections for ADC */
/* Options: ADC_u8_AREF_VOLT			// AREF, Internal Vref turned off
 * 			ADC_u8_AVCC_VOLT			// AVCC with external capacitor at AREF pin
 * 			ADC_u8_INTERNAL_VOLT 	    // Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */
#define  ADC_u8_VREF_SELECT				ADC_u8_AVCC_VOLT

/* Presentation of the ADC Conversion Result */
/* Options: ADC_u8_RIGHT_ADJUST
 * 			ADC_u8_LEFT_ADJUST
 */
#define  ADC_u8_RESULT_ADJUST			ADC_u8_RIGHT_ADJUST

/* Auto Trigger Disable/Enable */
/* Options: ADC_u8_AUTO_TRIGGER_DISABLE
 * 			ADC_u8_AUTO_TRIGGER_ENABLE
 */
#define  ADC_u8_AUTO_TRIGGER_SELECT		ADC_u8_AUTO_TRIGGER_DISABLE

/* Auto Trigger Source Selections for ADC */
/* Options: ADC_u8_FREE_RUNNING_MODE
 * 			ADC_u8_ANALOG_COMPARATOR
 * 			ADC_u8_EXI_REQUEST_0
 * 			ADC_u8_TMR_0_COMPARE_MATCH
 * 			ADC_u8_TMR_0_OVERFLOW
 * 			ADC_u8_TMR_COMPARE_MATCH_B
 * 			ADC_u8_TMR_1_OVERFLOW
 * 			ADC_u8_TMR_1_CAPTURE_EVENT
 */
#define  ADC_u8_AUTO_TRIGGER_SOURCE		ADC_u8_FREE_RUNNING_MODE

/* Prescaler Selections for ADC */
/* Options: ADC_u8_DIVISION_FACTOR_2
 * 			ADC_u8_DIVISION_FACTOR_4
 * 			ADC_u8_DIVISION_FACTOR_8
 * 			ADC_u8_DIVISION_FACTOR_16
 * 			ADC_u8_DIVISION_FACTOR_32
 * 			ADC_u8_DIVISION_FACTOR_64
 * 			ADC_u8_DIVISION_FACTOR_128
 */
#define  ADC_u8_PRESCALER_SELECT		ADC_u8_DIVISION_FACTOR_64
/* End of Configurations */

#endif /* ADC_CONFIG_H_ */