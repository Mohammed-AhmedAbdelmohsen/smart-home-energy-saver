/*
 * ADC.h

 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../LIB/STD_TYPES.h"

/* Registers Definitions */
#define ADMUX           *((volatile u8*)0x27)
#define ADCSRA          *((volatile u8*)0x26)
#define ADCH            *((volatile u8*)0x25)
#define ADCL            *((volatile u8*)0x24)

/* 16-bit register access for full 10-bit resolution */
#define ADC_DATA_REG    *((volatile u16*)0x24)

/* ADMUX Bits */
#define MUX0            0
#define MUX1            1
#define MUX2            2
#define MUX3            3
#define MUX4            4
#define ADLAR           5
#define REFS0           6
#define REFS1           7

/* ADCSRA Bits */
#define ADPS0           0
#define ADPS1           1
#define ADPS2           2
#define ADIE            3
#define ADIF            4
#define ADATE           5
#define ADSC            6
#define ADEN            7

/* ADC Channels */
#define ADC_CHANNEL0    0
#define ADC_CHANNEL1    1
#define ADC_CHANNEL2    2
#define ADC_CHANNEL3    3
#define ADC_CHANNEL4    4
#define ADC_CHANNEL5    5
#define ADC_CHANNEL6    6
#define ADC_CHANNEL7    7

/* Voltage Reference Options */
#define ADC_REFERANCE_EXTERNAL   0
#define ADC_REFERANCE_AVCC       1
#define ADC_REFERANCE_INTERNAL   2

/* Function Prototypes */
void ADC_Init(u8 ADC_ref);
u16  ADC_u16ReadChannelSync(u8 ChannelNum);
void ADC_StartConversionAsync(u8 ChannelNum);
void ADC_SetCallback(void (*Copy_pvNotification)(u16 Copy_u16Val));

#endif /* MCAL_ADC_ADC_H_ */
