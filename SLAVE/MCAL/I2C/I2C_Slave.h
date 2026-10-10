/*
 * I2C_Slave.h

 */

#ifndef MCAL_I2C_SLAVE_I2C_SLAVE_H_
#define MCAL_I2C_SLAVE_I2C_SLAVE_H_

#include "../../LIB/STD_TYPES.h"

/* ==================================================================== */
/*                            I2C REGISTERS                             */
/* ==================================================================== */

#define TWBR    (*(volatile u8*)(0x20))
#define TWCR    (*(volatile u8*)(0x56))
#define TWSR    (*(volatile u8*)(0x21))
#define TWDR    (*(volatile u8*)(0x23))
#define TWAR    (*(volatile u8*)(0x22))

/* TWCR Bits */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
#define TWIE    0

/* TWSR Slave Status Codes */
#define I2C_SLAVE_OWN_SLA_W_RECEIVED        0x60
#define I2C_SLAVE_DATA_RECEIVED_ACK_RETURN  0x80
#define I2C_SLAVE_DATA_RECEIVED_NACK_RETURN 0x88
#define I2C_SLAVE_STOP_OR_REP_START         0xA0

#define I2C_SLAVE_OWN_SLA_R_RECEIVED        0xA8
#define I2C_SLAVE_DATA_TRANSMITTED_ACK      0xB8
#define I2C_SLAVE_DATA_TRANSMITTED_NACK     0xC0

/* ==================================================================== */
/*                         FUNCTION PROTOTYPES                          */
/* ==================================================================== */

void I2C_SlaveInit(u8 SlaveAddress);
void I2C_SlaveListen(void);
u8   I2C_SlaveReadByte(void);
void I2C_SlaveWriteByte(u8 Data);
void I2C_SlaveReceiveString(u8 *Buffer);

#endif /* MCAL_I2C_SLAVE_I2C_SLAVE_H_ */
