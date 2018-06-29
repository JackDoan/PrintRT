/***************************************************************************//**
* \file DriverSPI_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_DriverSPI_H)
#define CY_SCB_BOOT_DriverSPI_H

#include "DriverSPI_PVT.h"

#if (DriverSPI_SCB_MODE_I2C_INC)
    #include "DriverSPI_I2C.h"
#endif /* (DriverSPI_SCB_MODE_I2C_INC) */

#if (DriverSPI_SCB_MODE_EZI2C_INC)
    #include "DriverSPI_EZI2C.h"
#endif /* (DriverSPI_SCB_MODE_EZI2C_INC) */

#if (DriverSPI_SCB_MODE_SPI_INC || DriverSPI_SCB_MODE_UART_INC)
    #include "DriverSPI_SPI_UART.h"
#endif /* (DriverSPI_SCB_MODE_SPI_INC || DriverSPI_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define DriverSPI_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DriverSPI) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (DriverSPI_SCB_MODE_I2C_INC)
    #define DriverSPI_I2C_BTLDR_COMM_ENABLED     (DriverSPI_BTLDR_COMM_ENABLED && \
                                                            (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             DriverSPI_I2C_SLAVE_CONST))
#else
     #define DriverSPI_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (DriverSPI_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (DriverSPI_SCB_MODE_EZI2C_INC)
    #define DriverSPI_EZI2C_BTLDR_COMM_ENABLED   (DriverSPI_BTLDR_COMM_ENABLED && \
                                                         DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define DriverSPI_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (DriverSPI_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (DriverSPI_SCB_MODE_SPI_INC)
    #define DriverSPI_SPI_BTLDR_COMM_ENABLED     (DriverSPI_BTLDR_COMM_ENABLED && \
                                                            (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             DriverSPI_SPI_SLAVE_CONST))
#else
        #define DriverSPI_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (DriverSPI_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (DriverSPI_SCB_MODE_UART_INC)
       #define DriverSPI_UART_BTLDR_COMM_ENABLED    (DriverSPI_BTLDR_COMM_ENABLED && \
                                                            (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (DriverSPI_UART_RX_DIRECTION && \
                                                              DriverSPI_UART_TX_DIRECTION)))
#else
     #define DriverSPI_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (DriverSPI_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define DriverSPI_BTLDR_COMM_MODE_ENABLED    (DriverSPI_I2C_BTLDR_COMM_ENABLED   || \
                                                     DriverSPI_SPI_BTLDR_COMM_ENABLED   || \
                                                     DriverSPI_EZI2C_BTLDR_COMM_ENABLED || \
                                                     DriverSPI_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void DriverSPI_I2CCyBtldrCommStart(void);
    void DriverSPI_I2CCyBtldrCommStop (void);
    void DriverSPI_I2CCyBtldrCommReset(void);
    cystatus DriverSPI_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DriverSPI_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (DriverSPI_SCB_MODE_I2C_CONST_CFG)
        #define DriverSPI_CyBtldrCommStart   DriverSPI_I2CCyBtldrCommStart
        #define DriverSPI_CyBtldrCommStop    DriverSPI_I2CCyBtldrCommStop
        #define DriverSPI_CyBtldrCommReset   DriverSPI_I2CCyBtldrCommReset
        #define DriverSPI_CyBtldrCommRead    DriverSPI_I2CCyBtldrCommRead
        #define DriverSPI_CyBtldrCommWrite   DriverSPI_I2CCyBtldrCommWrite
    #endif /* (DriverSPI_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void DriverSPI_EzI2CCyBtldrCommStart(void);
    void DriverSPI_EzI2CCyBtldrCommStop (void);
    void DriverSPI_EzI2CCyBtldrCommReset(void);
    cystatus DriverSPI_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DriverSPI_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (DriverSPI_SCB_MODE_EZI2C_CONST_CFG)
        #define DriverSPI_CyBtldrCommStart   DriverSPI_EzI2CCyBtldrCommStart
        #define DriverSPI_CyBtldrCommStop    DriverSPI_EzI2CCyBtldrCommStop
        #define DriverSPI_CyBtldrCommReset   DriverSPI_EzI2CCyBtldrCommReset
        #define DriverSPI_CyBtldrCommRead    DriverSPI_EzI2CCyBtldrCommRead
        #define DriverSPI_CyBtldrCommWrite   DriverSPI_EzI2CCyBtldrCommWrite
    #endif /* (DriverSPI_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void DriverSPI_SpiCyBtldrCommStart(void);
    void DriverSPI_SpiCyBtldrCommStop (void);
    void DriverSPI_SpiCyBtldrCommReset(void);
    cystatus DriverSPI_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DriverSPI_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (DriverSPI_SCB_MODE_SPI_CONST_CFG)
        #define DriverSPI_CyBtldrCommStart   DriverSPI_SpiCyBtldrCommStart
        #define DriverSPI_CyBtldrCommStop    DriverSPI_SpiCyBtldrCommStop
        #define DriverSPI_CyBtldrCommReset   DriverSPI_SpiCyBtldrCommReset
        #define DriverSPI_CyBtldrCommRead    DriverSPI_SpiCyBtldrCommRead
        #define DriverSPI_CyBtldrCommWrite   DriverSPI_SpiCyBtldrCommWrite
    #endif /* (DriverSPI_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void DriverSPI_UartCyBtldrCommStart(void);
    void DriverSPI_UartCyBtldrCommStop (void);
    void DriverSPI_UartCyBtldrCommReset(void);
    cystatus DriverSPI_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DriverSPI_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (DriverSPI_SCB_MODE_UART_CONST_CFG)
        #define DriverSPI_CyBtldrCommStart   DriverSPI_UartCyBtldrCommStart
        #define DriverSPI_CyBtldrCommStop    DriverSPI_UartCyBtldrCommStop
        #define DriverSPI_CyBtldrCommReset   DriverSPI_UartCyBtldrCommReset
        #define DriverSPI_CyBtldrCommRead    DriverSPI_UartCyBtldrCommRead
        #define DriverSPI_CyBtldrCommWrite   DriverSPI_UartCyBtldrCommWrite
    #endif /* (DriverSPI_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_BTLDR_COMM_ENABLED)
    #if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void DriverSPI_CyBtldrCommStart(void);
        void DriverSPI_CyBtldrCommStop (void);
        void DriverSPI_CyBtldrCommReset(void);
        cystatus DriverSPI_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus DriverSPI_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DriverSPI)
        #define CyBtldrCommStart    DriverSPI_CyBtldrCommStart
        #define CyBtldrCommStop     DriverSPI_CyBtldrCommStop
        #define CyBtldrCommReset    DriverSPI_CyBtldrCommReset
        #define CyBtldrCommWrite    DriverSPI_CyBtldrCommWrite
        #define CyBtldrCommRead     DriverSPI_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DriverSPI) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DriverSPI_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define DriverSPI_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define DriverSPI_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define DriverSPI_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define DriverSPI_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef DriverSPI_SPI_BYTE_TO_BYTE
    #define DriverSPI_SPI_BYTE_TO_BYTE   (16u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef DriverSPI_UART_BYTE_TO_BYTE
    #define DriverSPI_UART_BYTE_TO_BYTE  (2500u)
#endif /* DriverSPI_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_DriverSPI_H) */


/* [] END OF FILE */
