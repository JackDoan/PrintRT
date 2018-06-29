/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_DriverSPI_H)
#define CY_SCB_PVT_DriverSPI_H

#include "DriverSPI.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define DriverSPI_SetI2CExtClkInterruptMode(interruptMask) DriverSPI_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define DriverSPI_ClearI2CExtClkInterruptSource(interruptMask) DriverSPI_CLEAR_INTR_I2C_EC(interruptMask)
#define DriverSPI_GetI2CExtClkInterruptSource()                (DriverSPI_INTR_I2C_EC_REG)
#define DriverSPI_GetI2CExtClkInterruptMode()                  (DriverSPI_INTR_I2C_EC_MASK_REG)
#define DriverSPI_GetI2CExtClkInterruptSourceMasked()          (DriverSPI_INTR_I2C_EC_MASKED_REG)

#if (!DriverSPI_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define DriverSPI_SetSpiExtClkInterruptMode(interruptMask) \
                                                                DriverSPI_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define DriverSPI_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                DriverSPI_CLEAR_INTR_SPI_EC(interruptMask)
    #define DriverSPI_GetExtSpiClkInterruptSource()                 (DriverSPI_INTR_SPI_EC_REG)
    #define DriverSPI_GetExtSpiClkInterruptMode()                   (DriverSPI_INTR_SPI_EC_MASK_REG)
    #define DriverSPI_GetExtSpiClkInterruptSourceMasked()           (DriverSPI_INTR_SPI_EC_MASKED_REG)
#endif /* (!DriverSPI_CY_SCBIP_V1) */

#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void DriverSPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (DriverSPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DriverSPI_CUSTOM_INTR_HANDLER)
    extern cyisraddress DriverSPI_customIntrHandler;
#endif /* !defined (CY_REMOVE_DriverSPI_CUSTOM_INTR_HANDLER) */
#endif /* (DriverSPI_SCB_IRQ_INTERNAL) */

extern DriverSPI_BACKUP_STRUCT DriverSPI_backup;

#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 DriverSPI_scbMode;
    extern uint8 DriverSPI_scbEnableWake;
    extern uint8 DriverSPI_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 DriverSPI_mode;
    extern uint8 DriverSPI_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * DriverSPI_rxBuffer;
    extern uint8   DriverSPI_rxDataBits;
    extern uint32  DriverSPI_rxBufferSize;

    extern volatile uint8 * DriverSPI_txBuffer;
    extern uint8   DriverSPI_txDataBits;
    extern uint32  DriverSPI_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 DriverSPI_numberOfAddr;
    extern uint8 DriverSPI_subAddrSize;
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (DriverSPI_SCB_MODE_I2C_CONST_CFG || \
        DriverSPI_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 DriverSPI_IntrTxMask;
#endif /* (! (DriverSPI_SCB_MODE_I2C_CONST_CFG || \
              DriverSPI_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define DriverSPI_SCB_MODE_I2C_RUNTM_CFG     (DriverSPI_SCB_MODE_I2C      == DriverSPI_scbMode)
    #define DriverSPI_SCB_MODE_SPI_RUNTM_CFG     (DriverSPI_SCB_MODE_SPI      == DriverSPI_scbMode)
    #define DriverSPI_SCB_MODE_UART_RUNTM_CFG    (DriverSPI_SCB_MODE_UART     == DriverSPI_scbMode)
    #define DriverSPI_SCB_MODE_EZI2C_RUNTM_CFG   (DriverSPI_SCB_MODE_EZI2C    == DriverSPI_scbMode)
    #define DriverSPI_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (DriverSPI_SCB_MODE_UNCONFIG == DriverSPI_scbMode)

    /* Defines wakeup enable */
    #define DriverSPI_SCB_WAKE_ENABLE_CHECK       (0u != DriverSPI_scbEnableWake)
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!DriverSPI_CY_SCBIP_V1)
    #define DriverSPI_SCB_PINS_NUMBER    (7u)
#else
    #define DriverSPI_SCB_PINS_NUMBER    (2u)
#endif /* (!DriverSPI_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_DriverSPI_H) */


/* [] END OF FILE */
