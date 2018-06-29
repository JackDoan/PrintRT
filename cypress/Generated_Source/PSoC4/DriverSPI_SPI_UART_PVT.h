/***************************************************************************//**
* \file DriverSPI_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_DriverSPI_H)
#define CY_SCB_SPI_UART_PVT_DriverSPI_H

#include "DriverSPI_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  DriverSPI_rxBufferHead;
    extern volatile uint32  DriverSPI_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   DriverSPI_rxBufferOverflow;
    /** @} globals */
#endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  DriverSPI_txBufferHead;
    extern volatile uint32  DriverSPI_txBufferTail;
#endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if (DriverSPI_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 DriverSPI_rxBufferInternal[DriverSPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER) */

#if (DriverSPI_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 DriverSPI_txBufferInternal[DriverSPI_TX_BUFFER_SIZE];
#endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void DriverSPI_SpiPostEnable(void);
void DriverSPI_SpiStop(void);

#if (DriverSPI_SCB_MODE_SPI_CONST_CFG)
    void DriverSPI_SpiInit(void);
#endif /* (DriverSPI_SCB_MODE_SPI_CONST_CFG) */

#if (DriverSPI_SPI_WAKE_ENABLE_CONST)
    void DriverSPI_SpiSaveConfig(void);
    void DriverSPI_SpiRestoreConfig(void);
#endif /* (DriverSPI_SPI_WAKE_ENABLE_CONST) */

void DriverSPI_UartPostEnable(void);
void DriverSPI_UartStop(void);

#if (DriverSPI_SCB_MODE_UART_CONST_CFG)
    void DriverSPI_UartInit(void);
#endif /* (DriverSPI_SCB_MODE_UART_CONST_CFG) */

#if (DriverSPI_UART_WAKE_ENABLE_CONST)
    void DriverSPI_UartSaveConfig(void);
    void DriverSPI_UartRestoreConfig(void);
#endif /* (DriverSPI_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in DriverSPI_SetPins() */
#define DriverSPI_UART_RX_PIN_ENABLE    (DriverSPI_UART_RX)
#define DriverSPI_UART_TX_PIN_ENABLE    (DriverSPI_UART_TX)

/* UART RTS and CTS position to be used in  DriverSPI_SetPins() */
#define DriverSPI_UART_RTS_PIN_ENABLE    (0x10u)
#define DriverSPI_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define DriverSPI_SpiUartEnableIntRx(intSourceMask)  DriverSPI_SetRxInterruptMode(intSourceMask)
#define DriverSPI_SpiUartEnableIntTx(intSourceMask)  DriverSPI_SetTxInterruptMode(intSourceMask)
uint32  DriverSPI_SpiUartDisableIntRx(void);
uint32  DriverSPI_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_DriverSPI_H) */


/* [] END OF FILE */
