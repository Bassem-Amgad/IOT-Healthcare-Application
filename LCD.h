/*
 * LCD.h
 *
 * Created: 10/20/2016 6:14:18 PM
 *  Author: m.mamdooh
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_CLRDISP    0x01

////////////////////////////////////////////////////////
////////// prototypes /////////////////////////////////
//////////////////////////////////////////////////////
void LCD_WriteCommand(  char command ) ;
void LCD_init() ;
void LCD_WriteString(char *str);
void LCD_WriteData( char data );
void LCD_WriteInt (char data,char itoa_const[]);
void LCD_WriteHexaDecimal(unsigned char data,unsigned char Pos1);
//////////////////////////////////////////////////////
//////////////// Configuration //////////////////////
////////////////////////////////////////////////////
#define LCD_RSPin 9
#define LCD_RWPin 10
#define LCD_ENPin 11
#define LCD_D7 7
#define LCD_D6 6
#define LCD_D5 5
#define LCD_D4 4

#define LCD_Port 0




#endif /* LCD_H_ */