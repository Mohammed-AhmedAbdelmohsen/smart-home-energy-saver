/*
 * RoomCount.c
 * Room occupancy display (LCD) and LED bargraph.
 */

#include <stdio.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../HAL/LCD/LCD.h"
#include "App_Config.h"
#include "App_State.h"
#include "RoomCount.h"

void RoomCount_LedsSet(u8 Copy_u8Level)
{
    DIO_SetPinValue(ROOM_LED_PORT, ROOM_LED0_PIN, (Copy_u8Level >= 1) ? DIO_HIGH : DIO_LOW);
    DIO_SetPinValue(ROOM_LED_PORT, ROOM_LED1_PIN, (Copy_u8Level >= 2) ? DIO_HIGH : DIO_LOW);
    DIO_SetPinValue(ROOM_LED_PORT, ROOM_LED2_PIN, (Copy_u8Level >= 3) ? DIO_HIGH : DIO_LOW);
    DIO_SetPinValue(ROOM_LED_PORT, ROOM_LED3_PIN, (Copy_u8Level >= 4) ? DIO_HIGH : DIO_LOW);
}

void RoomCount_DisplayUpdate(void)
{
    char Buf[6];
    LCD_Move_Cursor(1, 11);
    sprintf(Buf, "N:%3u", G_u16RoomCount);
    LCD_WriteString((u8*)Buf);
}

void RoomCount_LedUpdate(void)
{
    u16 Local_u16Lit = (G_u16RoomCount > ROOM_LED_MAX) ? ROOM_LED_MAX : G_u16RoomCount;
    RoomCount_LedsSet((u8)Local_u16Lit);
}
