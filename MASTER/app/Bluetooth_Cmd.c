/*
 * Bluetooth_Cmd.c
 * Parsing and execution of commands received over Bluetooth.
 */

#include "../LIB/STD_TYPES.h"
#include "../HAL/BLUETOOTH/BLUETOOTH.h"
#include "App_Config.h"
#include "Slave_Link.h"
#include "TempControl.h"
#include "Bluetooth_Cmd.h"

void Bluetooth_CommandTask(void)
{
    u8 ReceivedBtByte = 0;

    if (Bluetooth_u8ReceiveByteAsync(&ReceivedBtByte) != 1)
    {
        return;
    }

    switch (ReceivedBtByte)
    {
        /* --- Master controls the fan locally --- */
        case 'F': /* Manual ON, enter override mode */
            TempCtrl_FanForce(1);
            Bluetooth_SendString((u8*)"Fan Forced ON\r\n");
            break;

        case 'f': /* Manual OFF, enter override mode */
            TempCtrl_FanForce(0);
            Bluetooth_SendString((u8*)"Fan Forced OFF\r\n");
            break;

        case 'A': /* Exit override mode, return fan to Auto */
        case 'a':
            TempCtrl_FanAuto();
            Bluetooth_SendString((u8*)"Fan Back to AUTO\r\n");
            break;

        /* --- Slave commands via I2C --- */
        case 'L': Master_SendI2CCommandChecked(SLAVE_CMD_LIGHT_ON);  break; /* External lighting ON (Manual)  */
        case 'l': Master_SendI2CCommandChecked(SLAVE_CMD_LIGHT_OFF); break; /* External lighting OFF (Manual) */
        case 'R':
        case 'r': Master_SendI2CCommandChecked(SLAVE_CMD_LIGHT_AUTO); break; /* External lighting back to Auto (LDR) */

        case 'D': Master_SendI2CCommandChecked(SLAVE_CMD_DOOR_OPEN);  break; /* Open door  */
        case 'd': Master_SendI2CCommandChecked(SLAVE_CMD_DOOR_CLOSE); break; /* Close door */

        case '0': Master_SendI2CCommandChecked(SLAVE_CMD_ROOM_LEDS_0); break; /* Internal LEDs OFF (Manual) */
        case '1': Master_SendI2CCommandChecked(SLAVE_CMD_ROOM_LEDS_1); break; /* 1 LED  (Manual) */
        case '2': Master_SendI2CCommandChecked(SLAVE_CMD_ROOM_LEDS_2); break; /* 2 LEDs (Manual) */
        case '3': Master_SendI2CCommandChecked(SLAVE_CMD_ROOM_LEDS_3); break; /* 3 LEDs (Manual) */
        case '4': Master_SendI2CCommandChecked(SLAVE_CMD_ROOM_LEDS_4); break; /* 4 LEDs (Manual) */
        case 'U':
        case 'u': Master_SendI2CCommandChecked(SLAVE_CMD_ROOM_LEDS_AUTO); break; /* Internal LEDs back to Auto (IR) */

        /* Required temperature via Bluetooth */
        default:
            if (ReceivedBtByte >= '0' && ReceivedBtByte <= '9')
            {
                TempCtrl_EnterDigit(ReceivedBtByte);
            }
            else if (ReceivedBtByte == '\r' || ReceivedBtByte == '\n' || ReceivedBtByte == '=')
            {
                TempCtrl_ConfirmInput();
            }
            break;
    }
}
