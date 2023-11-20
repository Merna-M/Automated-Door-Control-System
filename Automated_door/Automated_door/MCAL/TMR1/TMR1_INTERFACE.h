/*
 * TMR1_INTERFACE.h
 *
 * Created: 10/29/2023 10:40:54 AM
 *  Author: MERNA
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_


/****************************************** Includes ***************************************/
#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/STD_TYPES.h"


/****************************************** Prototypes ***************************************/
void TMR1_vInit(void);

void TMR1_vStart(void);

void TMR1_vStop(void);

void TMR1_vSetCompareMatchValue_A(u16 Copy_u16CompValueA);

void TMR1_vSetDutyCycle_PWM(f32 Copy_f32Duty);

void TMR1_vSetFrequency_PWM(u16 Copy_u16Frequency);



#endif /* TMR1_INTERFACE_H_ */