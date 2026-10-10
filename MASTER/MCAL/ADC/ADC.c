/*
 * ADC.c
 *

 */

#include "../../LIB/STD_TYPES.h"
#include "ADC.h"
#include "../../LIB/BIT_MATH.h"

/* Global Callback Pointer (Passes 10-bit ADC reading) */
static void (*ADC_pvCallBackNotificationFunc)(u16) = NULL;

void ADC_init(u8 ADC_ref)
{
    /* 1. Select Voltage Reference */
    switch (ADC_ref)
    {
    case ADC_REFERANCE_EXTERNAL:
        CLR_BIT(ADMUX, REFS1);
        CLR_BIT(ADMUX, REFS0);
        break;

    case ADC_REFERANCE_AVCC:
        CLR_BIT(ADMUX, REFS1);
        SET_BIT(ADMUX, REFS0);
        break;

    case ADC_REFERANCE_INTERNAL:
        SET_BIT(ADMUX, REFS1);
        SET_BIT(ADMUX, REFS0);
        break;
    }

    /* 2. Set Right Adjust (10-bit resolution) */
    CLR_BIT(ADMUX, ADLAR);

    /* 3. Set Prescaler: Division Factor 64 */
    SET_BIT(ADCSRA, ADPS2);
    SET_BIT(ADCSRA, ADPS1);
    CLR_BIT(ADCSRA, ADPS0);

    /* 4. Disable Auto Trigger */
    CLR_BIT(ADCSRA, ADATE);

    /* 5. Enable ADC Peripheral */
    SET_BIT(ADCSRA, ADEN);
}

/* Synchronous Read (Polling) */
u16 ADC_u16ReadChannelSync(u8 ChannelNum)
{
    /* 1. Clear MUX bits (0..4) and insert Channel Number */
    ADMUX = (ADMUX & 0xE0) | (ChannelNum & 0x1F);

    /* 2. Start Conversion */
    SET_BIT(ADCSRA, ADSC);

    /* 3. Polling: Wait until conversion is complete */
    while (READ_BIT(ADCSRA, ADSC) == 1);

    /* 4. Clear Interrupt Flag by setting it to 1 */
    SET_BIT(ADCSRA, ADIF);

    /* 5. Return 10-bit ADC data */
    return ADC_DATA_REG;
}

/* Asynchronous Read (Interrupt) */
void ADC_StartConversionAsync(u8 ChannelNum)
{
    /* 1. Clear MUX bits (0..4) and insert Channel Number */
    ADMUX = (ADMUX & 0xE0) | (ChannelNum & 0x1F);

    /* 2. Clear pending interrupt flag before enabling interrupt */
    SET_BIT(ADCSRA, ADIF);

    /* 3. Enable ADC Interrupt */
    SET_BIT(ADCSRA, ADIE);

    /* 4. Start Conversion */
    SET_BIT(ADCSRA, ADSC);
}

/* Set Callback Function */
void ADC_SetCallback(void (*Copy_pvNotification)(u16 Copy_u16Val))
{
    if (Copy_pvNotification != NULL)
    {
        ADC_pvCallBackNotificationFunc = Copy_pvNotification;
    }
}

/* ISR for ADC Conversion Complete */
void __vector_16(void) __attribute__((signal, used));
void __vector_16(void)
{
    if (ADC_pvCallBackNotificationFunc != NULL)
    {
        /* Disable interrupt until next manual trigger */
        CLR_BIT(ADCSRA, ADIE);

        /* Read conversion value and pass it to user callback */
        ADC_pvCallBackNotificationFunc(ADC_DATA_REG);
    }
}
