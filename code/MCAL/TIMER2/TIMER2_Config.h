#ifndef MCAL_TIMER2_TIMER2_CONFIG_H_
#define MCAL_TIMER2_TIMER2_CONFIG_H_

/*Timer Prescaler Options:
 * 0- TIMER_STOPPED
 * 1- TIMER_NO_PRESCALER
 * 2- TIMER_8_PRESCALER
 * 3- TIMER_64_PRESCALER
 * 4- TIMER_256_PRESCALER
 * 5- TIMER_1024_PRESCALER
 * 6- TIMER_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE
 * 7- TIMER_EXTERNAL_CLOCK_SOURCE_RISING_EDGE
 */
#define TIMER_SET_PRESCALER   TIMER_256_PRESCALER

/*TIMER0 Modes Options:
 * 1- TIMER2_NORMAL_MODE
 * 2- TIMER2_CTC_MODE
 * 3- TIMER2_PHASECORRECT_PWM_MODE
 * 4- TIMER2_FAST_PWM_MODE
 */

#define TIMER2_SET_MODE   TIMER2_FAST_PWM_MODE

/*Timer2 CTC Interrupt Options:
 * 1- TIMER2_CTC_INTERRUPT_ENABLED
 * 2- TIMER2_CTC_INTERRUPT_DISABLED
 */

#define TIMER2_SET_CTC_INTERRUPT   TIMER2_CTC_INTERRUPT_ENABLED

/*Timer2 CTC OC2 PIN Options:
 * 1- TIMER0_OC2_PIN_DISCONNECTED
 * 2- TIMER0_OC2_PIN_TOGGLE
 * 3- TIMER0_OC2_PIN_SET
 * 4- TIMER0_OC2_PIN_CLR
 */
#define TIMER2_SET_OC2_PIN_MODE  TIMER0_OC2_PIN_DISCONNECTED

/*Timer0 PWM MODE Options:
 * 1-TIMER2_NON_INVERTING_PWM
 * 2- TIMER2_INVERTING_PWM
 */
#define TIMER2_SET_PWM_MODE  TIMER2_NON_INVERTING_PWM






#endif /* MCAL_TIMER2_TIMER2_CONFIG_H_ */
