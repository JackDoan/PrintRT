/***************************************************************************//**
* \file DriverSPI_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_DriverSPI_H)
#define CY_SCB_PINS_DriverSPI_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define DriverSPI_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define DriverSPI_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define DriverSPI_REMOVE_TX_SDA_MISO_PIN      (1u)
#define DriverSPI_REMOVE_CTS_SCLK_PIN      (1u)
#define DriverSPI_REMOVE_RTS_SS0_PIN      (1u)
#define DriverSPI_REMOVE_SS1_PIN                 (1u)
#define DriverSPI_REMOVE_SS2_PIN                 (1u)
#define DriverSPI_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define DriverSPI_REMOVE_I2C_PINS                (1u)
#define DriverSPI_REMOVE_SPI_MASTER_PINS         (0u)
#define DriverSPI_REMOVE_SPI_MASTER_SCLK_PIN     (0u)
#define DriverSPI_REMOVE_SPI_MASTER_MOSI_PIN     (0u)
#define DriverSPI_REMOVE_SPI_MASTER_MISO_PIN     (0u)
#define DriverSPI_REMOVE_SPI_MASTER_SS0_PIN      (0u)
#define DriverSPI_REMOVE_SPI_MASTER_SS1_PIN      (0u)
#define DriverSPI_REMOVE_SPI_MASTER_SS2_PIN      (0u)
#define DriverSPI_REMOVE_SPI_MASTER_SS3_PIN      (0u)
#define DriverSPI_REMOVE_SPI_SLAVE_PINS          (1u)
#define DriverSPI_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define DriverSPI_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define DriverSPI_REMOVE_UART_TX_PIN             (1u)
#define DriverSPI_REMOVE_UART_RX_TX_PIN          (1u)
#define DriverSPI_REMOVE_UART_RX_PIN             (1u)
#define DriverSPI_REMOVE_UART_RX_WAKE_PIN        (1u)
#define DriverSPI_REMOVE_UART_RTS_PIN            (1u)
#define DriverSPI_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define DriverSPI_RX_WAKE_SCL_MOSI_PIN (0u == DriverSPI_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define DriverSPI_RX_SCL_MOSI_PIN     (0u == DriverSPI_REMOVE_RX_SCL_MOSI_PIN)
#define DriverSPI_TX_SDA_MISO_PIN     (0u == DriverSPI_REMOVE_TX_SDA_MISO_PIN)
#define DriverSPI_CTS_SCLK_PIN     (0u == DriverSPI_REMOVE_CTS_SCLK_PIN)
#define DriverSPI_RTS_SS0_PIN     (0u == DriverSPI_REMOVE_RTS_SS0_PIN)
#define DriverSPI_SS1_PIN                (0u == DriverSPI_REMOVE_SS1_PIN)
#define DriverSPI_SS2_PIN                (0u == DriverSPI_REMOVE_SS2_PIN)
#define DriverSPI_SS3_PIN                (0u == DriverSPI_REMOVE_SS3_PIN)

/* Mode defined pins */
#define DriverSPI_I2C_PINS               (0u == DriverSPI_REMOVE_I2C_PINS)
#define DriverSPI_SPI_MASTER_PINS        (0u == DriverSPI_REMOVE_SPI_MASTER_PINS)
#define DriverSPI_SPI_MASTER_SCLK_PIN    (0u == DriverSPI_REMOVE_SPI_MASTER_SCLK_PIN)
#define DriverSPI_SPI_MASTER_MOSI_PIN    (0u == DriverSPI_REMOVE_SPI_MASTER_MOSI_PIN)
#define DriverSPI_SPI_MASTER_MISO_PIN    (0u == DriverSPI_REMOVE_SPI_MASTER_MISO_PIN)
#define DriverSPI_SPI_MASTER_SS0_PIN     (0u == DriverSPI_REMOVE_SPI_MASTER_SS0_PIN)
#define DriverSPI_SPI_MASTER_SS1_PIN     (0u == DriverSPI_REMOVE_SPI_MASTER_SS1_PIN)
#define DriverSPI_SPI_MASTER_SS2_PIN     (0u == DriverSPI_REMOVE_SPI_MASTER_SS2_PIN)
#define DriverSPI_SPI_MASTER_SS3_PIN     (0u == DriverSPI_REMOVE_SPI_MASTER_SS3_PIN)
#define DriverSPI_SPI_SLAVE_PINS         (0u == DriverSPI_REMOVE_SPI_SLAVE_PINS)
#define DriverSPI_SPI_SLAVE_MOSI_PIN     (0u == DriverSPI_REMOVE_SPI_SLAVE_MOSI_PIN)
#define DriverSPI_SPI_SLAVE_MISO_PIN     (0u == DriverSPI_REMOVE_SPI_SLAVE_MISO_PIN)
#define DriverSPI_UART_TX_PIN            (0u == DriverSPI_REMOVE_UART_TX_PIN)
#define DriverSPI_UART_RX_TX_PIN         (0u == DriverSPI_REMOVE_UART_RX_TX_PIN)
#define DriverSPI_UART_RX_PIN            (0u == DriverSPI_REMOVE_UART_RX_PIN)
#define DriverSPI_UART_RX_WAKE_PIN       (0u == DriverSPI_REMOVE_UART_RX_WAKE_PIN)
#define DriverSPI_UART_RTS_PIN           (0u == DriverSPI_REMOVE_UART_RTS_PIN)
#define DriverSPI_UART_CTS_PIN           (0u == DriverSPI_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
    #include "DriverSPI_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (DriverSPI_RX_SCL_MOSI) */

#if (DriverSPI_RX_SCL_MOSI_PIN)
    #include "DriverSPI_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (DriverSPI_RX_SCL_MOSI) */

#if (DriverSPI_TX_SDA_MISO_PIN)
    #include "DriverSPI_uart_tx_i2c_sda_spi_miso.h"
#endif /* (DriverSPI_TX_SDA_MISO) */

