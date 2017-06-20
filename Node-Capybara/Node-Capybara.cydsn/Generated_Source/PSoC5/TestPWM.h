/*******************************************************************************
* File Name: TestPWM.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_TestPWM_H)
#define CY_PWM_TestPWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TestPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define TestPWM_Resolution                     (16u)
#define TestPWM_UsingFixedFunction             (0u)
#define TestPWM_DeadBandMode                   (0u)
#define TestPWM_KillModeMinTime                (0u)
#define TestPWM_KillMode                       (0u)
#define TestPWM_PWMMode                        (0u)
#define TestPWM_PWMModeIsCenterAligned         (0u)
#define TestPWM_DeadBandUsed                   (0u)
#define TestPWM_DeadBand2_4                    (0u)

#if !defined(TestPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define TestPWM_UseStatus                  (1u)
#else
    #define TestPWM_UseStatus                  (0u)
#endif /* !defined(TestPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(TestPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define TestPWM_UseControl                 (1u)
#else
    #define TestPWM_UseControl                 (0u)
#endif /* !defined(TestPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define TestPWM_UseOneCompareMode              (1u)
#define TestPWM_MinimumKillTime                (1u)
#define TestPWM_EnableMode                     (0u)

#define TestPWM_CompareMode1SW                 (0u)
#define TestPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define TestPWM__B_PWM__DISABLED 0
#define TestPWM__B_PWM__ASYNCHRONOUS 1
#define TestPWM__B_PWM__SINGLECYCLE 2
#define TestPWM__B_PWM__LATCHED 3
#define TestPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define TestPWM__B_PWM__DBMDISABLED 0
#define TestPWM__B_PWM__DBM_2_4_CLOCKS 1
#define TestPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define TestPWM__B_PWM__ONE_OUTPUT 0
#define TestPWM__B_PWM__TWO_OUTPUTS 1
#define TestPWM__B_PWM__DUAL_EDGE 2
#define TestPWM__B_PWM__CENTER_ALIGN 3
#define TestPWM__B_PWM__DITHER 5
#define TestPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define TestPWM__B_PWM__LESS_THAN 1
#define TestPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define TestPWM__B_PWM__GREATER_THAN 3
#define TestPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define TestPWM__B_PWM__EQUAL 0
#define TestPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!TestPWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!TestPWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!TestPWM_PWMModeIsCenterAligned) */
        #if (TestPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (TestPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_256_CLOCKS || \
            TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(TestPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (TestPWM_KillModeMinTime) */

        /* Backup control register */
        #if(TestPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (TestPWM_UseControl) */

    #endif /* (!TestPWM_UsingFixedFunction) */

}TestPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    TestPWM_Start(void) ;
void    TestPWM_Stop(void) ;

#if (TestPWM_UseStatus || TestPWM_UsingFixedFunction)
    void  TestPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 TestPWM_ReadStatusRegister(void) ;
#endif /* (TestPWM_UseStatus || TestPWM_UsingFixedFunction) */

#define TestPWM_GetInterruptSource() TestPWM_ReadStatusRegister()

#if (TestPWM_UseControl)
    uint8 TestPWM_ReadControlRegister(void) ;
    void  TestPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (TestPWM_UseControl) */

#if (TestPWM_UseOneCompareMode)
   #if (TestPWM_CompareMode1SW)
       void    TestPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (TestPWM_CompareMode1SW) */
#else
    #if (TestPWM_CompareMode1SW)
        void    TestPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (TestPWM_CompareMode1SW) */
    #if (TestPWM_CompareMode2SW)
        void    TestPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (TestPWM_CompareMode2SW) */
#endif /* (TestPWM_UseOneCompareMode) */

#if (!TestPWM_UsingFixedFunction)
    uint16   TestPWM_ReadCounter(void) ;
    uint16 TestPWM_ReadCapture(void) ;

    #if (TestPWM_UseStatus)
            void TestPWM_ClearFIFO(void) ;
    #endif /* (TestPWM_UseStatus) */

    void    TestPWM_WriteCounter(uint16 counter)
            ;
#endif /* (!TestPWM_UsingFixedFunction) */

void    TestPWM_WritePeriod(uint16 period)
        ;
uint16 TestPWM_ReadPeriod(void) ;

#if (TestPWM_UseOneCompareMode)
    void    TestPWM_WriteCompare(uint16 compare)
            ;
    uint16 TestPWM_ReadCompare(void) ;
