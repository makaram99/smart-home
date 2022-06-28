/*
 * TIMER_Interface.h
 *
 *  Created on: Nov 18, 2021
 *      Author: gerges
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

/*Timer0 Initialization*/
void TIMER0_VidInit(void);
/*Set Preload Function*/
void TIMER0_VidSetPreload(u8 Copy_u8Preload);
/*Set CTC Value Function*/
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue);

void TIMER0_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void));
void TIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void));

#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
