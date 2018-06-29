/*******************************************************************************
* File Name: EndStops_1.h  
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

#if !defined(CY_PINS_EndStops_1_ALIASES_H) /* Pins EndStops_1_ALIASES_H */
#define CY_PINS_EndStops_1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define EndStops_1_0			(EndStops_1__0__PC)
#define EndStops_1_0_PS		(EndStops_1__0__PS)
#define EndStops_1_0_PC		(EndStops_1__0__PC)
#define EndStops_1_0_DR		(EndStops_1__0__DR)
#define EndStops_1_0_SHIFT	(EndStops_1__0__SHIFT)
#define EndStops_1_0_INTR	((uint16)((uint16)0x0003u << (EndStops_1__0__SHIFT*2u)))

#define EndStops_1_1			(EndStops_1__1__PC)
#define EndStops_1_1_PS		(EndStops_1__1__PS)
#define EndStops_1_1_PC		(EndStops_1__1__PC)
#define EndStops_1_1_DR		(EndStops_1__1__DR)
#define EndStops_1_1_SHIFT	(EndStops_1__1__SHIFT)
#define EndStops_1_1_INTR	((uint16)((uint16)0x0003u << (EndStops_1__1__SHIFT*2u)))

#define EndStops_1_2			(EndStops_1__2__PC)
#define EndStops_1_2_PS		(EndStops_1__2__PS)
#define EndStops_1_2_PC		(EndStops_1__2__PC)
#define EndStops_1_2_DR		(EndStops_1__2__DR)
#define EndStops_1_2_SHIFT	(EndStops_1__2__SHIFT)
#define EndStops_1_2_INTR	((uint16)((uint16)0x0003u << (EndStops_1__2__SHIFT*2u)))

#define EndStops_1_3			(EndStops_1__3__PC)
#define EndStops_1_3_PS		(EndStops_1__3__PS)
#define EndStops_1_3_PC		(EndStops_1__3__PC)
#define EndStops_1_3_DR		(EndStops_1__3__DR)
#define EndStops_1_3_SHIFT	(EndStops_1__3__SHIFT)
#define EndStops_1_3_INTR	((uint16)((uint16)0x0003u << (EndStops_1__3__SHIFT*2u)))

#define EndStops_1_4			(EndStops_1__4__PC)
#define EndStops_1_4_PS		(EndStops_1__4__PS)
#define EndStops_1_4_PC		(EndStops_1__4__PC)
#define EndStops_1_4_DR		(EndStops_1__4__DR)
#define EndStops_1_4_SHIFT	(EndStops_1__4__SHIFT)
#define EndStops_1_4_INTR	((uint16)((uint16)0x0003u << (EndStops_1__4__SHIFT*2u)))

#define EndStops_1_5			(EndStops_1__5__PC)
#define EndStops_1_5_PS		(EndStops_1__5__PS)
#define EndStops_1_5_PC		(EndStops_1__5__PC)
#define EndStops_1_5_DR		(EndStops_1__5__DR)
#define EndStops_1_5_SHIFT	(EndStops_1__5__SHIFT)
#define EndStops_1_5_INTR	((uint16)((uint16)0x0003u << (EndStops_1__5__SHIFT*2u)))

#define EndStops_1_INTR_ALL	 ((uint16)(EndStops_1_0_INTR| EndStops_1_1_INTR| EndStops_1_2_INTR| EndStops_1_3_INTR| EndStops_1_4_INTR| EndStops_1_5_INTR))


#endif /* End Pins EndStops_1_ALIASES_H */


/* [] END OF FILE */
