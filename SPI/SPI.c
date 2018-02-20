/*
 * SPI.c
 *
 * Created: 2/20/2018 2:57:28 AM
 *  Author: Youssef
 */

#include "DIO.h"
#include "SPI.h"
#include "SPI_Cfg.h"
#include "common.h"

const SPI_CfgType * CfgPtr;

void SPI_masterInit(void)
{
	CfgPtr = &SPI_ConfigParam [0];
	DIO_PinDirection(SS_SPI,OUTPUT);
	DIO_PinDirection(MISO,INPUT);
	DIO_PinDirection(MOSI,OUTPUT);
	DIO_PinDirection(SCK,OUTPUT);
	DIO_WritePin(SS_SPI,HIGH);
	SPCR |=(1<<6)|(CfgPtr->SPI_Type<<4)|(CfgPtr->Clock_Sel0<<0);
	}


void SPI_Transmit(char cData)
{
	SPDR=cData;
	while(!(Get_Bit(SPSR,7)));
}

void SPI_Recieve(char *data){
	while(!(Get_Bit(SPSR,7)));
	*data=SPDR;
}
