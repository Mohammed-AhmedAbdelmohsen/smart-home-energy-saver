/*
 * LCD_ST7920.h
 *

 */

#ifndef HAL_LCD_ST7920_LCD_ST7920_H_
#define HAL_LCD_ST7920_LCD_ST7920_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"

/* ==================================================================== */
/*                         HARDWARE CONFIGURATION                       */
/* ==================================================================== */

#define ST7920_DATA_PORT       DIO_PORTD   /* D0..D7 connected to PD0..PD7 */
#define ST7920_CTRL_PORT       DIO_PORTA

#define ST7920_RS_PIN          DIO_PIN0    /* Pin 4 on LCD */
#define ST7920_RW_PIN          DIO_PIN1    /* Pin 5 on LCD */
#define ST7920_E_PIN           DIO_PIN2    /* Pin 6 on LCD */

/* ==================================================================== */
/*                         FUNCTION PROTOTYPES                          */
/* ==================================================================== */

void ST7920_Init(void);
void ST7920_SendCmd(u8 Copy_u8Cmd);
void ST7920_SendData(u8 Copy_u8Data);
void ST7920_Clear(void);
void ST7920_SetCursor(u8 Copy_u8Row, u8 Copy_u8Col);
void ST7920_WriteString(u8 *Copy_pStr);

#endif /* HAL_LCD_ST7920_LCD_ST7920_H_ */
