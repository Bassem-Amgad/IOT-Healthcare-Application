/*
 * ADC.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: wsalat.com
 */


#define ADMUX *(volatile u8*) 0x27
#define ADCSRA *(volatile u8*) 0x26
#define ADCH *(volatile u8*) 0x25
#define ADCL *(volatile u8*) 0x24
#define ADSC 6
#define ADIF 4

void ADC_voidInit (void);
u16 ADC_u16Convert (u8 channel_num);



