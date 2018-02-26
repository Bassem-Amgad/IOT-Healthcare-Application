#include "DIO.h"
#include "LCD.h"
#include "common.h"
 
#define F_CPU (12000000ul)
#include <util/delay.h>



 void LCD_WriteCommand(char command) {
	 DIO_WritePin(LCD_RSPin,0);
	 DIO_WritePin(LCD_RWPin,0);
	 //
	 DIO_WritePin(LCD_D7,Get_Bit(command,7));
	 DIO_WritePin(LCD_D6,Get_Bit(command,6));
	 DIO_WritePin(LCD_D5,Get_Bit(command,5));
	 DIO_WritePin(LCD_D4,Get_Bit(command,4));
	 //
	 DIO_WritePin(LCD_ENPin,1);
	 _delay_us(10);
	 DIO_WritePin(LCD_ENPin,0);
	 //
	DIO_WritePin(LCD_D7,Get_Bit(command,3));
	DIO_WritePin(LCD_D6,Get_Bit(command,2));
	DIO_WritePin(LCD_D5,Get_Bit(command,1));
	DIO_WritePin(LCD_D4,Get_Bit(command,0));
	 //
	 DIO_WritePin(LCD_ENPin,1);
	 _delay_us(10);
	 DIO_WritePin(LCD_ENPin,0);
	 _delay_us(10);
	 
	
}
void LCD_init() {
	
	DIO_PinDirection(LCD_RSPin,OUTPUT);
	DIO_PinDirection(LCD_RWPin,OUTPUT);
	DIO_PinDirection( LCD_ENPin,OUTPUT);
	DIO_PinDirection(LCD_D7,OUTPUT);
	DIO_PinDirection(LCD_D6,OUTPUT);
	DIO_PinDirection(LCD_D5,OUTPUT);
	DIO_PinDirection(LCD_D4,OUTPUT);
	
	_delay_ms(15);
	LCD_WriteCommand(0x33);
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);
	LCD_WriteCommand(0x0c);
	LCD_WriteCommand(0x01);
	_delay_us(2000);
	LCD_WriteCommand(0x06);
	_delay_us(1000);
	
	
}
void LCD_WriteString(char *str){
	
	while(*str>0){
		LCD_WriteData(  *str );
		str++;
		
	}
	
}
void LCD_WriteData(  char data ){
	DIO_WritePin(LCD_RSPin,1);
	DIO_WritePin(LCD_RWPin,0);
	DIO_WritePin(LCD_D7,Get_Bit(data,7));
	DIO_WritePin(LCD_D6,Get_Bit(data,6));
	DIO_WritePin(LCD_D5,Get_Bit(data,5));
	DIO_WritePin(LCD_D4,Get_Bit(data,4));
	DIO_WritePin(LCD_ENPin,1);
	_delay_us(10);
	DIO_WritePin(LCD_ENPin,0);
	DIO_WritePin(LCD_D7,Get_Bit(data,3));
	DIO_WritePin(LCD_D6,Get_Bit(data,2));
	DIO_WritePin(LCD_D5,Get_Bit(data,1));
	DIO_WritePin(LCD_D4,Get_Bit(data,0));
	DIO_WritePin(LCD_ENPin,1);
	_delay_us(10);
	DIO_WritePin(LCD_ENPin,0);
	_delay_us(10);
	
}
void LCD_WriteInt (char data,char itoa_const[]){
	itoa(data,itoa_const,10);
	LCD_WriteString(itoa_const);
}