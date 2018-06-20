/*
 * ADC.c

 *
 *  Created on: ??þ/??þ/????
 *      Author: wsalat.com
 */
#include "Types.h"
#include "ADc.h"

void ADC_voidInit(void){

	ADMUX =0x40;
	ADCSRA =0x87;
	}

u16 ADC_u16Convert (u8 channel_num){
	u16 data;
	channel_num=channel_num&0b00000111;
	ADMUX |=channel_num;
	ADCSRA |=(1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	data=ADCL;
	data |=(ADCH<<8);
	return data;
}
