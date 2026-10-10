/*
 * I2C_Master.c
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "I2C_Master.h"

/* How many times we poll TWINT before giving up and declaring "no response".
 * Generous margin for 8MHz F_CPU / 100kHz I2C. If you change F_CPU or the
 * I2C clock a lot, re-check this still gives you a few hundred microseconds
 * of patience before timing out. */
#define I2C_TIMEOUT_LOOPS   10000UL

/* Waits for TWINT to be set (with a timeout), then checks the status code
 * matches what we expected.
 * Returns 0 on success, 1 on timeout OR unexpected status (e.g. NACK). */
static u8 I2C_WaitAndCheck(u8 ExpectedStatus)
{
    u32 Local_u32Timeout = I2C_TIMEOUT_LOOPS;

    while ((READ_BIT(TWCR, TWINT) == 0) && (Local_u32Timeout > 0))
    {
        Local_u32Timeout--;
    }

    if (Local_u32Timeout == 0)
    {
        return 1; /* Bus never responded -> timeout, do NOT hang forever */
    }

    if ((TWSR & 0xF8) != ExpectedStatus)
    {
        return 1; /* Got a reply, but not the one we expected */
    }

    return 0; /* success */
}

void I2C_MasterInit(u32 SCL_Clock)
{
    /* Set frequency based on F_CPU = 8MHz */
    TWBR = (u8)(((8000000UL / SCL_Clock) - 16) / (2 * I2C_PRESCALER_VAL));

    /* Prescaler = 1 (TWPS1 = 0, TWPS0 = 0) */
    TWSR &= ~(0x03);

    /* Enable peripheral */
    SET_BIT(TWCR, TWEN);
}

u8 I2C_MasterSendStart(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    return I2C_WaitAndCheck(I2C_START_ACK);
}

u8 I2C_MasterSendRepeatedStart(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    return I2C_WaitAndCheck(I2C_REP_START_ACK);
}

u8 I2C_MasterSendAddressWrite(u8 SlaveAddress)
{
    TWDR = (SlaveAddress << 1); /* Read/Write bit = 0 (Write) */
    TWCR = (1 << TWINT) | (1 << TWEN);
    return I2C_WaitAndCheck(I2C_SLAVE_ADDR_WRITE_ACK);
}

u8 I2C_MasterSendAddressRead(u8 SlaveAddress)
{
    TWDR = (SlaveAddress << 1) | 0x01; /* Read/Write bit = 1 (Read) */
    TWCR = (1 << TWINT) | (1 << TWEN);
    return I2C_WaitAndCheck(I2C_SLAVE_ADDR_READ_ACK);
}

u8 I2C_MasterSendData(u8 Data)
{
    TWDR = Data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    return I2C_WaitAndCheck(I2C_MASTER_DATA_TRANSMIT_ACK);
}

u8 I2C_MasterReadDataWithACK(u8 *Copy_pu8Data)
{
    u8 Local_u8Status;

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    Local_u8Status = I2C_WaitAndCheck(I2C_MASTER_DATA_RECEIVE_ACK);
    *Copy_pu8Data = TWDR;
    return Local_u8Status;
}

u8 I2C_MasterReadDataWithNACK(u8 *Copy_pu8Data)
{
    u8 Local_u8Status;

    TWCR = (1 << TWINT) | (1 << TWEN);
    Local_u8Status = I2C_WaitAndCheck(I2C_MASTER_DATA_RECEIVE_NACK);
    *Copy_pu8Data = TWDR;
    return Local_u8Status;
}

void I2C_MasterSendStop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

u8 I2C_MasterSendString(u8 SlaveAddress, const char *Str)
{
    u8 Local_u8Status;

    Local_u8Status = I2C_MasterSendStart();
    if (Local_u8Status != 0)
    {
        I2C_MasterSendStop(); /* release the bus even though we failed */
        return Local_u8Status;
    }

    Local_u8Status = I2C_MasterSendAddressWrite(SlaveAddress);
    if (Local_u8Status != 0)
    {
        I2C_MasterSendStop();
        return Local_u8Status;
    }

    while (*Str != '\0')
    {
        Local_u8Status = I2C_MasterSendData((u8)(*Str));
        if (Local_u8Status != 0)
        {
            I2C_MasterSendStop();
            return Local_u8Status;
        }
        Str++;
    }

    I2C_MasterSendData('\0'); /* Send end of string */
    I2C_MasterSendStop();
    return 0;
}
