/*******************************************************************************
* File Name: DriverSPI_ss2_m.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "DriverSPI_ss2_m.h"

static DriverSPI_ss2_m_BACKUP_STRUCT  DriverSPI_ss2_m_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DriverSPI_ss2_m_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet DriverSPI_ss2_m_SUT.c usage_DriverSPI_ss2_m_Sleep_Wakeup
*******************************************************************************/
void DriverSPI_ss2_m_Sleep(void)
{
    #if defined(DriverSPI_ss2_m__PC)
        DriverSPI_ss2_m_backup.pcState = DriverSPI_ss2_m_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DriverSPI_ss2_m_backup.usbState = DriverSPI_ss2_m_CR1_REG;
            DriverSPI_ss2_m_USB_POWER_REG |= DriverSPI_ss2_m_USBIO_ENTER_SLEEP;
            DriverSPI_ss2_m_CR1_REG &= DriverSPI_ss2_m_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DriverSPI_ss2_m__SIO)
        DriverSPI_ss2_m_backup.sioState = DriverSPI_ss2_m_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DriverSPI_ss2_m_SIO_REG &= (uint32)(~DriverSPI_ss2_m_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DriverSPI_ss2_m_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to DriverSPI_ss2_m_Sleep() for an example usage.
*******************************************************************************/
void DriverSPI_ss2_m_Wakeup(void)
{
    #if defined(DriverSPI_ss2_m__PC)
        DriverSPI_ss2_m_PC = DriverSPI_ss2_m_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DriverSPI_ss2_m_USB_POWER_REG &= DriverSPI_ss2_m_USBIO_EXIT_SLEEP_PH1;
            DriverSPI_ss2_m_CR1_REG = DriverSPI_ss2_m_backup.usbState;
            DriverSPI_ss2_m_USB_POWER_REG &= DriverSPI_ss2_m_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DriverSPI_ss2_m__SIO)
        DriverSPI_ss2_m_SIO_REG = DriverSPI_ss2_m_backup.sioState;
    #endif
}


/* [] END OF FILE */