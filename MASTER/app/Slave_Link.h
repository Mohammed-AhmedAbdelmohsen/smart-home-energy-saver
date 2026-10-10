/*
 * Slave_Link.h
 * Sending commands to the Slave MCU over I2C.
 */

#ifndef SLAVE_LINK_H_
#define SLAVE_LINK_H_

#include "../LIB/STD_TYPES.h"

/* Returns 0 on success, non-zero if the slave did not respond. */
u8   Master_SendI2CCommand(u8 Command);

/* Same, but reports a failure over Bluetooth. */
void Master_SendI2CCommandChecked(u8 Command);

#endif /* SLAVE_LINK_H_ */
