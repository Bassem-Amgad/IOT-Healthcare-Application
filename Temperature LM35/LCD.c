/*
 * LCD.c
 *
 *  Created on: 8 Sep 2017
 *      Author: Bassem
 */
#include <util/delay.h>
#define F_CPU 8000000
#include "Types.h"
#include "utilss.h"
#include "DIO.h"
#include "LCD.h"

extern void LCD_voidInit (void)
{
	// define 3 Control Pins
	DIO_voidSetDirection (DIO_u8PinB0,DIO_u8PinOp);//E
	DIO_voidSetDirection (DIO_u8PinB1,DIO_u8PinOp);//RS
	DIO_voidSetDirection (DIO_u8PinB2,DIO_u8PinOp);//RW

	// define 8 data Pins
	DIO_voidSetDirection (DIO_u8PinC0,DIO_u8PinOp);//D0
	DIO_voidSetDirection (DIO_u8PinC1,DIO_u8PinOp);//D1
	DIO_voidSetDirection (DIO_u8PinC2,DIO_u8PinOp);//D2
	DIO_voidSetDirection (DIO_u8PinC3,DIO_u8PinOp);//D3
	DIO_voidSetDirection (DIO_u8PinC4,DIO_u8PinOp);//D4
	DIO_voidSetDirection (DIO_u8PinC5,DIO_u8PinOp);//D5
	DIO_voidSetDirection (DIO_u8PinC6,DIO_u8PinOp);//D6
	DIO_voidSetDirection (DIO_u8PinC7,DIO_u8PinOp);//D7

	_delay_ms(30);
	LCD_voidWriteCommand(0b00111000);// font=0,n=1
	_delay_ms(40);
	LCD_voidWriteCommand(0b00001110);
	_delay_ms(40);
	LCD_voidWriteCommand(0b00000001);
	_delay_ms(2);
	//LCD_voidWriteCommand(0b00000001); // Entry mode set

}

extern void LCD_voidWriteCommand(u8 command)
{
	// RS=0 to make command
	DIO_voidWritePIN(DIO_u8PinB1,DIO_u8LOW);

	// RW=0 to write
	DIO_voidWritePIN(DIO_u8PinB2,DIO_u8LOW);

	// read the command
	PORTC=command;

	// enable the EN pin for 2ms then disable it
	DIO_voidWritePIN(DIO_u8PinB0,DIO_u8HIGH);
	_delay_ms (2);
	DIO_voidWritePIN(DIO_u8PinB0,DIO_u8LOW);
}

extern void LCD_voidDisplay(u8 data)
{
	// RS=1 to dispaly
		DIO_voidWritePIN(DIO_u8PinB1,DIO_u8HIGH);

	// RW=0 to write
	DIO_voidWritePIN(DIO_u8PinB2,DIO_u8LOW);

	// read the data
	PORTC=data;

	// enable the EN pin for 2ms then disable it
	DIO_voidWritePIN(DIO_u8PinB0,DIO_u8HIGH);
	_delay_ms (2);
	DIO_voidWritePIN(DIO_u8PinB0,DIO_u8LOW);
}

/*
#include "DIO.h"
#include "LCD.h"

int main(void)
{
LCD_voidInit();
LCD_voidDisplay("M");
	While(1)
		{

		}
return 0;
}

 */
