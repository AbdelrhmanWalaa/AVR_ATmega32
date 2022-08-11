/*
 * SPI_Interface.h
 *
 *   Created on: Jul 27, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Serial Peripheral Interface (SPI) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */
 
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/* Functions' Prototypes */
void SPI_vdInitialization( void );
void SPI_vdSendData	  	 ( u8 Copy_u8SentData );
void SPI_vdRecvData	  	 ( u8 Copy_u8RecvData );

#endif /* SPI_INTERFACE_H_ */