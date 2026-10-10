/*
 * RoomCount.h
 * Room occupancy display (LCD) and LED bargraph.
 */

#ifndef ROOMCOUNT_H_
#define ROOMCOUNT_H_

void RoomCount_DisplayUpdate(void);
void RoomCount_LedUpdate(void);
void RoomCount_LedsSet(u8 Copy_u8Level);  /* Manual bargraph level (0..ROOM_LED_MAX) */

#endif /* ROOMCOUNT_H_ */
