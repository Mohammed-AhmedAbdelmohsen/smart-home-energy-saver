/*

 * RAIN_SENSOR.c
 *

*/



#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO.h"
#include "RAIN_SENSOR.h"

void RAIN_SENSOR_Init(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    DIO_InitPin(Copy_u8Port, Copy_u8Pin, DIO_INPUT);
}

u8 RAIN_SENSOR_u8GetStatus(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    u8 Local_u8PinVal = DIO_HIGH;
    u8 Local_u8RainStatus = RAIN_NOT_DETECTED;

    Local_u8PinVal=DIO_ReadPinValue(Copy_u8Port, Copy_u8Pin);

    if (Local_u8PinVal == DIO_LOW)
    {
        Local_u8RainStatus = RAIN_DETECTED;
    }
    else
    {
        Local_u8RainStatus = RAIN_NOT_DETECTED;
    }

    return Local_u8RainStatus;
}
