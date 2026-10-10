#include "LCD_ST7920.h"
#include <util/delay.h>

void ST7920_SendCmd(u8 Copy_u8Cmd)
{
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_RS_PIN, DIO_LOW);  /* RS = 0 (Command) */
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_RW_PIN, DIO_LOW);  /* RW = 0 (Write)   */

    DIO_SetPortValue(ST7920_DATA_PORT, Copy_u8Cmd);

    /* Enable Pulse */
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_E_PIN, DIO_HIGH);
    _delay_us(5);
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_E_PIN, DIO_LOW);
    _delay_us(72);
}

void ST7920_SendData(u8 Copy_u8Data)
{
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_RS_PIN, DIO_HIGH); /* RS = 1 (Data) */
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_RW_PIN, DIO_LOW);  /* RW = 0 (Write) */

    DIO_SetPortValue(ST7920_DATA_PORT, Copy_u8Data);

    /* Enable Pulse */
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_E_PIN, DIO_HIGH);
    _delay_us(5);
    DIO_SetPinValue(ST7920_CTRL_PORT, ST7920_E_PIN, DIO_LOW);
    _delay_us(72);
}

void ST7920_Clear(void)
{
    ST7920_SendCmd(0x01);
    _delay_ms(2);
}

void ST7920_Init(void)
{
    /* Initialize ports */
    DIO_InitPort(ST7920_DATA_PORT, DIO_PORT_OUTPUT);
    DIO_InitPin(ST7920_CTRL_PORT, ST7920_RS_PIN, DIO_OUTPUT);
    DIO_InitPin(ST7920_CTRL_PORT, ST7920_RW_PIN, DIO_OUTPUT);
    DIO_InitPin(ST7920_CTRL_PORT, ST7920_E_PIN, DIO_OUTPUT);

    _delay_ms(50);

    ST7920_SendCmd(0x30); /* 8-bit basic instruction set */
    _delay_us(150);
    ST7920_SendCmd(0x30);
    _delay_us(50);
    ST7920_SendCmd(0x0C); /* Display ON, Cursor OFF */
    _delay_us(120);
    ST7920_Clear();
    ST7920_SendCmd(0x06); /* Entry mode: Cursor increments */
    _delay_ms(2);
}

void ST7920_SetCursor(u8 Copy_u8Row, u8 Copy_u8Col)
{
    u8 Local_u8Address = 0x80;
    switch (Copy_u8Row)
    {
        case 0: Local_u8Address = 0x80 + Copy_u8Col; break;
        case 1: Local_u8Address = 0x90 + Copy_u8Col; break;
        case 2: Local_u8Address = 0x88 + Copy_u8Col; break;
        case 3: Local_u8Address = 0x98 + Copy_u8Col; break;
        default: break;
    }
    ST7920_SendCmd(Local_u8Address);
}

void ST7920_WriteString(u8 *Copy_pStr)
{
    u8 i = 0;
    while (Copy_pStr[i] != '\0')
    {
        ST7920_SendData(Copy_pStr[i]);
        i++;
    }
}