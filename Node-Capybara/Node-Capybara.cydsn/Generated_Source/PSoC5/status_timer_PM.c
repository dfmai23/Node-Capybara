/*******************************************************************************
* File Name: status_timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "status_timer.h"

static status_timer_backupStruct status_timer_backup;


/*******************************************************************************
* Function Name: status_timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  status_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void status_timer_SaveConfig(void) 
{
    #if (!status_timer_UsingFixedFunction)
        status_timer_backup.TimerUdb = status_timer_ReadCounter();
        status_timer_backup.InterruptMaskValue = status_timer_STATUS_MASK;
        #if (status_timer_UsingHWCaptureCounter)
            status_timer_backup.TimerCaptureCounter = status_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!status_timer_UDB_CONTROL_REG_REMOVED)
            status_timer_backup.TimerControlRegister = status_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: status_timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  status_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void status_timer_RestoreConfig(void) 
{   
    #if (!status_timer_UsingFixedFunction)

        status_timer_WriteCounter(status_timer_backup.TimerUdb);
        status_timer_STATUS_MASK =status_timer_backup.InterruptMaskValue;
        #if (status_timer_UsingHWCaptureCounter)
            status_timer_SetCaptureCount(status_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!status_timer_UDB_CONTROL_REG_REMOVED)
            status_timer_WriteControlRegister(status_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: status_timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  status_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void status_timer_Sleep(void) 
{
    #if(!status_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(status_timer_CTRL_ENABLE == (status_timer_CONTROL & status_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            status_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            status_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    status_timer_Stop();
    status_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: status_timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  status_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void status_timer_Wakeup(void) 
{
    status_timer_RestoreConfig();
    #if(!status_timer_UDB_CONTROL_REG_REMOVED)
        if(status_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                status_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
