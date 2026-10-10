/*
 * BLUETOOTH.c
 */

#include "BLUETOOTH.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

void Bluetooth_Init(void)
{
    /* 1. Configure UART pins */
    DIO_InitPin(DIO_PORTD, DIO_PIN0, DIO_INPUT);   /* PD0: RXD */
    DIO_InitPin(DIO_PORTD, DIO_PIN1, DIO_OUTPUT);  /* PD1: TXD */

    /* 2. Initialize UART with 9600 baud rate and 8-bit data size */
    UART_Init(9600, 8);
}

void Bluetooth_SendByte(u8 Copy_u8Data)
{
    /* Send a byte via your UART_Tx function */
    UART_Tx(Copy_u8Data);
}

void Bluetooth_SendString(u8 Copy_u8String[])
{
    /* Send a string via your UART_TxStr function */
    if (Copy_u8String != NULL)
    {
        UART_TxStr(Copy_u8String);
    }
}

u8 Bluetooth_u8ReceiveByteSync(void)
{
    /* Receive a byte synchronously via UART_Rx */
    return UART_Rx();
}

u8 Bluetooth_u8ReceiveByteAsync(u8 *Copy_pu8ReceivedByte)
{
    /* Non-blocking reception by checking RXC flag directly from UCSRA */
    if (READ_BIT(UCSRA, RXC) == 1)
    {
        if (Copy_pu8ReceivedByte != NULL)
        {
            *Copy_pu8ReceivedByte = UDR;
        }
        return 1; /* Byte received successfully */
    }
    return 0;     /* No new data */
}