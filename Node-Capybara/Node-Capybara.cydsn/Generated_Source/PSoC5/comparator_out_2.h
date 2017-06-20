/*******************************************************************************
* File Name: comparator_out_2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_comparator_out_2_H) /* Pins comparator_out_2_H */
#define CY_PINS_comparator_out_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "comparator_out_2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 comparator_out_2__PORT == 15 && ((comparator_out_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    comparator_out_2_Write(uint8 value);
void    comparator_out_2_SetDriveMode(uint8 mode);
uint8   comparator_out_2_ReadDataReg(void);
uint8   comparator_out_2_Read(void);
void    comparator_out_2_SetInterruptMode(uint16 position, uint16 mode);
uint8   comparator_out_2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the comparator_out_2_SetDriveMode() function.
     *  @{
     */
        #define comparator_out_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define comparator_out_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define comparator_out_2_DM_RES_UP          PIN_DM_RES_UP
        #define comparator_out_2_DM_RES_DWN         PIN_DM_RES_DWN
        #define comparator_out_2_DM_OD_LO           PIN_DM_OD_LO
        #define comparator_out_2_DM_OD_HI           PIN_DM_OD_HI
        #define comparator_out_2_DM_STRONG          PIN_DM_STRONG
        #define comparator_out_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define comparator_out_2_MASK               comparator_out_2__MASK
#define comparator_out_2_SHIFT              comparator_out_2__SHIFT
#define comparator_out_2_WIDTH              1u

/* Interrupt constants */
#if defined(comparator_out_2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in comparator_out_2_SetInterruptMode() function.
     *  @{
     */
        #define comparator_out_2_INTR_NONE      (uint16)(0x0000u)
        #define comparator_out_2_INTR_RISING    (uint16)(0x0001u)
        #define comparator_out_2_INTR_FALLING   (uint16)(0x0002u)
        #define comparator_out_2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define comparator_out_2_INTR_MASK      (0x01u) 
#endif /* (comparator_out_2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define comparator_out_2_PS                     (* (reg8 *) comparator_out_2__PS)
/* Data Register */
#define comparator_out_2_DR                     (* (reg8 *) comparator_out_2__DR)
/* Port Number */
#define comparator_out_2_PRT_NUM                (* (reg8 *) comparator_out_2__PRT) 
/* Connect to Analog Globals */                                                  
#define comparator_out_2_AG                     (* (reg8 *) comparator_out_2__AG)                       
/* Analog MUX bux enable */
#define comparator_out_2_AMUX                   (* (reg8 *) comparator_out_2__AMUX) 
/* Bidirectional Enable */                                                        
#define comparator_out_2_BIE                    (* (reg8 *) comparator_out_2__BIE)
/* Bit-mask for Aliased Register Access */
#define comparator_out_2_BIT_MASK               (* (reg8 *) comparator_out_2__BIT_MASK)
/* Bypass Enable */
#define comparator_out_2_BYP                    (* (reg8 *) comparator_out_2__BYP)
/* Port wide control signals */                                                   
#define comparator_out_2_CTL                    (* (reg8 *) comparator_out_2__CTL)
/* Drive Modes */
#define comparator_out_2_DM0                    (* (reg8 *) comparator_out_2__DM0) 
#define comparator_out_2_DM1                    (* (reg8 *) comparator_out_2__DM1)
#define comparator_out_2_DM2                    (* (reg8 *) comparator_out_2__DM2) 
/* Input Buffer Disable Override */
#define comparator_out_2_INP_DIS                (* (reg8 *) comparator_out_2__INP_DIS)
/* LCD Common or Segment Drive */
#define comparator_out_2_LCD_COM_SEG            (* (reg8 *) comparator_out_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define comparator_out_2_LCD_EN                 (* (reg8 *) comparator_out_2__LCD_EN)
/* Slew Rate Control */
#define comparator_out_2_SLW                    (* (reg8 *) comparator_out_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define comparator_out_2_PRTDSI__CAPS_SEL       (* (reg8 *) comparator_out_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define comparator_out_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) comparator_out_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define comparator_out_2_PRTDSI__OE_SEL0        (* (reg8 *) comparator_out_2__PRTDSI__OE_SEL0) 
#define comparator_out_2_PRTDSI__OE_SEL1        (* (reg8 *) comparator_out_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define comparator_out_2_PRTDSI__OUT_SEL0       (* (reg8 *) comparator_out_2__PRTDSI__OUT_SEL0) 
#define comparator_out_2_PRTDSI__OUT_SEL1       (* (reg8 *) comparator_out_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define comparator_out_2_PRTDSI__SYNC_OUT       (* (reg8 *) comparator_out_2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(comparator_out_2__SIO_CFG)
    #define comparator_out_2_SIO_HYST_EN        (* (reg8 *) comparator_out_2__SIO_HYST_EN)
    #define comparator_out_2_SIO_REG_HIFREQ     (* (reg8 *) comparator_out_2__SIO_REG_HIFREQ)
    #define comparator_out_2_SIO_CFG            (* (reg8 *) comparator_out_2__SIO_CFG)
    #define comparator_out_2_SIO_DIFF           (* (reg8 *) comparator_out_2__SIO_DIFF)
#endif /* (comparator_out_2__SIO_CFG) */

/* Interrupt Registers */
#if defined(comparator_out_2__INTSTAT)
    #define comparator_out_2_INTSTAT            (* (reg8 *) comparator_out_2__INTSTAT)
    #define comparator_out_2_SNAP               (* (reg8 *) comparator_out_2__SNAP)
    
	#define comparator_out_2_0_INTTYPE_REG 		(* (reg8 *) comparator_out_2__0__INTTYPE)
#endif /* (comparator_out_2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_comparator_out_2_H */


/* [] END OF FILE */
