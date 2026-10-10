/*
 * EEPROM.c
 *

 */

#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_TYPES.h"

#include "EEPROM.h"
void EEPROM_Write (u16 Address , u8 Data)
{
	EEAR = Address ;

	SET_BIT(EECR , EEMWE) ;
	SET_BIT(EECR , EEWE) ;
	EEDR = Data ;

	while (READ_BIT(EECR , EEWE) == 1) ;
}
u8 EEPROM_Read (u16 Address)
{
	EEAR = Address ;
	SET_BIT(EECR , EERE) ;
	return EEDR ;
}
