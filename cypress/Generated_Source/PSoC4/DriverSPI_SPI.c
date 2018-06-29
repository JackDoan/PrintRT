/***************************************************************************//**
* \file DriverSPI_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DriverSPI_PVT.h"
#include "DriverSPI_SPI_UART_PVT.h"

#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const DriverSPI_SPI_INIT_STRUCT DriverSPI_configSpi =
    {
        DriverSPI_SPI_MODE,
        DriverSPI_SPI_SUB_MODE,
        DriverSPI_SPI_CLOCK_MODE,
        DriverSPI_SPI_OVS_FACTOR,
        DriverSPI_SPI_MEDIAN_FILTER_ENABLE,
        DriverSPI_SPI_LATE_MISO_SAMPLE_ENABLE,
        DriverSPI_SPI_WAKE_ENABLE,
        DriverSPI_SPI_RX_DATA_BITS_NUM,
        DriverSPI_SPI_TX_DATA_BITS_NUM,
        DriverSPI_SPI_BITS_ORDER,
        DriverSPI_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) DriverSPI_SCB_IRQ_INTERNAL,
        DriverSPI_SPI_INTR_RX_MASK,
        DriverSPI_SPI_RX_TRIGGER_LEVEL,
        DriverSPI_SPI_INTR_TX_MASK,
        DriverSPI_SPI_TX_TRIGGER_LEVEL,
        (uint8) DriverSPI_SPI_BYTE_MODE_ENABLE,
        (uint8) DriverSPI_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) DriverSPI_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: DriverSPI_SpiInit
    ****************************************************************************//**
    *
    *  Configures the DriverSPI for SPI operation.
    *
    *  This function is intended specifically to be used when the DriverSPI 
    *  configuration is set to “Unconfigured DriverSPI” in the customizer. 
    *  After initializing the DriverSPI in SPI mode using this function, 
    *  the component can be enabled using the DriverSPI_Start() or 
    * DriverSPI_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void DriverSPI_SpiInit(const DriverSPI_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            DriverSPI_SetPins(DriverSPI_SCB_MODE_SPI, config->mode, DriverSPI_DUMMY_PARAM);

            /* Store internal configuration */
            DriverSPI_scbMode       = (uint8) DriverSPI_SCB_MODE_SPI;
            DriverSPI_scbEnableWake = (uint8) config->enableWake;
            DriverSPI_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            DriverSPI_rxBuffer      =         config->rxBuffer;
            DriverSPI_rxDataBits    = (uint8) config->rxDataBits;
            DriverSPI_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            DriverSPI_txBuffer      =         config->txBuffer;
            DriverSPI_txDataBits    = (uint8) config->txDataBits;
            DriverSPI_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            DriverSPI_CTRL_REG     = DriverSPI_GET_CTRL_OVS(config->oversample)           |
                                            DriverSPI_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            DriverSPI_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            DriverSPI_CTRL_SPI;

            DriverSPI_SPI_CTRL_REG = DriverSPI_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            DriverSPI_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          DriverSPI_SPI_MODE_TI_PRECEDES_MASK) |
                                            DriverSPI_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            DriverSPI_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            DriverSPI_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            DriverSPI_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            DriverSPI_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            DriverSPI_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            DriverSPI_RX_CTRL_REG     =  DriverSPI_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                DriverSPI_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                DriverSPI_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                DriverSPI_SPI_RX_CTRL;

            DriverSPI_RX_FIFO_CTRL_REG = DriverSPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            DriverSPI_TX_CTRL_REG      = DriverSPI_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                DriverSPI_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                DriverSPI_SPI_TX_CTRL;

            DriverSPI_TX_FIFO_CTRL_REG = DriverSPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (DriverSPI_ISR_NUMBER);
            CyIntSetPriority(DriverSPI_ISR_NUMBER, DriverSPI_ISR_PRIORITY);
            (void) CyIntSetVector(DriverSPI_ISR_NUMBER, &DriverSPI_SPI_UART_ISR);

            /* Configure interrupt sources */
            DriverSPI_INTR_I2C_EC_MASK_REG = DriverSPI_NO_INTR_SOURCES;
            DriverSPI_INTR_SPI_EC_MASK_REG = DriverSPI_NO_INTR_SOURCES;
            DriverSPI_INTR_SLAVE_MASK_REG  = DriverSPI_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            DriverSPI_INTR_MASTER_MASK_REG = DriverSPI_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            DriverSPI_INTR_RX_MASK_REG     = DriverSPI_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            DriverSPI_INTR_TX_MASK_REG     = DriverSPI_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            DriverSPI_IntrTxMask = LO16(DriverSPI_INTR_TX_MASK_REG);

            /* Set active SS0 */
            DriverSPI_SpiSetActiveSlaveSelect(DriverSPI_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            DriverSPI_rxBufferHead     = 0u;
            DriverSPI_rxBufferTail     = 0u;
            DriverSPI_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            DriverSPI_txBufferHead = 0u;
            DriverSPI_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: DriverSPI_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void DriverSPI_SpiInit(void)
    {
        /* Configure SPI interface */
        DriverSPI_CTRL_REG     = DriverSPI_SPI_DEFAULT_CTRL;
        DriverSPI_SPI_CTRL_REG = DriverSPI_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        DriverSPI_RX_CTRL_REG      = DriverSPI_SPI_DEFAULT_RX_CTRL;
        DriverSPI_RX_FIFO_CTRL_REG = DriverSPI_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        DriverSPI_TX_CTRL_REG      = DriverSPI_SPI_DEFAULT_TX_CTRL;
        DriverSPI_TX_FIFO_CTRL_REG = DriverSPI_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(DriverSPI_SCB_IRQ_INTERNAL)
            CyIntDisable    (DriverSPI_ISR_NUMBER);
            CyIntSetPriority(DriverSPI_ISR_NUMBER, DriverSPI_ISR_PRIORITY);
            (void) CyIntSetVector(DriverSPI_ISR_NUMBER, &DriverSPI_SPI_UART_ISR);
    #endif /* (DriverSPI_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        DriverSPI_INTR_I2C_EC_MASK_REG = DriverSPI_SPI_DEFAULT_INTR_I2C_EC_MASK;
        DriverSPI_INTR_SPI_EC_MASK_REG = DriverSPI_SPI_DEFAULT_INTR_SPI_EC_MASK;
        DriverSPI_INTR_SLAVE_MASK_REG  = DriverSPI_SPI_DEFAULT_INTR_SLAVE_MASK;
        DriverSPI_INTR_MASTER_MASK_REG = DriverSPI_SPI_DEFAULT_INTR_MASTER_MASK;
        DriverSPI_INTR_RX_MASK_REG     = DriverSPI_SPI_DEFAULT_INTR_RX_MASK;
        DriverSPI_INTR_TX_MASK_REG     = DriverSPI_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        DriverSPI_IntrTxMask = LO16(DriverSPI_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (DriverSPI_SPI_MASTER_CONST)
        DriverSPI_SpiSetActiveSlaveSelect(DriverSPI_SPI_SLAVE_SELECT0);
    #endif /* (DriverSPI_SPI_MASTER_CONST) */

    #if(DriverSPI_INTERNAL_RX_SW_BUFFER_CONST)
        DriverSPI_rxBufferHead     = 0u;
        DriverSPI_rxBufferTail     = 0u;
        DriverSPI_rxBufferOverflow = 0u;
    #endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(DriverSPI_INTERNAL_TX_SW_BUFFER_CONST)
        DriverSPI_txBufferHead = 0u;
        DriverSPI_txBufferTail = 0u;
    #endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: DriverSPI_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void DriverSPI_SpiPostEnable(void)
{
#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (DriverSPI_CHECK_SPI_MASTER)
    {
    #if (DriverSPI_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_CTS_SCLK_HSIOM_REG, DriverSPI_CTS_SCLK_HSIOM_MASK,
                                       DriverSPI_CTS_SCLK_HSIOM_POS, DriverSPI_CTS_SCLK_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_CTS_SCLK_PIN) */

    #if (DriverSPI_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_RTS_SS0_HSIOM_REG, DriverSPI_RTS_SS0_HSIOM_MASK,
                                       DriverSPI_RTS_SS0_HSIOM_POS, DriverSPI_RTS_SS0_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_RTS_SS0_PIN) */

    #if (DriverSPI_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS1_HSIOM_REG, DriverSPI_SS1_HSIOM_MASK,
                                       DriverSPI_SS1_HSIOM_POS, DriverSPI_SS1_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SS1_PIN) */

    #if (DriverSPI_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS2_HSIOM_REG, DriverSPI_SS2_HSIOM_MASK,
                                       DriverSPI_SS2_HSIOM_POS, DriverSPI_SS2_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SS2_PIN) */

    #if (DriverSPI_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS3_HSIOM_REG, DriverSPI_SS3_HSIOM_MASK,
                                       DriverSPI_SS3_HSIOM_POS, DriverSPI_SS3_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SS3_PIN) */
    }

