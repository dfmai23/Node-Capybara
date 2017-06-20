/*******************************************************************************
* File Name: TestPWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TestPWM.h"

static TestPWM_backupStruct TestPWM_backup;


/*******************************************************************************
* Function Name: TestPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TestPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TestPWM_SaveConfig(void) 
{

    #if(!TestPWM_UsingFixedFunction)
        #if(!TestPWM_PWMModeIsCenterAligned)
            TestPWM_backup.PWMPeriod = TestPWM_ReadPeriod();
        #endif /* (!TestPWM_PWMModeIsCenterAligned) */
        TestPWM_backup.PWMUdb = TestPWM_ReadCounter();
        #if (TestPWM_UseStatus)
            TestPWM_backup.InterruptMaskValue = TestPWM_STATUS_MASK;
        #endif /* (TestPWM_UseStatus) */

        #if(TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_256_CLOCKS || \
            TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_2_4_CLOCKS)
            TestPWM_backup.PWMdeadBandValue = TestPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(TestPWM_KillModeMinTime)
             TestPWM_backup.PWMKillCounterPeriod = TestPWM_ReadKillTime();
        #endif /* (TestPWM_KillModeMinTime) */

        #if(TestPWM_UseControl)
            TestPWM_backup.PWMControlRegister = TestPWM_ReadControlRegister();
        #endif /* (TestPWM_UseControl) */
    #endif  /* (!TestPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TestPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TestPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TestPWM_RestoreConfig(void) 
{
        #if(!TestPWM_UsingFixedFunction)
            #if(!TestPWM_PWMModeIsCenterAligned)
                TestPWM_WritePeriod(TestPWM_backup.PWMPeriod);
            #endif /* (!TestPWM_PWMModeIsCenterAligned) */

            TestPWM_WriteCounter(TestPWM_backup.PWMUdb);

            #if (TestPWM_UseStatus)
                TestPWM_STATUS_MASK = TestPWM_backup.InterruptMaskValue;
            #endif /* (TestPWM_UseStatus) */

            #if(TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_256_CLOCKS || \
                TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_2_4_CLOCKS)
                TestPWM_WriteDeadTime(TestPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(TestPWM_KillModeMinTime)
                TestPWM_WriteKillTime(TestPWM_backup.PWMKillCounterPeriod);
            #endif /* (TestPWM_KillModeMinTime) */

            #if(TestPWM_UseControl)
                TestPWM_WriteControlRegister(TestPWM_backup.PWMControlRegister);
            #endif /* (TestPWM_UseControl) */
        #endif  /* (!TestPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: TestPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TestPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void TestPWM_Sleep(void) 
{
    #if(TestPWM_UseControl)
        if(TestPWM_CTRL_ENABLE == (TestPWM_CONTROL & TestPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            TestPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            TestPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (TestPWM_UseControl) */

    /* Stop component */
    TestPWM_Stop();

    /* Save registers configuration */
    TestPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: TestPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TestPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TestPWM_Wakeup(void) 
{
     /* Restore registers values */
    TestPWM_RestoreConfig();

    if(TestPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        TestPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
