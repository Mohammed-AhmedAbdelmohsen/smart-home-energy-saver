/*
 * KP.c

 *
 * FIX (see chat): this file had already removed the blocking
 * "wait for release" loop (good) but it still switched a column pin
 * low and read the rows on the very next line, with zero settle time.
 * On real hardware the row line takes a few microseconds to actually
 * reach the new logic level after the column switches, so a normal
 * press could be scanned before it settled and get missed - that's
 * what made it feel like you had to hold the key down for a while
 * before it registered. Adding a short _delay_us(5) after driving the
 * column, before sampling the rows, fixes it.
 */
#include <util/delay.h>
#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO.h"

#include "KP.h"


const u8 KP_arr[4][4] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

void KP_Init (u8 PORT_Name)
{
	DIO_InitPort(PORT_Name, 0xF0) ;
	DIO_SetPortValue(PORT_Name, 0xFF) ;
}

u8 KP_GetVal (u8 PORT_Name)
{
	u8 col, row, pb_state, val = KP_NOT_PRESSED;

	/* المرور على الصفوف (Output Pins: 4, 5, 6, 7) */
	for (row = 0; row < 4; row++)
	{
		DIO_SetPinValue(PORT_Name, row + 4, DIO_LOW);
		_delay_us(5); /* let the line settle before sampling */

		/* قراءة الأعمدة (Input Pins: 0, 1, 2, 3) */
		for (col = 0; col < 4; col++)
		{
			pb_state = DIO_ReadPinValue(PORT_Name, col);
			if (pb_state == KP_PRESSED)
			{
				/* استخراج القيمة المقابلة للصف والعمود */
				val = KP_arr[row][col];
			}
		}

		/* إعادة الصف لوضع HIGH */
		DIO_SetPinValue(PORT_Name, row + 4, DIO_HIGH);
	}

	return val;
}
