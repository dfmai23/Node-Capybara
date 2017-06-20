/*******************************************************************************
* File Name: TestPWM.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TestPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef TestPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* TestPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 TestPWM_initVar = 0u;


/*******************************************************************************
* Function Name: TestPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TestPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void TestPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(TestPWM_initVar == 0u)
    {
        TestPWM_Init();
        TestPWM_initVar = 1u;
    }
    TestPWM_Enable();

}


/*******************************************************************************
* Function Name: TestPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  TestPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TestPWM_Init(void) 
{
    #if (TestPWM_UsingFixedFunction || TestPWM_UseControl)
        uint8 ctrl;
    #endif /* (TestPWM_UsingFixedFunction || TestPWM_UseControl) */

    #if(!TestPWM_UsingFixedFunction)
        #if(TestPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 TestPWM_interruptState;
        #endif /* (TestPWM_UseStatus) */
    #endif /* (!TestPWM_UsingFixedFunction) */

    #if (TestPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        TestPWM_CONTROL |= TestPWM_CFG0_MODE;
        #if (TestPWM_DeadBand2_4)
            TestPWM_CONTROL |= TestPWM_CFG0_DB;
        #endif /* (TestPWM_DeadBand2_4) */

        ctrl = TestPWM_CONTROL3 & ((uint8 )(~TestPWM_CTRL_CMPMODE1_MASK));
        TestPWM_CONTROL3 = ctrl | TestPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        TestPWM_RT1 &= ((uint8)(~TestPWM_RT1_MASK));
        TestPWM_RT1 |= TestPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        TestPWM_RT1 &= ((uint8)(~TestPWM_SYNCDSI_MASK));
        TestPWM_RT1 |= TestPWM_SYNCDSI_EN;

    #elif (TestPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = TestPWM_CONTROL & ((uint8)(~TestPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~TestPWM_CTRL_CMPMODE1_MASK));
        TestPWM_CONTROL = ctrl | TestPWM_DEFAULT_COMPARE2_MODE |
                                   TestPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (TestPWM_UsingFixedFunction) */

    #if (!TestPWM_UsingFixedFunction)
        #if (TestPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            TestPWM_AUX_CONTROLDP0 |= (TestPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (TestPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            TestPWM_AUX_CONTROLDP0 |= (TestPWM_AUX_CTRL_FIFO0_CLR);
            TestPWM_AUX_CONTROLDP1 |= (TestPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (TestPWM_Resolution == 8) */

        TestPWM_WriteCounter(TestPWM_INIT_PERIOD_VALUE);
    #endif /* (!TestPWM_UsingFixedFunction) */

    TestPWM_WritePeriod(TestPWM_INIT_PERIOD_VALUE);

        #if (TestPWM_UseOneCompareMode)
            TestPWM_WriteCompare(TestPWM_INIT_COMPARE_VALUE1);
        #else
            TestPWM_WriteCompare1(TestPWM_INIT_COMPARE_VALUE1);
            TestPWM_WriteCompare2(TestPWM_INIT_COMPARE_VALUE2);
        #endif /* (TestPWM_UseOneCompareMode) */

        #if (TestPWM_KillModeMinTime)
            TestPWM_WriteKillTime(TestPWM_MinimumKillTime);
        #endif /* (TestPWM_KillModeMinTime) */

        #if (TestPWM_DeadBandUsed)
            TestPWM_WriteDeadTime(TestPWM_INIT_DEAD_TIME);
        #endif /* (TestPWM_DeadBandUsed) */

    #if (TestPWM_UseStatus || TestPWM_UsingFixedFunction)
        TestPWM_SetInterruptMode(TestPWM_INIT_INTERRUPTS_MODE);
    #endif /* (TestPWM_UseStatus || TestPWM_UsingFixedFunction) */

    #if (TestPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        TestPWM_GLOBAL_ENABLE |= TestPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        TestPWM_CONTROL2 |= TestPWM_CTRL2_IRQ_SEL;
    #else
        #if(TestPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TestPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TestPWM_STATUS_AUX_CTRL |= TestPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(TestPWM_interruptState);

            /* Clear the FIFO to enable the TestPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            TestPWM_ClearFIFO();
        #endif /* (TestPWM_UseStatus) */
    #endif /* (TestPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TestPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void TestPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (TestPWM_UsingFixedFunction)
        TestPWM_GLOBAL_ENABLE |= TestPWM_BLOCK_EN_MASK;
        TestPWM_GLOBAL_STBY_ENABLE |= TestPWM_BLOCK_STBY_EN_MASK;
    #endif /* (TestPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (TestPWM_UseControl || TestPWM_UsingFixedFunction)
        TestPWM_CONTROL |= TestPWM_CTRL_ENABLE;
    #endif /* (TestPWM_UseControl || TestPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TestPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void TestPWM_Stop(void) 
{
    #if (TestPWM_UseControl || TestPWM_UsingFixedFunction)
        TestPWM_CONTROL &= ((uint8)(~TestPWM_CTRL_ENABLE));
    #endif /* (TestPWM_UseControl || TestPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (TestPWM_UsingFixedFunction)
        TestPWM_GLOBAL_ENABLE &= ((uint8)(~TestPWM_BLOCK_EN_MASK));
        TestPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~TestPWM_BLOCK_STBY_EN_MASK));
    #endif /* (TestPWM_UsingFixedFunction) */
}

