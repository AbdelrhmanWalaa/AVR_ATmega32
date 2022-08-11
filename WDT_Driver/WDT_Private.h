/*
 * WDT_Private.h
 *
 *   Created on: Aug 5, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Watch Dog Timer (WDT) registers' locations and description.
 */

#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

/* Registers' Locations */
#define WDT_u8_WDTCR_REG		* ( ( volatile u8 * ) 0x41 )

/* Registers' Description */
/* Watchdog Timer Control Register – WDTCR */
/* Bit 4 – WDTOE: Watchdog Turn-off Enable */
#define WDT_u8_WDTOE_BIT		4
/* Bit 3 – WDE: Watchdog Enable */
#define WDT_u8_WDE_BIT			3
/* Bits 2..0 – WDP2, WDP1, WDP0: Watchdog Timer Prescaler 2, 1, and 0 */
#define WDT_u8_WDP2_BIT			2
#define WDT_u8_WDP1_BIT			1
#define WDT_u8_WDP0_BIT			0
/* End of WDTCR Register */

#endif /* WDT_PRIVATE_H_ */