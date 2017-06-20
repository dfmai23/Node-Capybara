/*******************************************************************************
* File Name: My_ADC_IRQ.h
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
#if !defined(CY_ISR_My_ADC_IRQ_H)
#define CY_ISR_My_ADC_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void My_ADC_IRQ_Start(void);
void My_ADC_IRQ_StartEx(cyisraddress address);
void My_ADC_IRQ_Stop(void);

CY_ISR_PROTO(My_ADC_IRQ_Interrupt);

void My_ADC_IRQ_SetVector(cyisraddress address);
cyisraddress My_ADC_IRQ_GetVector(void);

void My_ADC_IRQ_SetPriority(uint8 priority);
uint8 My_ADC_IRQ_GetPriority(void);

void My_ADC_IRQ_Enable(void);
uint8 My_ADC_IRQ_GetState(void);
void My_ADC_IRQ_Disable(void);

void My_ADC_IRQ_SetPending(void);
void My_ADC_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the My_ADC_IRQ ISR. */
#define My_ADC_IRQ_INTC_VECTOR            ((reg32 *) My_ADC_IRQ__INTC_VECT)

/* Address of the My_ADC_IRQ ISR priority. */
#define My_ADC_IRQ_INTC_PRIOR             ((reg8 *) My_ADC_IRQ__INTC_PRIOR_REG)

/* Priority of the My_ADC_IRQ interrupt. */
#define My_ADC_IRQ_INTC_PRIOR_NUMBER      My_ADC_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable My_ADC_IRQ interrupt. */
#define My_ADC_IRQ_INTC_SET_EN            ((reg32 *) My_ADC_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the My_ADC_IRQ interrupt. */
#define My_ADC_IRQ_INTC_CLR_EN            ((reg32 *) My_ADC_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the My_ADC_IRQ interrupt state to pending. */
#define My_ADC_IRQ_INTC_SET_PD            ((reg32 *) My_ADC_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the My_ADC_IRQ interrupt. */
#define My_ADC_IRQ_INTC_CLR_PD            ((reg32 *) My_ADC_IRQ__INTC_CLR_PD_REG)


#endif /* CY_ISR_My_ADC_IRQ_H */


/* [] END OF FILE */
