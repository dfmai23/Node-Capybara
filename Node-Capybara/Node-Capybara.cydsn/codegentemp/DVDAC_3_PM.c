/*******************************************************************************
* File Name: DVDAC_3_PM.c
* Version 2.10
*
* Description:
*  This file provides the power management source code to the API for the
*  DVDAC component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DVDAC_3.h"
#include "DVDAC_3_VDAC8.h"

static DVDAC_3_BACKUP_STRUCT  DVDAC_3_backup;


/*******************************************************************************
* Function Name: DVDAC_3_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The
*  DVDAC_3_Sleep() API saves the current component state. Then it
*  calls the DVDAC_3_Stop() function and calls
*  DVDAC_3_SaveConfig() to save the hardware configuration. Call the
*  DVDAC_3_Sleep() function before calling the CyPmSleep() or the
*  CyPmHibernate() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void DVDAC_3_Sleep(void) 
{
    /* Save VDAC8's enable state */
    if(0u != (DVDAC_3_VDAC8_PWRMGR & DVDAC_3_VDAC8_ACT_PWR_EN))
    {
        DVDAC_3_backup.enableState = 1u;
    }
    else
    {
        DVDAC_3_backup.enableState = 0u;
    }

    DVDAC_3_Stop();
    DVDAC_3_SaveConfig();
}


/*******************************************************************************
* Function Name: DVDAC_3_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  DVDAC_3_Sleep() was called. The DVDAC_3_Wakeup() function
*  calls the DVDAC_3_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  DVDAC_3_Sleep() function was called, the DVDAC_Wakeup() function
*  will also re-enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void DVDAC_3_Wakeup(void) 
{
    DVDAC_3_RestoreConfig();

    if(DVDAC_3_backup.enableState == 1u)
    {
        DVDAC_3_Enable();
    }
}


/*******************************************************************************
* Function Name: DVDAC_3_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the DVDAC_3_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void DVDAC_3_SaveConfig(void) 
{
    DVDAC_3_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: DVDAC_3_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the DVDAC_3_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void DVDAC_3_RestoreConfig(void) 
{
    DVDAC_3_VDAC8_RestoreConfig();
}


/* [] END OF FILE */
