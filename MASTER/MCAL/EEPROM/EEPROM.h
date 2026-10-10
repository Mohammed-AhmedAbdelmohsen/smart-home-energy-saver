#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../LIB/STD_TYPES.h"

/* Registers Definitions (Memory-Mapped IO for ATmega32) */
#define EEARL   (*(volatile u8*)(0x3E))
#define EEARH   (*(volatile u8*)(0x3F))
#define EEAR    (*(volatile u16*)(0x3E))

#define EEDR    (*(volatile u8*)(0x3D))
#define EECR    (*(volatile u8*)(0x3C))

/* EECR Register Bits */
#define EERE    0
#define EEWE    1
#define EEMWE   2
#define EERIE   3

/* Functions Prototypes */
void EEPROM_Write(u16 Address, u8 Data);
u8 EEPROM_Read(u16 Address);

#endif /* EEPROM_H_ */
