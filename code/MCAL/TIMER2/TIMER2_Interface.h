

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

/*Timer2 Initialization*/
void TIMER2_VidInit(void);
/*Set Preload Function*/
void TIMER2_VidSetPreload(u8 Copy_u8Preload);
/*Set CTC Value Function*/
void TIMER2_VidSetCTCValue(u8 Copy_u8CTCValue);


void TIMER2_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void));
void TIMER2_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void));

/*INITIATE PWM*/
void M_Pwm2Init(void);

/*SET DUTY CYCLE*/
void M_Pwm2SetDutyCycle(f64 f64_local_dutyCycle);

void M_Pwm2Start(void);
void M_Pwm2Stop(void);
#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