#if (DriverSPI_CTS_SCLK_PIN)
    #include "DriverSPI_uart_cts_spi_sclk.h"
#endif /* (DriverSPI_CTS_SCLK) */

#if (DriverSPI_RTS_SS0_PIN)
    #include "DriverSPI_uart_rts_spi_ss0.h"
#endif /* (DriverSPI_RTS_SS0_PIN) */

#if (DriverSPI_SS1_PIN)
    #include "DriverSPI_spi_ss1.h"
#endif /* (DriverSPI_SS1_PIN) */

#if (DriverSPI_SS2_PIN)
    #include "DriverSPI_spi_ss2.h"
#endif /* (DriverSPI_SS2_PIN) */

#if (DriverSPI_SS3_PIN)
    #include "DriverSPI_spi_ss3.h"
#endif /* (DriverSPI_SS3_PIN) */

#if (DriverSPI_I2C_PINS)
    #include "DriverSPI_scl.h"
    #include "DriverSPI_sda.h"
#endif /* (DriverSPI_I2C_PINS) */

#if (DriverSPI_SPI_MASTER_PINS)
#if (DriverSPI_SPI_MASTER_SCLK_PIN)
    #include "DriverSPI_sclk_m.h"
#endif /* (DriverSPI_SPI_MASTER_SCLK_PIN) */

#if (DriverSPI_SPI_MASTER_MOSI_PIN)
    #include "DriverSPI_mosi_m.h"
#endif /* (DriverSPI_SPI_MASTER_MOSI_PIN) */

#if (DriverSPI_SPI_MASTER_MISO_PIN)
    #include "DriverSPI_miso_m.h"
#endif /*(DriverSPI_SPI_MASTER_MISO_PIN) */
#endif /* (DriverSPI_SPI_MASTER_PINS) */

#if (DriverSPI_SPI_SLAVE_PINS)
    #include "DriverSPI_sclk_s.h"
    #include "DriverSPI_ss_s.h"

#if (DriverSPI_SPI_SLAVE_MOSI_PIN)
    #include "DriverSPI_mosi_s.h"
#endif /* (DriverSPI_SPI_SLAVE_MOSI_PIN) */

#if (DriverSPI_SPI_SLAVE_MISO_PIN)
    #include "DriverSPI_miso_s.h"
#endif /*(DriverSPI_SPI_SLAVE_MISO_PIN) */
#endif /* (DriverSPI_SPI_SLAVE_PINS) */

#if (DriverSPI_SPI_MASTER_SS0_PIN)
    #include "DriverSPI_ss0_m.h"
#endif /* (DriverSPI_SPI_MASTER_SS0_PIN) */

#if (DriverSPI_SPI_MASTER_SS1_PIN)
    #include "DriverSPI_ss1_m.h"
#endif /* (DriverSPI_SPI_MASTER_SS1_PIN) */

#if (DriverSPI_SPI_MASTER_SS2_PIN)
    #include "DriverSPI_ss2_m.h"
#endif /* (DriverSPI_SPI_MASTER_SS2_PIN) */

#if (DriverSPI_SPI_MASTER_SS3_PIN)
    #include "DriverSPI_ss3_m.h"
#endif /* (DriverSPI_SPI_MASTER_SS3_PIN) */

#if (DriverSPI_UART_TX_PIN)
    #include "DriverSPI_tx.h"
#endif /* (DriverSPI_UART_TX_PIN) */

#if (DriverSPI_UART_RX_TX_PIN)
    #include "DriverSPI_rx_tx.h"
#endif /* (DriverSPI_UART_RX_TX_PIN) */

#if (DriverSPI_UART_RX_PIN)
    #include "DriverSPI_rx.h"
#endif /* (DriverSPI_UART_RX_PIN) */

#if (DriverSPI_UART_RX_WAKE_PIN)
    #include "DriverSPI_rx_wake.h"
#endif /* (DriverSPI_UART_RX_WAKE_PIN) */

#if (DriverSPI_UART_RTS_PIN)
    #include "DriverSPI_rts.h"
#endif /* (DriverSPI_UART_RTS_PIN) */

#if (DriverSPI_UART_CTS_PIN)
    #include "DriverSPI_cts.h"
#endif /* (DriverSPI_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (DriverSPI_RX_SCL_MOSI_PIN)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define DriverSPI_RX_SCL_MOSI_HSIOM_MASK      (DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_POS       (DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_SEL_GPIO  (DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_SEL_I2C   (DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_SEL_SPI   (DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define DriverSPI_RX_SCL_MOSI_HSIOM_SEL_UART  (DriverSPI_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_MASK      (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_POS       (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (DriverSPI_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) DriverSPI_INTCFG_TYPE_MASK << \
                                                                           DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins DriverSPI_RX_SCL_MOSI_PIN or DriverSPI_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (DriverSPI_RX_SCL_MOSI_PIN) */

#if (DriverSPI_TX_SDA_MISO_PIN)
    #define DriverSPI_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define DriverSPI_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define DriverSPI_TX_SDA_MISO_HSIOM_MASK      (DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define DriverSPI_TX_SDA_MISO_HSIOM_POS       (DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define DriverSPI_TX_SDA_MISO_HSIOM_SEL_GPIO  (DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define DriverSPI_TX_SDA_MISO_HSIOM_SEL_I2C   (DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define DriverSPI_TX_SDA_MISO_HSIOM_SEL_SPI   (DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define DriverSPI_TX_SDA_MISO_HSIOM_SEL_UART  (DriverSPI_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (DriverSPI_TX_SDA_MISO_PIN) */

