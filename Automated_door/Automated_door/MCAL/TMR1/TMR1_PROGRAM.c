/*
 * TMR1_PROGRAM.c
 *
 * Created: 10/29/2023 10:40:08 AM
 *  Author: MERNA
 */ 

#include "TMR1_INTERFACE.h"
#include "TMR1_REGISTER.h"
#include "TMR1_PRIVATE.h"
#include "TMR1_CONFIG.h"

/******************************************************************************************************/
void TMR1_vInit(void)
{
	#if TMR1_MODE == TMR1_NORMAL_MODE
	//Select Normal Mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_CORRECT_8_BIT
	//Select PWM, Phase Correct, 8-bit Mode
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_CORRECT_9_BIT
	//Select PWM, Phase Correct, 9-bit Mode
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_CORRECT_10_BIT
	//Select PWM, Phase Correct, 10-bit Mode
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_CTC_OCR1A
	//Select CTC Mode with top value = OCR1A Mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_FAST_8_BIT
	//Select Fast PWM, 8-bit Mode
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_FAST_9_BIT
	//Select Fast PWM, 9-bit
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_FAST_10_BIT
	//Select Fast PWM, 10-bit
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_FREQ_ICR1
	//Select PWM, Phase and Frequency Correct with top value ICR1 Mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_FREQ_OCR1A
	//Select PWM, Phase and Frequency Correct with top value OCR1A Mode
	SET_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_CORRECT_ICR1
	//Select PWM, Phase Correct with top value = ICR1 Mode
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_PWM_PHASE_CORRECT_OCR1A
	//Select PWM, Phase Correct with top value OCR1A Mode
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_CTC_ICR1
	//Select CTC with top value ICR1 Mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#elif TMR1_MODE == TMR1_FAST_PWM_ICR1
	//Select Fast PWM with top value ICR1 Mode
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#if TMR1_PWM_MODE == TMR1_PWM_INVERTING
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	
	#elif TMR1_PWM_MODE == TMR1_PWM_NONINVERTING
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	#endif
	
	//select top value ICR1, 4999 -> periodic time = 20 msec. , freq = 50hz.
	//ICR1 = 4999;
	#elif TMR1_MODE == TMR1_FASR_PWM_OCR1A
	//Select Fast PWM with top value OCR1A Mode
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#endif
}

/******************************************************************************************************/
void TMR1_vStart(void)
{
	#if TMR1_PRESCALAR_SEL == TMR1_PRESCALAR_1
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	
	#elif TMR1_PRESCALAR_SEL == TMR1_PRESCALAR_8
	CLR_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	
	#elif TMR1_PRESCALAR_SEL == TMR1_PRESCALAR_64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	
	#elif TMR1_PRESCALAR_SEL == TMR1_PRESCALAR_256
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	SET_BIT(TCCR1B,CS12);
	
	#elif TMR1_PRESCALAR_SEL == TMR1_PRESCALAR_1024
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	SET_BIT(TCCR1B,CS12);
	
	#endif
}

/******************************************************************************************************/
void TMR1_vStop(void)
{
	TCCR1B &= ~(0x07);
}

/******************************************************************************************************/

void TMR1_vSetCompareMatchValue_A(u16 Copy_u16CompValueA)
{
	OCR1A = Copy_u16CompValueA;
}

/******************************************************************************************************/

void TMR1_vSetDutyCycle_PWM(f32 Copy_f32Duty)
{
	if(Copy_f32Duty <= 100)
	{
		#if TMR1_MODE == TMR1_FAST_PWM_ICR1
		#if TMR1_PWM_MODE == TMR1_PWM_INVERTING
		Copy_f32Duty = 100 - Copy_f32Duty;
		OCR1A = ((Copy_f32Duty*(ICR1+1))/100)-1;
		
		#elif TMR1_PWM_MODE == TMR1_PWM_NONINVERTING
		OCR1A = ((Copy_f32Duty*(ICR1+1))/100)-1;
		
		#endif
		#endif
		
	}
}

/******************************************************************************************************/

void TMR1_vSetFrequency_PWM(u16 Copy_u16Frequency)
{
	#if TMR1_MODE == TMR1_FAST_PWM_ICR1
	//under condition -> tick time = 4 usec.
	ICR1 = (1000000ul/(4*Copy_u16Frequency))-1;
	#endif
}

/******************************************************************************************************/

