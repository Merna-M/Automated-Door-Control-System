/*
 * SRVM_PROGRAM.c
 *
 * Created: 10/30/2023 11:14:53 PM
 *  Author: MERNA
 */ 

/* UTILES_LIB */
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/TMR1/TMR1_INTERFACE.h"


void SRVM_voidOn(u8 Copy_u8Angle)
{
	f32 LOC_DutyCycle = ((Copy_u8Angle*5.0)/180)+5;
	/* TMR1 init at pwm mode 14 */
	TMR1_vInit();
	/* Set pwm fre. = 50 */
	TMR1_vSetFrequency_PWM(50);
	/* Set pwm duty cycle between 5 : 10
	 depend on desired angle[0 : 180] */
	TMR1_vSetDutyCycle_PWM(LOC_DutyCycle);
	/* TMR1 start */
	TMR1_vStart();
}


void SRVM_voidOff(void)
{
	/* TMR1 stop */
	TMR1_vStop();
}