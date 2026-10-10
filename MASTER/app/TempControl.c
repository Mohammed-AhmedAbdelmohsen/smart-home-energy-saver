/*
 * TempControl.c
 * Temperature sensing, set-point entry, fan control and LCD status.
 */

#include <stdio.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
#include "App_Config.h"
#include "TempControl.h"

static u8  L_u8CurrentTemp       = 0;
static u8  L_u8SetTemp           = DEFAULT_SET_TEMP;
static u16 L_u16InputTemp        = 0;
static u8  L_u8DigitCount        = 0;
static u8  L_u8NeedDisplayUpdate = 1;

/* Manual override flag for fan: 0 = Auto, 1 = Manual */
static u8  L_u8FanManualMode     = 0;

/* Read the LM35 sensor */
static u8 LM35_u8ReadTemp(void)
{
    u16 Local_u16AdcVal = ADC_u16ReadChannelSync(LM35_ADC_CHANNEL);
    return (u8)(((u32)Local_u16AdcVal * LM35_SCALE_NUM) / LM35_SCALE_DEN);
}

void TempCtrl_EnterDigit(u8 Copy_u8Digit)
{
    if (L_u8DigitCount == 0 || L_u8DigitCount >= MAX_TEMP_DIGITS)
    {
        L_u16InputTemp = (Copy_u8Digit - '0');
        L_u8DigitCount = 1;
    }
    else
    {
        L_u16InputTemp = (L_u16InputTemp * 10) + (Copy_u8Digit - '0');
        L_u8DigitCount++;
    }

    if (L_u16InputTemp > MAX_SET_TEMP)
    {
        L_u16InputTemp = MAX_SET_TEMP;
        L_u8DigitCount = MAX_TEMP_DIGITS;
    }

    L_u8SetTemp = (u8)L_u16InputTemp;
    L_u8NeedDisplayUpdate = 1;
}

void TempCtrl_ConfirmInput(void)
{
    L_u8DigitCount = 0;
    L_u8NeedDisplayUpdate = 1;
}

void TempCtrl_ClearSetTemp(void)
{
    L_u8DigitCount = 0;
    L_u16InputTemp = 0;
    L_u8SetTemp = 0;
    L_u8NeedDisplayUpdate = 1;
}

void TempCtrl_FanForce(u8 Copy_u8On)
{
    L_u8FanManualMode = 1;
    DIO_SetPinValue(FAN_LED_PORT, FAN_LED_PIN, Copy_u8On ? DIO_HIGH : DIO_LOW);
    L_u8NeedDisplayUpdate = 1;
}

void TempCtrl_FanAuto(void)
{
    L_u8FanManualMode = 0;
    L_u8NeedDisplayUpdate = 1;
}

void TempCtrl_SensorTask(void)
{
    u8 ReadTemp = LM35_u8ReadTemp();

    if (ReadTemp != L_u8CurrentTemp)
    {
        L_u8CurrentTemp = ReadTemp;
        L_u8NeedDisplayUpdate = 1;
    }

    /* Automatic fan control only works if there is no manual override */
    if (!L_u8FanManualMode)
    {
        if (L_u8CurrentTemp > L_u8SetTemp)
        {
            DIO_SetPinValue(FAN_LED_PORT, FAN_LED_PIN, DIO_HIGH);
        }
        else
        {
            DIO_SetPinValue(FAN_LED_PORT, FAN_LED_PIN, DIO_LOW);
        }
    }
}

void TempCtrl_DisplayTask(void)
{
    char DisplayBuffer[17];

    if (!L_u8NeedDisplayUpdate)
    {
        return;
    }
    L_u8NeedDisplayUpdate = 0;

    LCD_Move_Cursor(0, 0);
    sprintf(DisplayBuffer, "Cur:%3dC Set:%3dC", L_u8CurrentTemp, L_u8SetTemp);
    LCD_WriteString((u8*)DisplayBuffer);

    LCD_Move_Cursor(1, 0);
    if (L_u8FanManualMode)
    {
        LCD_WriteString((u8*)"Fan: MANUAL OVR ");
    }
    else if (L_u8CurrentTemp > L_u8SetTemp)
    {
        LCD_WriteString((u8*)"Fan LED: ON     ");
    }
    else
    {
        LCD_WriteString((u8*)"Fan LED: OFF    ");
    }
}
