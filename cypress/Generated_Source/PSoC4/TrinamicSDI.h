/*******************************************************************************
* File Name: TrinamicSDI.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TrinamicSDI_H) /* Pins TrinamicSDI_H */
#define CY_PINS_TrinamicSDI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TrinamicSDI_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} TrinamicSDI_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TrinamicSDI_Read(void);
void    TrinamicSDI_Write(uint8 value);
uint8   TrinamicSDI_ReadDataReg(void);
#if defined(TrinamicSDI__PC) || (CY_PSOC4_4200L) 
    void    TrinamicSDI_SetDriveMode(uint8 mode);
#endif
void    TrinamicSDI_SetInterruptMode(uint16 position, uint16 mode);
uint8   TrinamicSDI_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TrinamicSDI_Sleep(void); 
void TrinamicSDI_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TrinamicSDI__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TrinamicSDI_DRIVE_MODE_BITS        (3)
    #define TrinamicSDI_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TrinamicSDI_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TrinamicSDI_SetDriveMode() function.
         *  @{
         */
        #define TrinamicSDI_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TrinamicSDI_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TrinamicSDI_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TrinamicSDI_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TrinamicSDI_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TrinamicSDI_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TrinamicSDI_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TrinamicSDI_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TrinamicSDI_MASK               TrinamicSDI__MASK
#define TrinamicSDI_SHIFT              TrinamicSDI__SHIFT
#define TrinamicSDI_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TrinamicSDI_SetInterruptMode() function.
     *  @{
     */
        #define TrinamicSDI_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TrinamicSDI_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TrinamicSDI_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TrinamicSDI_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TrinamicSDI__SIO)
    #define TrinamicSDI_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TrinamicSDI__PC) && (CY_PSOC4_4200L)
    #define TrinamicSDI_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TrinamicSDI_USBIO_DISABLE              ((uint32)(~TrinamicSDI_USBIO_ENABLE))
    #define TrinamicSDI_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TrinamicSDI_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TrinamicSDI_USBIO_ENTER_SLEEP          ((uint32)((1u << TrinamicSDI_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TrinamicSDI_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicSDI_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TrinamicSDI_USBIO_SUSPEND_SHIFT)))
    #define TrinamicSDI_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TrinamicSDI_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicSDI_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TrinamicSDI__PC)
    /* Port Configuration */
    #define TrinamicSDI_PC                 (* (reg32 *) TrinamicSDI__PC)
#endif
/* Pin State */
#define TrinamicSDI_PS                     (* (reg32 *) TrinamicSDI__PS)
/* Data Register */
#define TrinamicSDI_DR                     (* (reg32 *) TrinamicSDI__DR)
/* Input Buffer Disable Override */
#define TrinamicSDI_INP_DIS                (* (reg32 *) TrinamicSDI__PC2)

/* Interrupt configuration Registers */
#define TrinamicSDI_INTCFG                 (* (reg32 *) TrinamicSDI__INTCFG)
#define TrinamicSDI_INTSTAT                (* (reg32 *) TrinamicSDI__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TrinamicSDI_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TrinamicSDI__SIO)
    #define TrinamicSDI_SIO_REG            (* (reg32 *) TrinamicSDI__SIO)
#endif /* (TrinamicSDI__SIO_CFG) */

/* USBIO registers */
#if !defined(TrinamicSDI__PC) && (CY_PSOC4_4200L)
    #define TrinamicSDI_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TrinamicSDI_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TrinamicSDI_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TrinamicSDI_DRIVE_MODE_SHIFT       (0x00u)
#define TrinamicSDI_DRIVE_MODE_MASK        (0x07u << TrinamicSDI_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TrinamicSDI_H */


/* [] END OF FILE */
