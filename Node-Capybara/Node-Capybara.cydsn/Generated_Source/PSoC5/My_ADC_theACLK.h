/*******************************************************************************
* File Name: My_ADC_theACLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_My_ADC_theACLK_H)
#define CY_CLOCK_My_ADC_theACLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void My_ADC_theACLK_Start(void) ;
void My_ADC_theACLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void My_ADC_theACLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void My_ADC_theACLK_StandbyPower(uint8 state) ;
void My_ADC_theACLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 My_ADC_theACLK_GetDividerRegister(void) ;
void My_ADC_theACLK_SetModeRegister(uint8 modeBitMask) ;
void My_ADC_theACLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 My_ADC_theACLK_GetModeRegister(void) ;
void My_ADC_theACLK_SetSourceRegister(uint8 clkSource) ;
uint8 My_ADC_theACLK_GetSourceRegister(void) ;
#if defined(My_ADC_theACLK__CFG3)
void My_ADC_theACLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 My_ADC_theACLK_GetPhaseRegister(void) ;
#endif /* defined(My_ADC_theACLK__CFG3) */

#define My_ADC_theACLK_Enable()                       My_ADC_theACLK_Start()
#define My_ADC_theACLK_Disable()                      My_ADC_theACLK_Stop()
#define My_ADC_theACLK_SetDivider(clkDivider)         My_ADC_theACLK_SetDividerRegister(clkDivider, 1u)
#define My_ADC_theACLK_SetDividerValue(clkDivider)    My_ADC_theACLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define My_ADC_theACLK_SetMode(clkMode)               My_ADC_theACLK_SetModeRegister(clkMode)
#define My_ADC_theACLK_SetSource(clkSource)           My_ADC_theACLK_SetSourceRegister(clkSource)
#if defined(My_ADC_theACLK__CFG3)
#define My_ADC_theACLK_SetPhase(clkPhase)             My_ADC_theACLK_SetPhaseRegister(clkPhase)
#define My_ADC_theACLK_SetPhaseValue(clkPhase)        My_ADC_theACLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(My_ADC_theACLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define My_ADC_theACLK_CLKEN              (* (reg8 *) My_ADC_theACLK__PM_ACT_CFG)
#define My_ADC_theACLK_CLKEN_PTR          ((reg8 *) My_ADC_theACLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define My_ADC_theACLK_CLKSTBY            (* (reg8 *) My_ADC_theACLK__PM_STBY_CFG)
#define My_ADC_theACLK_CLKSTBY_PTR        ((reg8 *) My_ADC_theACLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define My_ADC_theACLK_DIV_LSB            (* (reg8 *) My_ADC_theACLK__CFG0)
#define My_ADC_theACLK_DIV_LSB_PTR        ((reg8 *) My_ADC_theACLK__CFG0)
#define My_ADC_theACLK_DIV_PTR            ((reg16 *) My_ADC_theACLK__CFG0)

/* Clock MSB divider configuration register. */
#define My_ADC_theACLK_DIV_MSB            (* (reg8 *) My_ADC_theACLK__CFG1)
#define My_ADC_theACLK_DIV_MSB_PTR        ((reg8 *) My_ADC_theACLK__CFG1)

/* Mode and source configuration register */
#define My_ADC_theACLK_MOD_SRC            (* (reg8 *) My_ADC_theACLK__CFG2)
#define My_ADC_theACLK_MOD_SRC_PTR        ((reg8 *) My_ADC_theACLK__CFG2)

#if defined(My_ADC_theACLK__CFG3)
/* Analog clock phase configuration register */
#define My_ADC_theACLK_PHASE              (* (reg8 *) My_ADC_theACLK__CFG3)
#define My_ADC_theACLK_PHASE_PTR          ((reg8 *) My_ADC_theACLK__CFG3)
#endif /* defined(My_ADC_theACLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define My_ADC_theACLK_CLKEN_MASK         My_ADC_theACLK__PM_ACT_MSK
#define My_ADC_theACLK_CLKSTBY_MASK       My_ADC_theACLK__PM_STBY_MSK

/* CFG2 field masks */
#define My_ADC_theACLK_SRC_SEL_MSK        My_ADC_theACLK__CFG2_SRC_SEL_MASK
#define My_ADC_theACLK_MODE_MASK          (~(My_ADC_theACLK_SRC_SEL_MSK))

#if defined(My_ADC_theACLK__CFG3)
/* CFG3 phase mask */
#define My_ADC_theACLK_PHASE_MASK         My_ADC_theACLK__CFG3_PHASE_DLY_MASK
#endif /* defined(My_ADC_theACLK__CFG3) */

#endif /* CY_CLOCK_My_ADC_theACLK_H */


/* [] END OF FILE */
