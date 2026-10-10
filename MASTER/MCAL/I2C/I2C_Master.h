/*
 * I2C_Master.h

 */

#ifndef MCAL_I2C_MASTER_I2C_MASTER_H_
#define MCAL_I2C_MASTER_I2C_MASTER_H_

#include "../../LIB/STD_TYPES.h"

#define I2C_PRESCALER_VAL     1

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

/* TWSR Status Codes */
#define I2C_START_ACK                0x08
#define I2C_REP_START_ACK            0x10
#define I2C_SLAVE_ADDR_WRITE_ACK     0x18
#define I2C_SLAVE_ADDR_READ_ACK      0x40
#define I2C_MASTER_DATA_TRANSMIT_ACK 0x28
#define I2C_MASTER_DATA_RECEIVE_ACK  0x50
#define I2C_MASTER_DATA_RECEIVE_NACK 0x58

/* ==================================================================== */
/*                         FUNCTION PROTOTYPES                          */
/* ==================================================================== */

/* Return value convention for every function below (except Init/Stop):
 *   0 = success
 *   1 = timeout / bus error (slave never answered, or answered wrong) */
void I2C_MasterInit(u32 SCL_Clock);
u8   I2C_MasterSendStart(void);
u8   I2C_MasterSendRepeatedStart(void);
u8   I2C_MasterSendAddressWrite(u8 SlaveAddress);
u8   I2C_MasterSendAddressRead(u8 SlaveAddress);
u8   I2C_MasterSendData(u8 Data);
u8   I2C_MasterReadDataWithACK(u8 *Copy_pu8Data);
u8   I2C_MasterReadDataWithNACK(u8 *Copy_pu8Data);
void I2C_MasterSendStop(void);
u8   I2C_MasterSendString(u8 SlaveAddress, const char *Str);

#endif /* MCAL_I2C_MASTER_I2C_MASTER_H_ */
