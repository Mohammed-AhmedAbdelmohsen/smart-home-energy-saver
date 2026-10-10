/*
 * BLUETOOTH.h
 *

 */

#ifndef HAL_BLUETOOTH_BLUETOOTH_H_
#define HAL_BLUETOOTH_BLUETOOTH_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/UART/UART.h"

void Bluetooth_Init(void);
void Bluetooth_SendByte(u8 Copy_u8Data);
void Bluetooth_SendString(u8 Copy_u8String[]);
u8   Bluetooth_u8ReceiveByteSync(void);
u8   Bluetooth_u8ReceiveByteAsync(u8 *Copy_pu8ReceivedByte);
#endif /* HAL_BLUETOOTH_BLUETOOTH_H_ */