#else
    void    TestPWM_WriteCompare1(uint16 compare)
            ;
    uint16 TestPWM_ReadCompare1(void) ;
    void    TestPWM_WriteCompare2(uint16 compare)
            ;
    uint16 TestPWM_ReadCompare2(void) ;
#endif /* (TestPWM_UseOneCompareMode) */


#if (TestPWM_DeadBandUsed)
    void    TestPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   TestPWM_ReadDeadTime(void) ;
#endif /* (TestPWM_DeadBandUsed) */

#if ( TestPWM_KillModeMinTime)
    void TestPWM_WriteKillTime(uint8 killtime) ;
    uint8 TestPWM_ReadKillTime(void) ;
#endif /* ( TestPWM_KillModeMinTime) */

void TestPWM_Init(void) ;
void TestPWM_Enable(void) ;
void TestPWM_Sleep(void) ;
void TestPWM_Wakeup(void) ;
void TestPWM_SaveConfig(void) ;
void TestPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define TestPWM_INIT_PERIOD_VALUE          (30000u)
#define TestPWM_INIT_COMPARE_VALUE1        (15000u)
#define TestPWM_INIT_COMPARE_VALUE2        (63u)
#define TestPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    TestPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    TestPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    TestPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    TestPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define TestPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  TestPWM_CTRL_CMPMODE2_SHIFT)
#define TestPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)2u <<  TestPWM_CTRL_CMPMODE1_SHIFT)
#define TestPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (TestPWM_UsingFixedFunction)
   #define TestPWM_PERIOD_LSB              (*(reg16 *) TestPWM_PWMHW__PER0)
   #define TestPWM_PERIOD_LSB_PTR          ( (reg16 *) TestPWM_PWMHW__PER0)
   #define TestPWM_COMPARE1_LSB            (*(reg16 *) TestPWM_PWMHW__CNT_CMP0)
   #define TestPWM_COMPARE1_LSB_PTR        ( (reg16 *) TestPWM_PWMHW__CNT_CMP0)
   #define TestPWM_COMPARE2_LSB            (0x00u)
   #define TestPWM_COMPARE2_LSB_PTR        (0x00u)
   #define TestPWM_COUNTER_LSB             (*(reg16 *) TestPWM_PWMHW__CNT_CMP0)
   #define TestPWM_COUNTER_LSB_PTR         ( (reg16 *) TestPWM_PWMHW__CNT_CMP0)
   #define TestPWM_CAPTURE_LSB             (*(reg16 *) TestPWM_PWMHW__CAP0)
   #define TestPWM_CAPTURE_LSB_PTR         ( (reg16 *) TestPWM_PWMHW__CAP0)
   #define TestPWM_RT1                     (*(reg8 *)  TestPWM_PWMHW__RT1)
   #define TestPWM_RT1_PTR                 ( (reg8 *)  TestPWM_PWMHW__RT1)

#else
   #if (TestPWM_Resolution == 8u) /* 8bit - PWM */

       #if(TestPWM_PWMModeIsCenterAligned)
           #define TestPWM_PERIOD_LSB      (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define TestPWM_PERIOD_LSB_PTR  ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define TestPWM_PERIOD_LSB      (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define TestPWM_PERIOD_LSB_PTR  ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (TestPWM_PWMModeIsCenterAligned) */

       #define TestPWM_COMPARE1_LSB        (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define TestPWM_COMPARE1_LSB_PTR    ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define TestPWM_COMPARE2_LSB        (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define TestPWM_COMPARE2_LSB_PTR    ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define TestPWM_COUNTERCAP_LSB      (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define TestPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define TestPWM_COUNTER_LSB         (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define TestPWM_COUNTER_LSB_PTR     ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define TestPWM_CAPTURE_LSB         (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define TestPWM_CAPTURE_LSB_PTR     ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(TestPWM_PWMModeIsCenterAligned)
               #define TestPWM_PERIOD_LSB      (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define TestPWM_PERIOD_LSB_PTR  ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define TestPWM_PERIOD_LSB      (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define TestPWM_PERIOD_LSB_PTR  ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (TestPWM_PWMModeIsCenterAligned) */

            #define TestPWM_COMPARE1_LSB       (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define TestPWM_COMPARE1_LSB_PTR   ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define TestPWM_COMPARE2_LSB       (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define TestPWM_COMPARE2_LSB_PTR   ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define TestPWM_COUNTERCAP_LSB     (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define TestPWM_COUNTERCAP_LSB_PTR ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define TestPWM_COUNTER_LSB        (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define TestPWM_COUNTER_LSB_PTR    ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define TestPWM_CAPTURE_LSB        (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define TestPWM_CAPTURE_LSB_PTR    ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(TestPWM_PWMModeIsCenterAligned)
               #define TestPWM_PERIOD_LSB      (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define TestPWM_PERIOD_LSB_PTR  ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define TestPWM_PERIOD_LSB      (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define TestPWM_PERIOD_LSB_PTR  ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (TestPWM_PWMModeIsCenterAligned) */

            #define TestPWM_COMPARE1_LSB       (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define TestPWM_COMPARE1_LSB_PTR   ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define TestPWM_COMPARE2_LSB       (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define TestPWM_COMPARE2_LSB_PTR   ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define TestPWM_COUNTERCAP_LSB     (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define TestPWM_COUNTERCAP_LSB_PTR ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define TestPWM_COUNTER_LSB        (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define TestPWM_COUNTER_LSB_PTR    ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define TestPWM_CAPTURE_LSB        (*(reg16 *) TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define TestPWM_CAPTURE_LSB_PTR    ((reg16 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define TestPWM_AUX_CONTROLDP1          (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define TestPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (TestPWM_Resolution == 8) */

   #define TestPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define TestPWM_AUX_CONTROLDP0          (*(reg8 *)  TestPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define TestPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   TestPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (TestPWM_UsingFixedFunction) */

