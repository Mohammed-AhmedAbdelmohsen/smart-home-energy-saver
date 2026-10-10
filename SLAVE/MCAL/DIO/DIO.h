/*
 * DIO.h
 *

 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* ==================================================================== */
/*                           DIO REGISTERS                              */
/* ==================================================================== */

/* PORT A */
#define PORTA    (*((volatile u8*)0x3B))
#define DDRA     (*((volatile u8*)0x3A))
#define PINA     (*((volatile u8*)0x39))

/* PORT B */
#define PORTB    (*((volatile u8*)0x38))
#define DDRB     (*((volatile u8*)0x37))
#define PINB     (*((volatile u8*)0x36))

/* PORT C */
#define PORTC    (*((volatile u8*)0x35))
#define DDRC     (*((volatile u8*)0x34))
#define PINC     (*((volatile u8*)0x33))

/* PORT D */
#define PORTD    (*((volatile u8*)0x32))
#define DDRD     (*((volatile u8*)0x31))
#define PIND     (*((volatile u8*)0x30))

/* ==================================================================== */
/*                           DIO CONFIGURATIONS                         */
/* ==================================================================== */

/* Port Definitions */
#define DIO_PORTA          1
#define DIO_PORTB          2
#define DIO_PORTC          3
#define DIO_PORTD          4

/* Pin Definitions */
#define DIO_PIN0           0
#define DIO_PIN1           1
#define DIO_PIN2           2
#define DIO_PIN3           3
#define DIO_PIN4           4
#define DIO_PIN5           5
#define DIO_PIN6           6
#define DIO_PIN7           7

/* Pin Directions */
#define DIO_INPUT          0
#define DIO_OUTPUT         1
#define DIO_INPUT_PULLUP   2

/* Pin Values */
#define DIO_LOW            0
#define DIO_HIGH           1

/* Port Directions & Values */
#define DIO_PORT_INPUT     0x00
#define DIO_PORT_OUTPUT    0xFF
#define DIO_PORT_LOW       0x00
#define DIO_PORT_HIGH      0xFF

/* ==================================================================== */
/*                        FUNCTION PROTOTYPES                           */
/* ==================================================================== */

void DIO_InitPin      (u8 PORT_Name , u8 PIN_Number , u8 Mode) ;
void DIO_SetPinValue  (u8 PORT_Name , u8 PIN_Number , u8 Val ) ;
void DIO_TogPinValue  (u8 PORT_Name , u8 PIN_Number          ) ;
u8   DIO_ReadPinValue (u8 PORT_Name , u8 PIN_Number          ) ;

void DIO_InitPort     (u8 PORT_Name , u8 Mode) ;
void DIO_SetPortValue (u8 PORT_Name , u8 Val ) ;
void DIO_TogPortValue (u8 PORT_Name          ) ;
u8   DIO_ReadPortValue(u8 PORT_Name          ) ;

#endif /* MCAL_DIO_DIO_H_ */
