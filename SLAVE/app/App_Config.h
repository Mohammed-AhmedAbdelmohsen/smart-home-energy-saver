/*
 * App_Config.h
 * Application-level configuration (addresses, pins, thresholds, timings).
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/Servo/Servo.h"

/* --- Communication --- */
#define SLAVE_I2C_ADDRESS     0x20

/* --- Rain sensor --- */
#define RAIN_SENSOR_PORT      DIO_PORTC
#define RAIN_SENSOR_PIN       DIO_PIN2

/* --- Indicator LEDs --- */
#define PASS_LED_PORT         DIO_PORTC
#define PASS_LED_PIN          DIO_PIN3    /* Correct password confirmation LED */

#define RAIN_LED_PORT         DIO_PORTC
#define RAIN_LED_PIN          DIO_PIN5    /* Rain detection LED */

#define LIGHT_LED_PORT        DIO_PORTC
#define LIGHT_LED_PIN         DIO_PIN4    /* External lighting LED */

/* --- Light sensor (LDR) --- */
#define LDR_PORT              DIO_PORTA
#define LDR_PIN               DIO_PIN0
#define LDR_ADC_CHANNEL       ADC_CHANNEL0
#define LDR_THRESHOLD         500

/* --- Keypad --- */
#define KEYPAD_PORT           DIO_PORTB
#define PASSWORD_LENGTH       4
#define PASSWORD_VALUE        "1234"

/* --- Door servo --- */
#define DOOR_SERVO_CHANNEL    SERVO_2     /* PD5 */
#define DOOR_OPEN_ANGLE       90
#define DOOR_CLOSED_ANGLE     0
#define DOOR_OPEN_TICKS       500         /* 500 * 10ms = 5s */

/* --- IR gate people counter (two beams, one gate) --- */
#define IR_OUTER_PORT         DIO_PORTD
#define IR_OUTER_PIN          DIO_PIN6    /* Outer gate sensor */

#define IR_INNER_PORT         DIO_PORTC
#define IR_INNER_PIN          DIO_PIN6    /* Inner gate sensor */

/* Gate state machine */
#define GATE_STATE_IDLE         0
#define GATE_STATE_OUTER_FIRST  1
#define GATE_STATE_INNER_FIRST  2
#define GATE_STATE_WAIT_CLEAR   3
#define GATE_TIMEOUT_TICKS      100       /* One second to pass */

/* --- Room-count LED bargraph --- */
#define ROOM_LED_PORT         DIO_PORTD
#define ROOM_LED0_PIN         DIO_PIN0
#define ROOM_LED1_PIN         DIO_PIN1
#define ROOM_LED2_PIN         DIO_PIN2
#define ROOM_LED3_PIN         DIO_PIN3
#define ROOM_LED_MAX          4

/* --- Timing --- */
#define APP_TICK_US           10000       /* Timer0 period: 10ms */
#define SENSORS_PERIOD_TICKS  10          /* Sensors polled every 100ms */

/* --- Commands received from the Master over I2C --- */
#define CMD_LIGHT_OFF         0x10
#define CMD_LIGHT_ON          0x11
#define CMD_LIGHT_AUTO        0x12
#define CMD_DOOR_CLOSE        0x20
#define CMD_DOOR_OPEN         0x21
#define CMD_ROOM_LEDS_0       0x30
#define CMD_ROOM_LEDS_1       0x31
#define CMD_ROOM_LEDS_2       0x32
#define CMD_ROOM_LEDS_3       0x33
#define CMD_ROOM_LEDS_4       0x34
#define CMD_ROOM_LEDS_AUTO    0x35

#endif /* APP_CONFIG_H_ */
