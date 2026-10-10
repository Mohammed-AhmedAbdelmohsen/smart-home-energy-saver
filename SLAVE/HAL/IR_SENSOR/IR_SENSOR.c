/*
 * IR_SENSOR.c
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "IR_SENSOR.h"


void IR_SENSOR_Init(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    DIO_InitPin(Copy_u8Port, Copy_u8Pin, DIO_INPUT);
}

u8 IR_SENSOR_u8GetStatus(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    u8 Local_u8PinVal = DIO_ReadPinValue(Copy_u8Port, Copy_u8Pin);
    u8 Local_u8Status;

    /* Active-low: module pulls OUT to 0V when it sees an object/break */
    if (Local_u8PinVal == DIO_LOW)
    {
        Local_u8Status = IR_OBJECT_DETECTED;
    }
    else
    {
        Local_u8Status = IR_NO_OBJECT;
    }

    return Local_u8Status;
}
