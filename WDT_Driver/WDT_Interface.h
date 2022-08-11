/*
 * WDT_Interface.h
 *
 *   Created on: Aug 5, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Watch Dog Timer (WDT) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

/* Watchdog Timer Prescalers */
#define WDT_u8_16K_PRESCALER		0		// Typical Time-out at: Vcc = 3.0V -> 17.1 ms , Vcc = 5.0V -> 16.3 ms
#define WDT_u8_32K_PRESCALER		1       // Typical Time-out at: Vcc = 3.0V -> 34.3 ms , Vcc = 5.0V -> 32.5 ms
#define WDT_u8_64K_PRESCALER		2       // Typical Time-out at: Vcc = 3.0V -> 68.5 ms , Vcc = 5.0V -> 65 ms
#define WDT_u8_128K_PRESCALER		3       // Typical Time-out at: Vcc = 3.0V -> 0.14 s , Vcc = 5.0V -> 0.13 s
#define WDT_u8_256K_PRESCALER		4       // Typical Time-out at: Vcc = 3.0V -> 0.27 s , Vcc = 5.0V -> 0.26 s
#define WDT_u8_512K_PRESCALER		5       // Typical Time-out at: Vcc = 3.0V -> 0.55 s , Vcc = 5.0V -> 0.52 s
#define WDT_u8_1024K_PRESCALER		6       // Typical Time-out at: Vcc = 3.0V -> 1.1 s , Vcc = 5.0V -> 1.0 s
#define WDT_u8_2048K_PRESCALER		7       // Typical Time-out at: Vcc = 3.0V -> 2.2 s , Vcc = 5.0V -> 2.1 s

/* Functions' Prototypes */
u8	 WDT_u8Enable ( u8 Copy_u8Prescaler );
void WDT_vdDisable( void );

#endif /* WDT_INTERFACE_H_ */