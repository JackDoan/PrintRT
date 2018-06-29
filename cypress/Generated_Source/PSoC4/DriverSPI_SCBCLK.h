/*******************************************************************************
* File Name: DriverSPI_SCBCLK.h
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

#if !defined(CY_CLOCK_DriverSPI_SCBCLK_H)
#define CY_CLOCK_DriverSPI_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void DriverSPI_SCBCLK_StartEx(uint32 alignClkDiv);
#define DriverSPI_SCBCLK_Start() \
    DriverSPI_SCBCLK_StartEx(DriverSPI_SCBCLK__PA_DIV_ID)

#else

void DriverSPI_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void DriverSPI_SCBCLK_Stop(void);

void DriverSPI_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 DriverSPI_SCBCLK_GetDividerRegister(void);
uint8  DriverSPI_SCBCLK_GetFractionalDividerRegister(void);

#define DriverSPI_SCBCLK_Enable()                         DriverSPI_SCBCLK_Start()
#define DriverSPI_SCBCLK_Disable()                        DriverSPI_SCBCLK_Stop()
#define DriverSPI_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    DriverSPI_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define DriverSPI_SCBCLK_SetDivider(clkDivider)           DriverSPI_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define DriverSPI_SCBCLK_SetDividerValue(clkDivider)      DriverSPI_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define DriverSPI_SCBCLK_DIV_ID     DriverSPI_SCBCLK__DIV_ID

#define DriverSPI_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define DriverSPI_SCBCLK_CTRL_REG   (*(reg32 *)DriverSPI_SCBCLK__CTRL_REGISTER)
#define DriverSPI_SCBCLK_DIV_REG    (*(reg32 *)DriverSPI_SCBCLK__DIV_REGISTER)

#define DriverSPI_SCBCLK_CMD_DIV_SHIFT          (0u)
#define DriverSPI_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define DriverSPI_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define DriverSPI_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define DriverSPI_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << DriverSPI_SCBCLK_CMD_DISABLE_SHIFT))
#define DriverSPI_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << DriverSPI_SCBCLK_CMD_ENABLE_SHIFT))

#define DriverSPI_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define DriverSPI_SCBCLK_DIV_FRAC_SHIFT (3u)
#define DriverSPI_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define DriverSPI_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define DriverSPI_SCBCLK_DIV_REG        (*(reg32 *)DriverSPI_SCBCLK__REGISTER)
#define DriverSPI_SCBCLK_ENABLE_REG     DriverSPI_SCBCLK_DIV_REG
#define DriverSPI_SCBCLK_DIV_FRAC_MASK  DriverSPI_SCBCLK__FRAC_MASK
#define DriverSPI_SCBCLK_DIV_FRAC_SHIFT (16u)
#define DriverSPI_SCBCLK_DIV_INT_MASK   DriverSPI_SCBCLK__DIVIDER_MASK
#define DriverSPI_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_DriverSPI_SCBCLK_H) */

/* [] END OF FILE */