#if(TestPWM_KillModeMinTime )
    #define TestPWM_KILLMODEMINTIME        (*(reg8 *)  TestPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define TestPWM_KILLMODEMINTIME_PTR    ((reg8 *)   TestPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (TestPWM_KillModeMinTime ) */

#if(TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_256_CLOCKS)
    #define TestPWM_DEADBAND_COUNT         (*(reg8 *)  TestPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define TestPWM_DEADBAND_COUNT_PTR     ((reg8 *)   TestPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define TestPWM_DEADBAND_LSB_PTR       ((reg8 *)   TestPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define TestPWM_DEADBAND_LSB           (*(reg8 *)  TestPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (TestPWM_UsingFixedFunction)
        #define TestPWM_DEADBAND_COUNT         (*(reg8 *)  TestPWM_PWMHW__CFG0)
        #define TestPWM_DEADBAND_COUNT_PTR     ((reg8 *)   TestPWM_PWMHW__CFG0)
        #define TestPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << TestPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define TestPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define TestPWM_DEADBAND_COUNT         (*(reg8 *)  TestPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define TestPWM_DEADBAND_COUNT_PTR     ((reg8 *)   TestPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define TestPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << TestPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define TestPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (TestPWM_UsingFixedFunction) */
#endif /* (TestPWM_DeadBandMode == TestPWM__B_PWM__DBM_256_CLOCKS) */



#if (TestPWM_UsingFixedFunction)
    #define TestPWM_STATUS                 (*(reg8 *) TestPWM_PWMHW__SR0)
    #define TestPWM_STATUS_PTR             ((reg8 *) TestPWM_PWMHW__SR0)
    #define TestPWM_STATUS_MASK            (*(reg8 *) TestPWM_PWMHW__SR0)
    #define TestPWM_STATUS_MASK_PTR        ((reg8 *) TestPWM_PWMHW__SR0)
    #define TestPWM_CONTROL                (*(reg8 *) TestPWM_PWMHW__CFG0)
    #define TestPWM_CONTROL_PTR            ((reg8 *) TestPWM_PWMHW__CFG0)
    #define TestPWM_CONTROL2               (*(reg8 *) TestPWM_PWMHW__CFG1)
    #define TestPWM_CONTROL3               (*(reg8 *) TestPWM_PWMHW__CFG2)
    #define TestPWM_GLOBAL_ENABLE          (*(reg8 *) TestPWM_PWMHW__PM_ACT_CFG)
    #define TestPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) TestPWM_PWMHW__PM_ACT_CFG)
    #define TestPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) TestPWM_PWMHW__PM_STBY_CFG)
    #define TestPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) TestPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define TestPWM_BLOCK_EN_MASK          (TestPWM_PWMHW__PM_ACT_MSK)
    #define TestPWM_BLOCK_STBY_EN_MASK     (TestPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define TestPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define TestPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define TestPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define TestPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define TestPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define TestPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define TestPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << TestPWM_CTRL_ENABLE_SHIFT)
    #define TestPWM_CTRL_RESET             (uint8)((uint8)0x01u << TestPWM_CTRL_RESET_SHIFT)
    #define TestPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << TestPWM_CTRL_CMPMODE2_SHIFT)
    #define TestPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << TestPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TestPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define TestPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << TestPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define TestPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define TestPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define TestPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define TestPWM_STATUS_TC_INT_EN_MASK_SHIFT            (TestPWM_STATUS_TC_SHIFT - 4u)
    #define TestPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define TestPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (TestPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define TestPWM_STATUS_TC              (uint8)((uint8)0x01u << TestPWM_STATUS_TC_SHIFT)
    #define TestPWM_STATUS_CMP1            (uint8)((uint8)0x01u << TestPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define TestPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)TestPWM_STATUS_TC >> 4u)
    #define TestPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)TestPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define TestPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define TestPWM_RT1_MASK              (uint8)((uint8)0x03u << TestPWM_RT1_SHIFT)
    #define TestPWM_SYNC                  (uint8)((uint8)0x03u << TestPWM_RT1_SHIFT)
    #define TestPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define TestPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << TestPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define TestPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << TestPWM_SYNCDSI_SHIFT)


