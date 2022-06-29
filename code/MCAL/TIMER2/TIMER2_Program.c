#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"
#include"..\..\MCAL\MDIO\MDIO_Interface.h"
#include"TIMER2_Private.h"
#include"TIMER2_Config.h"

void (*TIMER2_CallBack)(void);

/*Timer2 Initialization*/
void TIMER2_VidInit(void)
{
	/*Select the suitable Prescaler */
	TCCR2&=0xF8;
	TCCR2|=TIMER_SET_PRESCALER;
	/*Mode Select*/
#if TIMER2_SET_MODE == TIMER2_NORMAL_MODE
	CLR_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
	/*Timer Overflow Interrupt Enable*/
	SET_BIT(TIMSK,7);

#elif TIMER2_SET_MODE == TIMER2_CTC_MODE
	CLR_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
#if TIMER2_SET_CTC_INTERRUPT == TIMER2_CTC_INTERRUPT_ENABLED
	SET_BIT(TIMSK,6);
#elif TIMER2_SET_CTC_INTERRUPT == TIMER2_CTC_INTERRUPT_DISABLED
	CLR_BIT(TIMSK,6);
#else
#error "TIMER2 CTC Interrupt Mode is not valid..."
#endif
#if TIMER2_SET_OC2_PIN_MODE == TIMER2_OC2_PIN_DISCONNECTED
	CLR_BIT(TCCR2,5);
	CLR_BIT(TCCR2,4);
#elif TIMER2_SET_OC2_PIN_MODE == TIMER2_OC2_PIN_TOGGLE
	CLR_BIT(TCCR2,5);
	SET_BIT(TCCR2,4);
#elif TIMER2_SET_OC2_PIN_MODE == TIMER2_OC2_PIN_SET
	SET_BIT(TCCR2,5);
	SET_BIT(TCCR2,4);
#elif TIMER2_SET_OC2_PIN_MODE == TIMER2_OC2_PIN_CLR
	SET_BIT(TCCR2,5);
	CLR_BIT(TCCR2,4);
#else
#error "TIMER2 CTC OC2 Mode is not valid..."
#endif
#elif TIMER2_SET_MODE == TIMER2_PHASECORRECT_PWM_MODE
	SET_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
#if TIMER2_SET_PWM_MODE == TIMER2_NON_INVERTING_PWM
	SET_BIT(TCCR2,5);
	CLR_BIT(TCCR2,4);

#elif TIMER2_SET_PWM_MODE == TIMER2_INVERTING_PWM
	SET_BIT(TCCR2,5);
	SET_BIT(TCCR2,4);
#else
#error "PWM Mode is not valid..."
#endif
#elif TIMER2_SET_MODE == TIMER2_FAST_PWM_MODE
	SET_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
#if TIMER2_SET_PWM_MODE == TIMER2_NON_INVERTING_PWM
	SET_BIT(TCCR2,5);
	CLR_BIT(TCCR2,4);

#elif TIMER2_SET_PWM_MODE == TIMER2_INVERTING_PWM
	SET_BIT(TCCR2,5);
	SET_BIT(TCCR2,4);
#else
#error "PWM Mode is not valid..."
#endif
#else
#error "TIMER2 Mode is not valid..."
#endif

}
/*Set Preload Function*/
void TIMER2_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT2=Copy_u8Preload;
}
/*Set CTC Value Function*/
void TIMER2_VidSetCTCValue(u8 Copy_u8CTCValue)
{
	OCR2=Copy_u8CTCValue;
}
void TIMER2_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER2_CallBack=Copy_VidCallBack;
}
void TIMER2_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER2_CallBack=Copy_VidCallBack;
}


void __vector_4(void)   __attribute__((signal));
void __vector_4(void)
{
	TIMER2_CallBack();
}
void __vector_5(void)   __attribute__((signal));
void __vector_5(void)
{
	TIMER2_CallBack();
}


void M_Pwm2Init(void)
{
	CLR_BIT(TCCR2,0);
	SET_BIT(TCCR2,1);

}

void M_Pwm2SetDutyCycle(f64 f64_local_dutyCycle)
{
	OCR2 = ((f64_local_dutyCycle * 1250 ) / 100 ) - 1;
}
void M_Pwm2Start(void)
{
	// to select 1024 division factor
	 	/*SET_BIT(TCCR2,0);
	 	CLR_BIT(TCCR2,1);
	 	SET_BIT(TCCR2,2);*/
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);

}
void M_Pwm2Stop(void)
{
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
}
