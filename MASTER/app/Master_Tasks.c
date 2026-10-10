/*
 * Master_Tasks.c
 * Periodic application task (run from the Timer0 10ms tick):
 * Bluetooth, keypad, temperature/fan control and LCD refresh.
 */

#include "../LIB/STD_TYPES.h"
#include "../HAL/KP/KP.h"
#include "App_Config.h"
#include "Bluetooth_Cmd.h"
#include "TempControl.h"
#include "Master_Tasks.h"

static u8 L_u8LastKey = KP_NOT_PRESSED;

/* Keypad input: set temperature in range [0 - 100] */
static void Keypad_Task(void)
{
    u8 Key = KP_GetVal(KEYPAD_PORT);

    if (Key != KP_NOT_PRESSED && Key != L_u8LastKey)
    {
        if (Key >= '0' && Key <= '9')
        {
            TempCtrl_EnterDigit(Key);
        }
        else if (Key == '=')
        {
            TempCtrl_ConfirmInput();
        }
        else if (Key == 'C' || Key == 'N')
        {
            TempCtrl_ClearSetTemp();
        }
    }
    L_u8LastKey = Key;
}

/* Called every 10ms from Timer0 */
void Master_PeriodicTask(void)
{
    static u8 Local_u8TempCounter = 0;

    Bluetooth_CommandTask();
    Keypad_Task();

    Local_u8TempCounter++;
    if (Local_u8TempCounter >= TEMP_PERIOD_TICKS)
    {
        Local_u8TempCounter = 0;
        TempCtrl_SensorTask();
    }

    TempCtrl_DisplayTask();
}
