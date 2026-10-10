/*
 * Timer0.c

 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO.h"
#include "Timer0.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

static u32 G0_Prescaller = 1;
static u32 G0_Counts = 0;
static u8  G_Preload = 0;
static void (*Timer0_OVF_ptr)(void) = NULL;
static void (*Timer0_CTC_ptr)(void) = NULL;

void Timer0_Init(u32 Prescaller, u8 Mode)
{
    G0_Prescaller = Prescaller;

    /* 1. Set Timer Prescaler */
    switch (Prescaller)
    {
    case TIMER0_PRESCALLER_1:
        CLR_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
        break;
    case TIMER0_PRESCALLER_8:
        CLR_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); CLR_BIT(TCCR0, CS00);
        break;
    case TIMER0_PRESCALLER_64:
        CLR_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
        break;
    case TIMER0_PRESCALLER_256:
        SET_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); CLR_BIT(TCCR0, CS00);
        break;
    case TIMER0_PRESCALLER_1024:
        SET_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
        break;
    }

    /* 2. Select Waveform Generation Mode */
    switch (Mode)
    {
    case TIMER0_OVF:
        CLR_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        SET_BIT(TIMSK, TOIE0);
        break;

    case TIMER0_CTC:
        CLR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        SET_BIT(TIMSK, OCIE0);
        break;

    case TIMER0_FAST_PWM:
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        SET_BIT(TCCR0, COM01);
        CLR_BIT(TCCR0, COM00);
        DIO_InitPin(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
        break;

    case TIMER0_PHASE_CORRECT:
        SET_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        SET_BIT(TCCR0, COM01);
        CLR_BIT(TCCR0, COM00);
        DIO_InitPin(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
        break;
    }

    /* Enable Global Interrupt */
    SET_BIT(SREG, I_BIT);
}

void Timer0_SetDesiredTime(u32 TimeInMicro, void (*fptr)(void))
{
    /* At 8 MHz: Tick time = (Prescaler / 8) us -> OVF_Time = 256 * Tick = 32 * Prescaler us */
    f32 OVF_Time = 32.0f * (f32)G0_Prescaller;
    f32 Desired_OVF_Counts = (f32)TimeInMicro / OVF_Time;

    Timer0_OVF_ptr = fptr;

    if (Desired_OVF_Counts < 1.0f)
    {
        G0_Counts = 1;
        G_Preload = (u8)(256.0f - (256.0f * Desired_OVF_Counts));
        TCNT0 = G_Preload;
    }
    else if (Desired_OVF_Counts == 1.0f)
    {
        G0_Counts = 1;
        G_Preload = 0;
        TCNT0 = 0;
    }
    else
    {
        G0_Counts = (u32)Desired_OVF_Counts;
        f32 Fraction = Desired_OVF_Counts - (f32)G0_Counts;

        if (Fraction != 0.0f)
        {
            G_Preload = (u8)(256.0f - (256.0f * Fraction));
            TCNT0 = G_Preload;
            G0_Counts++;
        }
        else
        {
            G_Preload = 0;
            TCNT0 = 0;
        }
    }
}

void Timer0_GeneratePWM(u8 CompareValue)
{
    OCR0 = CompareValue;
}

void Timer0_SetCTCCallback(void (*fptr)(void))
{
    if (fptr != NULL)
    {
        Timer0_CTC_ptr = fptr;
    }
}

/* ISR for Timer0 Compare Match (CTC) */
void __vector_10(void) __attribute__((signal, used));
void __vector_10(void)
{
    if (Timer0_CTC_ptr != NULL)
    {
        Timer0_CTC_ptr();
    }
}

/* ISR for Timer0 Overflow (OVF) */
void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
    static u32 Counter = 0;
    Counter++;

    if (Counter >= G0_Counts)
    {
        TCNT0 = G_Preload;
        Counter = 0;

        if (Timer0_OVF_ptr != NULL)
        {
            Timer0_OVF_ptr();
        }
    }
}
