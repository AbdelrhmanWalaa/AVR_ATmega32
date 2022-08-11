/*
 * GLI_Program.c
 *
 *   Created on: Apr 25, 2021
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all Global Interrupt (GLI) functions' implementations.
 */

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GLI_Interface.h"
#include "GLI_Private.h"

/* 1.Function to set I bit in SREG, to enable the Global Interrupt Enable (GIE). */
void GLI_vdEnableGIE ( void )
{
	SET_BIT( GLI_u8_SREG_REG, GLI_u8_I_BIT );
}

/* 2.Function to clear I bit in SREG, to disable the Global Interrupt Enable (GIE). */
void GLI_vdDisableGIE( void )
{
	CLR_BIT( GLI_u8_SREG_REG, GLI_u8_I_BIT );
}