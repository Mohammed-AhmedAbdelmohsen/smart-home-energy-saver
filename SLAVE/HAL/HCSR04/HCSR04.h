/*
 * HCSR04.h
 * Simple software (bit-banged) HC-SR04 ultrasonic distance driver.
 *
 * Why not use the Timer1 Input Capture Unit (Timer1_CaptureTonCounts)?
 * -> Timer1 is already running the servo PWM (Fast-PWM Mode 14, TOP = ICR1).
 *    The ICU also writes into ICR1 on every capture event, which would
 *    stomp on the PWM TOP value and glitch the servo. So this driver
 *    measures the echo pulse purely in software on any free GPIO pins,
 *    leaving Timer1 alone for the servo.
 *
 * IMPORTANT: HCSR04_u16GetDistanceCM() is a BLOCKING call (up to ~30ms
 * worst case). Only call it from the main while(1) loop, never from
 * inside a Timer ISR/callback, or you will stall everything else
 * (keypad, LCD, servo timing) that depends on that interrupt.
 */

#ifndef HAL_HCSR04_HCSR04_H_
#define HAL_HCSR04_HCSR04_H_

#include "../../LIB/STD_TYPES.h"

/* Returned when no echo comes back in time (out of range / bad wiring) */
#define HCSR04_NO_ECHO   0xFFFFU

void HCSR04_Init(u8 TrigPort, u8 TrigPin, u8 EchoPort, u8 EchoPin);
u16  HCSR04_u16GetDistanceCM(u8 TrigPort, u8 TrigPin, u8 EchoPort, u8 EchoPin);

#endif /* HAL_HCSR04_HCSR04_H_ */
