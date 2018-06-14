/*
 * Project_RFID.c
 *
 * Created: 26/4
 *  Author: Youssef
 */ 


#include "SPI.h"
#include "DIO.h"
#include "RFID.h"
#include "LCD.h"
#define F_CPU 8000000ul
#include <util/delay.h>
#include "UART.h"



int main(void)
{  unsigned char byte;
	unsigned char str[MAX_LEN];
	unsigned char V[3];
	 LCD_init();
	SPI_masterInit();
	RFID_Init();
	UART_Init();
		
		
	while(1)
    {
		 byte  = mfrc522_request(PICC_CMD_WUPA,str);
		
		
		if(byte == CARD_FOUND)
		{
			DIO_PinDirection(30,OUTPUT);
			DIO_WritePin(30,HIGH);
			byte = mfrc522_get_card_serial(str);
			if(byte == CARD_FOUND)
			{
				for(int i =0;i<4;i++){
				 UART_Transmit(str[i]);
				
				
				_delay_ms(1000);
				}
		
			}
		
			else
			{
				
			}
		}
		
		_delay_ms(1000);
		
			
    }
}