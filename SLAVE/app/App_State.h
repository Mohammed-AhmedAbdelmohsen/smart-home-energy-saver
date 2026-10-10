/*
 * App_State.h
 * Application state shared between the slave modules.
 */

#ifndef APP_STATE_H_
#define APP_STATE_H_

#include "../LIB/STD_TYPES.h"

extern volatile u16 G_u16PassLedTimerCount;
extern volatile u8  G_u8PassLedIsOpen;
extern volatile u16 G_u16RoomCount;
extern volatile u8  G_u8LightManualMode;    /* External lighting override */
extern volatile u8  G_u8RoomLedManualMode;  /* Internal LEDs override     */

#endif /* APP_STATE_H_ */
