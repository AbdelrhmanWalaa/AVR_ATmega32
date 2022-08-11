/*
 * ADC_Interface.h
 *
 *   Created on: Apr 28, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Successive Approximation Analog to Digital Converter (SAADC) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/* ADC Multiplexer Selection Register – ADMUX */
/*
 * Bit 7, 6 –> REFS1, REFS0: Voltage Reference Selection Bits
 */
#define ADC_u8_REFS1_BIT	7
#define ADC_u8_REFS0_BIT	6
/*
 * Bit 5 –> ADLAR: ADC Left Adjust Result
 */
#define ADC_u8_ADLAR_BIT	5
/*
 * Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
 */
/* Channels 0->7: Single Ended Input Channels */
#define ADC_u8_CHANNEL_0	0
#define ADC_u8_CHANNEL_1	1
#define ADC_u8_CHANNEL_2	2
#define ADC_u8_CHANNEL_3	3
#define ADC_u8_CHANNEL_4	4
#define ADC_u8_CHANNEL_5	5
#define ADC_u8_CHANNEL_6	6
#define ADC_u8_CHANNEL_7	7
/* Channels 8->29: Differential Input Channels */
#define ADC_u8_CHANNEL_8	8
#define ADC_u8_CHANNEL_9	9
#define ADC_u8_CHANNEL_10	10
#define ADC_u8_CHANNEL_11	11
#define ADC_u8_CHANNEL_12	12
#define ADC_u8_CHANNEL_13	13
#define ADC_u8_CHANNEL_14	14
#define ADC_u8_CHANNEL_15	15
#define ADC_u8_CHANNEL_16	16
#define ADC_u8_CHANNEL_17	17
#define ADC_u8_CHANNEL_18	18
#define ADC_u8_CHANNEL_19	19
#define ADC_u8_CHANNEL_20	20
#define ADC_u8_CHANNEL_21	21
#define ADC_u8_CHANNEL_22	22
#define ADC_u8_CHANNEL_23	23
#define ADC_u8_CHANNEL_24	24
#define ADC_u8_CHANNEL_25	25
#define ADC_u8_CHANNEL_26	26
#define ADC_u8_CHANNEL_27	27
#define ADC_u8_CHANNEL_28	28
#define ADC_u8_CHANNEL_29	29
/* Channels 30->31: Testing Purpose Channels */
#define ADC_u8_CHANNEL_30	30
#define ADC_u8_CHANNEL_31	31

/* ADC Control and Status Register A – ADCSRA */
/*
 * Bit 7 – ADEN: ADC Enable
 */
#define ADC_u8_ADEN_BIT		7
/*
 * Bit 6 – ADSC: ADC Start Conversion
 */
#define ADC_u8_ADSC_BIT		6
/*
 * Bit 5 – ADATE: ADC Auto Trigger Enable
 */
#define ADC_u8_ADATE_BIT	5
/*
 * Bit 4 – ADIF: ADC Interrupt Flag
 */
#define ADC_u8_ADIF_BIT		4
/*
 * Bit 3 – ADIE: ADC Interrupt Enable
 */
#define ADC_u8_ADIE_BIT		3
/*
 * Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
 */
#define ADC_u8_ADPS2_BIT	2
#define ADC_u8_ADPS1_BIT	1
#define ADC_u8_ADPS0_BIT	0

/* Special FunctionIO Register – SFIOR */
/*
 * Bit 7:5 – ADTS2:0: ADC Auto Trigger Source
 */
#define ADC_u8_ADTS2_BIT	7
#define ADC_u8_ADTS1_BIT	6
#define ADC_u8_ADTS0_BIT	5

/* Functions' prototypes */
void ADC_vdInitialization ( void );
u8	 ADC_u8GetDigitalValue( u8 Copy_u8ChannelId, u16 * Copy_pu16DigitalValue );

#endif /* ADC_INTERFACE_H_ */