/*
 * Servo.c

 */

#include <avr/io.h>
#include "../../LIB/STD_TYPES.h"
#include "Servo.h"

void Servo_Init(void)
{
    DDRD |= (1 << PD4) | (1 << PD5);

    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); /* Prescaler = 8 */

    ICR1 = 20000;

    OCR1A = 1000; /* PD5 - Servo 2 */
    OCR1B = 1000; /* PD4 - Servo 1 */
}

void Servo_SetAngle(u8 Servo_Channel, u8 Angle)
{
    if (Angle > 180) Angle = 180;

    u16 Ticks = 1000 + (((u32)Angle * 1000UL) / 180UL);

    if (Servo_Channel == SERVO_1)
    {
        OCR1B = Ticks;
    }
    else if (Servo_Channel == SERVO_2)
    {
        OCR1A = Ticks;
    }
}
