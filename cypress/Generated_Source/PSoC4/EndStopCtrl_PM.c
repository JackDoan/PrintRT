/*******************************************************************************
* File Name: EndStopCtrl_PM.c
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

#include "EndStopCtrl.h"

/* Check for removal by optimization */
#if !defined(EndStopCtrl_Sync_ctrl_reg__REMOVED)

static EndStopCtrl_BACKUP_STRUCT  EndStopCtrl_backup = {0u};

    
/*******************************************************************************
* Function Name: EndStopCtrl_SaveConfig
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
void EndStopCtrl_SaveConfig(void) 
{
    EndStopCtrl_backup.controlState = EndStopCtrl_Control;
}


/*******************************************************************************
* Function Name: EndStopCtrl_RestoreConfig
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
void EndStopCtrl_RestoreConfig(void) 
{
     EndStopCtrl_Control = EndStopCtrl_backup.controlState;
}


/*******************************************************************************
* Function Name: EndStopCtrl_Sleep
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
void EndStopCtrl_Sleep(void) 
{
    EndStopCtrl_SaveConfig();
}


/*******************************************************************************
* Function Name: EndStopCtrl_Wakeup
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
void EndStopCtrl_Wakeup(void)  
{
    EndStopCtrl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
