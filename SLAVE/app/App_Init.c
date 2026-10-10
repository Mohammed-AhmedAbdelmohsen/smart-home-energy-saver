/*
 * App_Init.c
 * System initialization for the slave MCU.
 */

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/Timer0/Timer0.h"
#include "../MCAL/I2C/I2C_Slave.h"
#include "../HAL/RAIN_SENSOR/RAIN_SENSOR.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KP/KP.h"
#include "../HAL/Servo/Servo.h"
#include "../HAL/IR_SENSOR/IR_SENSOR.h"
#include "App_Config.h"
#include "RoomCount.h"
#include "Slave_Tasks.h"
#include "App_Init.h"

static void Leds_Init(void)
{
    DIO_InitPin(PASS_LED_PORT, PASS_LED_PIN, DIO_OUTPUT);
    DIO_SetPinValue(PASS_LED_PORT, PASS_LED_PIN, DIO_LOW);

    DIO_InitPin(RAIN_LED_PORT, RAIN_LED_PIN, DIO_OUTPUT);
    DIO_SetPinValue(RAIN_LED_PORT, RAIN_LED_PIN, DIO_LOW);

    DIO_InitPin(LIGHT_LED_PORT, LIGHT_LED_PIN, DIO_OUTPUT);
    DIO_SetPinValue(LIGHT_LED_PORT, LIGHT_LED_PIN, DIO_LOW);

    /* Internal room LEDs (PD0..PD3) */
    DIO_InitPin(ROOM_LED_PORT, ROOM_LED0_PIN, DIO_OUTPUT);
    DIO_InitPin(ROOM_LED_PORT, ROOM_LED1_PIN, DIO_OUTPUT);
    DIO_InitPin(ROOM_LED_PORT, ROOM_LED2_PIN, DIO_OUTPUT);
    DIO_InitPin(ROOM_LED_PORT, ROOM_LED3_PIN, DIO_OUTPUT);
    RoomCount_LedUpdate();
}

void App_Init(void)
{
    /* 1. LCD and keypad */
    LCD_Init();
    KP_Init(KEYPAD_PORT);

    /* 2. Inputs */
    DIO_InitPin(LDR_PORT, LDR_PIN, DIO_INPUT);
    RAIN_SENSOR_Init(RAIN_SENSOR_PORT, RAIN_SENSOR_PIN);

    /* 3. LED outputs */
    Leds_Init();

    /* 4. ADC */
    ADC_Init(ADC_REFERANCE_AVCC);

    /* 5. Servo and IR sensors */
    Servo_Init();
    Servo_SetAngle(DOOR_SERVO_CHANNEL, DOOR_CLOSED_ANGLE);
    IR_SENSOR_Init(IR_OUTER_PORT, IR_OUTER_PIN);
    IR_SENSOR_Init(IR_INNER_PORT, IR_INNER_PIN);

    /* 6. I2C slave */
    I2C_SlaveInit(SLAVE_I2C_ADDRESS);

    LCD_ClrDisplay();
    LCD_WriteString((u8*)"Enter Pass: ");
    RoomCount_DisplayUpdate();

    /* 7. Periodic tick */
    Timer0_Init(TIMER0_PRESCALLER_64, TIMER0_OVF);
    Timer0_SetDesiredTime(APP_TICK_US, Slave_PeriodicTask);
}
