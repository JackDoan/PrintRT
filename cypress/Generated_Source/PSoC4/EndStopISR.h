/*******************************************************************************
* File Name: EndStopISR.h
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
#if !defined(CY_ISR_EndStopISR_H)
#define CY_ISR_EndStopISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void EndStopISR_Start(void);
void EndStopISR_StartEx(cyisraddress address);
void EndStopISR_Stop(void);

CY_ISR_PROTO(EndStopISR_Interrupt);

void EndStopISR_SetVector(cyisraddress address);
cyisraddress EndStopISR_GetVector(void);

void EndStopISR_SetPriority(uint8 priority);
uint8 EndStopISR_GetPriority(void);

void EndStopISR_Enable(void);
uint8 EndStopISR_GetState(void);
void EndStopISR_Disable(void);

void EndStopISR_SetPending(void);
void EndStopISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the EndStopISR ISR. */
#define EndStopISR_INTC_VECTOR            ((reg32 *) EndStopISR__INTC_VECT)

/* Address of the EndStopISR ISR priority. */
#define EndStopISR_INTC_PRIOR             ((reg32 *) EndStopISR__INTC_PRIOR_REG)

/* Priority of the EndStopISR interrupt. */
#define EndStopISR_INTC_PRIOR_NUMBER      EndStopISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable EndStopISR interrupt. */
#define EndStopISR_INTC_SET_EN            ((reg32 *) EndStopISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the EndStopISR interrupt. */
#define EndStopISR_INTC_CLR_EN            ((reg32 *) EndStopISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the EndStopISR interrupt state to pending. */
#define EndStopISR_INTC_SET_PD            ((reg32 *) EndStopISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the EndStopISR interrupt. */
#define EndStopISR_INTC_CLR_PD            ((reg32 *) EndStopISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_EndStopISR_H */


/* [] END OF FILE */
