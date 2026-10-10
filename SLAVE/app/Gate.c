/*
 * Gate.c
 * IR gate state machine that counts people entering / leaving.
 */

#include "../LIB/STD_TYPES.h"
#include "../HAL/IR_SENSOR/IR_SENSOR.h"
#include "App_Config.h"
#include "App_State.h"
#include "RoomCount.h"
#include "Gate.h"

void Gate_Update(void)
{
    static u8  Local_u8GateState   = GATE_STATE_IDLE;
    static u16 Local_u16Timeout    = 0;
    u8 Local_u8OuterBroken = (IR_SENSOR_u8GetStatus(IR_OUTER_PORT, IR_OUTER_PIN) == IR_OBJECT_DETECTED);
    u8 Local_u8InnerBroken = (IR_SENSOR_u8GetStatus(IR_INNER_PORT, IR_INNER_PIN) == IR_OBJECT_DETECTED);
    u8 Local_u8CountChanged = 0;

    switch (Local_u8GateState)
    {
        case GATE_STATE_IDLE:
            if (Local_u8OuterBroken && !Local_u8InnerBroken)
            {
                Local_u8GateState = GATE_STATE_OUTER_FIRST;
                Local_u16Timeout  = 0;
            }
            else if (Local_u8InnerBroken && !Local_u8OuterBroken)
            {
                Local_u8GateState = GATE_STATE_INNER_FIRST;
                Local_u16Timeout  = 0;
            }
            break;

        case GATE_STATE_OUTER_FIRST:
            if (Local_u8InnerBroken)
            {
                G_u16RoomCount++;
                Local_u8CountChanged = 1;
                Local_u8GateState = GATE_STATE_WAIT_CLEAR;
            }
            else if (!Local_u8OuterBroken)
            {
                Local_u8GateState = GATE_STATE_IDLE;
            }
            else if (++Local_u16Timeout >= GATE_TIMEOUT_TICKS)
            {
                Local_u8GateState = GATE_STATE_IDLE;
            }
            break;

        case GATE_STATE_INNER_FIRST:
            if (Local_u8OuterBroken)
            {
                if (G_u16RoomCount > 0)
                {
                    G_u16RoomCount--;
                }
                Local_u8CountChanged = 1;
                Local_u8GateState = GATE_STATE_WAIT_CLEAR;
            }
            else if (!Local_u8InnerBroken)
            {
                Local_u8GateState = GATE_STATE_IDLE;
            }
            else if (++Local_u16Timeout >= GATE_TIMEOUT_TICKS)
            {
                Local_u8GateState = GATE_STATE_IDLE;
            }
            break;

        case GATE_STATE_WAIT_CLEAR:
        default:
            if (!Local_u8OuterBroken && !Local_u8InnerBroken)
            {
                Local_u8GateState = GATE_STATE_IDLE;
            }
            break;
    }

    if (Local_u8CountChanged)
    {
        RoomCount_DisplayUpdate();
        if (!G_u8RoomLedManualMode)
        {
            RoomCount_LedUpdate();
        }
    }
}
