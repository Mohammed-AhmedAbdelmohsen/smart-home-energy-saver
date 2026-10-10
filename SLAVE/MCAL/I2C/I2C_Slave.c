/*
 * I2C_Slave.c
 *
 *  Created on: Sep 12, 2026
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "I2C_Slave.h"

void I2C_SlaveInit(u8 SlaveAddress)
{
    /* 1. Set the specific slave address */
    TWAR = (SlaveAddress << 1);

    /* 2. Enable peripheral and enable ACK response */
    TWCR = (1 << TWEN) | (1 << TWEA);
}

void I2C_SlaveListen(void)
{
    /* Wait until the slave is addressed by the master */
    while (1)
    {
        /* Enable listening and reset the Flag */
        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
        while (READ_BIT(TWCR, TWINT) == 0);

        /* Check if addressed with a write command */
        if ((TWSR & 0xF8) == I2C_SLAVE_OWN_SLA_W_RECEIVED)
        {
            break;
        }
    }
}

u8 I2C_SlaveReadByte(void)
{
    /* Clear flag to prepare for receiving the next byte with ACK */
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (READ_BIT(TWCR, TWINT) == 0);

    /* Check successful data reception */
    while (((TWSR & 0xF8) != I2C_SLAVE_DATA_RECEIVED_ACK_RETURN) &&
           ((TWSR & 0xF8) != I2C_SLAVE_STOP_OR_REP_START));

    return TWDR;
}

void I2C_SlaveWriteByte(u8 Data)
{
    TWDR = Data;
    /* Clear flag to transmit data to master */
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (READ_BIT(TWCR, TWINT) == 0);
    while ((TWSR & 0xF8) != I2C_SLAVE_DATA_TRANSMITTED_ACK);
}

void I2C_SlaveReceiveString(u8 *Buffer)
{
    u8 i = 0;
    u8 ReceivedByte = 0;

    /* 1. Wait for master call */
    I2C_SlaveListen();

    /* 2. Read string bytes until reaching Null Terminator or Stop */
    do
    {
        ReceivedByte = I2C_SlaveReadByte();
        Buffer[i] = ReceivedByte;
        i++;
    } while (ReceivedByte != '\0' && (TWSR & 0xF8) != I2C_SLAVE_STOP_OR_REP_START);

    Buffer[i] = '\0';
}