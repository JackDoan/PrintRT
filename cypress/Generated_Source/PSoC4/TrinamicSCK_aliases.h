/*******************************************************************************
* File Name: TrinamicSCK.h  
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

#if !defined(CY_PINS_TrinamicSCK_ALIASES_H) /* Pins TrinamicSCK_ALIASES_H */
#define CY_PINS_TrinamicSCK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TrinamicSCK_0			(TrinamicSCK__0__PC)
#define TrinamicSCK_0_PS		(TrinamicSCK__0__PS)
#define TrinamicSCK_0_PC		(TrinamicSCK__0__PC)
#define TrinamicSCK_0_DR		(TrinamicSCK__0__DR)
#define TrinamicSCK_0_SHIFT	(TrinamicSCK__0__SHIFT)
#define TrinamicSCK_0_INTR	((uint16)((uint16)0x0003u << (TrinamicSCK__0__SHIFT*2u)))

#define TrinamicSCK_INTR_ALL	 ((uint16)(TrinamicSCK_0_INTR))


#endif /* End Pins TrinamicSCK_ALIASES_H */


/* [] END OF FILE */
