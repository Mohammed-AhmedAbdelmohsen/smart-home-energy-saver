/*
 * EXTI.h
 *

 */

#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_

#include "../../LIB/STD_TYPES.h"

/* ==================================================================== */
/*                          EXTI REGISTERS                              */
/* ==================================================================== */

#define MCUCR       (*(volatile u8*)(0x55))
#define MCUCSR      (*(volatile u8*)(0x54))
#define GICR        (*(volatile u8*)(0x5B))
#define GIFR        (*(volatile u8*)(0x5A))
#define SREG        (*(volatile u8*)(0x5F))

/* MCUCR Bits */
#define ISC11       3
#define ISC10       2
#define ISC01       1
#define ISC00       0

/* MCUCSR Bits */
#define ISC2        6

/* GICR Bits */
#define INT1        7
#define INT0        6
#define INT2        5

/* GIFR Bits */
#define INTF1       7
#define INTF0       6
#define INTF2       5

/* SREG Bits */
#define I_BIT       7

/* ==================================================================== */
/*                       EXTI SENSE MODES                               */
/* ==================================================================== */

#define FALING_EDGE_SENSE   1
#define RISING_EDGE_SENSE   2
#define ON_CHANGE_SENSE     3
#define LOW_LEVEL_SENSE     4

/* ==================================================================== */
/*                     FUNCTION PROTOTYPES                              */
/* ==================================================================== */

void EXTI0_Init (u8 Sense) ;
void EXTI1_Init (u8 Sense) ;
void EXTI2_Init (u8 Sense) ;

void EXTI0_CallBack (void (*fptr)(void)) ;
void EXTI1_CallBack (void (*fptr)(void)) ;
void EXTI2_CallBack (void (*fptr)(void)) ;

void EXTI0_Enable(void);
void EXTI0_Disable(void);

void EXTI1_Enable(void);
void EXTI1_Disable(void);

void EXTI2_Enable(void);
void EXTI2_Disable(void);

#endif /* MCAL_EXTI_EXTI_H_ */
