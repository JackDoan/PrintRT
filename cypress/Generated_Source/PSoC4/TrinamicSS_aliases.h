/*******************************************************************************
* File Name: TrinamicSS.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TrinamicSS_ALIASES_H) /* Pins TrinamicSS_ALIASES_H */
#define CY_PINS_TrinamicSS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TrinamicSS_0			(TrinamicSS__0__PC)
#define TrinamicSS_0_PS		(TrinamicSS__0__PS)
#define TrinamicSS_0_PC		(TrinamicSS__0__PC)
#define TrinamicSS_0_DR		(TrinamicSS__0__DR)
#define TrinamicSS_0_SHIFT	(TrinamicSS__0__SHIFT)
#define TrinamicSS_0_INTR	((uint16)((uint16)0x0003u << (TrinamicSS__0__SHIFT*2u)))

#define TrinamicSS_1			(TrinamicSS__1__PC)
#define TrinamicSS_1_PS		(TrinamicSS__1__PS)
#define TrinamicSS_1_PC		(TrinamicSS__1__PC)
#define TrinamicSS_1_DR		(TrinamicSS__1__DR)
#define TrinamicSS_1_SHIFT	(TrinamicSS__1__SHIFT)
#define TrinamicSS_1_INTR	((uint16)((uint16)0x0003u << (TrinamicSS__1__SHIFT*2u)))

#define TrinamicSS_2			(TrinamicSS__2__PC)
#define TrinamicSS_2_PS		(TrinamicSS__2__PS)
#define TrinamicSS_2_PC		(TrinamicSS__2__PC)
#define TrinamicSS_2_DR		(TrinamicSS__2__DR)
#define TrinamicSS_2_SHIFT	(TrinamicSS__2__SHIFT)
#define TrinamicSS_2_INTR	((uint16)((uint16)0x0003u << (TrinamicSS__2__SHIFT*2u)))

#define TrinamicSS_3			(TrinamicSS__3__PC)
#define TrinamicSS_3_PS		(TrinamicSS__3__PS)
#define TrinamicSS_3_PC		(TrinamicSS__3__PC)
#define TrinamicSS_3_DR		(TrinamicSS__3__DR)
#define TrinamicSS_3_SHIFT	(TrinamicSS__3__SHIFT)
#define TrinamicSS_3_INTR	((uint16)((uint16)0x0003u << (TrinamicSS__3__SHIFT*2u)))

#define TrinamicSS_INTR_ALL	 ((uint16)(TrinamicSS_0_INTR| TrinamicSS_1_INTR| TrinamicSS_2_INTR| TrinamicSS_3_INTR))


#endif /* End Pins TrinamicSS_ALIASES_H */


/* [] END OF FILE */
