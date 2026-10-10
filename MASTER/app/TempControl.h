/*
 * TempControl.h
 * Temperature sensing, set-point entry, fan control and LCD status.
 */

#ifndef TEMPCONTROL_H_
#define TEMPCONTROL_H_

#include "../LIB/STD_TYPES.h"

void TempCtrl_EnterDigit(u8 Copy_u8Digit);   /* Digit '0'..'9' */
void TempCtrl_ConfirmInput(void);            /* '=' / Enter    */
void TempCtrl_ClearSetTemp(void);            /* Clear key      */

void TempCtrl_FanForce(u8 Copy_u8On);        /* Manual override ON/OFF */
void TempCtrl_FanAuto(void);                 /* Back to automatic      */

void TempCtrl_SensorTask(void);              /* Read LM35 + auto fan   */
void TempCtrl_DisplayTask(void);             /* Refresh LCD if needed  */

#endif /* TEMPCONTROL_H_ */
