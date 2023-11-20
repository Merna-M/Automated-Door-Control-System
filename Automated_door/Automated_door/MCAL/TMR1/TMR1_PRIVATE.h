/*
 * TMR1_PRIVATE.h
 *
 * Created: 10/29/2023 10:41:36 AM
 *  Author: MERNA
 */ 


#ifndef TMR1_PRIVATE_H_
#define TMR1_PRIVATE_H_

/* Timer1 Modes */
#define TMR1_NORMAL_MODE							1
#define TMR1_PWM_PHASE_CORRECT_8_BIT				2 
#define TMR1_PWM_PHASE_CORRECT_9_BIT				3
#define TMR1_PWM_PHASE_CORRECT_10_BIT				4
#define TMR1_CTC_OCR1A								5
#define TMR1_PWM_FAST_8_BIT							6
#define TMR1_PWM_FAST_9_BIT							7
#define TMR1_PWM_FAST_10_BIT						8
#define TMR1_PWM_PHASE_FREQ_ICR1					9
#define TMR1_PWM_PHASE_FREQ_OCR1A					10
#define TMR1_PWM_PHASE_CORRECT_ICR1					11
#define TMR1_PWM_PHASE_CORRECT_OCR1A				12
#define TMR1_CTC_ICR1								13

#define TMR1_FAST_PWM_ICR1							15
#define TMR1_FASR_PWM_OCR1A							16		


/* PWM Modes */
#define TMR1_PWM_INVERTING							1
#define TMR1_PWM_NONINVERTING						2

/* Prescalar Values */
#define TMR1_PRESCALAR_1							1
#define TMR1_PRESCALAR_8							2
#define TMR1_PRESCALAR_64							3
#define TMR1_PRESCALAR_256							4
#define TMR1_PRESCALAR_1024							5



#endif /* TMR1_PRIVATE_H_ */