#else

    #if (DriverSPI_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SCLK_M_HSIOM_REG, DriverSPI_SCLK_M_HSIOM_MASK,
                                       DriverSPI_SCLK_M_HSIOM_POS, DriverSPI_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_MISO_SDA_TX_PIN_PIN) */

    #if (DriverSPI_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS0_M_HSIOM_REG, DriverSPI_SS0_M_HSIOM_MASK,
                                       DriverSPI_SS0_M_HSIOM_POS, DriverSPI_SS0_M_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SPI_MASTER_SS0_PIN) */

    #if (DriverSPI_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS1_M_HSIOM_REG, DriverSPI_SS1_M_HSIOM_MASK,
                                       DriverSPI_SS1_M_HSIOM_POS, DriverSPI_SS1_M_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SPI_MASTER_SS1_PIN) */

    #if (DriverSPI_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS2_M_HSIOM_REG, DriverSPI_SS2_M_HSIOM_MASK,
                                       DriverSPI_SS2_M_HSIOM_POS, DriverSPI_SS2_M_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SPI_MASTER_SS2_PIN) */

    #if (DriverSPI_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS3_M_HSIOM_REG, DriverSPI_SS3_M_HSIOM_MASK,
                                       DriverSPI_SS3_M_HSIOM_POS, DriverSPI_SS3_M_HSIOM_SEL_SPI);
    #endif /* (DriverSPI_SPI_MASTER_SS3_PIN) */

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    DriverSPI_SetTxInterruptMode(DriverSPI_IntrTxMask);
}


