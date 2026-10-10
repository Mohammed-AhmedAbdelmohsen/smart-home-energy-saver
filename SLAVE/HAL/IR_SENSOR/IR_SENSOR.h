/*
 * IR_SENSOR.h
 * Simple digital IR obstacle-detector driver (e.g. the common
 * 3-pin "IR obstacle avoidance" module: VCC, GND, OUT).
 *
 * Replaces the two HC-SR04 ultrasonic sensors that used to sit at the
 * gate. An IR module only needs ONE digital pin (its OUT pin) instead
 * of the HC-SR04's TRIG+ECHO pair, and the read is a plain, instant
 * GPIO read - no microsecond timing, no blocking loops. That means it
 * is safe to poll from inside a timer ISR, unlike HCSR04_u16GetDistanceCM().
 *
 * Most of these modules pull OUT LOW when they see an object/beam
 * break, and HIGH when clear (active-low, open-collector-style output,
 * same convention already used by RAIN_SENSOR.c in this codebase).
 */

#ifndef HAL_IR_SENSOR_IR_SENSOR_H_
#define HAL_IR_SENSOR_IR_SENSOR_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

#define IR_NO_OBJECT      0
#define IR_OBJECT_DETECTED 1

void IR_SENSOR_Init(u8 Copy_u8Port, u8 Copy_u8Pin);
u8   IR_SENSOR_u8GetStatus(u8 Copy_u8Port, u8 Copy_u8Pin);


#endif /* HAL_IR_SENSOR_IR_SENSOR_H_ */
