/*******************************************************************************
* File Name: TrinamicSDO.h  
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

#if !defined(CY_PINS_TrinamicSDO_H) /* Pins TrinamicSDO_H */
#define CY_PINS_TrinamicSDO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TrinamicSDO_aliases.h"


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
} TrinamicSDO_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TrinamicSDO_Read(void);
void    TrinamicSDO_Write(uint8 value);
uint8   TrinamicSDO_ReadDataReg(void);
#if defined(TrinamicSDO__PC) || (CY_PSOC4_4200L) 
    void    TrinamicSDO_SetDriveMode(uint8 mode);
#endif
void    TrinamicSDO_SetInterruptMode(uint16 position, uint16 mode);
uint8   TrinamicSDO_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TrinamicSDO_Sleep(void); 
void TrinamicSDO_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TrinamicSDO__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TrinamicSDO_DRIVE_MODE_BITS        (3)
    #define TrinamicSDO_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TrinamicSDO_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TrinamicSDO_SetDriveMode() function.
         *  @{
         */
        #define TrinamicSDO_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TrinamicSDO_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TrinamicSDO_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TrinamicSDO_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TrinamicSDO_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TrinamicSDO_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TrinamicSDO_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TrinamicSDO_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TrinamicSDO_MASK               TrinamicSDO__MASK
#define TrinamicSDO_SHIFT              TrinamicSDO__SHIFT
#define TrinamicSDO_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TrinamicSDO_SetInterruptMode() function.
     *  @{
     */
        #define TrinamicSDO_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TrinamicSDO_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TrinamicSDO_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TrinamicSDO_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TrinamicSDO__SIO)
    #define TrinamicSDO_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TrinamicSDO__PC) && (CY_PSOC4_4200L)
    #define TrinamicSDO_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TrinamicSDO_USBIO_DISABLE              ((uint32)(~TrinamicSDO_USBIO_ENABLE))
    #define TrinamicSDO_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TrinamicSDO_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TrinamicSDO_USBIO_ENTER_SLEEP          ((uint32)((1u << TrinamicSDO_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TrinamicSDO_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicSDO_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TrinamicSDO_USBIO_SUSPEND_SHIFT)))
    #define TrinamicSDO_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TrinamicSDO_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicSDO_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TrinamicSDO__PC)
    /* Port Configuration */
    #define TrinamicSDO_PC                 (* (reg32 *) TrinamicSDO__PC)
#endif
/* Pin State */
#define TrinamicSDO_PS                     (* (reg32 *) TrinamicSDO__PS)
/* Data Register */
#define TrinamicSDO_DR                     (* (reg32 *) TrinamicSDO__DR)
/* Input Buffer Disable Override */
#define TrinamicSDO_INP_DIS                (* (reg32 *) TrinamicSDO__PC2)

/* Interrupt configuration Registers */
#define TrinamicSDO_INTCFG                 (* (reg32 *) TrinamicSDO__INTCFG)
#define TrinamicSDO_INTSTAT                (* (reg32 *) TrinamicSDO__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TrinamicSDO_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TrinamicSDO__SIO)
    #define TrinamicSDO_SIO_REG            (* (reg32 *) TrinamicSDO__SIO)
#endif /* (TrinamicSDO__SIO_CFG) */

/* USBIO registers */
#if !defined(TrinamicSDO__PC) && (CY_PSOC4_4200L)
    #define TrinamicSDO_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TrinamicSDO_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TrinamicSDO_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TrinamicSDO_DRIVE_MODE_SHIFT       (0x00u)
#define TrinamicSDO_DRIVE_MODE_MASK        (0x07u << TrinamicSDO_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TrinamicSDO_H */


/* [] END OF FILE */
