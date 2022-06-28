/*
 * TIMER_Program.c
 *
 *  Created on: Nov 18, 2021
 *      Author: gerges
 */

#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"
#include"TIMER_Private.h"
#include"TIMER_Config.h"

void (*TIMER0_CallBack)(void);

/*Timer0 Initialization*/
void TIMER0_VidInit(void)
{
	/*Select the suitable Prescaler */
	TCCR0&=0xF8;
	TCCR0|=TIMER_SET_PRESCALER;
	/*Mode Select*/
#if TIMER0_SET_MODE == TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/*Timer Overflow Interrupt Enable*/
	SET_BIT(TIMSK,0);

#elif TIMER0_SET_MODE == TIMER0_CTC_MODE
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#if TIMER0_SET_CTC_INTERRUPT == TIMER0_CTC_INTERRUPT_ENABLED
	SET_BIT(TIMSK,1);
#elif TIMER0_SET_CTC_INTERRUPT == TIMER0_CTC_INTERRUPT_DISABLED
	CLR_BIT(TIMSK,1);
#else
#error "TIMER0 CTC Interrupt Mode is not valid..."
#endif
#if TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_DISCONNECTED
	CLR_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_TOGGLE
	CLR_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_SET
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_CLR
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
#else
#error "TIMER0 CTC OC0 Mode is not valid..."
#endif
#elif TIMER0_SET_MODE == TIMER0_PHASECORRECT_PWM_MODE
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
#if TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);

#elif TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#else
#error "PWM Mode is not valid..."
#endif
#elif TIMER0_SET_MODE == TIMER0_FAST_PWM_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
#if TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);

#elif TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
#else
#error "PWM Mode is not valid..."
#endif
#else
#error "TIMER0 Mode is not valid..."
#endif

}
/*Set Preload Function*/
void TIMER0_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT0=Copy_u8Preload;
}
/*Set CTC Value Function*/
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue)
{
	OCR0=Copy_u8CTCValue;
}
void TIMER0_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack=Copy_VidCallBack;
}
void TIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack=Copy_VidCallBack;
}
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	TIMER0_CallBack();
}
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
	TIMER0_CallBack();
}
