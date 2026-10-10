/*
 * Slave_Link.c
 * Sending commands to the Slave MCU over I2C.
 */

#include "../LIB/STD_TYPES.h"
#include "../MCAL/I2C/I2C_Master.h"
#include "../HAL/BLUETOOTH/BLUETOOTH.h"
#include "App_Config.h"
#include "Slave_Link.h"

/* Send a command byte to the slave via I2C.
 * Returns 0 on success, 1 if the slave never responded (timeout/error) -
 * in that case we still release the bus with a Stop so the sender never
 * freezes, and we let the caller know so it can report the failure. */
u8 Master_SendI2CCommand(u8 Command)
{
    u8 Local_u8Status;

    Local_u8Status = I2C_MasterSendStart();
    if (Local_u8Status != 0)
    {
        I2C_MasterSendStop();
        return Local_u8Status;
    }

    Local_u8Status = I2C_MasterSendAddressWrite(SLAVE_I2C_ADDRESS);
    if (Local_u8Status != 0)
    {
        I2C_MasterSendStop();
        return Local_u8Status;
    }

    Local_u8Status = I2C_MasterSendData(Command);
    I2C_MasterSendStop(); /* always release the bus, success or not */

    return Local_u8Status;
}

/* Sends the command and, if the slave didn't answer, reports it over
 * Bluetooth so the failure is visible immediately. */
void Master_SendI2CCommandChecked(u8 Command)
{
    if (Master_SendI2CCommand(Command) != 0)
    {
        Bluetooth_SendString((u8*)"Slave not responding!\r\n");
    }
}
