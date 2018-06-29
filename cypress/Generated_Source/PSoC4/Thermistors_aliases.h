/*******************************************************************************
* File Name: Thermistors.h  
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

#if !defined(CY_PINS_Thermistors_ALIASES_H) /* Pins Thermistors_ALIASES_H */
#define CY_PINS_Thermistors_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Thermistors_0			(Thermistors__0__PC)
#define Thermistors_0_PS		(Thermistors__0__PS)
#define Thermistors_0_PC		(Thermistors__0__PC)
#define Thermistors_0_DR		(Thermistors__0__DR)
#define Thermistors_0_SHIFT	(Thermistors__0__SHIFT)
#define Thermistors_0_INTR	((uint16)((uint16)0x0003u << (Thermistors__0__SHIFT*2u)))

#define Thermistors_1			(Thermistors__1__PC)
#define Thermistors_1_PS		(Thermistors__1__PS)
#define Thermistors_1_PC		(Thermistors__1__PC)
#define Thermistors_1_DR		(Thermistors__1__DR)
#define Thermistors_1_SHIFT	(Thermistors__1__SHIFT)
#define Thermistors_1_INTR	((uint16)((uint16)0x0003u << (Thermistors__1__SHIFT*2u)))

#define Thermistors_INTR_ALL	 ((uint16)(Thermistors_0_INTR| Thermistors_1_INTR))


#endif /* End Pins Thermistors_ALIASES_H */


/* [] END OF FILE */
