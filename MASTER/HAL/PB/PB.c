/*
 * PB.c

 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "PB.h"
#include "../../LIB/BIT_MATH.h"

void PB_Init(u8 PORT_Name, u8 PIN_Number, u8 PullUpState)
{
    /* Set Pin as Input */
    DIO_InitPin(PORT_Name, PIN_Number, DIO_INPUT);

    /* Configure Internal Pull-up Resistor */
    if (PullUpState == PB_PULL_UP_ENABLE)
    {
        DIO_SetPinValue(PORT_Name, PIN_Number, DIO_HIGH);
    }
    else
    {
        DIO_SetPinValue(PORT_Name, PIN_Number, DIO_LOW);
    }
}

u8 PB_ReadStatus(u8 PORT_Name, u8 PIN_Number)
{
    return DIO_ReadPinValue(PORT_Name, PIN_Number);
}
