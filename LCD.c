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
void Hexa(unsigned char decimal){
	switch(decimal){
		case 0:
		LCD_WriteString("0");
		break;
		case 1:
		LCD_WriteString("1");
		break;
		case 2:
		LCD_WriteString("2");
		break;
		case 3:
		LCD_WriteString("3");
		break;
		case 4:
		LCD_WriteString("4");
		break;
		case 5:
		LCD_WriteString("5");
		break;
		case 6:
		LCD_WriteString("6");
		break;
		case 7:
		LCD_WriteString("7");
		break;
		case 8:
		LCD_WriteString("8");
		break;
		case 9:
		LCD_WriteString("9");
		break;
		case 10:
		LCD_WriteString("A");
		break;
		case 11:
		LCD_WriteString("B");
		break;
		case 12:
		LCD_WriteString("C");
		break;
		case 13:
		LCD_WriteString("D");
		break;
		case 14:
		LCD_WriteString("E");
		break;
		case 15:
		LCD_WriteString("F");
		break;
		
	}
}
void LCD_WriteHexaDecimal(unsigned char data,unsigned char Pos1){
unsigned char left_nibble_data,right_nibble_data ;
right_nibble_data =(data & 0x0f);
left_nibble_data=(data & 0xf0)>>4;
LCD_WriteCommand(Pos1);
 Hexa(left_nibble_data);
 LCD_WriteCommand(Pos1+1);
 Hexa(right_nibble_data);


}
