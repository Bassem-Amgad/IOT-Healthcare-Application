/*
 * main.c
 *
 *  Created on: 8 Dec 2017
 *      Author: Bassem
 */
#include <util/delay.h>
#include "Types.h"
#include "DIO.h"
#include "SPI.h"
#include "LCD.h"

#define asci_conv 48
#define end_transfer 16
u8 arr[4];
int main(void)
{
	SPI_Init();
	LCD_voidInit ();
	LCD_voidWriteCommand(0x80);
	extern u8 SPDR_NewValue;
	extern u8 flag;
	u8 read_data=0;
	u8 data_arr[2];
	u8 spi_case=1;
	u8 temp_value=0;
	u8 bpm_value=0;
	u8 ox_value=0;
	if (spi_case==1)
			{
				temp_value=36;
				bpm_value=82;
				ox_value=93;
			}
			else if (spi_case==2)
			{
				temp_value=36;
				bpm_value=82;
				ox_value=93;
			}

	arr[0]=temp_value;
	arr[1]=bpm_value;
	arr[2]=ox_value;
	arr[3]=end_transfer;
	while(1)
	{
		if (flag==1)
		{
			read_data = SPDR_NewValue;
			for (u8 i=0 ; i<2 ; i++)
				{
					data_arr[i]=(read_data%10);
					read_data /= 10;
				}
			LCD_voidDisplay(asci_conv+data_arr[1]);
			LCD_voidDisplay(asci_conv+data_arr[0]);
			LCD_voidDisplay(' ');
			flag=0;
			//_delay_us(50);
		}
	}
}
