/*******************************************************************************
* File Name: DVDAC_4_IntClock.h
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

#if !defined(CY_CLOCK_DVDAC_4_IntClock_H)
#define CY_CLOCK_DVDAC_4_IntClock_H

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

void DVDAC_4_IntClock_Start(void) ;
void DVDAC_4_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DVDAC_4_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DVDAC_4_IntClock_StandbyPower(uint8 state) ;
void DVDAC_4_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DVDAC_4_IntClock_GetDividerRegister(void) ;
void DVDAC_4_IntClock_SetModeRegister(uint8 modeBitMask) ;
void DVDAC_4_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 DVDAC_4_IntClock_GetModeRegister(void) ;
void DVDAC_4_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 DVDAC_4_IntClock_GetSourceRegister(void) ;
#if defined(DVDAC_4_IntClock__CFG3)
void DVDAC_4_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 DVDAC_4_IntClock_GetPhaseRegister(void) ;
#endif /* defined(DVDAC_4_IntClock__CFG3) */

#define DVDAC_4_IntClock_Enable()                       DVDAC_4_IntClock_Start()
#define DVDAC_4_IntClock_Disable()                      DVDAC_4_IntClock_Stop()
#define DVDAC_4_IntClock_SetDivider(clkDivider)         DVDAC_4_IntClock_SetDividerRegister(clkDivider, 1u)
#define DVDAC_4_IntClock_SetDividerValue(clkDivider)    DVDAC_4_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define DVDAC_4_IntClock_SetMode(clkMode)               DVDAC_4_IntClock_SetModeRegister(clkMode)
#define DVDAC_4_IntClock_SetSource(clkSource)           DVDAC_4_IntClock_SetSourceRegister(clkSource)
#if defined(DVDAC_4_IntClock__CFG3)
#define DVDAC_4_IntClock_SetPhase(clkPhase)             DVDAC_4_IntClock_SetPhaseRegister(clkPhase)
#define DVDAC_4_IntClock_SetPhaseValue(clkPhase)        DVDAC_4_IntClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DVDAC_4_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DVDAC_4_IntClock_CLKEN              (* (reg8 *) DVDAC_4_IntClock__PM_ACT_CFG)
#define DVDAC_4_IntClock_CLKEN_PTR          ((reg8 *) DVDAC_4_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DVDAC_4_IntClock_CLKSTBY            (* (reg8 *) DVDAC_4_IntClock__PM_STBY_CFG)
#define DVDAC_4_IntClock_CLKSTBY_PTR        ((reg8 *) DVDAC_4_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DVDAC_4_IntClock_DIV_LSB            (* (reg8 *) DVDAC_4_IntClock__CFG0)
#define DVDAC_4_IntClock_DIV_LSB_PTR        ((reg8 *) DVDAC_4_IntClock__CFG0)
#define DVDAC_4_IntClock_DIV_PTR            ((reg16 *) DVDAC_4_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define DVDAC_4_IntClock_DIV_MSB            (* (reg8 *) DVDAC_4_IntClock__CFG1)
#define DVDAC_4_IntClock_DIV_MSB_PTR        ((reg8 *) DVDAC_4_IntClock__CFG1)

/* Mode and source configuration register */
#define DVDAC_4_IntClock_MOD_SRC            (* (reg8 *) DVDAC_4_IntClock__CFG2)
#define DVDAC_4_IntClock_MOD_SRC_PTR        ((reg8 *) DVDAC_4_IntClock__CFG2)

#if defined(DVDAC_4_IntClock__CFG3)
/* Analog clock phase configuration register */
#define DVDAC_4_IntClock_PHASE              (* (reg8 *) DVDAC_4_IntClock__CFG3)
#define DVDAC_4_IntClock_PHASE_PTR          ((reg8 *) DVDAC_4_IntClock__CFG3)
#endif /* defined(DVDAC_4_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DVDAC_4_IntClock_CLKEN_MASK         DVDAC_4_IntClock__PM_ACT_MSK
#define DVDAC_4_IntClock_CLKSTBY_MASK       DVDAC_4_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define DVDAC_4_IntClock_SRC_SEL_MSK        DVDAC_4_IntClock__CFG2_SRC_SEL_MASK
#define DVDAC_4_IntClock_MODE_MASK          (~(DVDAC_4_IntClock_SRC_SEL_MSK))

#if defined(DVDAC_4_IntClock__CFG3)
/* CFG3 phase mask */
#define DVDAC_4_IntClock_PHASE_MASK         DVDAC_4_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(DVDAC_4_IntClock__CFG3) */

#endif /* CY_CLOCK_DVDAC_4_IntClock_H */


/* [] END OF FILE */
