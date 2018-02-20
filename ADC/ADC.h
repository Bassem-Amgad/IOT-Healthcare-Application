/*
 * ADC.h
 *
 *  Created on: 22 Sep 2017
 *      Author: Bassem
 */
#include "Types.h"
#include "ADC_cfg.h"
#ifndef ADC_H_
#define ADC_H_

typedef enum {Divide_2=1, Divide_4=2,Divide_8=3,Divide_16=4,Divide_32=5,Divide_64=6,Divide_128=7} ADC_CLKPrescaler;
typedef struct
{
	//ADC_ConversionSize Bit_Size;
	/*ADPS2 ADPS1 ADPS0 Division Factor
		0 	 0     0         2
		0	 0     1       	 2
		0 	 1     0         4
		0 	 1     1         8
		1 	 0     0         16
		1 	 0     1         32
		1 	 1     0         64
		1 	 1     1 	    128*/
	ADC_CLKPrescaler prescaler;
}ADC_ConfigType;
extern const ADC_ConfigType ADC_ConfigParam[ADC_PERIF_NUM];

extern void ADC_voidInit (void);
extern void ADC_voidConvert(u8 pin_number);
void __vector_16 (void)  __attribute__((signal,__INTR_ATTRS));


#endif /* ADC_H_ */