#if (DriverSPI_CTS_SCLK_PIN)
    #define DriverSPI_CTS_SCLK_HSIOM_REG   (*(reg32 *) DriverSPI_uart_cts_spi_sclk__0__HSIOM)
    #define DriverSPI_CTS_SCLK_HSIOM_PTR   ( (reg32 *) DriverSPI_uart_cts_spi_sclk__0__HSIOM)
    
    #define DriverSPI_CTS_SCLK_HSIOM_MASK      (DriverSPI_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define DriverSPI_CTS_SCLK_HSIOM_POS       (DriverSPI_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define DriverSPI_CTS_SCLK_HSIOM_SEL_GPIO  (DriverSPI_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define DriverSPI_CTS_SCLK_HSIOM_SEL_I2C   (DriverSPI_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define DriverSPI_CTS_SCLK_HSIOM_SEL_SPI   (DriverSPI_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define DriverSPI_CTS_SCLK_HSIOM_SEL_UART  (DriverSPI_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (DriverSPI_CTS_SCLK_PIN) */

#if (DriverSPI_RTS_SS0_PIN)
    #define DriverSPI_RTS_SS0_HSIOM_REG   (*(reg32 *) DriverSPI_uart_rts_spi_ss0__0__HSIOM)
    #define DriverSPI_RTS_SS0_HSIOM_PTR   ( (reg32 *) DriverSPI_uart_rts_spi_ss0__0__HSIOM)
    
    #define DriverSPI_RTS_SS0_HSIOM_MASK      (DriverSPI_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define DriverSPI_RTS_SS0_HSIOM_POS       (DriverSPI_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define DriverSPI_RTS_SS0_HSIOM_SEL_GPIO  (DriverSPI_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define DriverSPI_RTS_SS0_HSIOM_SEL_I2C   (DriverSPI_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define DriverSPI_RTS_SS0_HSIOM_SEL_SPI   (DriverSPI_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1)
    #define DriverSPI_RTS_SS0_HSIOM_SEL_UART  (DriverSPI_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1) */
#endif /* (DriverSPI_RTS_SS0_PIN) */

#if (DriverSPI_SS1_PIN)
    #define DriverSPI_SS1_HSIOM_REG  (*(reg32 *) DriverSPI_spi_ss1__0__HSIOM)
    #define DriverSPI_SS1_HSIOM_PTR  ( (reg32 *) DriverSPI_spi_ss1__0__HSIOM)
    
    #define DriverSPI_SS1_HSIOM_MASK     (DriverSPI_spi_ss1__0__HSIOM_MASK)
    #define DriverSPI_SS1_HSIOM_POS      (DriverSPI_spi_ss1__0__HSIOM_SHIFT)
    #define DriverSPI_SS1_HSIOM_SEL_GPIO (DriverSPI_spi_ss1__0__HSIOM_GPIO)
    #define DriverSPI_SS1_HSIOM_SEL_I2C  (DriverSPI_spi_ss1__0__HSIOM_I2C)
    #define DriverSPI_SS1_HSIOM_SEL_SPI  (DriverSPI_spi_ss1__0__HSIOM_SPI)
#endif /* (DriverSPI_SS1_PIN) */

#if (DriverSPI_SS2_PIN)
    #define DriverSPI_SS2_HSIOM_REG     (*(reg32 *) DriverSPI_spi_ss2__0__HSIOM)
    #define DriverSPI_SS2_HSIOM_PTR     ( (reg32 *) DriverSPI_spi_ss2__0__HSIOM)
    
    #define DriverSPI_SS2_HSIOM_MASK     (DriverSPI_spi_ss2__0__HSIOM_MASK)
    #define DriverSPI_SS2_HSIOM_POS      (DriverSPI_spi_ss2__0__HSIOM_SHIFT)
    #define DriverSPI_SS2_HSIOM_SEL_GPIO (DriverSPI_spi_ss2__0__HSIOM_GPIO)
    #define DriverSPI_SS2_HSIOM_SEL_I2C  (DriverSPI_spi_ss2__0__HSIOM_I2C)
    #define DriverSPI_SS2_HSIOM_SEL_SPI  (DriverSPI_spi_ss2__0__HSIOM_SPI)
#endif /* (DriverSPI_SS2_PIN) */

#if (DriverSPI_SS3_PIN)
    #define DriverSPI_SS3_HSIOM_REG     (*(reg32 *) DriverSPI_spi_ss3__0__HSIOM)
    #define DriverSPI_SS3_HSIOM_PTR     ( (reg32 *) DriverSPI_spi_ss3__0__HSIOM)
    
    #define DriverSPI_SS3_HSIOM_MASK     (DriverSPI_spi_ss3__0__HSIOM_MASK)
    #define DriverSPI_SS3_HSIOM_POS      (DriverSPI_spi_ss3__0__HSIOM_SHIFT)
    #define DriverSPI_SS3_HSIOM_SEL_GPIO (DriverSPI_spi_ss3__0__HSIOM_GPIO)
    #define DriverSPI_SS3_HSIOM_SEL_I2C  (DriverSPI_spi_ss3__0__HSIOM_I2C)
    #define DriverSPI_SS3_HSIOM_SEL_SPI  (DriverSPI_spi_ss3__0__HSIOM_SPI)
#endif /* (DriverSPI_SS3_PIN) */

#if (DriverSPI_I2C_PINS)
    #define DriverSPI_SCL_HSIOM_REG  (*(reg32 *) DriverSPI_scl__0__HSIOM)
    #define DriverSPI_SCL_HSIOM_PTR  ( (reg32 *) DriverSPI_scl__0__HSIOM)
    
    #define DriverSPI_SCL_HSIOM_MASK     (DriverSPI_scl__0__HSIOM_MASK)
    #define DriverSPI_SCL_HSIOM_POS      (DriverSPI_scl__0__HSIOM_SHIFT)
    #define DriverSPI_SCL_HSIOM_SEL_GPIO (DriverSPI_sda__0__HSIOM_GPIO)
    #define DriverSPI_SCL_HSIOM_SEL_I2C  (DriverSPI_sda__0__HSIOM_I2C)
    
    #define DriverSPI_SDA_HSIOM_REG  (*(reg32 *) DriverSPI_sda__0__HSIOM)
    #define DriverSPI_SDA_HSIOM_PTR  ( (reg32 *) DriverSPI_sda__0__HSIOM)
    
    #define DriverSPI_SDA_HSIOM_MASK     (DriverSPI_sda__0__HSIOM_MASK)
    #define DriverSPI_SDA_HSIOM_POS      (DriverSPI_sda__0__HSIOM_SHIFT)
    #define DriverSPI_SDA_HSIOM_SEL_GPIO (DriverSPI_sda__0__HSIOM_GPIO)
    #define DriverSPI_SDA_HSIOM_SEL_I2C  (DriverSPI_sda__0__HSIOM_I2C)
