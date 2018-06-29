/***************************************************************************//**
* \file DriverSPI_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DriverSPI.h"
#include "DriverSPI_PVT.h"

#if(DriverSPI_SCB_MODE_I2C_INC)
    #include "DriverSPI_I2C_PVT.h"
#endif /* (DriverSPI_SCB_MODE_I2C_INC) */

#if(DriverSPI_SCB_MODE_EZI2C_INC)
    #include "DriverSPI_EZI2C_PVT.h"
#endif /* (DriverSPI_SCB_MODE_EZI2C_INC) */

#if(DriverSPI_SCB_MODE_SPI_INC || DriverSPI_SCB_MODE_UART_INC)
    #include "DriverSPI_SPI_UART_PVT.h"
#endif /* (DriverSPI_SCB_MODE_SPI_INC || DriverSPI_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
   (DriverSPI_SCB_MODE_I2C_CONST_CFG   && (!DriverSPI_I2C_WAKE_ENABLE_CONST))   || \
   (DriverSPI_SCB_MODE_EZI2C_CONST_CFG && (!DriverSPI_EZI2C_WAKE_ENABLE_CONST)) || \
   (DriverSPI_SCB_MODE_SPI_CONST_CFG   && (!DriverSPI_SPI_WAKE_ENABLE_CONST))   || \
   (DriverSPI_SCB_MODE_UART_CONST_CFG  && (!DriverSPI_UART_WAKE_ENABLE_CONST)))

    DriverSPI_BACKUP_STRUCT DriverSPI_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: DriverSPI_Sleep
****************************************************************************//**
*
*  Prepares the DriverSPI component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the DriverSPI_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void DriverSPI_Sleep(void)
{
#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DriverSPI_SCB_WAKE_ENABLE_CHECK)
    {
        if(DriverSPI_SCB_MODE_I2C_RUNTM_CFG)
        {
            DriverSPI_I2CSaveConfig();
        }
        else if(DriverSPI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DriverSPI_EzI2CSaveConfig();
        }
    #if(!DriverSPI_CY_SCBIP_V1)
        else if(DriverSPI_SCB_MODE_SPI_RUNTM_CFG)
        {
            DriverSPI_SpiSaveConfig();
        }
        else if(DriverSPI_SCB_MODE_UART_RUNTM_CFG)
        {
            DriverSPI_UartSaveConfig();
        }
    #endif /* (!DriverSPI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        DriverSPI_backup.enableState = (uint8) DriverSPI_GET_CTRL_ENABLED;

        if(0u != DriverSPI_backup.enableState)
        {
            DriverSPI_Stop();
        }
    }

#else

    #if (DriverSPI_SCB_MODE_I2C_CONST_CFG && DriverSPI_I2C_WAKE_ENABLE_CONST)
        DriverSPI_I2CSaveConfig();

    #elif (DriverSPI_SCB_MODE_EZI2C_CONST_CFG && DriverSPI_EZI2C_WAKE_ENABLE_CONST)
        DriverSPI_EzI2CSaveConfig();

    #elif (DriverSPI_SCB_MODE_SPI_CONST_CFG && DriverSPI_SPI_WAKE_ENABLE_CONST)
        DriverSPI_SpiSaveConfig();

    #elif (DriverSPI_SCB_MODE_UART_CONST_CFG && DriverSPI_UART_WAKE_ENABLE_CONST)
        DriverSPI_UartSaveConfig();

    #else

        DriverSPI_backup.enableState = (uint8) DriverSPI_GET_CTRL_ENABLED;

        if(0u != DriverSPI_backup.enableState)
        {
            DriverSPI_Stop();
        }

    #endif /* defined (DriverSPI_SCB_MODE_I2C_CONST_CFG) && (DriverSPI_I2C_WAKE_ENABLE_CONST) */

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DriverSPI_Wakeup
****************************************************************************//**
*
*  Prepares the DriverSPI component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the DriverSPI_Wakeup() function without first calling the 
*   DriverSPI_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void DriverSPI_Wakeup(void)
{
#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DriverSPI_SCB_WAKE_ENABLE_CHECK)
    {
        if(DriverSPI_SCB_MODE_I2C_RUNTM_CFG)
        {
            DriverSPI_I2CRestoreConfig();
        }
        else if(DriverSPI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DriverSPI_EzI2CRestoreConfig();
        }
    #if(!DriverSPI_CY_SCBIP_V1)
        else if(DriverSPI_SCB_MODE_SPI_RUNTM_CFG)
        {
            DriverSPI_SpiRestoreConfig();
        }
        else if(DriverSPI_SCB_MODE_UART_RUNTM_CFG)
        {
            DriverSPI_UartRestoreConfig();
        }
    #endif /* (!DriverSPI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != DriverSPI_backup.enableState)
        {
            DriverSPI_Enable();
        }
    }

#else

    #if (DriverSPI_SCB_MODE_I2C_CONST_CFG  && DriverSPI_I2C_WAKE_ENABLE_CONST)
        DriverSPI_I2CRestoreConfig();

    #elif (DriverSPI_SCB_MODE_EZI2C_CONST_CFG && DriverSPI_EZI2C_WAKE_ENABLE_CONST)
        DriverSPI_EzI2CRestoreConfig();

    #elif (DriverSPI_SCB_MODE_SPI_CONST_CFG && DriverSPI_SPI_WAKE_ENABLE_CONST)
        DriverSPI_SpiRestoreConfig();

    #elif (DriverSPI_SCB_MODE_UART_CONST_CFG && DriverSPI_UART_WAKE_ENABLE_CONST)
        DriverSPI_UartRestoreConfig();

    #else

        if(0u != DriverSPI_backup.enableState)
        {
            DriverSPI_Enable();
        }

    #endif /* (DriverSPI_I2C_WAKE_ENABLE_CONST) */

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
