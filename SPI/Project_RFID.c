/*
 * Project_RFID.c
 *
 * Created: 2/23/2018 11:51:04 PM
 *  Author: Youssef
 */ 


#include "SPI.h"
#include "DIO.h"
#include "RFID.h"
#include "LCD.h"




int main(void)
{   LCD_init();
	SPI_masterInit();
	
	char y;
	char z[2];
	
    while(1)
    {
		RFID_writeToRegister(FIFODataReg ,255);
		y= RFID_readFromRegister(FIFODataReg);
		LCD_WriteCommand(0x80);
		LCD_WriteInt(y,z);
		
    }
}