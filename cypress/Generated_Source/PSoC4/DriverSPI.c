/***************************************************************************//**
* \file DriverSPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (DriverSPI_SCB_MODE_I2C_INC)
    #include "DriverSPI_I2C_PVT.h"
#endif /* (DriverSPI_SCB_MODE_I2C_INC) */

#if (DriverSPI_SCB_MODE_EZI2C_INC)
    #include "DriverSPI_EZI2C_PVT.h"
#endif /* (DriverSPI_SCB_MODE_EZI2C_INC) */

#if (DriverSPI_SCB_MODE_SPI_INC || DriverSPI_SCB_MODE_UART_INC)
    #include "DriverSPI_SPI_UART_PVT.h"
#endif /* (DriverSPI_SCB_MODE_SPI_INC || DriverSPI_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 DriverSPI_scbMode = DriverSPI_SCB_MODE_UNCONFIG;
    uint8 DriverSPI_scbEnableWake;
    uint8 DriverSPI_scbEnableIntr;

    /* I2C configuration variables */
    uint8 DriverSPI_mode;
    uint8 DriverSPI_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * DriverSPI_rxBuffer;
    uint8  DriverSPI_rxDataBits;
    uint32 DriverSPI_rxBufferSize;

    volatile uint8 * DriverSPI_txBuffer;
    uint8  DriverSPI_txDataBits;
    uint32 DriverSPI_txBufferSize;

    /* EZI2C configuration variables */
    uint8 DriverSPI_numberOfAddr;
    uint8 DriverSPI_subAddrSize;
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** DriverSPI_initVar indicates whether the DriverSPI 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the DriverSPI_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  DriverSPI_Init() function can be called before the 
*  DriverSPI_Start() or DriverSPI_Enable() function.
*/
uint8 DriverSPI_initVar = 0u;


#if (! (DriverSPI_SCB_MODE_I2C_CONST_CFG || \
        DriverSPI_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * DriverSPI_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent DriverSPI_Enable() call.
    */
    uint16 DriverSPI_IntrTxMask = 0u;
#endif /* (! (DriverSPI_SCB_MODE_I2C_CONST_CFG || \
              DriverSPI_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (DriverSPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DriverSPI_CUSTOM_INTR_HANDLER)
    void (*DriverSPI_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_DriverSPI_CUSTOM_INTR_HANDLER) */
#endif /* (DriverSPI_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void DriverSPI_ScbEnableIntr(void);
static void DriverSPI_ScbModeStop(void);
static void DriverSPI_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: DriverSPI_Init
****************************************************************************//**
*
*  Initializes the DriverSPI component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  DriverSPI_I2CInit, DriverSPI_SpiInit, 
*  DriverSPI_UartInit or DriverSPI_EzI2CInit.
*
*******************************************************************************/
void DriverSPI_Init(void)
{
#if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DriverSPI_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DriverSPI_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (DriverSPI_SCB_MODE_I2C_CONST_CFG)
    DriverSPI_I2CInit();

#elif (DriverSPI_SCB_MODE_SPI_CONST_CFG)
    DriverSPI_SpiInit();

#elif (DriverSPI_SCB_MODE_UART_CONST_CFG)
    DriverSPI_UartInit();

#elif (DriverSPI_SCB_MODE_EZI2C_CONST_CFG)
    DriverSPI_EzI2CInit();

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DriverSPI_Enable
****************************************************************************//**
*
*  Enables DriverSPI component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  DriverSPI_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The DriverSPI configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured DriverSPI”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void DriverSPI_Enable(void)
{
#if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!DriverSPI_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DriverSPI_CTRL_REG |= DriverSPI_CTRL_ENABLED;

        DriverSPI_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        DriverSPI_ScbModePostEnable();
    }
#else
    DriverSPI_CTRL_REG |= DriverSPI_CTRL_ENABLED;

    DriverSPI_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    DriverSPI_ScbModePostEnable();
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DriverSPI_Start
****************************************************************************//**
*
*  Invokes DriverSPI_Init() and DriverSPI_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  DriverSPI_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void DriverSPI_Start(void)
{
    if (0u == DriverSPI_initVar)
    {
        DriverSPI_Init();
        DriverSPI_initVar = 1u; /* Component was initialized */
    }

    DriverSPI_Enable();
}


/*******************************************************************************
* Function Name: DriverSPI_Stop
****************************************************************************//**
*
*  Disables the DriverSPI component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function DriverSPI_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void DriverSPI_Stop(void)
{
#if (DriverSPI_SCB_IRQ_INTERNAL)
    DriverSPI_DisableInt();
#endif /* (DriverSPI_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    DriverSPI_ScbModeStop();

    /* Disable SCB IP */
    DriverSPI_CTRL_REG &= (uint32) ~DriverSPI_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    DriverSPI_SetTxInterruptMode(DriverSPI_NO_INTR_SOURCES);

#if (DriverSPI_SCB_IRQ_INTERNAL)
    DriverSPI_ClearPendingInt();
#endif /* (DriverSPI_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DriverSPI_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void DriverSPI_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = DriverSPI_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~DriverSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (DriverSPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DriverSPI_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: DriverSPI_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void DriverSPI_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = DriverSPI_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~DriverSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (DriverSPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DriverSPI_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (DriverSPI_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: DriverSPI_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void DriverSPI_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_DriverSPI_CUSTOM_INTR_HANDLER)
        DriverSPI_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_DriverSPI_CUSTOM_INTR_HANDLER) */
    }
