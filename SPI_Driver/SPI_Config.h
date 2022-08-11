/*
 * SPI_Config.h
 *
 *   Created on: Jul 27, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Serial Peripheral Interface (SPI) pre-build configurations, through which user can configure before using the SPI peripheral.
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* SPI Configurations' Definitions */
/* Master/Slave Mode */
#define SPI_u8_SLAVE_MODE			0
#define SPI_u8_MASTER_MODE			1

/* Data Order */
#define SPI_u8_LSB_FIRST			0
#define SPI_u8_MSB_FIRST			1

/* Interrupt Enable */
#define SPI_u8_INT_DISABLE			0
#define SPI_u8_INT_ENABLE			1

/* Clock Rate */
#define SPI_u8_SCK_FREQ_2			0
#define SPI_u8_SCK_FREQ_4			1
#define SPI_u8_SCK_FREQ_8			2
#define SPI_u8_SCK_FREQ_16			3
#define SPI_u8_SCK_FREQ_32			4
#define SPI_u8_SCK_FREQ_64			5
#define SPI_u8_SCK_FREQ_128			6
/* End of SPI Configurations' Definitions */

/* SPI Configurations */
/* Master/Slave Mode Select */
/* Options: SPI_u8_SLAVE_MODE
 *			SPI_u8_MASTER_MODE
 */
#define SPI_u8_MODE_SELECT			SPI_u8_MASTER_MODE
 
/* Data Order Select */
/* Options: SPI_u8_LSB_FIRST
 * 			SPI_u8_MSB_FIRST
 */
#define SPI_u8_DATA_ORDER_SELECT 	SPI_u8_LSB_FIRST

/* Interrupt Enable Select */
/* Options: SPI_u8_INT_DISABLE
 * 			SPI_u8_INT_ENABLE
 */
#define SPI_u8_INT_ENABLE_SELECT	SPI_u8_INT_DISABLE

/* Clock Rate Select */
/* Options: SPI_u8_SCK_FREQ_2				// Fosc/2
 * 			SPI_u8_SCK_FREQ_4				// Fosc/4
 * 			SPI_u8_SCK_FREQ_8				// Fosc/8
 * 			SPI_u8_SCK_FREQ_16				// Fosc/16
 * 			SPI_u8_SCK_FREQ_32				// Fosc/32
 * 			SPI_u8_SCK_FREQ_64				// Fosc/64
 * 			SPI_u8_SCK_FREQ_128				// Fosc/128
 */
#define SPI_u8_CLOCK_RATE_SELECT	SPI_u8_SCK_FREQ_8
/* End of SPI Configurations */

#endif /* SPI_CONFIG_H_ */