/*******************************************************************************
* Function Name: DriverSPI_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void DriverSPI_SpiStop(void)
{
#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (DriverSPI_CHECK_SPI_MASTER)
    {
    #if (DriverSPI_CTS_SCLK_PIN)
        /* Set output pin state after block is disabled */
        DriverSPI_uart_cts_spi_sclk_Write(DriverSPI_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_CTS_SCLK_HSIOM_REG, DriverSPI_CTS_SCLK_HSIOM_MASK,
                                       DriverSPI_CTS_SCLK_HSIOM_POS, DriverSPI_CTS_SCLK_HSIOM_SEL_GPIO);
    #endif /* (DriverSPI_uart_cts_spi_sclk_PIN) */

    #if (DriverSPI_RTS_SS0_PIN)
        /* Set output pin state after block is disabled */
        DriverSPI_uart_rts_spi_ss0_Write(DriverSPI_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_RTS_SS0_HSIOM_REG, DriverSPI_RTS_SS0_HSIOM_MASK,
                                       DriverSPI_RTS_SS0_HSIOM_POS, DriverSPI_RTS_SS0_HSIOM_SEL_GPIO);
    #endif /* (DriverSPI_uart_rts_spi_ss0_PIN) */

    #if (DriverSPI_SS1_PIN)
        /* Set output pin state after block is disabled */
        DriverSPI_spi_ss1_Write(DriverSPI_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS1_HSIOM_REG, DriverSPI_SS1_HSIOM_MASK,
                                       DriverSPI_SS1_HSIOM_POS, DriverSPI_SS1_HSIOM_SEL_GPIO);
    #endif /* (DriverSPI_SS1_PIN) */

    #if (DriverSPI_SS2_PIN)
        /* Set output pin state after block is disabled */
        DriverSPI_spi_ss2_Write(DriverSPI_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS2_HSIOM_REG, DriverSPI_SS2_HSIOM_MASK,
                                       DriverSPI_SS2_HSIOM_POS, DriverSPI_SS2_HSIOM_SEL_GPIO);
    #endif /* (DriverSPI_SS2_PIN) */

    #if (DriverSPI_SS3_PIN)
        /* Set output pin state after block is disabled */
        DriverSPI_spi_ss3_Write(DriverSPI_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS3_HSIOM_REG, DriverSPI_SS3_HSIOM_MASK,
                                       DriverSPI_SS3_HSIOM_POS, DriverSPI_SS3_HSIOM_SEL_GPIO);
    #endif /* (DriverSPI_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        DriverSPI_IntrTxMask = LO16(DriverSPI_GetTxInterruptMode() & DriverSPI_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        DriverSPI_IntrTxMask = LO16(DriverSPI_GetTxInterruptMode() & DriverSPI_INTR_SPIS_TX_RESTORE);
    }