#endif /* (DriverSPI_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: DriverSPI_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void DriverSPI_ScbEnableIntr(void)
{
#if (DriverSPI_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != DriverSPI_scbEnableIntr)
        {
            DriverSPI_EnableInt();
        }

    #else
        DriverSPI_EnableInt();

    #endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (DriverSPI_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DriverSPI_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void DriverSPI_ScbModePostEnable(void)
{
#if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!DriverSPI_CY_SCBIP_V1)
    if (DriverSPI_SCB_MODE_SPI_RUNTM_CFG)
    {
        DriverSPI_SpiPostEnable();
    }
    else if (DriverSPI_SCB_MODE_UART_RUNTM_CFG)
    {
        DriverSPI_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!DriverSPI_CY_SCBIP_V1) */

#elif (DriverSPI_SCB_MODE_SPI_CONST_CFG)
    DriverSPI_SpiPostEnable();

#elif (DriverSPI_SCB_MODE_UART_CONST_CFG)
    DriverSPI_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DriverSPI_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void DriverSPI_ScbModeStop(void)
{
#if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DriverSPI_SCB_MODE_I2C_RUNTM_CFG)
    {
        DriverSPI_I2CStop();
    }
    else if (DriverSPI_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DriverSPI_EzI2CStop();
    }
#if (!DriverSPI_CY_SCBIP_V1)
    else if (DriverSPI_SCB_MODE_SPI_RUNTM_CFG)
    {
        DriverSPI_SpiStop();
    }
    else if (DriverSPI_SCB_MODE_UART_RUNTM_CFG)
    {
        DriverSPI_UartStop();
    }
#endif /* (!DriverSPI_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (DriverSPI_SCB_MODE_I2C_CONST_CFG)
    DriverSPI_I2CStop();

#elif (DriverSPI_SCB_MODE_EZI2C_CONST_CFG)
    DriverSPI_EzI2CStop();

#elif (DriverSPI_SCB_MODE_SPI_CONST_CFG)
    DriverSPI_SpiStop();

#elif (DriverSPI_SCB_MODE_UART_CONST_CFG)
    DriverSPI_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: DriverSPI_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void DriverSPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[DriverSPI_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!DriverSPI_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!DriverSPI_CY_SCBIP_V1) */
        
        uint32 hsiomSel[DriverSPI_SCB_PINS_NUMBER] = 
        {
            DriverSPI_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            DriverSPI_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (DriverSPI_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (DriverSPI_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < DriverSPI_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = DriverSPI_PIN_DM_ALG_HIZ;
        }

        if ((DriverSPI_SCB_MODE_I2C   == mode) ||
            (DriverSPI_SCB_MODE_EZI2C == mode))
        {
        #if (DriverSPI_RX_SCL_MOSI_PIN)
            hsiomSel[DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_PIN_DM_OD_LO;
        #elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX] = DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX] = DriverSPI_PIN_DM_OD_LO;
        #else
        #endif /* (DriverSPI_RX_SCL_MOSI_PIN) */
        
        #if (DriverSPI_TX_SDA_MISO_PIN)
            hsiomSel[DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_PIN_DM_OD_LO;
        #endif /* (DriverSPI_TX_SDA_MISO_PIN) */
        }
    #if (!DriverSPI_CY_SCBIP_V1)
        else if (DriverSPI_SCB_MODE_SPI == mode)
        {
        #if (DriverSPI_RX_SCL_MOSI_PIN)
            hsiomSel[DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX] = DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (DriverSPI_RX_SCL_MOSI_PIN) */
        
        #if (DriverSPI_TX_SDA_MISO_PIN)
            hsiomSel[DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (DriverSPI_TX_SDA_MISO_PIN) */
        
        #if (DriverSPI_CTS_SCLK_PIN)
            hsiomSel[DriverSPI_CTS_SCLK_PIN_INDEX] = DriverSPI_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (DriverSPI_CTS_SCLK_PIN) */

            if (DriverSPI_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;
                pinsDm[DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                pinsDm[DriverSPI_CTS_SCLK_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;

            #if (DriverSPI_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[DriverSPI_RTS_SS0_PIN_INDEX] = DriverSPI_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [DriverSPI_RTS_SS0_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;
            #endif /* (DriverSPI_RTS_SS0_PIN) */

            #if (DriverSPI_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= DriverSPI_TX_SDA_MISO_PIN_MASK;
            #endif /* (DriverSPI_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                pinsDm[DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;
                pinsDm[DriverSPI_CTS_SCLK_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;

            #if (DriverSPI_RTS_SS0_PIN)
                hsiomSel [DriverSPI_RTS_SS0_PIN_INDEX] = DriverSPI_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [DriverSPI_RTS_SS0_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                pinsInBuf |= DriverSPI_RTS_SS0_PIN_MASK;
            #endif /* (DriverSPI_RTS_SS0_PIN) */

            #if (DriverSPI_SS1_PIN)
                hsiomSel [DriverSPI_SS1_PIN_INDEX] = DriverSPI_SS1_HSIOM_SEL_SPI;
                pinsDm   [DriverSPI_SS1_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                pinsInBuf |= DriverSPI_SS1_PIN_MASK;
            #endif /* (DriverSPI_SS1_PIN) */

            #if (DriverSPI_SS2_PIN)
                hsiomSel [DriverSPI_SS2_PIN_INDEX] = DriverSPI_SS2_HSIOM_SEL_SPI;
                pinsDm   [DriverSPI_SS2_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                pinsInBuf |= DriverSPI_SS2_PIN_MASK;
            #endif /* (DriverSPI_SS2_PIN) */

            #if (DriverSPI_SS3_PIN)
                hsiomSel [DriverSPI_SS3_PIN_INDEX] = DriverSPI_SS3_HSIOM_SEL_SPI;
                pinsDm   [DriverSPI_SS3_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                pinsInBuf |= DriverSPI_SS3_PIN_MASK;
            #endif /* (DriverSPI_SS3_PIN) */

                /* Disable input buffers */
            #if (DriverSPI_RX_SCL_MOSI_PIN)
                pinsInBuf |= DriverSPI_RX_SCL_MOSI_PIN_MASK;
            #elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= DriverSPI_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (DriverSPI_RX_SCL_MOSI_PIN) */

            #if (DriverSPI_CTS_SCLK_PIN)
                pinsInBuf |= DriverSPI_CTS_SCLK_PIN_MASK;
            #endif /* (DriverSPI_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (DriverSPI_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (DriverSPI_TX_SDA_MISO_PIN)
                hsiomSel[DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_PIN_DM_OD_LO;
            #endif /* (DriverSPI_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (DriverSPI_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (DriverSPI_RX_SCL_MOSI_PIN)
                    hsiomSel[DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DriverSPI_RX_SCL_MOSI_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;
                #elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX] = DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;
                #else
                #endif /* (DriverSPI_RX_SCL_MOSI_PIN) */
                }

                if (0u != (DriverSPI_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (DriverSPI_TX_SDA_MISO_PIN)
                    hsiomSel[DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [DriverSPI_TX_SDA_MISO_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= DriverSPI_TX_SDA_MISO_PIN_MASK;
                #endif /* (DriverSPI_TX_SDA_MISO_PIN) */
                }

            #if !(DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1)
                if (DriverSPI_UART_MODE_STD == subMode)
                {
                    if (0u != (DriverSPI_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (DriverSPI_CTS_SCLK_PIN)
                        hsiomSel[DriverSPI_CTS_SCLK_PIN_INDEX] = DriverSPI_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [DriverSPI_CTS_SCLK_PIN_INDEX] = DriverSPI_PIN_DM_DIG_HIZ;
                    #endif /* (DriverSPI_CTS_SCLK_PIN) */
                    }

                    if (0u != (DriverSPI_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (DriverSPI_RTS_SS0_PIN)
                        hsiomSel[DriverSPI_RTS_SS0_PIN_INDEX] = DriverSPI_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [DriverSPI_RTS_SS0_PIN_INDEX] = DriverSPI_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= DriverSPI_RTS_SS0_PIN_MASK;
                    #endif /* (DriverSPI_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1) */
            }
        }
    #endif /* (!DriverSPI_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (DriverSPI_RX_SCL_MOSI_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_RX_SCL_MOSI_HSIOM_REG,
                                       DriverSPI_RX_SCL_MOSI_HSIOM_MASK,
                                       DriverSPI_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[DriverSPI_RX_SCL_MOSI_PIN_INDEX]);

        DriverSPI_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[DriverSPI_RX_SCL_MOSI_PIN_INDEX]);

        #if (!DriverSPI_CY_SCBIP_V1)
            DriverSPI_SET_INP_DIS(DriverSPI_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         DriverSPI_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & DriverSPI_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!DriverSPI_CY_SCBIP_V1) */
    
    #elif (DriverSPI_RX_WAKE_SCL_MOSI_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       DriverSPI_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DriverSPI_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[DriverSPI_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DriverSPI_SET_INP_DIS(DriverSPI_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     DriverSPI_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & DriverSPI_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        DriverSPI_SET_INCFG_TYPE(DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        DriverSPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        DriverSPI_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (DriverSPI_RX_WAKE_SCL_MOSI_PIN) */

    #if (DriverSPI_TX_SDA_MISO_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_TX_SDA_MISO_HSIOM_REG,
                                       DriverSPI_TX_SDA_MISO_HSIOM_MASK,
                                       DriverSPI_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[DriverSPI_TX_SDA_MISO_PIN_INDEX]);

        DriverSPI_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[DriverSPI_TX_SDA_MISO_PIN_INDEX]);

    #if (!DriverSPI_CY_SCBIP_V1)
        DriverSPI_SET_INP_DIS(DriverSPI_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     DriverSPI_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & DriverSPI_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!DriverSPI_CY_SCBIP_V1) */
    #endif /* (DriverSPI_RX_SCL_MOSI_PIN) */

    #if (DriverSPI_CTS_SCLK_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_CTS_SCLK_HSIOM_REG,
                                       DriverSPI_CTS_SCLK_HSIOM_MASK,
                                       DriverSPI_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[DriverSPI_CTS_SCLK_PIN_INDEX]);

        DriverSPI_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[DriverSPI_CTS_SCLK_PIN_INDEX]);

        DriverSPI_SET_INP_DIS(DriverSPI_uart_cts_spi_sclk_INP_DIS,
                                     DriverSPI_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & DriverSPI_CTS_SCLK_PIN_MASK)));
    #endif /* (DriverSPI_CTS_SCLK_PIN) */

    #if (DriverSPI_RTS_SS0_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_RTS_SS0_HSIOM_REG,
                                       DriverSPI_RTS_SS0_HSIOM_MASK,
                                       DriverSPI_RTS_SS0_HSIOM_POS,
                                       hsiomSel[DriverSPI_RTS_SS0_PIN_INDEX]);

        DriverSPI_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[DriverSPI_RTS_SS0_PIN_INDEX]);

        DriverSPI_SET_INP_DIS(DriverSPI_uart_rts_spi_ss0_INP_DIS,
                                     DriverSPI_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & DriverSPI_RTS_SS0_PIN_MASK)));
    #endif /* (DriverSPI_RTS_SS0_PIN) */

    #if (DriverSPI_SS1_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS1_HSIOM_REG,
                                       DriverSPI_SS1_HSIOM_MASK,
                                       DriverSPI_SS1_HSIOM_POS,
                                       hsiomSel[DriverSPI_SS1_PIN_INDEX]);

        DriverSPI_spi_ss1_SetDriveMode((uint8) pinsDm[DriverSPI_SS1_PIN_INDEX]);

        DriverSPI_SET_INP_DIS(DriverSPI_spi_ss1_INP_DIS,
                                     DriverSPI_spi_ss1_MASK,
                                     (0u != (pinsInBuf & DriverSPI_SS1_PIN_MASK)));
    #endif /* (DriverSPI_SS1_PIN) */

    #if (DriverSPI_SS2_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS2_HSIOM_REG,
                                       DriverSPI_SS2_HSIOM_MASK,
                                       DriverSPI_SS2_HSIOM_POS,
                                       hsiomSel[DriverSPI_SS2_PIN_INDEX]);

        DriverSPI_spi_ss2_SetDriveMode((uint8) pinsDm[DriverSPI_SS2_PIN_INDEX]);

        DriverSPI_SET_INP_DIS(DriverSPI_spi_ss2_INP_DIS,
                                     DriverSPI_spi_ss2_MASK,
                                     (0u != (pinsInBuf & DriverSPI_SS2_PIN_MASK)));
    #endif /* (DriverSPI_SS2_PIN) */

    #if (DriverSPI_SS3_PIN)
        DriverSPI_SET_HSIOM_SEL(DriverSPI_SS3_HSIOM_REG,
                                       DriverSPI_SS3_HSIOM_MASK,
                                       DriverSPI_SS3_HSIOM_POS,
                                       hsiomSel[DriverSPI_SS3_PIN_INDEX]);

        DriverSPI_spi_ss3_SetDriveMode((uint8) pinsDm[DriverSPI_SS3_PIN_INDEX]);

        DriverSPI_SET_INP_DIS(DriverSPI_spi_ss3_INP_DIS,
                                     DriverSPI_spi_ss3_MASK,
                                     (0u != (pinsInBuf & DriverSPI_SS3_PIN_MASK)));
    #endif /* (DriverSPI_SS3_PIN) */
    }

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: DriverSPI_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void DriverSPI_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (DriverSPI_CTRL_REG & DriverSPI_CTRL_EC_AM_MODE)) &&
            (0u == (DriverSPI_I2C_CTRL_REG & DriverSPI_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            DriverSPI_CTRL_REG &= ~DriverSPI_CTRL_EC_AM_MODE;
            DriverSPI_CTRL_REG |=  DriverSPI_CTRL_EC_AM_MODE;
        }

        DriverSPI_I2C_SLAVE_CMD_REG = DriverSPI_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (DriverSPI_CY_SCBIP_V0 || DriverSPI_CY_SCBIP_V1) */


/* [] END OF FILE */
