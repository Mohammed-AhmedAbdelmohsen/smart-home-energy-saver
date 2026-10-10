/*
 * 7SEG.h
 *
 *  Created on: Sep 6, 2026
 *      Author: Ahmed
 */

#ifndef HAL_7SEG_H_
#define HAL_7SEG_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

/* ==================================================================== */
/*                        7-SEGMENT CONFIGURATIONS                      */
/* ==================================================================== */

#define COMMON_CATHODE    1
#define COMMON_ANODE      2

/* ==================================================================== */
/*                         FUNCTION PROTOTYPES                          */
/* ==================================================================== */

void SEG_Init(u8 PORT_Name);
void SEG_WriteNumber(u8 PORT_Name, u8 Num, u8 Type);

#endif /* HAL_7SEG_H_ */
