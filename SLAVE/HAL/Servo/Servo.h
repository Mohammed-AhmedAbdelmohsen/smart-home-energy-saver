/*
 * Servo.h

 */

#ifndef HAL_SERVO_SERVO_H_
#define HAL_SERVO_SERVO_H_

#include "../../LIB/STD_TYPES.h"

#define SERVO_1    1  /* المظلة (Awning) على PD4 - OC1B */
#define SERVO_2    2  /* الباب (Door) على PD5 - OC1A */

void Servo_Init(void);
void Servo_SetAngle(u8 Servo_Channel, u8 Angle);

#endif /* HAL_SERVO_SERVO_H_ */
