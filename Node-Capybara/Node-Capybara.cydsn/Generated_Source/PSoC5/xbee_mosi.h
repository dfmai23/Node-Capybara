/*******************************************************************************
* File Name: xbee_mosi.h  
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

#if !defined(CY_PINS_xbee_mosi_H) /* Pins xbee_mosi_H */
#define CY_PINS_xbee_mosi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "xbee_mosi_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 xbee_mosi__PORT == 15 && ((xbee_mosi__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    xbee_mosi_Write(uint8 value);
void    xbee_mosi_SetDriveMode(uint8 mode);
uint8   xbee_mosi_ReadDataReg(void);
uint8   xbee_mosi_Read(void);
void    xbee_mosi_SetInterruptMode(uint16 position, uint16 mode);
uint8   xbee_mosi_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the xbee_mosi_SetDriveMode() function.
     *  @{
     */
        #define xbee_mosi_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define xbee_mosi_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define xbee_mosi_DM_RES_UP          PIN_DM_RES_UP
        #define xbee_mosi_DM_RES_DWN         PIN_DM_RES_DWN
        #define xbee_mosi_DM_OD_LO           PIN_DM_OD_LO
        #define xbee_mosi_DM_OD_HI           PIN_DM_OD_HI
        #define xbee_mosi_DM_STRONG          PIN_DM_STRONG
        #define xbee_mosi_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define xbee_mosi_MASK               xbee_mosi__MASK
#define xbee_mosi_SHIFT              xbee_mosi__SHIFT
#define xbee_mosi_WIDTH              1u

/* Interrupt constants */
#if defined(xbee_mosi__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in xbee_mosi_SetInterruptMode() function.
     *  @{
     */
        #define xbee_mosi_INTR_NONE      (uint16)(0x0000u)
        #define xbee_mosi_INTR_RISING    (uint16)(0x0001u)
        #define xbee_mosi_INTR_FALLING   (uint16)(0x0002u)
        #define xbee_mosi_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define xbee_mosi_INTR_MASK      (0x01u) 
#endif /* (xbee_mosi__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define xbee_mosi_PS                     (* (reg8 *) xbee_mosi__PS)
/* Data Register */
#define xbee_mosi_DR                     (* (reg8 *) xbee_mosi__DR)
/* Port Number */
#define xbee_mosi_PRT_NUM                (* (reg8 *) xbee_mosi__PRT) 
/* Connect to Analog Globals */                                                  
#define xbee_mosi_AG                     (* (reg8 *) xbee_mosi__AG)                       
/* Analog MUX bux enable */
#define xbee_mosi_AMUX                   (* (reg8 *) xbee_mosi__AMUX) 
/* Bidirectional Enable */                                                        
#define xbee_mosi_BIE                    (* (reg8 *) xbee_mosi__BIE)
/* Bit-mask for Aliased Register Access */
#define xbee_mosi_BIT_MASK               (* (reg8 *) xbee_mosi__BIT_MASK)
/* Bypass Enable */
#define xbee_mosi_BYP                    (* (reg8 *) xbee_mosi__BYP)
/* Port wide control signals */                                                   
#define xbee_mosi_CTL                    (* (reg8 *) xbee_mosi__CTL)
/* Drive Modes */
#define xbee_mosi_DM0                    (* (reg8 *) xbee_mosi__DM0) 
#define xbee_mosi_DM1                    (* (reg8 *) xbee_mosi__DM1)
#define xbee_mosi_DM2                    (* (reg8 *) xbee_mosi__DM2) 
/* Input Buffer Disable Override */
#define xbee_mosi_INP_DIS                (* (reg8 *) xbee_mosi__INP_DIS)
/* LCD Common or Segment Drive */
#define xbee_mosi_LCD_COM_SEG            (* (reg8 *) xbee_mosi__LCD_COM_SEG)
/* Enable Segment LCD */
#define xbee_mosi_LCD_EN                 (* (reg8 *) xbee_mosi__LCD_EN)
/* Slew Rate Control */
#define xbee_mosi_SLW                    (* (reg8 *) xbee_mosi__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define xbee_mosi_PRTDSI__CAPS_SEL       (* (reg8 *) xbee_mosi__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define xbee_mosi_PRTDSI__DBL_SYNC_IN    (* (reg8 *) xbee_mosi__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define xbee_mosi_PRTDSI__OE_SEL0        (* (reg8 *) xbee_mosi__PRTDSI__OE_SEL0) 
#define xbee_mosi_PRTDSI__OE_SEL1        (* (reg8 *) xbee_mosi__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define xbee_mosi_PRTDSI__OUT_SEL0       (* (reg8 *) xbee_mosi__PRTDSI__OUT_SEL0) 
#define xbee_mosi_PRTDSI__OUT_SEL1       (* (reg8 *) xbee_mosi__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define xbee_mosi_PRTDSI__SYNC_OUT       (* (reg8 *) xbee_mosi__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(xbee_mosi__SIO_CFG)
    #define xbee_mosi_SIO_HYST_EN        (* (reg8 *) xbee_mosi__SIO_HYST_EN)
    #define xbee_mosi_SIO_REG_HIFREQ     (* (reg8 *) xbee_mosi__SIO_REG_HIFREQ)
    #define xbee_mosi_SIO_CFG            (* (reg8 *) xbee_mosi__SIO_CFG)
    #define xbee_mosi_SIO_DIFF           (* (reg8 *) xbee_mosi__SIO_DIFF)
#endif /* (xbee_mosi__SIO_CFG) */

/* Interrupt Registers */
#if defined(xbee_mosi__INTSTAT)
    #define xbee_mosi_INTSTAT            (* (reg8 *) xbee_mosi__INTSTAT)
    #define xbee_mosi_SNAP               (* (reg8 *) xbee_mosi__SNAP)
    
	#define xbee_mosi_0_INTTYPE_REG 		(* (reg8 *) xbee_mosi__0__INTTYPE)
#endif /* (xbee_mosi__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_xbee_mosi_H */


/* [] END OF FILE */
