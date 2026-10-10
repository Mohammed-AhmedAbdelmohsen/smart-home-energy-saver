/*
 * ADC.h

 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../LIB/STD_TYPES.h"

/* ==================================================================== */
/*                           ADC REGISTERS                              */
/* ==================================================================== */

#define ADMUX           (*(volatile u8*)(0x27))
#define ADCSRA          (*(volatile u8*)(0x26))
#define ADCH            (*(volatile u8*)(0x25))
#define ADCL            (*(volatile u8*)(0x24))
#define ADC_DATA_REG    (*(volatile u16*)(0x24))
#define SFIOR           (*(volatile u8*)(0x50))

/* ADMUX Register Bits */
#define REFS1           7
#define REFS0           6
#define ADLAR           5
#define MUX4            4
#define MUX3            3
#define MUX2            2
#define MUX1            1
#define MUX0            0

/* ADCSRA Register Bits */
#define ADEN            7
#define ADSC            6
#define ADATE           5
#define ADIF            4
#define ADIE            3
#define ADPS2           2
#define ADPS1           1
#define ADPS0           0

/* SFIOR Register Bits (Auto Trigger Source) */
#define ADTS2           7
#define ADTS1           6
#define ADTS0           5

/* ==================================================================== */
/*                        ADC CONFIGURATIONS                            */
/* ==================================================================== */

/* Voltage Reference */
#define ADC_REFERANCE_EXTERNAL   1
#define ADC_REFERANCE_AVCC       2
#define ADC_REFERANCE_INTERNAL   3

/* ADC Channels */
#define ADC_CHANNEL0             0
#define ADC_CHANNEL1             1
#define ADC_CHANNEL2             2
#define ADC_CHANNEL3             3
#define ADC_CHANNEL4             4
#define ADC_CHANNEL5             5
#define ADC_CHANNEL6             6
#define ADC_CHANNEL7             7

/* ==================================================================== */
/*                        FUNCTION PROTOTYPES                           */
/* ==================================================================== */

void ADC_init(u8 ADC_ref);
u16  ADC_u16ReadChannelSync(u8 ChannelNum);
void ADC_StartConversionAsync(u8 ChannelNum);
void ADC_SetCallback(void (*Copy_pvNotification)(u16 Copy_u16Val));

#endif /* MCAL_ADC_ADC_H_ */
