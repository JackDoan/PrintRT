/*******************************************************************************
* File Name: TrinamicCLK.h  
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

#if !defined(CY_PINS_TrinamicCLK_ALIASES_H) /* Pins TrinamicCLK_ALIASES_H */
#define CY_PINS_TrinamicCLK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TrinamicCLK_0			(TrinamicCLK__0__PC)
#define TrinamicCLK_0_PS		(TrinamicCLK__0__PS)
#define TrinamicCLK_0_PC		(TrinamicCLK__0__PC)
#define TrinamicCLK_0_DR		(TrinamicCLK__0__DR)
#define TrinamicCLK_0_SHIFT	(TrinamicCLK__0__SHIFT)
#define TrinamicCLK_0_INTR	((uint16)((uint16)0x0003u << (TrinamicCLK__0__SHIFT*2u)))

#define TrinamicCLK_INTR_ALL	 ((uint16)(TrinamicCLK_0_INTR))


#endif /* End Pins TrinamicCLK_ALIASES_H */


/* [] END OF FILE */
