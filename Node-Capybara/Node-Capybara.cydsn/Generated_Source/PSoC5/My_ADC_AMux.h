/*******************************************************************************
* File Name: My_ADC_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_My_ADC_AMux_H)
#define CY_AMUX_My_ADC_AMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void My_ADC_AMux_Start(void) ;
#define My_ADC_AMux_Init() My_ADC_AMux_Start()
void My_ADC_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void My_ADC_AMux_Stop(void); */
/* void My_ADC_AMux_Select(uint8 channel); */
/* void My_ADC_AMux_Connect(uint8 channel); */
/* void My_ADC_AMux_Disconnect(uint8 channel); */
/* void My_ADC_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define My_ADC_AMux_CHANNELS  2u
#define My_ADC_AMux_MUXTYPE   1
#define My_ADC_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define My_ADC_AMux_NULL_CHANNEL 0xFFu
#define My_ADC_AMux_MUX_SINGLE   1
#define My_ADC_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if My_ADC_AMux_MUXTYPE == My_ADC_AMux_MUX_SINGLE
# if !My_ADC_AMux_ATMOSTONE
#  define My_ADC_AMux_Connect(channel) My_ADC_AMux_Set(channel)
# endif
# define My_ADC_AMux_Disconnect(channel) My_ADC_AMux_Unset(channel)
#else
# if !My_ADC_AMux_ATMOSTONE
void My_ADC_AMux_Connect(uint8 channel) ;
# endif
void My_ADC_AMux_Disconnect(uint8 channel) ;
#endif

#if My_ADC_AMux_ATMOSTONE
# define My_ADC_AMux_Stop() My_ADC_AMux_DisconnectAll()
# define My_ADC_AMux_Select(channel) My_ADC_AMux_FastSelect(channel)
void My_ADC_AMux_DisconnectAll(void) ;
#else
# define My_ADC_AMux_Stop() My_ADC_AMux_Start()
void My_ADC_AMux_Select(uint8 channel) ;
# define My_ADC_AMux_DisconnectAll() My_ADC_AMux_Start()
#endif

#endif /* CY_AMUX_My_ADC_AMux_H */


/* [] END OF FILE */
