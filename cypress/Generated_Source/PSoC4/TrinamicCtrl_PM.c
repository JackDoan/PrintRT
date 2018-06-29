/*******************************************************************************
* File Name: TrinamicCtrl_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TrinamicCtrl.h"

/* Check for removal by optimization */
#if !defined(TrinamicCtrl_Sync_ctrl_reg__REMOVED)

static TrinamicCtrl_BACKUP_STRUCT  TrinamicCtrl_backup = {0u};

    
/*******************************************************************************
* Function Name: TrinamicCtrl_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TrinamicCtrl_SaveConfig(void) 
{
    TrinamicCtrl_backup.controlState = TrinamicCtrl_Control;
}


/*******************************************************************************
* Function Name: TrinamicCtrl_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void TrinamicCtrl_RestoreConfig(void) 
{
     TrinamicCtrl_Control = TrinamicCtrl_backup.controlState;
}


/*******************************************************************************
* Function Name: TrinamicCtrl_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TrinamicCtrl_Sleep(void) 
{
    TrinamicCtrl_SaveConfig();
}


/*******************************************************************************
* Function Name: TrinamicCtrl_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TrinamicCtrl_Wakeup(void)  
{
    TrinamicCtrl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
