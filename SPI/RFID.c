/*
 * RFID.c
 *
 * Created: 2/24/2018 2:13:12 AM
 *  Author: Youssef
 */ 
#define F_CPU (12000000ul)
#include <util/delay.h>
#include "RFID.h"
#include "DIO.h"
#include "SPI.h"
void RFID_writeToRegister(char  addr, char  val) {
	DIO_WritePin(SS_SPI,LOW);  //RFID enable PIN

	//Address format: 0XXXXXX0
	SPI_Transmit((addr<<1)&0x7E);
	SPI_Transmit(val);
	DIO_WritePin(SS_SPI,HIGH);
	
}

char RFID_readFromRegister(char addr) {
	char val;
	DIO_WritePin(SS_SPI,LOW);
	SPI_Transmit(((addr<<1)&0x7E) | 0x80);
	SPI_Recieve(&val);
	DIO_WritePin(SS_SPI,HIGH);
	return val;
}
