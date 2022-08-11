/*
 * ADC_Private.h
 *
 *   Created on: Apr 28, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) registers' locations.
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/* Registers' Locations */
#define ADC_u8_ADMUX_REG	*( ( volatile u8 * ) 0x27 )
#define ADC_u8_ADCSRA_REG	*( ( volatile u8 * ) 0x26 )
#define ADC_u8_ADCH_REG		*( ( volatile u8 * ) 0x25 )
#define ADC_u8_ADCL_REG		*( ( volatile u8 * ) 0x24 )
/* DataType is u16 * in order to get both registers ( i.e. ADCH and ADCL ) locations in memory */
#define ADC_u16_ADC_REG		*( ( volatile u16 * ) 0x24 )

#define ADC_u8_SFIOR_REG	*( ( volatile u8 * ) 0x50 )

#endif /* ADC_PRIVATE_H_ */