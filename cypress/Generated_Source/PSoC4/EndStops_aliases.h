/*******************************************************************************
* File Name: EndStops.h  
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

#if !defined(CY_PINS_EndStops_ALIASES_H) /* Pins EndStops_ALIASES_H */
#define CY_PINS_EndStops_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define EndStops_0			(EndStops__0__PC)
#define EndStops_0_PS		(EndStops__0__PS)
#define EndStops_0_PC		(EndStops__0__PC)
#define EndStops_0_DR		(EndStops__0__DR)
#define EndStops_0_SHIFT	(EndStops__0__SHIFT)
#define EndStops_0_INTR	((uint16)((uint16)0x0003u << (EndStops__0__SHIFT*2u)))

#define EndStops_1			(EndStops__1__PC)
#define EndStops_1_PS		(EndStops__1__PS)
#define EndStops_1_PC		(EndStops__1__PC)
#define EndStops_1_DR		(EndStops__1__DR)
#define EndStops_1_SHIFT	(EndStops__1__SHIFT)
#define EndStops_1_INTR	((uint16)((uint16)0x0003u << (EndStops__1__SHIFT*2u)))

#define EndStops_2			(EndStops__2__PC)
#define EndStops_2_PS		(EndStops__2__PS)
#define EndStops_2_PC		(EndStops__2__PC)
#define EndStops_2_DR		(EndStops__2__DR)
#define EndStops_2_SHIFT	(EndStops__2__SHIFT)
#define EndStops_2_INTR	((uint16)((uint16)0x0003u << (EndStops__2__SHIFT*2u)))

#define EndStops_3			(EndStops__3__PC)
#define EndStops_3_PS		(EndStops__3__PS)
#define EndStops_3_PC		(EndStops__3__PC)
#define EndStops_3_DR		(EndStops__3__DR)
#define EndStops_3_SHIFT	(EndStops__3__SHIFT)
#define EndStops_3_INTR	((uint16)((uint16)0x0003u << (EndStops__3__SHIFT*2u)))

#define EndStops_4			(EndStops__4__PC)
#define EndStops_4_PS		(EndStops__4__PS)
#define EndStops_4_PC		(EndStops__4__PC)
#define EndStops_4_DR		(EndStops__4__DR)
#define EndStops_4_SHIFT	(EndStops__4__SHIFT)
#define EndStops_4_INTR	((uint16)((uint16)0x0003u << (EndStops__4__SHIFT*2u)))

#define EndStops_5			(EndStops__5__PC)
#define EndStops_5_PS		(EndStops__5__PS)
#define EndStops_5_PC		(EndStops__5__PC)
#define EndStops_5_DR		(EndStops__5__DR)
#define EndStops_5_SHIFT	(EndStops__5__SHIFT)
#define EndStops_5_INTR	((uint16)((uint16)0x0003u << (EndStops__5__SHIFT*2u)))

#define EndStops_INTR_ALL	 ((uint16)(EndStops_0_INTR| EndStops_1_INTR| EndStops_2_INTR| EndStops_3_INTR| EndStops_4_INTR| EndStops_5_INTR))


#endif /* End Pins EndStops_ALIASES_H */


/* [] END OF FILE */
