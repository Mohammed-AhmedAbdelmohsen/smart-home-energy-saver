/*
 * RTOS.c

 */
#include "../MCAL/Timer0/Timer0.h"

#include "RTOS.h"

struct RTPS_TCB myTasks[Max_Task];

void RTOS_INIT(void) {
	Timer0_Init(TIMER0_PRESCALLER_64, TIMER0_OVF);
	Timer0_SetDesiredTime(1000, RTOS_Scheduler);
}
u8 RTOS_Creat_Task(void (*fun)(void), u16 period, u8 priority, u16 Tf) {
	if ((priority >= 0) && (priority < Max_Task)) {
		if (fun == NULL) {
			return 1;
		} else {
			myTasks[priority].Tf = Tf;
			myTasks[priority].period = period;
			myTasks[priority].priority = priority;
			myTasks[priority].fun = fun;
		}

	}
	return 1;
}
void RTOS_Scheduler(void) {
	for (int i = 0; i < Max_Task; i++) {
		if (myTasks[i].fun != NULL)
		{
            if(myTasks[i].Tf == 0)
            {
            	myTasks[i].fun();
            	myTasks[i].Tf=myTasks[i].period-1;
            }
            else
            {
            	myTasks[i].Tf--;
            }
		}
	}
}
