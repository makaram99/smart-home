#ifndef MCAL_TIMER2_TIMER2_PRIVATE_H_
#define MCAL_TIMER2_TIMER2_PRIVATE_H_

#define TCCR2     *((volatile u8*)0x45)
#define TIMSK     *((volatile u8*)0x59)
#define TCNT2     *((volatile u8*)0x44)
#define OCR2      *((volatile u8*)0x43)


#define TIMER_STOPPED         0
#define TIMER_NO_PRESCALER    1
#define TIMER_8_PRESCALER     2
#define TIMER_64_PRESCALER    3
#define TIMER_256_PRESCALER   4
#define TIMER_1024_PRESCALER  5
#define TIMER_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE  6
#define TIMER_EXTERNAL_CLOCK_SOURCE_RISING_EDGE   7


#define TIMER2_NORMAL_MODE             1
#define TIMER2_CTC_MODE                2
#define TIMER2_PHASECORRECT_PWM_MODE   3
#define TIMER2_FAST_PWM_MODE           4

#define TIMER2_CTC_INTERRUPT_ENABLED      0
#define TIMER2_CTC_INTERRUPT_DISABLED     1


#define TIMER2_OC2_PIN_DISCONNECTED     0
#define TIMER2_OC2_PIN_TOGGLE           1
#define TIMER2_OC2_PIN_SET              2
#define TIMER2_OC2_PIN_CLR              3


#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
