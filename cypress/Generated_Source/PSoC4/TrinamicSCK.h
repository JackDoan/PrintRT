/*******************************************************************************
* File Name: TrinamicSCK.h  
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

#if !defined(CY_PINS_TrinamicSCK_H) /* Pins TrinamicSCK_H */
#define CY_PINS_TrinamicSCK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TrinamicSCK_aliases.h"


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
} TrinamicSCK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TrinamicSCK_Read(void);
void    TrinamicSCK_Write(uint8 value);
uint8   TrinamicSCK_ReadDataReg(void);
#if defined(TrinamicSCK__PC) || (CY_PSOC4_4200L) 
    void    TrinamicSCK_SetDriveMode(uint8 mode);
#endif
void    TrinamicSCK_SetInterruptMode(uint16 position, uint16 mode);
uint8   TrinamicSCK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TrinamicSCK_Sleep(void); 
void TrinamicSCK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TrinamicSCK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TrinamicSCK_DRIVE_MODE_BITS        (3)
    #define TrinamicSCK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TrinamicSCK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TrinamicSCK_SetDriveMode() function.
         *  @{
         */
        #define TrinamicSCK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TrinamicSCK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TrinamicSCK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TrinamicSCK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TrinamicSCK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TrinamicSCK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TrinamicSCK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TrinamicSCK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TrinamicSCK_MASK               TrinamicSCK__MASK
#define TrinamicSCK_SHIFT              TrinamicSCK__SHIFT
#define TrinamicSCK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TrinamicSCK_SetInterruptMode() function.
     *  @{
     */
        #define TrinamicSCK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TrinamicSCK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TrinamicSCK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TrinamicSCK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TrinamicSCK__SIO)
    #define TrinamicSCK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TrinamicSCK__PC) && (CY_PSOC4_4200L)
    #define TrinamicSCK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TrinamicSCK_USBIO_DISABLE              ((uint32)(~TrinamicSCK_USBIO_ENABLE))
    #define TrinamicSCK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TrinamicSCK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TrinamicSCK_USBIO_ENTER_SLEEP          ((uint32)((1u << TrinamicSCK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TrinamicSCK_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicSCK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TrinamicSCK_USBIO_SUSPEND_SHIFT)))
    #define TrinamicSCK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TrinamicSCK_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicSCK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TrinamicSCK__PC)
    /* Port Configuration */
    #define TrinamicSCK_PC                 (* (reg32 *) TrinamicSCK__PC)
#endif
/* Pin State */
#define TrinamicSCK_PS                     (* (reg32 *) TrinamicSCK__PS)
/* Data Register */
#define TrinamicSCK_DR                     (* (reg32 *) TrinamicSCK__DR)
/* Input Buffer Disable Override */
#define TrinamicSCK_INP_DIS                (* (reg32 *) TrinamicSCK__PC2)

/* Interrupt configuration Registers */
#define TrinamicSCK_INTCFG                 (* (reg32 *) TrinamicSCK__INTCFG)
#define TrinamicSCK_INTSTAT                (* (reg32 *) TrinamicSCK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TrinamicSCK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TrinamicSCK__SIO)
    #define TrinamicSCK_SIO_REG            (* (reg32 *) TrinamicSCK__SIO)
#endif /* (TrinamicSCK__SIO_CFG) */

/* USBIO registers */
#if !defined(TrinamicSCK__PC) && (CY_PSOC4_4200L)
    #define TrinamicSCK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TrinamicSCK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TrinamicSCK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TrinamicSCK_DRIVE_MODE_SHIFT       (0x00u)
#define TrinamicSCK_DRIVE_MODE_MASK        (0x07u << TrinamicSCK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TrinamicSCK_H */


/* [] END OF FILE */
