/*
 * KP.h

 */

#ifndef HAL_KP_KP_H_
#define HAL_KP_KP_H_

#define KP_PRESSED     0
#define KP_NOT_PRESSED 255
void KP_Init (u8 PORT_Name) ;
u8 KP_GetVal (u8 PORT_Name) ;

#endif /* HAL_KP_KP_H_ */
