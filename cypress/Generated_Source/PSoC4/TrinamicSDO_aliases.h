/*******************************************************************************
* File Name: TrinamicSDO.h  
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

#if !defined(CY_PINS_TrinamicSDO_ALIASES_H) /* Pins TrinamicSDO_ALIASES_H */
#define CY_PINS_TrinamicSDO_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TrinamicSDO_0			(TrinamicSDO__0__PC)
#define TrinamicSDO_0_PS		(TrinamicSDO__0__PS)
#define TrinamicSDO_0_PC		(TrinamicSDO__0__PC)
#define TrinamicSDO_0_DR		(TrinamicSDO__0__DR)
#define TrinamicSDO_0_SHIFT	(TrinamicSDO__0__SHIFT)
#define TrinamicSDO_0_INTR	((uint16)((uint16)0x0003u << (TrinamicSDO__0__SHIFT*2u)))

#define TrinamicSDO_INTR_ALL	 ((uint16)(TrinamicSDO_0_INTR))


#endif /* End Pins TrinamicSDO_ALIASES_H */


/* [] END OF FILE */
