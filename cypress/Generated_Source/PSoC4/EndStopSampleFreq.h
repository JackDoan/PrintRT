/*******************************************************************************
* File Name: EndStopSampleFreq.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_EndStopSampleFreq_H)
#define CY_CLOCK_EndStopSampleFreq_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void EndStopSampleFreq_StartEx(uint32 alignClkDiv);
#define EndStopSampleFreq_Start() \
    EndStopSampleFreq_StartEx(EndStopSampleFreq__PA_DIV_ID)

#else

void EndStopSampleFreq_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void EndStopSampleFreq_Stop(void);

void EndStopSampleFreq_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 EndStopSampleFreq_GetDividerRegister(void);
uint8  EndStopSampleFreq_GetFractionalDividerRegister(void);

#define EndStopSampleFreq_Enable()                         EndStopSampleFreq_Start()
#define EndStopSampleFreq_Disable()                        EndStopSampleFreq_Stop()
#define EndStopSampleFreq_SetDividerRegister(clkDivider, reset)  \
    EndStopSampleFreq_SetFractionalDividerRegister((clkDivider), 0u)
#define EndStopSampleFreq_SetDivider(clkDivider)           EndStopSampleFreq_SetDividerRegister((clkDivider), 1u)
#define EndStopSampleFreq_SetDividerValue(clkDivider)      EndStopSampleFreq_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define EndStopSampleFreq_DIV_ID     EndStopSampleFreq__DIV_ID

#define EndStopSampleFreq_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define EndStopSampleFreq_CTRL_REG   (*(reg32 *)EndStopSampleFreq__CTRL_REGISTER)
#define EndStopSampleFreq_DIV_REG    (*(reg32 *)EndStopSampleFreq__DIV_REGISTER)

#define EndStopSampleFreq_CMD_DIV_SHIFT          (0u)
#define EndStopSampleFreq_CMD_PA_DIV_SHIFT       (8u)
#define EndStopSampleFreq_CMD_DISABLE_SHIFT      (30u)
#define EndStopSampleFreq_CMD_ENABLE_SHIFT       (31u)

#define EndStopSampleFreq_CMD_DISABLE_MASK       ((uint32)((uint32)1u << EndStopSampleFreq_CMD_DISABLE_SHIFT))
#define EndStopSampleFreq_CMD_ENABLE_MASK        ((uint32)((uint32)1u << EndStopSampleFreq_CMD_ENABLE_SHIFT))

#define EndStopSampleFreq_DIV_FRAC_MASK  (0x000000F8u)
#define EndStopSampleFreq_DIV_FRAC_SHIFT (3u)
#define EndStopSampleFreq_DIV_INT_MASK   (0xFFFFFF00u)
#define EndStopSampleFreq_DIV_INT_SHIFT  (8u)

#else 

#define EndStopSampleFreq_DIV_REG        (*(reg32 *)EndStopSampleFreq__REGISTER)
#define EndStopSampleFreq_ENABLE_REG     EndStopSampleFreq_DIV_REG
#define EndStopSampleFreq_DIV_FRAC_MASK  EndStopSampleFreq__FRAC_MASK
#define EndStopSampleFreq_DIV_FRAC_SHIFT (16u)
#define EndStopSampleFreq_DIV_INT_MASK   EndStopSampleFreq__DIVIDER_MASK
#define EndStopSampleFreq_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_EndStopSampleFreq_H) */

/* [] END OF FILE */
