/*
 * App_Init.c
 * System initialization for the master MCU.
 */

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/Timer0/Timer0.h"
#include "../MCAL/I2C/I2C_Master.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KP/KP.h"
#include "../HAL/BLUETOOTH/BLUETOOTH.h"
#include "App_Config.h"
#include "Master_Tasks.h"
#include "App_Init.h"

void App_Init(void)
{
    /* Input and output pins */
    DIO_InitPin(FAN_LED_PORT, FAN_LED_PIN, DIO_OUTPUT);
    DIO_SetPinValue(FAN_LED_PORT, FAN_LED_PIN, DIO_LOW);

    /* Basic peripherals */
    ADC_init(ADC_REFERANCE_AVCC);
    LCD_Init();
    KP_Init(KEYPAD_PORT);
    I2C_MasterInit(I2C_BUS_SPEED_HZ);
    Bluetooth_Init();

    LCD_ClrDisplay();
    LCD_WriteString((u8*)"Smart Home Ready");

    /* Periodic interrupt every 10ms */
    Timer0_Init(TIMER0_PRESCALLER_64, TIMER0_OVF);
    Timer0_SetDesiredTime(APP_TICK_US, Master_PeriodicTask);
}
