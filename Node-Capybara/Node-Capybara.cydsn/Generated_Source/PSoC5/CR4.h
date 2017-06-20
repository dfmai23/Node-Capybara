/*******************************************************************************
* File Name: CR4.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_CR4_H) /* CY_CONTROL_REG_CR4_H */
#define CY_CONTROL_REG_CR4_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} CR4_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    CR4_Write(uint8 control) ;
uint8   CR4_Read(void) ;

void CR4_SaveConfig(void) ;
void CR4_RestoreConfig(void) ;
void CR4_Sleep(void) ; 
void CR4_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define CR4_Control        (* (reg8 *) CR4_Sync_ctrl_reg__CONTROL_REG )
#define CR4_Control_PTR    (  (reg8 *) CR4_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_CR4_H */


/* [] END OF FILE */