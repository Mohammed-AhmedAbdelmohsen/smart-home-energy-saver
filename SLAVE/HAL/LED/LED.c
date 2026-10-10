/*
 * LED.c
 *

 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "LED.h"

void LED_Init(u8 LedPort, u8 LedPin)
{
    DIO_InitPin(LedPort, LedPin, DIO_OUTPUT);
}

void LED_On(u8 LedPort, u8 LedPin)
{
    DIO_SetPinValue(LedPort, LedPin, DIO_HIGH);
}

void LED_Off(u8 LedPort, u8 LedPin)
{
    DIO_SetPinValue(LedPort, LedPin, DIO_LOW);
}

void LED_Tog(u8 LedPort, u8 LedPin)
{
    DIO_TogPinValue(LedPort, LedPin);
}

u8 LED_u8IsLedOn(u8 LedPort, u8 LedPin)
{
    return (DIO_ReadPinValue(LedPort, LedPin) == DIO_HIGH) ? LED_STATE_ON : LED_STATE_OFF;
}
