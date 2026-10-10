/*
 * UART.c

 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Math.h"
#include "UART.h"

void UART_Init(u32 BaudRate, u8 DataSize)
{
    /* 1. Calculate Baud Rate */
    u16 UBRR_Val = (8000000UL / (16UL * BaudRate)) - 1;

    /* Write UBRRH (URSEL must be 0) */
    UBRRH = (u8)((UBRR_Val >> 8) & 0x7F);
    UBRRL = (u8)UBRR_Val;

    /* 2. Enable Transmitter & Receiver */
    SET_BIT(UCSRB, TXEN);
    SET_BIT(UCSRB, RXEN);

    /* 3. Configure Frame Format (Atomic write to UCSRC with URSEL = 1) */
    u8 UCSRC_Temp = (1 << URSEL);

    switch (DataSize)
    {
    case 5:
        /* UCSZ1:0 = 00, UCSZ2 = 0 */
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case 6:
        /* UCSZ1:0 = 01, UCSZ2 = 0 */
        UCSRC_Temp |= (1 << UCSZ0);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case 7:
        /* UCSZ1:0 = 10, UCSZ2 = 0 */
        UCSRC_Temp |= (1 << UCSZ1);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case 8:
    default:
        /* UCSZ1:0 = 11, UCSZ2 = 0 */
        UCSRC_Temp |= (1 << UCSZ1) | (1 << UCSZ0);
        CLR_BIT(UCSRB, UCSZ2);
        break;
    case 9:
        /* UCSZ1:0 = 11, UCSZ2 = 1 */
        UCSRC_Temp |= (1 << UCSZ1) | (1 << UCSZ0);
        SET_BIT(UCSRB, UCSZ2);
        break;
    }

    UCSRC = UCSRC_Temp;
}

void UART_Tx(u8 Data)
{
    /* Wait for empty transmit buffer */
    while (READ_BIT(UCSRA, UDRE) == 0);
    UDR = Data;
}

void UART_TxStr(u8 str[])
{
    u8 i = 0;
    while (str[i] != '\0')
    {
        UART_Tx(str[i]);
        i++;
    }
}

u8 UART_Rx(void)
{
    /* Wait for data to be received */
    while (READ_BIT(UCSRA, RXC) == 0);
    return UDR;
}
