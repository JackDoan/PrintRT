/***************************************************************************//**
* \file DriverSPI_SPI_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(DriverSPI_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 DriverSPI_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 DriverSPI_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  DriverSPI_rxBufferOverflow;
    /** \} globals */
#endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if(DriverSPI_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 DriverSPI_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 DriverSPI_txBufferTail;
#endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if(DriverSPI_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 DriverSPI_rxBufferInternal[DriverSPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER) */

#if(DriverSPI_INTERNAL_TX_SW_BUFFER)
    volatile uint8 DriverSPI_txBufferInternal[DriverSPI_TX_BUFFER_SIZE];
#endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER) */


#if(DriverSPI_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  DriverSPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  DriverSPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 DriverSPI_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (DriverSPI_CHECK_RX_SW_BUFFER)
        {
            if (DriverSPI_rxBufferHead != DriverSPI_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (DriverSPI_rxBufferTail + 1u);

                if (DriverSPI_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = DriverSPI_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                DriverSPI_rxBufferTail = locTail;

                #if (DriverSPI_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (DriverSPI_INTR_RX_MASK_REG & DriverSPI_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        DriverSPI_INTR_RX_MASK_REG |= DriverSPI_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = DriverSPI_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  DriverSPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  DriverSPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 DriverSPI_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (DriverSPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (DriverSPI_CHECK_RX_SW_BUFFER)
        {
            locHead = DriverSPI_rxBufferHead;

            if(locHead >= DriverSPI_rxBufferTail)
            {
                size = (locHead - DriverSPI_rxBufferTail);
            }
            else
            {
                size = (locHead + (DriverSPI_INTERNAL_RX_BUFFER_SIZE - DriverSPI_rxBufferTail));
            }
        }
        #else
        {
            size = DriverSPI_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  DriverSPI_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  DriverSPI_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void DriverSPI_SpiUartClearRxBuffer(void)
    {
        #if (DriverSPI_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            DriverSPI_DisableInt();

            /* Flush RX software buffer */
            DriverSPI_rxBufferHead = DriverSPI_rxBufferTail;
            DriverSPI_rxBufferOverflow = 0u;

            DriverSPI_CLEAR_RX_FIFO;
            DriverSPI_ClearRxInterruptSource(DriverSPI_INTR_RX_ALL);

            #if (DriverSPI_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                DriverSPI_INTR_RX_MASK_REG |= DriverSPI_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            DriverSPI_EnableInt();
        }
        #else
        {
            DriverSPI_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (DriverSPI_RX_DIRECTION) */


#if(DriverSPI_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  DriverSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  DriverSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void DriverSPI_SpiUartWriteTxData(uint32 txData)
    {
    #if (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (DriverSPI_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((DriverSPI_txBufferHead == DriverSPI_txBufferTail) &&
                (DriverSPI_SPI_UART_FIFO_SIZE != DriverSPI_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                DriverSPI_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (DriverSPI_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (DriverSPI_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == DriverSPI_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                DriverSPI_ClearTxInterruptSource(DriverSPI_INTR_TX_NOT_FULL);

                DriverSPI_PutWordInTxBuffer(locHead, txData);

                DriverSPI_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (DriverSPI_INTR_TX_MASK_REG & DriverSPI_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    DriverSPI_INTR_TX_MASK_REG |= (uint32) DriverSPI_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (DriverSPI_SPI_UART_FIFO_SIZE == DriverSPI_GET_TX_FIFO_ENTRIES)
            {
            }

            DriverSPI_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  DriverSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  DriverSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void DriverSPI_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            DriverSPI_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  DriverSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  DriverSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 DriverSPI_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (DriverSPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (DriverSPI_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = DriverSPI_txBufferTail;

            if (DriverSPI_txBufferHead >= locTail)
            {
                size = (DriverSPI_txBufferHead - locTail);
            }
            else
            {
                size = (DriverSPI_txBufferHead + (DriverSPI_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = DriverSPI_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: DriverSPI_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  DriverSPI_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  DriverSPI_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void DriverSPI_SpiUartClearTxBuffer(void)
    {
        #if (DriverSPI_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            DriverSPI_DisableInt();

            /* Flush TX software buffer */
            DriverSPI_txBufferHead = DriverSPI_txBufferTail;

            DriverSPI_INTR_TX_MASK_REG &= (uint32) ~DriverSPI_INTR_TX_NOT_FULL;
            DriverSPI_CLEAR_TX_FIFO;
            DriverSPI_ClearTxInterruptSource(DriverSPI_INTR_TX_ALL);

            /* Release lock */
            DriverSPI_EnableInt();
        }
        #else
        {
            DriverSPI_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (DriverSPI_TX_DIRECTION) */


/*******************************************************************************
* Function Name: DriverSPI_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 DriverSPI_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = DriverSPI_GetRxInterruptMode();

    DriverSPI_SetRxInterruptMode(DriverSPI_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: DriverSPI_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 DriverSPI_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = DriverSPI_GetTxInterruptMode();

    DriverSPI_SetTxInterruptMode(DriverSPI_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: DriverSPI_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void DriverSPI_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (DriverSPI_ONE_BYTE_WIDTH == DriverSPI_rxDataBits)
        {
            DriverSPI_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            DriverSPI_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            DriverSPI_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: DriverSPI_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 DriverSPI_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (DriverSPI_ONE_BYTE_WIDTH == DriverSPI_rxDataBits)
        {
            value = DriverSPI_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) DriverSPI_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)DriverSPI_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: DriverSPI_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void DriverSPI_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (DriverSPI_ONE_BYTE_WIDTH == DriverSPI_txDataBits)
        {
            DriverSPI_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            DriverSPI_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            DriverSPI_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: DriverSPI_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 DriverSPI_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (DriverSPI_ONE_BYTE_WIDTH == DriverSPI_txDataBits)
        {
            value = (uint32) DriverSPI_txBuffer[idx];
        }
        else
        {
            value  = (uint32) DriverSPI_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) DriverSPI_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (DriverSPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
