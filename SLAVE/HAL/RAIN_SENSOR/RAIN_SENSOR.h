/*
 * RAIN_SENSOR.h
 *

 */

#ifndef HAL_RAIN_SENSOR_RAIN_SENSOR_H_
#define HAL_RAIN_SENSOR_RAIN_SENSOR_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

#define RAIN_NOT_DETECTED       0
#define RAIN_DETECTED           1

void RAIN_SENSOR_Init(u8 Copy_u8Port, u8 Copy_u8Pin);
u8   RAIN_SENSOR_u8GetStatus(u8 Copy_u8Port, u8 Copy_u8Pin);

#endif /* HAL_RAIN_SENSOR_RAIN_SENSOR_H_ */
