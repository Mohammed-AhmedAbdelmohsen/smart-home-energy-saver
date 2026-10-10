/*
 * Timer1.c
 *

 
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO.h"
#include "Timer1.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef GET_BIT
#define GET_BIT(REG, BIT) (((REG) >> (BIT)) & 1)
#endif

static u32 G_Prescaller = 1;
static u32 G_Counts = 0;
static u16 G_Preload = 0;
static void (*Timer1_ptr)(void) = NULL;

void Timer1_Init(u32 Prescaller, u8 Mode)
{
    G_Prescaller = Prescaller;

    /* 1. Prescaler Selection */
    switch (Prescaller)
    {
    case TIMER1_PRESCALLER_1:
        CLR_BIT(TCCR1B, CS12);
        CLR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS10);
        break;
    case TIMER1_PRESCALLER_8:
        CLR_BIT(TCCR1B, CS12);
        SET_BIT(TCCR1B, CS11);
        CLR_BIT(TCCR1B, CS10);
        break;
    case TIMER1_PRESCALLER_64:
        CLR_BIT(TCCR1B, CS12);
        SET_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS10);
        break;
    case TIMER1_PRESCALLER_256:
        SET_BIT(TCCR1B, CS12);
        CLR_BIT(TCCR1B, CS11);
        CLR_BIT(TCCR1B, CS10);
        break;
    case TIMER1_PRESCALLER_1024:
        SET_BIT(TCCR1B, CS12);
        CLR_BIT(TCCR1B, CS11);
        SET_BIT(TCCR1B, CS10);
        break;
    }

    /* 2. Generation Mode Selection */
    switch (Mode)
    {
    case TIMER1_OVF:
        CLR_BIT(TCCR1B, WGM13);
        CLR_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TIMSK, TOIE1);
        break;

    case TIMER1_CTC_TOP_OCR1A:
        CLR_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TIMSK, OCIE1A);
        break;

    case TIMER1_CTC_TOP_ICR1:
        SET_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TIMSK, OCIE1A);
        break;

    case TIMER1_FAST_PWM_8BIT:
        CLR_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, COM1A1);
        CLR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        CLR_BIT(TCCR1A, COM1B0);
        DIO_InitPin(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
        DIO_InitPin(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
        break;

    case TIMER1_FAST_PWM_9BIT:
        CLR_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, COM1A1);
        CLR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        CLR_BIT(TCCR1A, COM1B0);
        DIO_InitPin(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
        DIO_InitPin(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
        break;

    case TIMER1_FAST_PWM_10BIT:
        CLR_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, COM1A1);
        CLR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        CLR_BIT(TCCR1A, COM1B0);
        DIO_InitPin(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
        DIO_InitPin(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
        break;

    case TIMER1_FAST_PWM_TOP_ICR1:
        SET_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, COM1A1);
        CLR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        CLR_BIT(TCCR1A, COM1B0);
        DIO_InitPin(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
        DIO_InitPin(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
        break;

    case TIMER1_FAST_PWM_TOP_OCR1A:
        SET_BIT(TCCR1B, WGM13);
        SET_BIT(TCCR1B, WGM12);
        SET_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1A, WGM10);
        SET_BIT(TCCR1A, COM1A1);
        CLR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        CLR_BIT(TCCR1A, COM1B0);
        DIO_InitPin(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
        DIO_InitPin(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
        break;
    }

    SET_BIT(SREG, I_BIT);
}

void Timer1_SetDesiredTime(u32 TimeInMicro, void (*fptr)(void))
{
    f32 OVF_Time = 8192.0 * (f32)G_Prescaller;
    f32 Desires_OVF_Counts = (f32)TimeInMicro / OVF_Time;

    Timer1_ptr = fptr;

    if (Desires_OVF_Counts < 1.0)
    {
        G_Counts = 1;
        G_Preload = (u16)(65536.0 - (65536.0 * Desires_OVF_Counts));
        TCNT1 = G_Preload;
    }
    else if (Desires_OVF_Counts == 1.0)
    {
        G_Counts = 1;
        G_Preload = 0;
        TCNT1 = 0;
    }
    else
    {
        G_Counts = (u32)Desires_OVF_Counts;
        f32 Fraction = Desires_OVF_Counts - (f32)G_Counts;

        if (Fraction != 0.0)
        {
            G_Preload = (u16)(65536.0 - (65536.0 * Fraction));
            TCNT1 = G_Preload;
            G_Counts++;
        }
        else
        {
            G_Preload = 0;
            TCNT1 = 0;
        }
    }
}

void Timer1_SetTopValue(u16 TopVal)
{
    ICR1 = TopVal;
}

void Timer1_GeneratePWMA(u16 CompareVal)
{
    OCR1A = CompareVal;
}

void Timer1_GeneratePWMB(u16 CompareVal)
{
    OCR1B = CompareVal;
}

/* ISR for Timer1 Overflow */
void __vector_9(void) __attribute__((signal, used));
void __vector_9(void)
{
    static u32 Counter = 0;
    Counter++;

    if (Counter == G_Counts)
    {
        TCNT1 = G_Preload;
        Counter = 0;

        if (Timer1_ptr != NULL)
        {
            Timer1_ptr();
        }
    }
}

/* ICU: Capture High Time (Ton) */
u32 Timer1_CaptureTonCounts(void)
{
    u16 CountsForFirstRising;
    u16 CountsForFirstFalling;

    DIO_InitPin(DIO_PORTD, DIO_PIN6, DIO_INPUT);

    /* 1. Detect Rising Edge */
    SET_BIT(TCCR1B, ICNC1);
    SET_BIT(TCCR1B, ICES1);
    SET_BIT(TIFR, ICF1);
    while (GET_BIT(TIFR, ICF1) == 0);
    CountsForFirstRising = ICR1;
    SET_BIT(TIFR, ICF1);

    /* 2. Detect Falling Edge */
    CLR_BIT(TCCR1B, ICES1);
    while (GET_BIT(TIFR, ICF1) == 0);
    CountsForFirstFalling = ICR1;
    SET_BIT(TIFR, ICF1);

    return (u32)(CountsForFirstFalling - CountsForFirstRising);
}

/* ICU: Capture Low Time (Toff) */
u32 Timer1_CaptureToffCounts(void)
{
    u16 CountsForFirstFalling;
    u16 CountsForFirstRising;

    DIO_InitPin(DIO_PORTD, DIO_PIN6, DIO_INPUT);

    /* 1. Detect Falling Edge */
    SET_BIT(TCCR1B, ICNC1);
    CLR_BIT(TCCR1B, ICES1);
    SET_BIT(TIFR, ICF1);
    while (GET_BIT(TIFR, ICF1) == 0);
    CountsForFirstFalling = ICR1;
    SET_BIT(TIFR, ICF1);

    /* 2. Detect Rising Edge */
    SET_BIT(TCCR1B, ICES1);
    while (GET_BIT(TIFR, ICF1) == 0);
    CountsForFirstRising = ICR1;
    SET_BIT(TIFR, ICF1);

    return (u32)(CountsForFirstRising - CountsForFirstFalling);
}
