/*
 * ADC.c
 *
 *  Created on: 22 Sep 2017
 *      Author: Bassem
 */

#include "Types.h"
#include "utilss.h"
#include "DIO.h"
#include "ADC.h"


#define ADMUX *((u8*) 0x27)
#define ADCSRA *((u8*) 0x26)
#define ADCH *((u8*) 0x25)
#define ADCL *((u8*) 0x24)

#define SREG *((u8*)0x5f)

const ADC_ConfigType* CfgPtr;
u16 ADC_Conversion=0;
u8 flag=0;
extern void ADC_voidInit(void)
{
	CfgPtr = &ADC_ConfigParam [0];
	// reference voltage = 5
	clr_bit(ADMUX,7);
	set_bit(ADMUX,6);
	// Left Adjust
	set_bit(ADMUX,5);
	// ADC Enable
	set_bit(ADCSRA,7);
	// No Auto Trigger
	clr_bit(ADCSRA,5);
	// interrupt
	set_bit(ADCSRA,3);
	// Prescaler
	ADCSRA |= CfgPtr->prescaler << 0;
}

extern void ADC_voidConvert(u8 pin_number)
{
	u8 ADC_pin[5] = {0,0,0,0,0};
	u8 i=0;
	while (pin_number!=0)
	{
		for (i=0 ; i<5 ; i++)
			{
				ADC_pin[i]=(pin_number%2);
				pin_number /= 2;
			}
	}
	ADMUX |= (ADC_pin[i-1]<<(i-1)) | (ADC_pin[i-2]<<(i-2)) | (ADC_pin[i-3]<<(i-3)) | (ADC_pin[i-4]<<(i-4)) | (ADC_pin[i-5]<<(i-5));
	set_bit(SREG,7);
	set_bit(ADCSRA,6);
}

void __vector_16 (void)
{
	flag=1;
	set_bit(ADCSRA,4);
	ADC_Conversion |= ((get_bit(ADCL,6))<<0) |((get_bit(ADCL,7))<<1) | (ADCH <<2);
}
