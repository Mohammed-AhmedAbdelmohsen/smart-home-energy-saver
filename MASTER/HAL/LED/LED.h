/*
 * LED.h

 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

/* ==================================================================== */
/*                           LED DEFINITIONS                            */
/* ==================================================================== */

#define LED_STATE_OFF     0
#define LED_STATE_ON      1

/* ==================================================================== */
/*                         FUNCTION PROTOTYPES                          */
/* ==================================================================== */

void LED_Init(u8 LedPort, u8 LedPin);
void LED_On(u8 LedPort, u8 LedPin);
void LED_Off(u8 LedPort, u8 LedPin);
void LED_Tog(u8 LedPort, u8 LedPin);
u8   LED_u8IsLedOn(u8 LedPort, u8 LedPin);

#endif /* HAL_LED_LED_H_ */
