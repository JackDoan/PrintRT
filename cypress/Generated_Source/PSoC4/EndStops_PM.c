/*******************************************************************************
* File Name: EndStops.c  
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
#include "EndStops.h"

static EndStops_BACKUP_STRUCT  EndStops_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: EndStops_Sleep
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
*  \snippet EndStops_SUT.c usage_EndStops_Sleep_Wakeup
*******************************************************************************/
void EndStops_Sleep(void)
{
    #if defined(EndStops__PC)
        EndStops_backup.pcState = EndStops_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            EndStops_backup.usbState = EndStops_CR1_REG;
            EndStops_USB_POWER_REG |= EndStops_USBIO_ENTER_SLEEP;
            EndStops_CR1_REG &= EndStops_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(EndStops__SIO)
        EndStops_backup.sioState = EndStops_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        EndStops_SIO_REG &= (uint32)(~EndStops_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: EndStops_Wakeup
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
*  Refer to EndStops_Sleep() for an example usage.
*******************************************************************************/
void EndStops_Wakeup(void)
{
    #if defined(EndStops__PC)
        EndStops_PC = EndStops_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            EndStops_USB_POWER_REG &= EndStops_USBIO_EXIT_SLEEP_PH1;
            EndStops_CR1_REG = EndStops_backup.usbState;
            EndStops_USB_POWER_REG &= EndStops_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(EndStops__SIO)
        EndStops_SIO_REG = EndStops_backup.sioState;
    #endif
}


/* [] END OF FILE */
