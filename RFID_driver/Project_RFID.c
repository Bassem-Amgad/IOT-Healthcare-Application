#include "common.h"
#include "SPI.h"
#include "DIO.h"
#include "RFID.h"
#include "LCD.h"
#define F_CPU 8000000ul
#include <util/delay.h>
#include "UART.h"


int main(void)
{   unsigned char byte;
	unsigned char str[MAX_LEN];
	unsigned char flag=0 ;
	typedef struct{
		unsigned char new[4];
		unsigned char old[4];
		}ID;
	
	ID id;
	id.new[0]=55;
	unsigned char count=0;
	
   
    SPI_masterInit();
	RFID_Init();
	UART_Init();
	LCD_init();
	
	
	UART_Transmit_String("DATA,1\r");
	
	
	while(1)
    {
		
		byte  = mfrc522_request(PICC_CMD_WUPA,str);
		if(byte == CARD_FOUND )
		{
			    byte = mfrc522_get_card_serial(id.old);
		        if((id.old[0]==id.new[0]) & (id.old[1]==id.new[1]) &(id.old[2]==id.new[2]) & (id.old[3]==id.new[3]))
				{
				flag=1 ;
				}
			    else
			    {
			    flag=0;
			    }
			    if(flag==0){
					
				for(int i =0;i<4;i++)
				
				    {   	
						
					id.new[i]=id.old[i];
					Hexa_UART(id.old[i]);
					LCD_WriteHexaDecimal(id.old[i],0x80+i*2);
					}
					UART_Transmit_String("\r");
				}
			    else if (flag==1)
				{
				count++;
				if(count==100){
				id.new[0]=~id.old[0];
				count=0;}
			    }	
		   }
    }
}


