/*
 * main.c (Slave / Receiver MCU)
 */

#include "App_Init.h"
#include "Slave_Commands.h"

int main(void)
{
    App_Init();

    while (1)
    {
        /* Continuous, non-blocking check for I2C commands */
        Slave_CheckI2C();
    }

    return 0;
}