#endif /* (DriverSPI_I2C_PINS) */

#if (DriverSPI_SPI_SLAVE_PINS)
    #define DriverSPI_SCLK_S_HSIOM_REG   (*(reg32 *) DriverSPI_sclk_s__0__HSIOM)
    #define DriverSPI_SCLK_S_HSIOM_PTR   ( (reg32 *) DriverSPI_sclk_s__0__HSIOM)
    
    #define DriverSPI_SCLK_S_HSIOM_MASK      (DriverSPI_sclk_s__0__HSIOM_MASK)
    #define DriverSPI_SCLK_S_HSIOM_POS       (DriverSPI_sclk_s__0__HSIOM_SHIFT)
    #define DriverSPI_SCLK_S_HSIOM_SEL_GPIO  (DriverSPI_sclk_s__0__HSIOM_GPIO)
    #define DriverSPI_SCLK_S_HSIOM_SEL_SPI   (DriverSPI_sclk_s__0__HSIOM_SPI)
    
    #define DriverSPI_SS0_S_HSIOM_REG    (*(reg32 *) DriverSPI_ss0_s__0__HSIOM)
    #define DriverSPI_SS0_S_HSIOM_PTR    ( (reg32 *) DriverSPI_ss0_s__0__HSIOM)
    
    #define DriverSPI_SS0_S_HSIOM_MASK       (DriverSPI_ss0_s__0__HSIOM_MASK)
    #define DriverSPI_SS0_S_HSIOM_POS        (DriverSPI_ss0_s__0__HSIOM_SHIFT)
    #define DriverSPI_SS0_S_HSIOM_SEL_GPIO   (DriverSPI_ss0_s__0__HSIOM_GPIO)  
    #define DriverSPI_SS0_S_HSIOM_SEL_SPI    (DriverSPI_ss0_s__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_SLAVE_PINS) */

#if (DriverSPI_SPI_SLAVE_MOSI_PIN)
    #define DriverSPI_MOSI_S_HSIOM_REG   (*(reg32 *) DriverSPI_mosi_s__0__HSIOM)
    #define DriverSPI_MOSI_S_HSIOM_PTR   ( (reg32 *) DriverSPI_mosi_s__0__HSIOM)
    
    #define DriverSPI_MOSI_S_HSIOM_MASK      (DriverSPI_mosi_s__0__HSIOM_MASK)
    #define DriverSPI_MOSI_S_HSIOM_POS       (DriverSPI_mosi_s__0__HSIOM_SHIFT)
    #define DriverSPI_MOSI_S_HSIOM_SEL_GPIO  (DriverSPI_mosi_s__0__HSIOM_GPIO)
    #define DriverSPI_MOSI_S_HSIOM_SEL_SPI   (DriverSPI_mosi_s__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_SLAVE_MOSI_PIN) */

#if (DriverSPI_SPI_SLAVE_MISO_PIN)
    #define DriverSPI_MISO_S_HSIOM_REG   (*(reg32 *) DriverSPI_miso_s__0__HSIOM)
    #define DriverSPI_MISO_S_HSIOM_PTR   ( (reg32 *) DriverSPI_miso_s__0__HSIOM)
    
    #define DriverSPI_MISO_S_HSIOM_MASK      (DriverSPI_miso_s__0__HSIOM_MASK)
    #define DriverSPI_MISO_S_HSIOM_POS       (DriverSPI_miso_s__0__HSIOM_SHIFT)
    #define DriverSPI_MISO_S_HSIOM_SEL_GPIO  (DriverSPI_miso_s__0__HSIOM_GPIO)
    #define DriverSPI_MISO_S_HSIOM_SEL_SPI   (DriverSPI_miso_s__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_SLAVE_MISO_PIN) */

#if (DriverSPI_SPI_MASTER_MISO_PIN)
    #define DriverSPI_MISO_M_HSIOM_REG   (*(reg32 *) DriverSPI_miso_m__0__HSIOM)
    #define DriverSPI_MISO_M_HSIOM_PTR   ( (reg32 *) DriverSPI_miso_m__0__HSIOM)
    
    #define DriverSPI_MISO_M_HSIOM_MASK      (DriverSPI_miso_m__0__HSIOM_MASK)
    #define DriverSPI_MISO_M_HSIOM_POS       (DriverSPI_miso_m__0__HSIOM_SHIFT)
    #define DriverSPI_MISO_M_HSIOM_SEL_GPIO  (DriverSPI_miso_m__0__HSIOM_GPIO)
    #define DriverSPI_MISO_M_HSIOM_SEL_SPI   (DriverSPI_miso_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_MISO_PIN) */

#if (DriverSPI_SPI_MASTER_MOSI_PIN)
    #define DriverSPI_MOSI_M_HSIOM_REG   (*(reg32 *) DriverSPI_mosi_m__0__HSIOM)
    #define DriverSPI_MOSI_M_HSIOM_PTR   ( (reg32 *) DriverSPI_mosi_m__0__HSIOM)
    
    #define DriverSPI_MOSI_M_HSIOM_MASK      (DriverSPI_mosi_m__0__HSIOM_MASK)
    #define DriverSPI_MOSI_M_HSIOM_POS       (DriverSPI_mosi_m__0__HSIOM_SHIFT)
    #define DriverSPI_MOSI_M_HSIOM_SEL_GPIO  (DriverSPI_mosi_m__0__HSIOM_GPIO)
    #define DriverSPI_MOSI_M_HSIOM_SEL_SPI   (DriverSPI_mosi_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_MOSI_PIN) */

