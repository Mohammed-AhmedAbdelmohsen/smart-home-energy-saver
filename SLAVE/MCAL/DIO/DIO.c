/*
 * DIO.c
 *

 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO.h"

void DIO_InitPin(u8 PORT_Name, u8 PIN_Number, u8 Mode)
{
    if (PIN_Number > 7) return;

    switch (PORT_Name)
    {
    case DIO_PORTA:
        if (Mode == DIO_INPUT)
        {
            CLR_BIT(DDRA, PIN_Number);
            CLR_BIT(PORTA, PIN_Number); /* Floating */
        }
        else if (Mode == DIO_OUTPUT)
        {
            SET_BIT(DDRA, PIN_Number);
        }
        else if (Mode == DIO_INPUT_PULLUP)
        {
            CLR_BIT(DDRA, PIN_Number);
            SET_BIT(PORTA, PIN_Number); /* Enable Internal Pull-up */
        }
        break;

    case DIO_PORTB:
        if (Mode == DIO_INPUT)
        {
            CLR_BIT(DDRB, PIN_Number);
            CLR_BIT(PORTB, PIN_Number);
        }
        else if (Mode == DIO_OUTPUT)
        {
            SET_BIT(DDRB, PIN_Number);
        }
        else if (Mode == DIO_INPUT_PULLUP)
        {
            CLR_BIT(DDRB, PIN_Number);
            SET_BIT(PORTB, PIN_Number);
        }
        break;

    case DIO_PORTC:
        if (Mode == DIO_INPUT)
        {
            CLR_BIT(DDRC, PIN_Number);
            CLR_BIT(PORTC, PIN_Number);
        }
        else if (Mode == DIO_OUTPUT)
        {
            SET_BIT(DDRC, PIN_Number);
        }
        else if (Mode == DIO_INPUT_PULLUP)
        {
            CLR_BIT(DDRC, PIN_Number);
            SET_BIT(PORTC, PIN_Number);
        }
        break;

    case DIO_PORTD:
        if (Mode == DIO_INPUT)
        {
            CLR_BIT(DDRD, PIN_Number);
            CLR_BIT(PORTD, PIN_Number);
        }
        else if (Mode == DIO_OUTPUT)
        {
            SET_BIT(DDRD, PIN_Number);
        }
        else if (Mode == DIO_INPUT_PULLUP)
        {
            CLR_BIT(DDRD, PIN_Number);
            SET_BIT(PORTD, PIN_Number);
        }
        break;
    }
}

void DIO_SetPinValue(u8 PORT_Name, u8 PIN_Number, u8 Val)
{
    if (PIN_Number > 7) return;

    switch (PORT_Name)
    {
    case DIO_PORTA:
        if (Val == DIO_LOW)       CLR_BIT(PORTA, PIN_Number);
        else if (Val == DIO_HIGH) SET_BIT(PORTA, PIN_Number);
        break;
    case DIO_PORTB:
        if (Val == DIO_LOW)       CLR_BIT(PORTB, PIN_Number);
        else if (Val == DIO_HIGH) SET_BIT(PORTB, PIN_Number);
        break;
    case DIO_PORTC:
        if (Val == DIO_LOW)       CLR_BIT(PORTC, PIN_Number);
        else if (Val == DIO_HIGH) SET_BIT(PORTC, PIN_Number);
        break;
    case DIO_PORTD:
        if (Val == DIO_LOW)       CLR_BIT(PORTD, PIN_Number);
        else if (Val == DIO_HIGH) SET_BIT(PORTD, PIN_Number);
        break;
    }
}

void DIO_TogPinValue(u8 PORT_Name, u8 PIN_Number)
{
    if (PIN_Number > 7) return;

    switch (PORT_Name)
    {
    case DIO_PORTA: TOG_BIT(PORTA, PIN_Number); break;
    case DIO_PORTB: TOG_BIT(PORTB, PIN_Number); break;
    case DIO_PORTC: TOG_BIT(PORTC, PIN_Number); break;
    case DIO_PORTD: TOG_BIT(PORTD, PIN_Number); break;
    }
}

u8 DIO_ReadPinValue(u8 PORT_Name, u8 PIN_Number)
{
    u8 PinValue = 0;
    if (PIN_Number > 7) return 0;

    switch (PORT_Name)
    {
    case DIO_PORTA: PinValue = READ_BIT(PINA, PIN_Number); break;
    case DIO_PORTB: PinValue = READ_BIT(PINB, PIN_Number); break;
    case DIO_PORTC: PinValue = READ_BIT(PINC, PIN_Number); break;
    case DIO_PORTD: PinValue = READ_BIT(PIND, PIN_Number); break;
    }
    return PinValue;
}

void DIO_InitPort(u8 PORT_Name, u8 Mode)
{
    switch (PORT_Name)
    {
    case DIO_PORTA: DDRA = Mode; break;
    case DIO_PORTB: DDRB = Mode; break;
    case DIO_PORTC: DDRC = Mode; break;
    case DIO_PORTD: DDRD = Mode; break;
    }
}

void DIO_SetPortValue(u8 PORT_Name, u8 Val)
{
    switch (PORT_Name)
    {
    case DIO_PORTA: PORTA = Val; break;
    case DIO_PORTB: PORTB = Val; break;
    case DIO_PORTC: PORTC = Val; break;
    case DIO_PORTD: PORTD = Val; break;
    }
}

void DIO_TogPortValue(u8 PORT_Name)
{
    switch (PORT_Name)
    {
    case DIO_PORTA: PORTA = ~PORTA; break;
    case DIO_PORTB: PORTB = ~PORTB; break;
    case DIO_PORTC: PORTC = ~PORTC; break;
    case DIO_PORTD: PORTD = ~PORTD; break;
    }
}

u8 DIO_ReadPortValue(u8 PORT_Name)
{
    u8 PortVal = 0;
    switch (PORT_Name)
    {
    case DIO_PORTA: PortVal = PINA; break;
    case DIO_PORTB: PortVal = PINB; break;
    case DIO_PORTC: PortVal = PINC; break;
    case DIO_PORTD: PortVal = PIND; break;
    }
    return PortVal;
}
