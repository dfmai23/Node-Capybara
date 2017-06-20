/*******************************************************************************
* File Name: CR4_PM.c
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

#include "CR4.h"

/* Check for removal by optimization */
#if !defined(CR4_Sync_ctrl_reg__REMOVED)

static CR4_BACKUP_STRUCT  CR4_backup = {0u};

    
/*******************************************************************************
* Function Name: CR4_SaveConfig
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
void CR4_SaveConfig(void) 
{
    CR4_backup.controlState = CR4_Control;
}


/*******************************************************************************
* Function Name: CR4_RestoreConfig
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
void CR4_RestoreConfig(void) 
{
     CR4_Control = CR4_backup.controlState;
}


/*******************************************************************************
* Function Name: CR4_Sleep
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
void CR4_Sleep(void) 
{
    CR4_SaveConfig();
}


/*******************************************************************************
* Function Name: CR4_Wakeup
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
void CR4_Wakeup(void)  
{
    CR4_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