#if (DriverSPI_SPI_MASTER_SCLK_PIN)
    #define DriverSPI_SCLK_M_HSIOM_REG   (*(reg32 *) DriverSPI_sclk_m__0__HSIOM)
    #define DriverSPI_SCLK_M_HSIOM_PTR   ( (reg32 *) DriverSPI_sclk_m__0__HSIOM)
    
    #define DriverSPI_SCLK_M_HSIOM_MASK      (DriverSPI_sclk_m__0__HSIOM_MASK)
    #define DriverSPI_SCLK_M_HSIOM_POS       (DriverSPI_sclk_m__0__HSIOM_SHIFT)
    #define DriverSPI_SCLK_M_HSIOM_SEL_GPIO  (DriverSPI_sclk_m__0__HSIOM_GPIO)
    #define DriverSPI_SCLK_M_HSIOM_SEL_SPI   (DriverSPI_sclk_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_SCLK_PIN) */

#if (DriverSPI_SPI_MASTER_SS0_PIN)
    #define DriverSPI_SS0_M_HSIOM_REG    (*(reg32 *) DriverSPI_ss0_m__0__HSIOM)
    #define DriverSPI_SS0_M_HSIOM_PTR    ( (reg32 *) DriverSPI_ss0_m__0__HSIOM)
    
    #define DriverSPI_SS0_M_HSIOM_MASK       (DriverSPI_ss0_m__0__HSIOM_MASK)
    #define DriverSPI_SS0_M_HSIOM_POS        (DriverSPI_ss0_m__0__HSIOM_SHIFT)
    #define DriverSPI_SS0_M_HSIOM_SEL_GPIO   (DriverSPI_ss0_m__0__HSIOM_GPIO)
    #define DriverSPI_SS0_M_HSIOM_SEL_SPI    (DriverSPI_ss0_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_SS0_PIN) */

#if (DriverSPI_SPI_MASTER_SS1_PIN)
    #define DriverSPI_SS1_M_HSIOM_REG    (*(reg32 *) DriverSPI_ss1_m__0__HSIOM)
    #define DriverSPI_SS1_M_HSIOM_PTR    ( (reg32 *) DriverSPI_ss1_m__0__HSIOM)
    
    #define DriverSPI_SS1_M_HSIOM_MASK       (DriverSPI_ss1_m__0__HSIOM_MASK)
    #define DriverSPI_SS1_M_HSIOM_POS        (DriverSPI_ss1_m__0__HSIOM_SHIFT)
    #define DriverSPI_SS1_M_HSIOM_SEL_GPIO   (DriverSPI_ss1_m__0__HSIOM_GPIO)
    #define DriverSPI_SS1_M_HSIOM_SEL_SPI    (DriverSPI_ss1_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_SS1_PIN) */

#if (DriverSPI_SPI_MASTER_SS2_PIN)
    #define DriverSPI_SS2_M_HSIOM_REG    (*(reg32 *) DriverSPI_ss2_m__0__HSIOM)
    #define DriverSPI_SS2_M_HSIOM_PTR    ( (reg32 *) DriverSPI_ss2_m__0__HSIOM)
    
    #define DriverSPI_SS2_M_HSIOM_MASK       (DriverSPI_ss2_m__0__HSIOM_MASK)
    #define DriverSPI_SS2_M_HSIOM_POS        (DriverSPI_ss2_m__0__HSIOM_SHIFT)
    #define DriverSPI_SS2_M_HSIOM_SEL_GPIO   (DriverSPI_ss2_m__0__HSIOM_GPIO)
    #define DriverSPI_SS2_M_HSIOM_SEL_SPI    (DriverSPI_ss2_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_SS2_PIN) */

#if (DriverSPI_SPI_MASTER_SS3_PIN)
    #define DriverSPI_SS3_M_HSIOM_REG    (*(reg32 *) DriverSPI_ss3_m__0__HSIOM)
    #define DriverSPI_SS3_M_HSIOM_PTR    ( (reg32 *) DriverSPI_ss3_m__0__HSIOM)
    
    #define DriverSPI_SS3_M_HSIOM_MASK      (DriverSPI_ss3_m__0__HSIOM_MASK)
    #define DriverSPI_SS3_M_HSIOM_POS       (DriverSPI_ss3_m__0__HSIOM_SHIFT)
    #define DriverSPI_SS3_M_HSIOM_SEL_GPIO  (DriverSPI_ss3_m__0__HSIOM_GPIO)
    #define DriverSPI_SS3_M_HSIOM_SEL_SPI   (DriverSPI_ss3_m__0__HSIOM_SPI)
#endif /* (DriverSPI_SPI_MASTER_SS3_PIN) */

#if (DriverSPI_UART_RX_PIN)
    #define DriverSPI_RX_HSIOM_REG   (*(reg32 *) DriverSPI_rx__0__HSIOM)
    #define DriverSPI_RX_HSIOM_PTR   ( (reg32 *) DriverSPI_rx__0__HSIOM)
    
    #define DriverSPI_RX_HSIOM_MASK      (DriverSPI_rx__0__HSIOM_MASK)
    #define DriverSPI_RX_HSIOM_POS       (DriverSPI_rx__0__HSIOM_SHIFT)
    #define DriverSPI_RX_HSIOM_SEL_GPIO  (DriverSPI_rx__0__HSIOM_GPIO)
    #define DriverSPI_RX_HSIOM_SEL_UART  (DriverSPI_rx__0__HSIOM_UART)
#endif /* (DriverSPI_UART_RX_PIN) */

