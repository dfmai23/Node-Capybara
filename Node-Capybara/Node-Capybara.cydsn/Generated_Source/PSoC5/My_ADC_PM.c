/*******************************************************************************
* File Name: My_ADC_PM.c
* Version 3.20
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "My_ADC.h"

static My_ADC_BACKUP_STRUCT My_ADC_backup =
{
    My_ADC_DISABLED,
    My_ADC_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: My_ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  My_ADC_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void My_ADC_SaveConfig(void) 
{
    My_ADC_backup.deccr = My_ADC_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: My_ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  My_ADC_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void My_ADC_RestoreConfig(void) 
{
    My_ADC_DEC_CR_REG = My_ADC_backup.deccr;
}


/*******************************************************************************
* Function Name: My_ADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  My_ADC_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void My_ADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((My_ADC_ACT_PWR_DEC_EN == (My_ADC_PWRMGR_DEC_REG & My_ADC_ACT_PWR_DEC_EN)) &&
       (My_ADC_ACT_PWR_DSM_EN == (My_ADC_PWRMGR_DSM_REG & My_ADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        My_ADC_backup.enableState = My_ADC_ENABLED;
        if((My_ADC_DEC_CR_REG & My_ADC_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            My_ADC_backup.enableState |= My_ADC_STARTED;
        }
		
        /* Stop the configuration */
        My_ADC_Stop();
    }
    else
    {
        /* Component is disabled */
        My_ADC_backup.enableState = My_ADC_DISABLED;
    }

    /* Save the user configuration */
    My_ADC_SaveConfig();
}


/*******************************************************************************
* Function Name: My_ADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  My_ADC_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void My_ADC_Wakeup(void) 
{
    /* Restore the configuration */
    My_ADC_RestoreConfig();

    /* Enables the component operation */
    if(My_ADC_backup.enableState != My_ADC_DISABLED)
    {
        My_ADC_Enable();
        if((My_ADC_backup.enableState & My_ADC_STARTED) != 0u)
        {
            My_ADC_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
