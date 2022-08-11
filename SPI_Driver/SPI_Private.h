/*
 * SPI_Private.h
 *
 *   Created on: Jul 27, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Serial Peripheral Interface (SPI) registers' locations and description.
 */
 
#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/* Registers' Locations */
#define SPI_u8_SPDR_REG			* ( ( volatile  u8 * ) 0x2F )
#define SPI_u8_SPSR_REG			* ( ( volatile  u8 * ) 0x2E )
#define SPI_u8_SPCR_REG			* ( ( volatile  u8 * ) 0x2D )

/* Registers' Description */
/* SPI Status Register – SPSR */
/* Bit 7 – SPIF: SPI Interrupt Flag */
#define SPI_u8_SPIF_BIT			7
/* Bit 6 – WCOL: Write COLlision Flag */
#define SPI_u8_WCOL_BIT			6
/* Bit 0 – SPI2X: Double SPI Speed Bit */
#define SPI_u8_SPI2X_BIT		0
/* End of SPSR Register */

/* SPI Control Register – SPCR */
/* Bit 7 – SPIE: SPI Interrupt Enable */
#define SPI_u8_SPIE_BIT			7
/* Bit 6 – SPE: SPI Enable */
#define SPI_u8_SPE_BIT			6
/* Bit 5 – DORD: Data Order */
#define SPI_u8_DORD_BIT			5
/* Bit 4 – MSTR: Master/Slave Select */
#define SPI_u8_SPE_BIT			4
/* Bit 3 – CPOL: Clock Polarity */
#define SPI_u8_MSTR_BIT			3
/* Bit 2 – CPHA: Clock Phase */
#define SPI_u8_CPHA_BIT			2
/* Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0 */
#define SPI_u8_SPR1_BIT			1
#define SPI_u8_SPR0_BIT			0
/* End of SPCR Register */

#endif /* TMR_PRIVATE_H_ */