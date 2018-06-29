/*******************************************************************************
* File Name: TrinamicCLK.h  
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

#if !defined(CY_PINS_TrinamicCLK_H) /* Pins TrinamicCLK_H */
#define CY_PINS_TrinamicCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TrinamicCLK_aliases.h"


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
} TrinamicCLK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   TrinamicCLK_Read(void);
void    TrinamicCLK_Write(uint8 value);
uint8   TrinamicCLK_ReadDataReg(void);
#if defined(TrinamicCLK__PC) || (CY_PSOC4_4200L) 
    void    TrinamicCLK_SetDriveMode(uint8 mode);
#endif
void    TrinamicCLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   TrinamicCLK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void TrinamicCLK_Sleep(void); 
void TrinamicCLK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(TrinamicCLK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define TrinamicCLK_DRIVE_MODE_BITS        (3)
    #define TrinamicCLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TrinamicCLK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the TrinamicCLK_SetDriveMode() function.
         *  @{
         */
        #define TrinamicCLK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define TrinamicCLK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define TrinamicCLK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define TrinamicCLK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define TrinamicCLK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define TrinamicCLK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define TrinamicCLK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define TrinamicCLK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define TrinamicCLK_MASK               TrinamicCLK__MASK
#define TrinamicCLK_SHIFT              TrinamicCLK__SHIFT
#define TrinamicCLK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TrinamicCLK_SetInterruptMode() function.
     *  @{
     */
        #define TrinamicCLK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define TrinamicCLK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define TrinamicCLK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define TrinamicCLK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(TrinamicCLK__SIO)
    #define TrinamicCLK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(TrinamicCLK__PC) && (CY_PSOC4_4200L)
    #define TrinamicCLK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define TrinamicCLK_USBIO_DISABLE              ((uint32)(~TrinamicCLK_USBIO_ENABLE))
    #define TrinamicCLK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define TrinamicCLK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define TrinamicCLK_USBIO_ENTER_SLEEP          ((uint32)((1u << TrinamicCLK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << TrinamicCLK_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicCLK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << TrinamicCLK_USBIO_SUSPEND_SHIFT)))
    #define TrinamicCLK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << TrinamicCLK_USBIO_SUSPEND_DEL_SHIFT)))
    #define TrinamicCLK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(TrinamicCLK__PC)
    /* Port Configuration */
    #define TrinamicCLK_PC                 (* (reg32 *) TrinamicCLK__PC)
#endif
/* Pin State */
#define TrinamicCLK_PS                     (* (reg32 *) TrinamicCLK__PS)
/* Data Register */
#define TrinamicCLK_DR                     (* (reg32 *) TrinamicCLK__DR)
/* Input Buffer Disable Override */
#define TrinamicCLK_INP_DIS                (* (reg32 *) TrinamicCLK__PC2)

/* Interrupt configuration Registers */
#define TrinamicCLK_INTCFG                 (* (reg32 *) TrinamicCLK__INTCFG)
#define TrinamicCLK_INTSTAT                (* (reg32 *) TrinamicCLK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define TrinamicCLK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(TrinamicCLK__SIO)
    #define TrinamicCLK_SIO_REG            (* (reg32 *) TrinamicCLK__SIO)
#endif /* (TrinamicCLK__SIO_CFG) */

/* USBIO registers */
#if !defined(TrinamicCLK__PC) && (CY_PSOC4_4200L)
    #define TrinamicCLK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define TrinamicCLK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define TrinamicCLK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define TrinamicCLK_DRIVE_MODE_SHIFT       (0x00u)
#define TrinamicCLK_DRIVE_MODE_MASK        (0x07u << TrinamicCLK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins TrinamicCLK_H */


/* [] END OF FILE */
