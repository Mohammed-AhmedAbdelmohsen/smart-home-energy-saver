/*
 * Servo.c
 *
 *  Created on: Sep 4, 2026
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/Timer1/Timer1.h"
#include "Servo.h"

void Servo_Init(void)
{
    /* 1. Initialize Timer1 in Fast PWM mode with ICR1 as top value and prescaler 8 */
    Timer1_Init(TIMER1_PRESCALLER_8, TIMER1_FAST_PWM_TOP_ICR1);

    /* 2. Set the frequency to 50Hz (period time 20ms) */
    Timer1_SetTopValue(19999);
}

void Servo_SetAngle(s8 Angle)
{
    /* Supported range: from -90 to +90 degrees */
    if (Angle < -90) Angle = -90;
    if (Angle > 90)  Angle = 90;

    /* Equation: 0 deg -> 1.5ms | -90 deg -> 1.0ms | +90 deg -> 2.0ms */
    f32 TonInMilli = 1.5 + ((f32)Angle / 180.0);

    /* Generate pulse on OC1A pin (PD5) */
    Timer1_GeneratePWMA((u16)(TonInMilli * 1000.0));
}