/*
 * App_State.c
 * Definitions of the application state shared between the slave modules.
 */

#include "App_State.h"

volatile u16 G_u16PassLedTimerCount = 0;
volatile u8  G_u8PassLedIsOpen      = 0;
volatile u16 G_u16RoomCount         = 0;
volatile u8  G_u8LightManualMode    = 0;
volatile u8  G_u8RoomLedManualMode  = 0;
