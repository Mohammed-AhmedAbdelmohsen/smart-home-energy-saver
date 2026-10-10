/*
 * ADC.c
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "ADC.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef READ_BIT
#define READ_BIT(REG, BIT) (((REG) >> (BIT)) & 1)
#endif

static void (*ADC_pvCallBackNotificationFunc)(u16) = NULL;

void ADC_Init(u8 ADC_ref)
{
    /* 1. Set the reference voltage */
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

    /* 2. Set right alignment for a complete 10-bit read */
    CLR_BIT(ADMUX, ADLAR);

    /* 3. Prescaler = 64 (125kHz frequency at 8MHz) */
    SET_BIT(ADCSRA, ADPS2);
    SET_BIT(ADCSRA, ADPS1);
    CLR_BIT(ADCSRA, ADPS0);

    /* 4. Disable Auto Trigger */
    CLR_BIT(ADCSRA, ADATE);

    /* 5. Enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

/* Synchronous read */
u16 ADC_u16ReadChannelSync(u8 ChannelNum)
{
    /* 1. Select the channel */
    ADMUX = (ADMUX & 0xE0) | (ChannelNum & 0x07);

    /* 2. Start conversion */
    SET_BIT(ADCSRA, ADSC);

    /* 3. Wait until conversion completes */
    while (READ_BIT(ADCSRA, ADIF) == 0);

    /* 4. Clear the Flag */
    SET_BIT(ADCSRA, ADIF);

    /* 5. Return the value */
    return ADC_DATA_REG;
}

void ADC_StartConversionAsync(u8 ChannelNum)
{
    ADMUX = (ADMUX & 0xE0) | (ChannelNum & 0x07);
    SET_BIT(ADCSRA, ADIF);
    SET_BIT(ADCSRA, ADIE);
    SET_BIT(ADCSRA, ADSC);
}

void ADC_SetCallback(void (*Copy_pvNotification)(u16 Copy_u16Val))
{
    if (Copy_pvNotification != NULL)
    {
        ADC_pvCallBackNotificationFunc = Copy_pvNotification;
    }
}

void __vector_16(void) __attribute__((signal, used));
void __vector_16(void)
{
    if (ADC_pvCallBackNotificationFunc != NULL)
    {
        CLR_BIT(ADCSRA, ADIE);
        ADC_pvCallBackNotificationFunc(ADC_DATA_REG);
    }
}