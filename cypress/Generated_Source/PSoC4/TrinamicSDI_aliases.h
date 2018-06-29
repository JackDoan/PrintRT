/*******************************************************************************
* File Name: TrinamicSDI.h  
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

#if !defined(CY_PINS_TrinamicSDI_ALIASES_H) /* Pins TrinamicSDI_ALIASES_H */
#define CY_PINS_TrinamicSDI_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TrinamicSDI_0			(TrinamicSDI__0__PC)
#define TrinamicSDI_0_PS		(TrinamicSDI__0__PS)
#define TrinamicSDI_0_PC		(TrinamicSDI__0__PC)
#define TrinamicSDI_0_DR		(TrinamicSDI__0__DR)
#define TrinamicSDI_0_SHIFT	(TrinamicSDI__0__SHIFT)
#define TrinamicSDI_0_INTR	((uint16)((uint16)0x0003u << (TrinamicSDI__0__SHIFT*2u)))

#define TrinamicSDI_INTR_ALL	 ((uint16)(TrinamicSDI_0_INTR))


#endif /* End Pins TrinamicSDI_ALIASES_H */


/* [] END OF FILE */
