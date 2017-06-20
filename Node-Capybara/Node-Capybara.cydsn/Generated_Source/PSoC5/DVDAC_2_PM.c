/*******************************************************************************
* File Name: DVDAC_2_PM.c
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

#include "DVDAC_2.h"
#include "DVDAC_2_VDAC8.h"

static DVDAC_2_BACKUP_STRUCT  DVDAC_2_backup;


/*******************************************************************************
* Function Name: DVDAC_2_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The
*  DVDAC_2_Sleep() API saves the current component state. Then it
*  calls the DVDAC_2_Stop() function and calls
*  DVDAC_2_SaveConfig() to save the hardware configuration. Call the
*  DVDAC_2_Sleep() function before calling the CyPmSleep() or the
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
void DVDAC_2_Sleep(void) 
{
    /* Save VDAC8's enable state */
    if(0u != (DVDAC_2_VDAC8_PWRMGR & DVDAC_2_VDAC8_ACT_PWR_EN))
    {
        DVDAC_2_backup.enableState = 1u;
    }
    else
    {
        DVDAC_2_backup.enableState = 0u;
    }

    DVDAC_2_Stop();
    DVDAC_2_SaveConfig();
}


/*******************************************************************************
* Function Name: DVDAC_2_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  DVDAC_2_Sleep() was called. The DVDAC_2_Wakeup() function
*  calls the DVDAC_2_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  DVDAC_2_Sleep() function was called, the DVDAC_Wakeup() function
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
void DVDAC_2_Wakeup(void) 
{
    DVDAC_2_RestoreConfig();

    if(DVDAC_2_backup.enableState == 1u)
    {
        DVDAC_2_Enable();
    }
}


/*******************************************************************************
* Function Name: DVDAC_2_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the DVDAC_2_Sleep() function.
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
void DVDAC_2_SaveConfig(void) 
{
    DVDAC_2_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: DVDAC_2_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the DVDAC_2_Wakeup() function.
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
void DVDAC_2_RestoreConfig(void) 
{
    DVDAC_2_VDAC8_RestoreConfig();
}


/* [] END OF FILE */
