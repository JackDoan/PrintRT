/*******************************************************************************
* File Name: TrianmicEnable.h  
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

#if !defined(CY_PINS_TrianmicEnable_ALIASES_H) /* Pins TrianmicEnable_ALIASES_H */
#define CY_PINS_TrianmicEnable_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TrianmicEnable_0			(TrianmicEnable__0__PC)
#define TrianmicEnable_0_PS		(TrianmicEnable__0__PS)
#define TrianmicEnable_0_PC		(TrianmicEnable__0__PC)
#define TrianmicEnable_0_DR		(TrianmicEnable__0__DR)
#define TrianmicEnable_0_SHIFT	(TrianmicEnable__0__SHIFT)
#define TrianmicEnable_0_INTR	((uint16)((uint16)0x0003u << (TrianmicEnable__0__SHIFT*2u)))

#define TrianmicEnable_INTR_ALL	 ((uint16)(TrianmicEnable_0_INTR))


#endif /* End Pins TrianmicEnable_ALIASES_H */


/* [] END OF FILE */
