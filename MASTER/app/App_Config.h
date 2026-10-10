/*
 * App_Config.h
 * Application-level configuration (addresses, pins, timings, commands).
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"

/* --- Pins / channels --- */
#define FAN_LED_PORT          DIO_PORTC
#define FAN_LED_PIN           DIO_PIN2
#define LM35_ADC_CHANNEL      ADC_CHANNEL0
#define KEYPAD_PORT           DIO_PORTB

/* --- Communication --- */
#define SLAVE_I2C_ADDRESS     0x20
#define I2C_BUS_SPEED_HZ      100000

/* --- Temperature --- */
#define DEFAULT_SET_TEMP      25
#define MAX_SET_TEMP          100
#define MAX_TEMP_DIGITS       3
#define LM35_SCALE_NUM        410UL     /* temp = adc * 410 / 1024 */
#define LM35_SCALE_DEN        1024UL

/* --- Timing --- */
#define APP_TICK_US           10000     /* Timer0 period: 10ms */
#define TEMP_PERIOD_TICKS     20        /* Temperature read every 200ms */

/* --- Commands sent to the Slave over I2C --- */
#define SLAVE_CMD_LIGHT_OFF       0x10
#define SLAVE_CMD_LIGHT_ON        0x11
#define SLAVE_CMD_LIGHT_AUTO      0x12
#define SLAVE_CMD_DOOR_CLOSE      0x20
#define SLAVE_CMD_DOOR_OPEN       0x21
#define SLAVE_CMD_ROOM_LEDS_0     0x30
#define SLAVE_CMD_ROOM_LEDS_1     0x31
#define SLAVE_CMD_ROOM_LEDS_2     0x32
#define SLAVE_CMD_ROOM_LEDS_3     0x33
#define SLAVE_CMD_ROOM_LEDS_4     0x34
#define SLAVE_CMD_ROOM_LEDS_AUTO  0x35

#endif /* APP_CONFIG_H_ */
