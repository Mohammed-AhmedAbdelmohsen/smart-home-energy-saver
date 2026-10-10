/*
 * Slave_Commands.h
 * Reception and execution of Master commands over I2C.
 */

#ifndef SLAVE_COMMANDS_H_
#define SLAVE_COMMANDS_H_

#include "../LIB/STD_TYPES.h"

void Slave_ExecuteCommand(u8 Command);
void Slave_CheckI2C(void);   /* Non-blocking */

#endif /* SLAVE_COMMANDS_H_ */
