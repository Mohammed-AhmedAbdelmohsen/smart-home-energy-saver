/*
 * KP.c
 *
 *  Created on: 
 *     
 *
 *  FIX (see chat): the old version blocked with
 *      while (DIO_ReadPinValue(...) == KP_PRESSED);
 *  right inside the scan loop. Since KP_GetVal() is called from the
 *  Timer0 ISR, and AVR disables global interrupts for the whole time
 *  it's inside an ISR, that while() froze EVERYTHING (LCD, sensors,
 *  the new door timer) for as long as the key stayed pressed.
 *
 *  It also switched a column low and read the rows on the very next
 *  instruction, with no settle time - on real hardware the row line
 *  needs a few microseconds to actually reach the new logic level, so
 *  a quick/normal press could be scanned before it had settled and
 *  simply get missed, which is what made it feel like you had to hold
 *  the key down longer for it to register.
 *
 *  Both are fixed below: no blocking wait, and a short _delay_us(5)
 *  after driving each column before sampling the rows.
 */
#include <util/delay.h>
#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO.h"

#include "KP.h"

u8 KP_arr [4][4] =
{
		{'7' , '8' , '9' , '/'},
		{'4' , '5' , '6' , '*'},
		{'1' , '2' , '3' , '-'},
		{'C' , '0' , '=' , '+'}
};
void KP_Init (u8 PORT_Name)
{
	DIO_InitPort(PORT_Name, 0x0F) ;
	DIO_SetPortValue(PORT_Name, 0xFF) ;
}

u8 KP_GetVal (u8 PORT_Name)
{
	u8 col , row , pb_state , val = KP_NOT_PRESSED;
	for (col = 0 ; col < 4 ; col ++)
	{
		DIO_SetPinValue(PORT_Name, col, DIO_LOW) ;
		_delay_us(5) ; /* let the row line settle before we sample it */

		for (row = 0 ; row < 4 ; row ++)
		{
			pb_state = DIO_ReadPinValue(PORT_Name, row+4) ;
			if (pb_state == KP_PRESSED)
			{
				/* get value, no blocking wait for release anymore */
				val = KP_arr [col][row] ;
			}
		}
		DIO_SetPinValue(PORT_Name, col, DIO_HIGH) ;
	}
	return val ;
}
