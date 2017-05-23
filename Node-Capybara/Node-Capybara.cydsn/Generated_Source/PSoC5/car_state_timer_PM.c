/*******************************************************************************
* File Name: car_state_timer_PM.c
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

#include "car_state_timer.h"

static car_state_timer_backupStruct car_state_timer_backup;


/*******************************************************************************
* Function Name: car_state_timer_SaveConfig
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
*  car_state_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void car_state_timer_SaveConfig(void) 
{
    #if (!car_state_timer_UsingFixedFunction)
        car_state_timer_backup.TimerUdb = car_state_timer_ReadCounter();
        car_state_timer_backup.InterruptMaskValue = car_state_timer_STATUS_MASK;
        #if (car_state_timer_UsingHWCaptureCounter)
            car_state_timer_backup.TimerCaptureCounter = car_state_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!car_state_timer_UDB_CONTROL_REG_REMOVED)
            car_state_timer_backup.TimerControlRegister = car_state_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: car_state_timer_RestoreConfig
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
*  car_state_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void car_state_timer_RestoreConfig(void) 
{   
    #if (!car_state_timer_UsingFixedFunction)

        car_state_timer_WriteCounter(car_state_timer_backup.TimerUdb);
        car_state_timer_STATUS_MASK =car_state_timer_backup.InterruptMaskValue;
        #if (car_state_timer_UsingHWCaptureCounter)
            car_state_timer_SetCaptureCount(car_state_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!car_state_timer_UDB_CONTROL_REG_REMOVED)
            car_state_timer_WriteControlRegister(car_state_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: car_state_timer_Sleep
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
*  car_state_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void car_state_timer_Sleep(void) 
{
    #if(!car_state_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(car_state_timer_CTRL_ENABLE == (car_state_timer_CONTROL & car_state_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            car_state_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            car_state_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    car_state_timer_Stop();
    car_state_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: car_state_timer_Wakeup
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
*  car_state_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void car_state_timer_Wakeup(void) 
{
    car_state_timer_RestoreConfig();
    #if(!car_state_timer_UDB_CONTROL_REG_REMOVED)
        if(car_state_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                car_state_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