#if (DriverSPI_UART_RX_WAKE_PIN)
    #define DriverSPI_RX_WAKE_HSIOM_REG   (*(reg32 *) DriverSPI_rx_wake__0__HSIOM)
    #define DriverSPI_RX_WAKE_HSIOM_PTR   ( (reg32 *) DriverSPI_rx_wake__0__HSIOM)
    
    #define DriverSPI_RX_WAKE_HSIOM_MASK      (DriverSPI_rx_wake__0__HSIOM_MASK)
    #define DriverSPI_RX_WAKE_HSIOM_POS       (DriverSPI_rx_wake__0__HSIOM_SHIFT)
    #define DriverSPI_RX_WAKE_HSIOM_SEL_GPIO  (DriverSPI_rx_wake__0__HSIOM_GPIO)
    #define DriverSPI_RX_WAKE_HSIOM_SEL_UART  (DriverSPI_rx_wake__0__HSIOM_UART)
#endif /* (DriverSPI_UART_WAKE_RX_PIN) */

#if (DriverSPI_UART_CTS_PIN)
    #define DriverSPI_CTS_HSIOM_REG   (*(reg32 *) DriverSPI_cts__0__HSIOM)
    #define DriverSPI_CTS_HSIOM_PTR   ( (reg32 *) DriverSPI_cts__0__HSIOM)
    
    #define DriverSPI_CTS_HSIOM_MASK      (DriverSPI_cts__0__HSIOM_MASK)
    #define DriverSPI_CTS_HSIOM_POS       (DriverSPI_cts__0__HSIOM_SHIFT)
    #define DriverSPI_CTS_HSIOM_SEL_GPIO  (DriverSPI_cts__0__HSIOM_GPIO)
    #define DriverSPI_CTS_HSIOM_SEL_UART  (DriverSPI_cts__0__HSIOM_UART)
#endif /* (DriverSPI_UART_CTS_PIN) */

#if (DriverSPI_UART_TX_PIN)
    #define DriverSPI_TX_HSIOM_REG   (*(reg32 *) DriverSPI_tx__0__HSIOM)
    #define DriverSPI_TX_HSIOM_PTR   ( (reg32 *) DriverSPI_tx__0__HSIOM)
    
    #define DriverSPI_TX_HSIOM_MASK      (DriverSPI_tx__0__HSIOM_MASK)
    #define DriverSPI_TX_HSIOM_POS       (DriverSPI_tx__0__HSIOM_SHIFT)
    #define DriverSPI_TX_HSIOM_SEL_GPIO  (DriverSPI_tx__0__HSIOM_GPIO)
    #define DriverSPI_TX_HSIOM_SEL_UART  (DriverSPI_tx__0__HSIOM_UART)
#endif /* (DriverSPI_UART_TX_PIN) */

#if (DriverSPI_UART_RX_TX_PIN)
    #define DriverSPI_RX_TX_HSIOM_REG   (*(reg32 *) DriverSPI_rx_tx__0__HSIOM)
    #define DriverSPI_RX_TX_HSIOM_PTR   ( (reg32 *) DriverSPI_rx_tx__0__HSIOM)
    
    #define DriverSPI_RX_TX_HSIOM_MASK      (DriverSPI_rx_tx__0__HSIOM_MASK)
    #define DriverSPI_RX_TX_HSIOM_POS       (DriverSPI_rx_tx__0__HSIOM_SHIFT)
    #define DriverSPI_RX_TX_HSIOM_SEL_GPIO  (DriverSPI_rx_tx__0__HSIOM_GPIO)
    #define DriverSPI_RX_TX_HSIOM_SEL_UART  (DriverSPI_rx_tx__0__HSIOM_UART)
#endif /* (DriverSPI_UART_RX_TX_PIN) */

#if (DriverSPI_UART_RTS_PIN)
    #define DriverSPI_RTS_HSIOM_REG      (*(reg32 *) DriverSPI_rts__0__HSIOM)
    #define DriverSPI_RTS_HSIOM_PTR      ( (reg32 *) DriverSPI_rts__0__HSIOM)
    
    #define DriverSPI_RTS_HSIOM_MASK     (DriverSPI_rts__0__HSIOM_MASK)
    #define DriverSPI_RTS_HSIOM_POS      (DriverSPI_rts__0__HSIOM_SHIFT)    
    #define DriverSPI_RTS_HSIOM_SEL_GPIO (DriverSPI_rts__0__HSIOM_GPIO)
    #define DriverSPI_RTS_HSIOM_SEL_UART (DriverSPI_rts__0__HSIOM_UART)    
#endif /* (DriverSPI_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define DriverSPI_HSIOM_DEF_SEL      (0x00u)
#define DriverSPI_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for DriverSPI_CY_SCBIP_V0 
* and DriverSPI_CY_SCBIP_V1. It is not recommended to use them for 
* DriverSPI_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define DriverSPI_HSIOM_UART_SEL     (0x09u)
#define DriverSPI_HSIOM_I2C_SEL      (0x0Eu)
#define DriverSPI_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define DriverSPI_RX_SCL_MOSI_PIN_INDEX       (0u)
#define DriverSPI_TX_SDA_MISO_PIN_INDEX       (1u)
#define DriverSPI_CTS_SCLK_PIN_INDEX       (2u)
#define DriverSPI_RTS_SS0_PIN_INDEX       (3u)
#define DriverSPI_SS1_PIN_INDEX                  (4u)
#define DriverSPI_SS2_PIN_INDEX                  (5u)
#define DriverSPI_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define DriverSPI_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define DriverSPI_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << DriverSPI_RX_SCL_MOSI_PIN_INDEX)
#define DriverSPI_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << DriverSPI_TX_SDA_MISO_PIN_INDEX)
#define DriverSPI_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << DriverSPI_CTS_SCLK_PIN_INDEX)
#define DriverSPI_RTS_SS0_PIN_MASK     ((uint32) 0x01u << DriverSPI_RTS_SS0_PIN_INDEX)
#define DriverSPI_SS1_PIN_MASK                ((uint32) 0x01u << DriverSPI_SS1_PIN_INDEX)
#define DriverSPI_SS2_PIN_MASK                ((uint32) 0x01u << DriverSPI_SS2_PIN_INDEX)
#define DriverSPI_SS3_PIN_MASK                ((uint32) 0x01u << DriverSPI_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define DriverSPI_INTCFG_TYPE_MASK           (0x03u)
#define DriverSPI_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define DriverSPI_PIN_DM_ALG_HIZ  (0u)
#define DriverSPI_PIN_DM_DIG_HIZ  (1u)
#define DriverSPI_PIN_DM_OD_LO    (4u)
#define DriverSPI_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define DriverSPI_DM_MASK    (0x7u)
#define DriverSPI_DM_SIZE    (3u)
#define DriverSPI_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) DriverSPI_DM_MASK << (DriverSPI_DM_SIZE * (pos)))) >> \
                                                              (DriverSPI_DM_SIZE * (pos)) )

