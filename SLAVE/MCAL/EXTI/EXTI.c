/*
 * EXTI.c

 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EXTI.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Global Array of Pointers to Functions for EXTI0, EXTI1, EXTI2 */
static void (*ptr_EXTI[3])(void) = {NULL, NULL, NULL};

void EXTI0_Init(u8 Sense)
{
    switch (Sense)
    {
    case FALING_EDGE_SENSE:
        SET_BIT(MCUCR, ISC01);
        CLR_BIT(MCUCR, ISC00);
        break;
    case RISING_EDGE_SENSE:
        SET_BIT(MCUCR, ISC01);
        SET_BIT(MCUCR, ISC00);
        break;
    case ON_CHANGE_SENSE:
        CLR_BIT(MCUCR, ISC01);
        SET_BIT(MCUCR, ISC00);
        break;
    case LOW_LEVEL_SENSE:
        CLR_BIT(MCUCR, ISC01);
        CLR_BIT(MCUCR, ISC00);
        break;
    }

    /* Enable Global Interrupt & Peripheral Interrupt for INT0 */
    SET_BIT(SREG, I_BIT);
    SET_BIT(GICR, INT0);
}

void EXTI1_Init(u8 Sense)
{
    switch (Sense)
    {
    case FALING_EDGE_SENSE:
        SET_BIT(MCUCR, ISC11);
        CLR_BIT(MCUCR, ISC10);
        break;
    case RISING_EDGE_SENSE:
        SET_BIT(MCUCR, ISC11);
        SET_BIT(MCUCR, ISC10);
        break;
    case ON_CHANGE_SENSE:
        CLR_BIT(MCUCR, ISC11);
        SET_BIT(MCUCR, ISC10);
        break;
    case LOW_LEVEL_SENSE:
        CLR_BIT(MCUCR, ISC11);
        CLR_BIT(MCUCR, ISC10);
        break;
    }

    /* Enable Global Interrupt & Peripheral Interrupt for INT1 */
    SET_BIT(SREG, I_BIT);
    SET_BIT(GICR, INT1);
}

void EXTI2_Init(u8 Sense)
{
    switch (Sense)
    {
    case FALING_EDGE_SENSE:
        CLR_BIT(MCUCSR, ISC2);
        break;
    case RISING_EDGE_SENSE:
        SET_BIT(MCUCSR, ISC2);
        break;
    }

    /* Enable Global Interrupt & Peripheral Interrupt for INT2 */
    SET_BIT(SREG, I_BIT);
    SET_BIT(GICR, INT2);
}

void EXTI0_CallBack(void (*fptr)(void))
{
    if (fptr != NULL)
    {
        ptr_EXTI[0] = fptr;
    }
}

void EXTI1_CallBack(void (*fptr)(void))
{
    if (fptr != NULL)
    {
        ptr_EXTI[1] = fptr;
    }
}

void EXTI2_CallBack(void (*fptr)(void))
{
    if (fptr != NULL)
    {
        ptr_EXTI[2] = fptr;
    }
}

/* ISR for INT0 */
void __vector_1(void) __attribute__((signal, used));
void __vector_1(void)
{
    if (ptr_EXTI[0] != NULL)
    {
        ptr_EXTI[0]();
    }
}

/* ISR for INT1 */
void __vector_2(void) __attribute__((signal, used));
void __vector_2(void)
{
    if (ptr_EXTI[1] != NULL)
    {
        ptr_EXTI[1]();
    }
}

/* ISR for INT2 */
void __vector_3(void) __attribute__((signal, used));
void __vector_3(void)
{
    if (ptr_EXTI[2] != NULL)
    {
        ptr_EXTI[2]();
    }
}
