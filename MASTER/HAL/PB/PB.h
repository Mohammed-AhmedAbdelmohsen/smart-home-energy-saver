/*
 * PB.h
 *

 */

#ifndef HAL_PB_PB_H_
#define HAL_PB_PB_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

/* ==================================================================== */
/*                        PUSH BUTTON DEFINITIONS                       */
/* ==================================================================== */

#define PB_PRESSED             0
#define PB_RELEASED            1

#define PB_PULL_UP_DISABLE     0
#define PB_PULL_UP_ENABLE      1

/* ==================================================================== */
/*                         FUNCTION PROTOTYPES                          */
/* ==================================================================== */

void PB_Init(u8 PORT_Name, u8 PIN_Number, u8 PullUpState);
u8   PB_ReadStatus(u8 PORT_Name, u8 PIN_Number);

#endif /* HAL_PB_PB_H_ */
