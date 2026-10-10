/*
 * Slave_Tasks.c
 * Periodic application tasks (run from the Timer0 10ms tick):
 * keypad/password handling, door auto-close, sensors and gate counting.
 */

#include <string.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/RAIN_SENSOR/RAIN_SENSOR.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KP/KP.h"
#include "../HAL/Servo/Servo.h"
#include "App_Config.h"
#include "App_State.h"
#include "RoomCount.h"
#include "Gate.h"
#include "Slave_Tasks.h"

static u8   L_u8LastKey   = KP_NOT_PRESSED;
static u8   L_u8PassIndex = 0;
static char L_strPassBuffer[PASSWORD_LENGTH + 1] = {0};

static void Password_Reset(void)
{
    L_u8PassIndex = 0;
    memset(L_strPassBuffer, 0, sizeof(L_strPassBuffer));
}

static void Screen_ShowPrompt(void)
{
    LCD_ClrDisplay();
    LCD_WriteString((u8*)"Enter Pass: ");
    RoomCount_DisplayUpdate();
}

static void Keypad_Task(void)
{
    u8 Key = KP_GetVal(KEYPAD_PORT);

    if (Key != KP_NOT_PRESSED && Key != L_u8LastKey)
    {
        if (Key >= '0' && Key <= '9')
        {
            if (L_u8PassIndex < PASSWORD_LENGTH)
            {
                L_strPassBuffer[L_u8PassIndex] = Key;
                LCD_Move_Cursor(1, L_u8PassIndex);
                LCD_WriteData('*');
                L_u8PassIndex++;
            }
        }
        else if (Key == '=')
        {
            L_strPassBuffer[L_u8PassIndex] = '\0';
            if (strcmp(L_strPassBuffer, PASSWORD_VALUE) == 0)
            {
                LCD_ClrDisplay();
                LCD_WriteString((u8*)"Correct Pass!");

                DIO_SetPinValue(PASS_LED_PORT, PASS_LED_PIN, DIO_HIGH);
                Servo_SetAngle(DOOR_SERVO_CHANNEL, DOOR_OPEN_ANGLE);
                G_u8PassLedIsOpen = 1;
                G_u16PassLedTimerCount = 0;
            }
            else
            {
                LCD_ClrDisplay();
                LCD_WriteString((u8*)"Wrong Pass!");
            }
            Password_Reset();
        }
        else if (Key == 'C' || Key == 'N')
        {
            Password_Reset();
            Screen_ShowPrompt();
        }
    }
    L_u8LastKey = Key;
}

/* Close the door after DOOR_OPEN_TICKS */
static void Door_Task(void)
{
    if (G_u8PassLedIsOpen)
    {
        G_u16PassLedTimerCount++;
        if (G_u16PassLedTimerCount >= DOOR_OPEN_TICKS)
        {
            DIO_SetPinValue(PASS_LED_PORT, PASS_LED_PIN, DIO_LOW);
            Servo_SetAngle(DOOR_SERVO_CHANNEL, DOOR_CLOSED_ANGLE);
            G_u8PassLedIsOpen = 0;
            G_u16PassLedTimerCount = 0;
            Screen_ShowPrompt();
        }
    }
}

static void Sensors_Task(void)
{
    if (RAIN_SENSOR_u8GetStatus(RAIN_SENSOR_PORT, RAIN_SENSOR_PIN) == RAIN_DETECTED)
    {
        DIO_SetPinValue(RAIN_LED_PORT, RAIN_LED_PIN, DIO_HIGH);
    }
    else
    {
        DIO_SetPinValue(RAIN_LED_PORT, RAIN_LED_PIN, DIO_LOW);
    }

    if (!G_u8LightManualMode)
    {
        if (ADC_u16ReadChannelSync(LDR_ADC_CHANNEL) < LDR_THRESHOLD)
        {
            DIO_SetPinValue(LIGHT_LED_PORT, LIGHT_LED_PIN, DIO_HIGH);
        }
        else
        {
            DIO_SetPinValue(LIGHT_LED_PORT, LIGHT_LED_PIN, DIO_LOW);
        }
    }
}

/* Called every 10ms from Timer0 */
void Slave_PeriodicTask(void)
{
    static u8 Local_u8SensorsCounter = 0;

    Keypad_Task();
    Door_Task();

    Local_u8SensorsCounter++;
    if (Local_u8SensorsCounter >= SENSORS_PERIOD_TICKS)
    {
        Local_u8SensorsCounter = 0;
        Sensors_Task();
    }

    Gate_Update();
}
