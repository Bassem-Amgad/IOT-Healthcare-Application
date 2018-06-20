/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: wsalat.com
 */
#include "Types.h"
#include "DIO.h"
#include "ADC.h"
#include "LCD.h"
#include <util/delay.h>

#define vol_ref 5
#define scale 100 //10mv--> 1c
#define asci_conv 48

int main (void)
{
	u8 data_arr[3];
	u16 conv_reading=0;
	u8 temp_scaled_value;
	ADC_voidInit();
	LCD_voidInit();
	LCD_voidWriteCommand(0x80);
	LCD_voidDisplay('T');
	LCD_voidDisplay('E');
	LCD_voidDisplay('M');
	LCD_voidDisplay('P');
	LCD_voidDisplay(':');

	while(1){
		conv_reading=ADC_u16Convert(1);
		temp_scaled_value = (conv_reading*vol_ref*scale/1024);
		for (u8 i=0 ; i<3 ; i++)
			{
				data_arr[i]=(temp_scaled_value%10);
				temp_scaled_value /= 10;
			}
		_delay_ms(20);
		LCD_voidWriteCommand(0x86);
		LCD_voidDisplay(asci_conv+data_arr[2]);
		LCD_voidDisplay(asci_conv+data_arr[1]);
		LCD_voidDisplay(asci_conv+data_arr[0]);
	}
	return 0;
}
