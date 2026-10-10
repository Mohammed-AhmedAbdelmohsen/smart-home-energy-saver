/*
 * HCSR04.c
 * Software (bit-banged) HC-SR04 ultrasonic distance driver.
 */

#include <util/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "HCSR04.h"

/* The sensor itself times out and drops ECHO low after ~38ms if it
 * never sees a return pulse. 30ms of software timeout is comfortably
 * inside that, so we never hang forever on a disconnected/faulty sensor. */
#define HCSR04_TIMEOUT_US   30000UL

void HCSR04_Init(u8 TrigPort, u8 TrigPin, u8 EchoPort, u8 EchoPin)
{
    DIO_InitPin(TrigPort, TrigPin, DIO_OUTPUT);
    DIO_SetPinValue(TrigPort, TrigPin, DIO_LOW);
    DIO_InitPin(EchoPort, EchoPin, DIO_INPUT);
}

u16 HCSR04_u16GetDistanceCM(u8 TrigPort, u8 TrigPin, u8 EchoPort, u8 EchoPin)
{
    u32 Local_u32TimeUs;

    /* 1. Send a clean 10us trigger pulse */
    DIO_SetPinValue(TrigPort, TrigPin, DIO_HIGH);
    _delay_us(10);
    DIO_SetPinValue(TrigPort, TrigPin, DIO_LOW);

    /* 2. Wait for ECHO to rise (start of the return pulse) */
    Local_u32TimeUs = 0;
    while (DIO_ReadPinValue(EchoPort, EchoPin) == DIO_LOW)
    {
        _delay_us(1);
        Local_u32TimeUs++;
        if (Local_u32TimeUs >= HCSR04_TIMEOUT_US)
        {
            return HCSR04_NO_ECHO;   /* sensor not responding at all */
        }
    }

    /* 3. Measure how long ECHO stays high (the round-trip time) */
    Local_u32TimeUs = 0;
    while (DIO_ReadPinValue(EchoPort, EchoPin) == DIO_HIGH)
    {
        _delay_us(1);
        Local_u32TimeUs++;
        if (Local_u32TimeUs >= HCSR04_TIMEOUT_US)
        {
            return HCSR04_NO_ECHO;   /* out of range, nothing reflected back */
        }
    }

    /* 4. distance_cm = round_trip_time_us / 58  (speed of sound ~343 m/s) */
    return (u16)(Local_u32TimeUs / 58UL);
}