#else

#if (DriverSPI_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    DriverSPI_sclk_m_Write(DriverSPI_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    DriverSPI_SET_HSIOM_SEL(DriverSPI_SCLK_M_HSIOM_REG, DriverSPI_SCLK_M_HSIOM_MASK,
                                   DriverSPI_SCLK_M_HSIOM_POS, DriverSPI_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (DriverSPI_MISO_SDA_TX_PIN_PIN) */

#if (DriverSPI_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    DriverSPI_ss0_m_Write(DriverSPI_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    DriverSPI_SET_HSIOM_SEL(DriverSPI_SS0_M_HSIOM_REG, DriverSPI_SS0_M_HSIOM_MASK,
                                   DriverSPI_SS0_M_HSIOM_POS, DriverSPI_SS0_M_HSIOM_SEL_GPIO);
#endif /* (DriverSPI_SPI_MASTER_SS0_PIN) */

#if (DriverSPI_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    DriverSPI_ss1_m_Write(DriverSPI_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    DriverSPI_SET_HSIOM_SEL(DriverSPI_SS1_M_HSIOM_REG, DriverSPI_SS1_M_HSIOM_MASK,
                                   DriverSPI_SS1_M_HSIOM_POS, DriverSPI_SS1_M_HSIOM_SEL_GPIO);
#endif /* (DriverSPI_SPI_MASTER_SS1_PIN) */

#if (DriverSPI_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    DriverSPI_ss2_m_Write(DriverSPI_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    DriverSPI_SET_HSIOM_SEL(DriverSPI_SS2_M_HSIOM_REG, DriverSPI_SS2_M_HSIOM_MASK,
                                   DriverSPI_SS2_M_HSIOM_POS, DriverSPI_SS2_M_HSIOM_SEL_GPIO);
#endif /* (DriverSPI_SPI_MASTER_SS2_PIN) */

#if (DriverSPI_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    DriverSPI_ss3_m_Write(DriverSPI_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    DriverSPI_SET_HSIOM_SEL(DriverSPI_SS3_M_HSIOM_REG, DriverSPI_SS3_M_HSIOM_MASK,
                                   DriverSPI_SS3_M_HSIOM_POS, DriverSPI_SS3_M_HSIOM_SEL_GPIO);
#endif /* (DriverSPI_SPI_MASTER_SS3_PIN) */

    #if (DriverSPI_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        DriverSPI_IntrTxMask = LO16(DriverSPI_GetTxInterruptMode() & DriverSPI_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        DriverSPI_IntrTxMask = LO16(DriverSPI_GetTxInterruptMode() & DriverSPI_INTR_SPIS_TX_RESTORE);
    #endif /* (DriverSPI_SPI_MASTER_CONST) */

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (DriverSPI_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: DriverSPI_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - DriverSPI_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - DriverSPI_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - DriverSPI_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - DriverSPI_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void DriverSPI_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = DriverSPI_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~DriverSPI_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  DriverSPI_GET_SPI_CTRL_SS(slaveSelect);

        DriverSPI_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (DriverSPI_SPI_MASTER_CONST) */


#if !(DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: DriverSPI_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - DriverSPI_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - DriverSPI_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - DriverSPI_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - DriverSPI_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - DriverSPI_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - DriverSPI_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void DriverSPI_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = DriverSPI_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            DriverSPI_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            DriverSPI_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1) */


#if(DriverSPI_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: DriverSPI_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void DriverSPI_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        DriverSPI_ClearSpiExtClkInterruptSource(DriverSPI_INTR_SPI_EC_WAKE_UP);
        DriverSPI_SetSpiExtClkInterruptMode(DriverSPI_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: DriverSPI_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void DriverSPI_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        DriverSPI_SetSpiExtClkInterruptMode(DriverSPI_NO_INTR_SOURCES);
    }
#endif /* (DriverSPI_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
