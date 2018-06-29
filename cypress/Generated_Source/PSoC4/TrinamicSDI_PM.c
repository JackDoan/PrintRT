/*******************************************************************************
* File Name: TrinamicSDI.c  
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
#include "TrinamicSDI.h"

static TrinamicSDI_BACKUP_STRUCT  TrinamicSDI_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: TrinamicSDI_Sleep
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
*  \snippet TrinamicSDI_SUT.c usage_TrinamicSDI_Sleep_Wakeup
*******************************************************************************/
void TrinamicSDI_Sleep(void)
{
    #if defined(TrinamicSDI__PC)
        TrinamicSDI_backup.pcState = TrinamicSDI_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            TrinamicSDI_backup.usbState = TrinamicSDI_CR1_REG;
            TrinamicSDI_USB_POWER_REG |= TrinamicSDI_USBIO_ENTER_SLEEP;
            TrinamicSDI_CR1_REG &= TrinamicSDI_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TrinamicSDI__SIO)
        TrinamicSDI_backup.sioState = TrinamicSDI_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        TrinamicSDI_SIO_REG &= (uint32)(~TrinamicSDI_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: TrinamicSDI_Wakeup
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
*  Refer to TrinamicSDI_Sleep() for an example usage.
*******************************************************************************/
void TrinamicSDI_Wakeup(void)
{
    #if defined(TrinamicSDI__PC)
        TrinamicSDI_PC = TrinamicSDI_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            TrinamicSDI_USB_POWER_REG &= TrinamicSDI_USBIO_EXIT_SLEEP_PH1;
            TrinamicSDI_CR1_REG = TrinamicSDI_backup.usbState;
            TrinamicSDI_USB_POWER_REG &= TrinamicSDI_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TrinamicSDI__SIO)
        TrinamicSDI_SIO_REG = TrinamicSDI_backup.sioState;
    #endif
}


/* [] END OF FILE */
