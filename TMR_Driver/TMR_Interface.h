/*
 * TMR_Interface.h
 *
 *   Created on: Jul 27, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Timers (TMR) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

/* The 3 Timers counted from 0 to 2 */
#define TMR_u8_TMR0							0
#define TMR_u8_TMR1 						1
#define TMR_u8_TMR2 						2

/* The 3 Timers Channels counted from 0 to 2 */
#define TMR_u8_NO_CHANNEL					0
#define TMR_u8_TMR_1_CHANNEL_A				1
#define TMR_u8_TMR_1_CHANNEL_B				2

#define TMR_u8_FLAG_DOWN					0
#define TMR_u8_FLAG_UP						1

/* Functions' Prototypes */
void TMR_vdTMR0Initialization  ( void );
void TMR_vdTMR1Initialization  ( void );
void TMR_vdTMR2Initialization  ( void );
u8	 TMR_u8OVFSetCallBack	   ( u8 Copy_u8TimerId, void ( * Copy_pfOVFInterruptAction ) ( void ) );
u8	 TMR_u8COMPSetCallBack	   ( u8 Copy_u8TimerId, u8 Copy_u8Timer1ChannelId, void ( * Copy_pfCOMPInterruptAction ) ( void ) );
u8	 TMR_u8GetCounterValue	   ( u8 Copy_u8TimerId, u16 * Copy_pu16CounterValue );
u8	 TMR_u8SetCompareMatchValue( u8 Copy_u8TimerId, u8 Copy_u8Timer1ChannelId, u16 Copy_u16CompareMatchValue );
void TMR_u8SetInputCaptureValue( u16 Copy_u16InputCaptureValue );

#endif /* TMR_INTERFACE_H_ */