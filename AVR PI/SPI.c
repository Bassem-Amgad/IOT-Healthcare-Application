
#include "DIO.h"
#include "SPI.h"
#include "utilss.h"

u8 SPDR_NewValue=0;
u8 flag=1;
extern u8 arr[4];
const SPI_CfgType * CfgPtr;

void SPI_Init(void)
{
	CfgPtr = &SPI_ConfigParam [0];
	// Enable Global Interrupt
	set_bit(SREG,7);
	if (CfgPtr->SPI_Type==1)
		{
			DIO_voidSetDirection(MISO,DIO_u8PinIp);
			DIO_voidSetDirection(MOSI,DIO_u8PinOp);
			DIO_voidSetDirection(SS_Low,DIO_u8PinOp);
			DIO_voidSetDirection(SCK,DIO_u8PinOp);
			SPCR |= 1<<7 | 1<<6 | CfgPtr->Data_Order << 5 | CfgPtr->SPI_Type << 4 | CfgPtr->Clock_Polarity << 3 | CfgPtr->Clock_Phase << 2 |CfgPtr->Clock_Sel1 << 1 |CfgPtr->Clock_Sel0 << 0;
			//SPSR |= CfgPtr->Clock_Sel2 << 0;
		}
	else if (CfgPtr->SPI_Type==0)
		{
			DIO_voidSetDirection(MISO,DIO_u8PinOp);
			DIO_voidSetDirection(MOSI,DIO_u8PinIp);
			DIO_voidSetDirection(SS_Low,DIO_u8PinIp);
			DIO_voidSetDirection(SCK,DIO_u8PinIp);
			SPCR |= 1<<7 | 1<<6 | CfgPtr->SPI_Type << 4 ;
		}
}

void SPI_Transmit(u8 data){
	SPDR=data;
	while (!get_bit(SPSR,7));
	u8 temp = SPDR;
}
void SPI_Recieve(u8 *data){
	
	SPI_Transmit(0x00);
	while (!get_bit(SPSR,7));
	SPDR_NewValue=SPDR;
	*data=SPDR;
}
void __vector_12 (void)  __attribute__((signal,__INTR_ATTRS));
void __vector_12 (void)
{
	flag=1;
	static u8 transfer_counter=0;
	SPDR_NewValue=SPDR;
	if (SPDR_NewValue==(10+transfer_counter))
	{
		SPDR=arr[transfer_counter];
		transfer_counter++;
	}
	if (transfer_counter==4)
	{
		transfer_counter=0;
	}
}
