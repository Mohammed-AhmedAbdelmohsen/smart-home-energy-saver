/*
 * Slave_Commands.c
 * Reception and execution of Master commands over I2C.
 */

#include <avr/io.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/I2C/I2C_Slave.h"
#include "../HAL/Servo/Servo.h"
#include "App_Config.h"
#include "App_State.h"
#include "RoomCount.h"
#include "Slave_Commands.h"

/* Execute commands received from Master via I2C */
void Slave_ExecuteCommand(u8 Command)
{
    switch (Command)
    {
        /* External lighting */
        case CMD_LIGHT_ON:   /* Manual ON, enter override mode */
            G_u8LightManualMode = 1;
            DIO_SetPinValue(LIGHT_LED_PORT, LIGHT_LED_PIN, DIO_HIGH);
            break;

        case CMD_LIGHT_OFF:  /* Manual OFF, enter override mode */
            G_u8LightManualMode = 1;
            DIO_SetPinValue(LIGHT_LED_PORT, LIGHT_LED_PIN, DIO_LOW);
            break;

        case CMD_LIGHT_AUTO: /* Exit override mode, return to LDR control */
            G_u8LightManualMode = 0;
            break;

        /* Door servo */
        case CMD_DOOR_OPEN:
            Servo_SetAngle(DOOR_SERVO_CHANNEL, DOOR_OPEN_ANGLE);
            DIO_SetPinValue(PASS_LED_PORT, PASS_LED_PIN, DIO_HIGH);
            G_u8PassLedIsOpen = 1;
            G_u16PassLedTimerCount = 0;
            break;

        case CMD_DOOR_CLOSE:
            Servo_SetAngle(DOOR_SERVO_CHANNEL, DOOR_CLOSED_ANGLE);
            DIO_SetPinValue(PASS_LED_PORT, PASS_LED_PIN, DIO_LOW);
            G_u8PassLedIsOpen = 0;
            break;

        /* Internal LEDs (manual override mode) */
        case CMD_ROOM_LEDS_0:
        case CMD_ROOM_LEDS_1:
        case CMD_ROOM_LEDS_2:
        case CMD_ROOM_LEDS_3:
        case CMD_ROOM_LEDS_4:
            G_u8RoomLedManualMode = 1;
            RoomCount_LedsSet(Command - CMD_ROOM_LEDS_0);
            break;

        case CMD_ROOM_LEDS_AUTO: /* Exit override mode, return to IR control */
            G_u8RoomLedManualMode = 0;
            RoomCount_LedUpdate();
            break;

        default:
            break;
    }
}

/* Non-blocking check for I2C data reception */
void Slave_CheckI2C(void)
{
    if (READ_BIT(TWCR, TWINT) == 1)
    {
        if ((TWSR & 0xF8) == I2C_SLAVE_OWN_SLA_W_RECEIVED)
        {
            u8 Cmd = I2C_SlaveReadByte();
            Slave_ExecuteCommand(Cmd);
        }
        else
        {
            TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
        }
    }
}
