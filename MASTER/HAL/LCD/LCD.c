/*
 * LCD.c

 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#include <util/delay.h>
#include "../../LIB/BIT_MATH.h"

/*=========================================================
 * Private Functions
 *=========================================================*/

#if MODE == 4
static void LCD_Send4Bits(u8 Data)
{
    DIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN4, READ_BIT(Data, 0));
    DIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN5, READ_BIT(Data, 1));
    DIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN6, READ_BIT(Data, 2));
    DIO_SetPinValue(LCD_DATA_PORT, LCD_DATA_PIN7, READ_BIT(Data, 3));

    DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_us(1);
    DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_us(100);
}
#endif

/*=========================================================
 * LCD Initialization
 *=========================================================*/

void LCD_Init(void)
{
    _delay_ms(50);

    /* Control pins */
    DIO_InitPin(LCD_RS_PORT, LCD_RS_PIN, DIO_OUTPUT);
    DIO_InitPin(LCD_RW_PORT, LCD_RW_PIN, DIO_OUTPUT);
    DIO_InitPin(LCD_E_PORT, LCD_E_PIN, DIO_OUTPUT);

#if MODE == 8

    /* Data Port (8 pins) */
    DIO_InitPort(LCD_DATA_PORT, 0xFF);

    /* LCD Init Sequence */
    LCD_WriteCmd(0x38);     // 8-bit mode, 2 lines, 5x8 font
    _delay_ms(1);
    LCD_WriteCmd(0x0C);     // Display ON, Cursor OFF
    _delay_ms(1);
    LCD_ClrDisplay();
    _delay_ms(2);
    LCD_WriteCmd(0x06);     // Entry Mode: Auto increment cursor

#elif MODE == 4

    /* Data Pins (D4..D7) */
    DIO_InitPin(LCD_DATA_PORT, LCD_DATA_PIN4, DIO_OUTPUT);
    DIO_InitPin(LCD_DATA_PORT, LCD_DATA_PIN5, DIO_OUTPUT);
    DIO_InitPin(LCD_DATA_PORT, LCD_DATA_PIN6, DIO_OUTPUT);
    DIO_InitPin(LCD_DATA_PORT, LCD_DATA_PIN7, DIO_OUTPUT);

    DIO_SetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_SetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW);

    /* HD44780 Standard 4-bit Initialization Sequence */
    LCD_Send4Bits(0x03);
    _delay_ms(5);
    LCD_Send4Bits(0x03);
    _delay_us(150);
    LCD_Send4Bits(0x03);
    _delay_us(150);
    LCD_Send4Bits(0x02);     // Switch to 4-bit mode
    _delay_ms(2);

    LCD_WriteCmd(0x28);     // 4-bit mode, 2 lines, 5x8 font
    _delay_ms(1);
    LCD_WriteCmd(0x0C);     // Display ON, Cursor OFF
    _delay_ms(1);
    LCD_ClrDisplay();
    _delay_ms(2);
    LCD_WriteCmd(0x06);     // Entry Mode: Auto increment cursor

#endif
}

/*=========================================================
 * Write Command
 *=========================================================*/

void LCD_WriteCmd(u8 Cmd)
{
    DIO_SetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_SetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW);

#if MODE == 8
    DIO_SetPortValue(LCD_DATA_PORT, Cmd);
    DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_us(1);
    DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_us(100);

#elif MODE == 4
    LCD_Send4Bits(Cmd >> 4);    /* Send High Nibble */
    LCD_Send4Bits(Cmd & 0x0F);  /* Send Low Nibble */
#endif
}

/*=========================================================
 * Write Data / Character
 *=========================================================*/

void LCD_WriteData(u8 Data)
{
    DIO_SetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW);
    DIO_SetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH);

#if MODE == 8
    DIO_SetPortValue(LCD_DATA_PORT, Data);
    DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_us(1);
    DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
    _delay_us(100);

#elif MODE == 4
    LCD_Send4Bits(Data >> 4);   /* Send High Nibble */
    LCD_Send4Bits(Data & 0x0F); /* Send Low Nibble */
#endif
}

/*=========================================================
 * Write String & Numbers
 *=========================================================*/

void LCD_WriteString(u8 str[])
{
    u8 i = 0;
    while (str[i] != '\0')
    {
        LCD_WriteData(str[i]);
        i++;
    }
}

void LCD_WriteNumber(s32 Number)
{
    u8 Str[12];
    s8 i = 0;

    if (Number == 0)
    {
        LCD_WriteData('0');
        return;
    }

    if (Number < 0)
    {
        LCD_WriteData('-');
        Number = -Number;
    }

    while (Number > 0)
    {
        Str[i++] = (Number % 10) + '0';
        Number /= 10;
    }

    /* Print in correct order (reversed) */
    while (--i >= 0)
    {
        LCD_WriteData(Str[i]);
    }
}

/*=========================================================
 * Display Controls
 *=========================================================*/

void LCD_ClrDisplay(void)
{
    LCD_WriteCmd(0x01);
    _delay_ms(2);
}

void LCD_ShiftLeft(void)
{
    LCD_WriteCmd(0x18);
    _delay_us(100);
}

void LCD_ShiftRight(void)
{
    LCD_WriteCmd(0x1C);
    _delay_us(100);
}

void LCD_Move_Cursor(u8 row, u8 col)
{
    u8 AC = 0;

    if (row == 0)
    {
        AC = col;
    }
    else if (row == 1)
    {
        AC = col + 0x40;
    }

    LCD_WriteCmd(AC + 0x80);
}

/*=========================================================
 * Display Custom Character
 *=========================================================*/

void LCD_DispalyCustomChar(u8 Arr[], u8 BlockNumber, u8 row, u8 col)
{
    u8 i;

    /* Go to CGRAM */
    LCD_WriteCmd((BlockNumber * 8) + 0x40);

    /* Write character pattern */
    for (i = 0; i < 8; i++)
    {
        LCD_WriteData(Arr[i]);
    }

    /* Return to DDRAM */
    LCD_Move_Cursor(row, col);

    /* Display custom character */
    LCD_WriteData(BlockNumber);
}
