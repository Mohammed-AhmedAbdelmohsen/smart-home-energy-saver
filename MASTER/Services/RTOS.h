/*
 * RTOS.h
 *

 */

#ifndef SERVICES_RTOS_H_
#define SERVICES_RTOS_H_

#include "../LIB/STD_TYPES.h"

#define Max_Task 8
#define Tick     1


struct RTPS_TCB
{
	void (*fun)(void);
	u16 period;
	u8 priority;
	u16 Tf;

};

void RTOS_INIT(void);
u8 RTOS_Creat_Task(void (*fun)(void) , u16 period , u8 priority , u16 Tf);
void RTOS_Scheduler();

#endif /* SERVICES_RTOS_H_ */