#if (TestPWM_UseOneCompareMode)
    #if (TestPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: TestPWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void TestPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(TestPWM_UsingFixedFunction)

                #if(0 != TestPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << TestPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != TestPWM_CTRL_CMPMODE1_SHIFT) */

                TestPWM_CONTROL3 &= ((uint8)(~TestPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                TestPWM_CONTROL3 |= comparemodemasked;

            #elif (TestPWM_UseControl)

                #if(0 != TestPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << TestPWM_CTRL_CMPMODE1_SHIFT)) &
                                                TestPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & TestPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != TestPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != TestPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << TestPWM_CTRL_CMPMODE2_SHIFT)) &
                                               TestPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & TestPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != TestPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                TestPWM_CONTROL &= ((uint8)(~(TestPWM_CTRL_CMPMODE1_MASK |
                                            TestPWM_CTRL_CMPMODE2_MASK)));
                TestPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (TestPWM_UsingFixedFunction) */
        }
    #endif /* TestPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (TestPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: TestPWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void TestPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != TestPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << TestPWM_CTRL_CMPMODE1_SHIFT)) &
                                           TestPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & TestPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != TestPWM_CTRL_CMPMODE1_SHIFT) */

            #if (TestPWM_UseControl)
                TestPWM_CONTROL &= ((uint8)(~TestPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                TestPWM_CONTROL |= comparemodemasked;
            #endif /* (TestPWM_UseControl) */
        }
    #endif /* TestPWM_CompareMode1SW */

#if (TestPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: TestPWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != TestPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << TestPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 TestPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & TestPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != TestPWM_CTRL_CMPMODE2_SHIFT) */

        #if (TestPWM_UseControl)
            TestPWM_CONTROL &= ((uint8)(~TestPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            TestPWM_CONTROL |= comparemodemasked;
        #endif /* (TestPWM_UseControl) */
    }
    #endif /*TestPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!TestPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: TestPWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void TestPWM_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(TestPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: TestPWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 TestPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(TestPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(TestPWM_CAPTURE_LSB_PTR));
    }

    #if (TestPWM_UseStatus)


        /*******************************************************************************
        * Function Name: TestPWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void TestPWM_ClearFIFO(void) 
        {
            while(0u != (TestPWM_ReadStatusRegister() & TestPWM_STATUS_FIFONEMPTY))
            {
                (void)TestPWM_ReadCapture();
            }
        }

    #endif /* TestPWM_UseStatus */

#endif /* !TestPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: TestPWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void TestPWM_WritePeriod(uint16 period) 
{
    #if(TestPWM_UsingFixedFunction)
        CY_SET_REG16(TestPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(TestPWM_PERIOD_LSB_PTR, period);
    #endif /* (TestPWM_UsingFixedFunction) */
}

#if (TestPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: TestPWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void TestPWM_WriteCompare(uint16 compare) \
                                       
    {
        #if(TestPWM_UsingFixedFunction)
            CY_SET_REG16(TestPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(TestPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (TestPWM_UsingFixedFunction) */

        #if (TestPWM_PWMMode == TestPWM__B_PWM__DITHER)
            #if(TestPWM_UsingFixedFunction)
                CY_SET_REG16(TestPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(TestPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (TestPWM_UsingFixedFunction) */
        #endif /* (TestPWM_PWMMode == TestPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: TestPWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_WriteCompare1(uint16 compare) \
                                        
    {
        #if(TestPWM_UsingFixedFunction)
            CY_SET_REG16(TestPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(TestPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (TestPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: TestPWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_WriteCompare2(uint16 compare) \
                                        
    {
        #if(TestPWM_UsingFixedFunction)
            CY_SET_REG16(TestPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(TestPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (TestPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (TestPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: TestPWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!TestPWM_DeadBand2_4)
            CY_SET_REG8(TestPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            TestPWM_DEADBAND_COUNT &= ((uint8)(~TestPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(TestPWM_DEADBAND_COUNT_SHIFT)
                TestPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << TestPWM_DEADBAND_COUNT_SHIFT)) &
                                                    TestPWM_DEADBAND_COUNT_MASK;
            #else
                TestPWM_DEADBAND_COUNT |= deadtime & TestPWM_DEADBAND_COUNT_MASK;
            #endif /* (TestPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!TestPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: TestPWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 TestPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!TestPWM_DeadBand2_4)
            return (CY_GET_REG8(TestPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(TestPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(TestPWM_DEADBAND_COUNT & TestPWM_DEADBAND_COUNT_MASK)) >>
                                                                           TestPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (TestPWM_DEADBAND_COUNT & TestPWM_DEADBAND_COUNT_MASK);
            #endif /* (TestPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!TestPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (TestPWM_UseStatus || TestPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: TestPWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(TestPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: TestPWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 TestPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(TestPWM_STATUS_PTR));
    }

#endif /* (TestPWM_UseStatus || TestPWM_UsingFixedFunction) */


#if (TestPWM_UseControl)


    /*******************************************************************************
    * Function Name: TestPWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 TestPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(TestPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: TestPWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(TestPWM_CONTROL_PTR, control);
    }

#endif /* (TestPWM_UseControl) */


#if (!TestPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: TestPWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 TestPWM_ReadCapture(void) 
    {
        return (CY_GET_REG16(TestPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!TestPWM_UsingFixedFunction) */


#if (TestPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: TestPWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 TestPWM_ReadCompare(void) 
    {
        #if(TestPWM_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(TestPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(TestPWM_COMPARE1_LSB_PTR));
        #endif /* (TestPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: TestPWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 TestPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG16(TestPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: TestPWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 TestPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG16(TestPWM_COMPARE2_LSB_PTR));
    }

#endif /* (TestPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: TestPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 TestPWM_ReadPeriod(void) 
{
    #if(TestPWM_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(TestPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(TestPWM_PERIOD_LSB_PTR));
    #endif /* (TestPWM_UsingFixedFunction) */
}

#if ( TestPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: TestPWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TestPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(TestPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: TestPWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 TestPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(TestPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( TestPWM_KillModeMinTime) */

/* [] END OF FILE */