#if (DriverSPI_TX_SDA_MISO_PIN)
    #define DriverSPI_CHECK_TX_SDA_MISO_PIN_USED \
                (DriverSPI_PIN_DM_ALG_HIZ != \
                    DriverSPI_GET_P4_PIN_DM(DriverSPI_uart_tx_i2c_sda_spi_miso_PC, \
                                                   DriverSPI_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (DriverSPI_TX_SDA_MISO_PIN) */

#if (DriverSPI_RTS_SS0_PIN)
    #define DriverSPI_CHECK_RTS_SS0_PIN_USED \
                (DriverSPI_PIN_DM_ALG_HIZ != \
                    DriverSPI_GET_P4_PIN_DM(DriverSPI_uart_rts_spi_ss0_PC, \
                                                   DriverSPI_uart_rts_spi_ss0_SHIFT))
#endif /* (DriverSPI_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define DriverSPI_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define DriverSPI_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define DriverSPI_SET_HSIOM_SEL(reg, mask, pos, sel) DriverSPI_SET_REGISTER_BITS(reg, mask, pos, sel)
#define DriverSPI_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        DriverSPI_SET_REGISTER_BITS(reg, mask, pos, intType)
#define DriverSPI_SET_INP_DIS(reg, mask, val) DriverSPI_SET_REGISTER_BIT(reg, mask, val)

/* DriverSPI_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  DriverSPI_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (DriverSPI_CY_SCBIP_V0)
#if (DriverSPI_I2C_PINS)
    #define DriverSPI_SET_I2C_SCL_DR(val) DriverSPI_scl_Write(val)

    #define DriverSPI_SET_I2C_SCL_HSIOM_SEL(sel) \
                          DriverSPI_SET_HSIOM_SEL(DriverSPI_SCL_HSIOM_REG,  \
                                                         DriverSPI_SCL_HSIOM_MASK, \
                                                         DriverSPI_SCL_HSIOM_POS,  \
                                                         (sel))
    #define DriverSPI_WAIT_SCL_SET_HIGH  (0u == DriverSPI_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
    #define DriverSPI_SET_I2C_SCL_DR(val) \
                            DriverSPI_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define DriverSPI_SET_I2C_SCL_HSIOM_SEL(sel) \
                    DriverSPI_SET_HSIOM_SEL(DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define DriverSPI_WAIT_SCL_SET_HIGH  (0u == DriverSPI_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (DriverSPI_RX_SCL_MOSI_PIN)
    #define DriverSPI_SET_I2C_SCL_DR(val) \
                            DriverSPI_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define DriverSPI_SET_I2C_SCL_HSIOM_SEL(sel) \
                            DriverSPI_SET_HSIOM_SEL(DriverSPI_RX_SCL_MOSI_HSIOM_REG,  \
                                                           DriverSPI_RX_SCL_MOSI_HSIOM_MASK, \
                                                           DriverSPI_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define DriverSPI_WAIT_SCL_SET_HIGH  (0u == DriverSPI_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define DriverSPI_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define DriverSPI_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define DriverSPI_WAIT_SCL_SET_HIGH  (0u)
#endif /* (DriverSPI_I2C_PINS) */

/* SCB I2C: sda signal */
#if (DriverSPI_I2C_PINS)
    #define DriverSPI_WAIT_SDA_SET_HIGH  (0u == DriverSPI_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (DriverSPI_TX_SDA_MISO_PIN)
    #define DriverSPI_WAIT_SDA_SET_HIGH  (0u == DriverSPI_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define DriverSPI_WAIT_SDA_SET_HIGH  (0u)
#endif /* (DriverSPI_MOSI_SCL_RX_PIN) */
#endif /* (DriverSPI_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (DriverSPI_RX_SCL_MOSI_PIN)
    #define DriverSPI_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
    #define DriverSPI_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) DriverSPI_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(DriverSPI_UART_RX_WAKE_PIN)
    #define DriverSPI_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) DriverSPI_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (DriverSPI_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define DriverSPI_REMOVE_MOSI_SCL_RX_WAKE_PIN    DriverSPI_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define DriverSPI_REMOVE_MOSI_SCL_RX_PIN         DriverSPI_REMOVE_RX_SCL_MOSI_PIN
#define DriverSPI_REMOVE_MISO_SDA_TX_PIN         DriverSPI_REMOVE_TX_SDA_MISO_PIN
#ifndef DriverSPI_REMOVE_SCLK_PIN
#define DriverSPI_REMOVE_SCLK_PIN                DriverSPI_REMOVE_CTS_SCLK_PIN
#endif /* DriverSPI_REMOVE_SCLK_PIN */
#ifndef DriverSPI_REMOVE_SS0_PIN
#define DriverSPI_REMOVE_SS0_PIN                 DriverSPI_REMOVE_RTS_SS0_PIN
#endif /* DriverSPI_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define DriverSPI_MOSI_SCL_RX_WAKE_PIN   DriverSPI_RX_WAKE_SCL_MOSI_PIN
#define DriverSPI_MOSI_SCL_RX_PIN        DriverSPI_RX_SCL_MOSI_PIN
#define DriverSPI_MISO_SDA_TX_PIN        DriverSPI_TX_SDA_MISO_PIN
#ifndef DriverSPI_SCLK_PIN
#define DriverSPI_SCLK_PIN               DriverSPI_CTS_SCLK_PIN
#endif /* DriverSPI_SCLK_PIN */
#ifndef DriverSPI_SS0_PIN
#define DriverSPI_SS0_PIN                DriverSPI_RTS_SS0_PIN
#endif /* DriverSPI_SS0_PIN */

#if (DriverSPI_MOSI_SCL_RX_WAKE_PIN)
    #define DriverSPI_MOSI_SCL_RX_WAKE_HSIOM_REG     DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DriverSPI_MOSI_SCL_RX_WAKE_HSIOM_PTR     DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DriverSPI_MOSI_SCL_RX_WAKE_HSIOM_MASK    DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DriverSPI_MOSI_SCL_RX_WAKE_HSIOM_POS     DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define DriverSPI_MOSI_SCL_RX_WAKE_INTCFG_REG    DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DriverSPI_MOSI_SCL_RX_WAKE_INTCFG_PTR    DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define DriverSPI_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DriverSPI_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (DriverSPI_RX_WAKE_SCL_MOSI_PIN) */

#if (DriverSPI_MOSI_SCL_RX_PIN)
    #define DriverSPI_MOSI_SCL_RX_HSIOM_REG      DriverSPI_RX_SCL_MOSI_HSIOM_REG
    #define DriverSPI_MOSI_SCL_RX_HSIOM_PTR      DriverSPI_RX_SCL_MOSI_HSIOM_PTR
    #define DriverSPI_MOSI_SCL_RX_HSIOM_MASK     DriverSPI_RX_SCL_MOSI_HSIOM_MASK
    #define DriverSPI_MOSI_SCL_RX_HSIOM_POS      DriverSPI_RX_SCL_MOSI_HSIOM_POS
#endif /* (DriverSPI_MOSI_SCL_RX_PIN) */

#if (DriverSPI_MISO_SDA_TX_PIN)
    #define DriverSPI_MISO_SDA_TX_HSIOM_REG      DriverSPI_TX_SDA_MISO_HSIOM_REG
    #define DriverSPI_MISO_SDA_TX_HSIOM_PTR      DriverSPI_TX_SDA_MISO_HSIOM_REG
    #define DriverSPI_MISO_SDA_TX_HSIOM_MASK     DriverSPI_TX_SDA_MISO_HSIOM_REG
    #define DriverSPI_MISO_SDA_TX_HSIOM_POS      DriverSPI_TX_SDA_MISO_HSIOM_REG
#endif /* (DriverSPI_MISO_SDA_TX_PIN_PIN) */

#if (DriverSPI_SCLK_PIN)
    #ifndef DriverSPI_SCLK_HSIOM_REG
    #define DriverSPI_SCLK_HSIOM_REG     DriverSPI_CTS_SCLK_HSIOM_REG
    #define DriverSPI_SCLK_HSIOM_PTR     DriverSPI_CTS_SCLK_HSIOM_PTR
    #define DriverSPI_SCLK_HSIOM_MASK    DriverSPI_CTS_SCLK_HSIOM_MASK
    #define DriverSPI_SCLK_HSIOM_POS     DriverSPI_CTS_SCLK_HSIOM_POS
    #endif /* DriverSPI_SCLK_HSIOM_REG */
#endif /* (DriverSPI_SCLK_PIN) */

#if (DriverSPI_SS0_PIN)
    #ifndef DriverSPI_SS0_HSIOM_REG
    #define DriverSPI_SS0_HSIOM_REG      DriverSPI_RTS_SS0_HSIOM_REG
    #define DriverSPI_SS0_HSIOM_PTR      DriverSPI_RTS_SS0_HSIOM_PTR
    #define DriverSPI_SS0_HSIOM_MASK     DriverSPI_RTS_SS0_HSIOM_MASK
    #define DriverSPI_SS0_HSIOM_POS      DriverSPI_RTS_SS0_HSIOM_POS
    #endif /* DriverSPI_SS0_HSIOM_REG */
#endif /* (DriverSPI_SS0_PIN) */

#define DriverSPI_MOSI_SCL_RX_WAKE_PIN_INDEX DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX
#define DriverSPI_MOSI_SCL_RX_PIN_INDEX      DriverSPI_RX_SCL_MOSI_PIN_INDEX
#define DriverSPI_MISO_SDA_TX_PIN_INDEX      DriverSPI_TX_SDA_MISO_PIN_INDEX
#ifndef DriverSPI_SCLK_PIN_INDEX
#define DriverSPI_SCLK_PIN_INDEX             DriverSPI_CTS_SCLK_PIN_INDEX
#endif /* DriverSPI_SCLK_PIN_INDEX */
#ifndef DriverSPI_SS0_PIN_INDEX
#define DriverSPI_SS0_PIN_INDEX              DriverSPI_RTS_SS0_PIN_INDEX
#endif /* DriverSPI_SS0_PIN_INDEX */

#define DriverSPI_MOSI_SCL_RX_WAKE_PIN_MASK DriverSPI_RX_WAKE_SCL_MOSI_PIN_MASK
#define DriverSPI_MOSI_SCL_RX_PIN_MASK      DriverSPI_RX_SCL_MOSI_PIN_MASK
#define DriverSPI_MISO_SDA_TX_PIN_MASK      DriverSPI_TX_SDA_MISO_PIN_MASK
#ifndef DriverSPI_SCLK_PIN_MASK
#define DriverSPI_SCLK_PIN_MASK             DriverSPI_CTS_SCLK_PIN_MASK
#endif /* DriverSPI_SCLK_PIN_MASK */
#ifndef DriverSPI_SS0_PIN_MASK
#define DriverSPI_SS0_PIN_MASK              DriverSPI_RTS_SS0_PIN_MASK
#endif /* DriverSPI_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_DriverSPI_H) */


/* [] END OF FILE */
