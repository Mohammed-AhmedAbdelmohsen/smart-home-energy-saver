/*
 * Timer0.h
 *

 */

#ifndef MCAL_TIMER0_TIMER0_H_
#define MCAL_TIMER0_TIMER0_H_

#include "../../LIB/STD_TYPES.h"

/* ==================================================================== */
/*                         TIMER0 REGISTERS                             */
/* ==================================================================== */

#define TCCR0   (*(volatile u8*)(0x53))
#define TCNT0   (*(volatile u8*)(0x52))
#define OCR0    (*(volatile u8*)(0x5C))
#define TIMSK   (*(volatile u8*)(0x59))
#define TIFR    (*(volatile u8*)(0x58))
#define SREG    (*(volatile u8*)(0x5F))

/* TCCR0 Register Bits */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TIMSK Register Bits */
#define OCIE0   1
#define TOIE0   0

/* TIFR Register Bits */
#define OCF0    1
#define TOV0    0

/* SREG Register Bits */
#define I_BIT   7

/* ==================================================================== */
/*                       TIMER0 CONFIGURATIONS                          */
/* ==================================================================== */

/* Prescaler Options */
#define TIMER0_PRESCALLER_1     1
#define TIMER0_PRESCALLER_8     8
#define TIMER0_PRESCALLER_64    64
#define TIMER0_PRESCALLER_256   256
#define TIMER0_PRESCALLER_1024  1024

/* Generation Modes */
#define TIMER0_OVF              1
#define TIMER0_CTC              2
#define TIMER0_FAST_PWM         3
#define TIMER0_PHASE_CORRECT    4

/* ==================================================================== */
/*                        FUNCTION PROTOTYPES                           */
/* ==================================================================== */

void Timer0_Init(u32 Prescaller, u8 Mode);
void Timer0_SetDesiredTime(u32 TimeInMicro, void (*fptr)(void));
void Timer0_GeneratePWM(u8 CompareValue);
void Timer0_SetCTCCallback(void (*fptr)(void));

#endif /* MCAL_TIMER0_TIMER0_H_ */