#else
    #define TestPWM_STATUS                (*(reg8 *)   TestPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define TestPWM_STATUS_PTR            ((reg8 *)    TestPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define TestPWM_STATUS_MASK           (*(reg8 *)   TestPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define TestPWM_STATUS_MASK_PTR       ((reg8 *)    TestPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define TestPWM_STATUS_AUX_CTRL       (*(reg8 *)   TestPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define TestPWM_CONTROL               (*(reg8 *)   TestPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define TestPWM_CONTROL_PTR           ((reg8 *)    TestPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define TestPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define TestPWM_CTRL_RESET_SHIFT       (0x06u)
    #define TestPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define TestPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define TestPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define TestPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << TestPWM_CTRL_ENABLE_SHIFT)
    #define TestPWM_CTRL_RESET             (uint8)((uint8)0x01u << TestPWM_CTRL_RESET_SHIFT)
    #define TestPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << TestPWM_CTRL_CMPMODE2_SHIFT)
    #define TestPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << TestPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define TestPWM_STATUS_KILL_SHIFT          (0x05u)
    #define TestPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define TestPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define TestPWM_STATUS_TC_SHIFT            (0x02u)
    #define TestPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define TestPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define TestPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (TestPWM_STATUS_KILL_SHIFT)
    #define TestPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (TestPWM_STATUS_FIFONEMPTY_SHIFT)
    #define TestPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (TestPWM_STATUS_FIFOFULL_SHIFT)
    #define TestPWM_STATUS_TC_INT_EN_MASK_SHIFT            (TestPWM_STATUS_TC_SHIFT)
    #define TestPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (TestPWM_STATUS_CMP2_SHIFT)
    #define TestPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (TestPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define TestPWM_STATUS_KILL            (uint8)((uint8)0x00u << TestPWM_STATUS_KILL_SHIFT )
    #define TestPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << TestPWM_STATUS_FIFOFULL_SHIFT)
    #define TestPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << TestPWM_STATUS_FIFONEMPTY_SHIFT)
    #define TestPWM_STATUS_TC              (uint8)((uint8)0x01u << TestPWM_STATUS_TC_SHIFT)
    #define TestPWM_STATUS_CMP2            (uint8)((uint8)0x01u << TestPWM_STATUS_CMP2_SHIFT)
    #define TestPWM_STATUS_CMP1            (uint8)((uint8)0x01u << TestPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define TestPWM_STATUS_KILL_INT_EN_MASK            (TestPWM_STATUS_KILL)
    #define TestPWM_STATUS_FIFOFULL_INT_EN_MASK        (TestPWM_STATUS_FIFOFULL)
    #define TestPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (TestPWM_STATUS_FIFONEMPTY)
    #define TestPWM_STATUS_TC_INT_EN_MASK              (TestPWM_STATUS_TC)
    #define TestPWM_STATUS_CMP2_INT_EN_MASK            (TestPWM_STATUS_CMP2)
    #define TestPWM_STATUS_CMP1_INT_EN_MASK            (TestPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define TestPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define TestPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define TestPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define TestPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define TestPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* TestPWM_UsingFixedFunction */

#endif  /* CY_PWM_TestPWM_H */


/* [] END OF FILE */
