/*
 * 7SEG.c
 
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "7SEG.h"
#include "../../LIB/BIT_MATH.h"

static const u8 SEG_arr[10] =
{
    0x3F,   /* 0 */
    0x06,   /* 1 */
    0x5B,   /* 2 */
    0x4F,   /* 3 */
    0x66,   /* 4 */
    0x6D,   /* 5 */
    0x7D,   /* 6 */
    0x07,   /* 7 */
    0x7F,   /* 8 */
    0x6F    /* 9 */
};

void SEG_Init(u8 PORT_Name)
{
    /* Configure all pins of the selected port as OUTPUT */
    DIO_InitPort(PORT_Name, 0xFF);
}

void SEG_WriteNumber(u8 PORT_Name, u8 Num, u8 Type)
{
    if (Num <= 9)
    {
        if (Type == COMMON_CATHODE)
        {
            DIO_SetPortValue(PORT_Name, SEG_arr[Num]);
        }
        else if (Type == COMMON_ANODE)
        {
            DIO_SetPortValue(PORT_Name, ~SEG_arr[Num]);
        }
    }
}
