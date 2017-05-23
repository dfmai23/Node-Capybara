/*******************************************************************************
* File Name: hearbeat_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_hearbeat_isr_H)
#define CY_ISR_hearbeat_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void hearbeat_isr_Start(void);
void hearbeat_isr_StartEx(cyisraddress address);
void hearbeat_isr_Stop(void);

CY_ISR_PROTO(hearbeat_isr_Interrupt);

void hearbeat_isr_SetVector(cyisraddress address);
cyisraddress hearbeat_isr_GetVector(void);

void hearbeat_isr_SetPriority(uint8 priority);
uint8 hearbeat_isr_GetPriority(void);

void hearbeat_isr_Enable(void);
uint8 hearbeat_isr_GetState(void);
void hearbeat_isr_Disable(void);

void hearbeat_isr_SetPending(void);
void hearbeat_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the hearbeat_isr ISR. */
#define hearbeat_isr_INTC_VECTOR            ((reg32 *) hearbeat_isr__INTC_VECT)

/* Address of the hearbeat_isr ISR priority. */
#define hearbeat_isr_INTC_PRIOR             ((reg8 *) hearbeat_isr__INTC_PRIOR_REG)

/* Priority of the hearbeat_isr interrupt. */
#define hearbeat_isr_INTC_PRIOR_NUMBER      hearbeat_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable hearbeat_isr interrupt. */
#define hearbeat_isr_INTC_SET_EN            ((reg32 *) hearbeat_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the hearbeat_isr interrupt. */
#define hearbeat_isr_INTC_CLR_EN            ((reg32 *) hearbeat_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the hearbeat_isr interrupt state to pending. */
#define hearbeat_isr_INTC_SET_PD            ((reg32 *) hearbeat_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the hearbeat_isr interrupt. */
#define hearbeat_isr_INTC_CLR_PD            ((reg32 *) hearbeat_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_hearbeat_isr_H */


/* [] END OF FILE */
