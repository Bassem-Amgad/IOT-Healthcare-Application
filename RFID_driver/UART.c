#include "common.h"
#include "UART.h"
#include <avr/io.h>

void UART_Init(void ){
	UCSRA=UCSRA_INIT;
	Clear_Bit(UBRRH,7);
	UBRRH=(char)(UBRR_INIT>>8);
	UBRRL=(char)(UBRR_INIT);
	UCSRB=UCSRB_INIT;
	Set_Bit(UCSRC,7);
	UCSRC=UCSRC_INIT ;
	
}
void UART_Transmit( int Data ) {
		
		while((Get_Bit(UCSRA,5))==0);
		UDR=Data;
		
}
void UART_Receive( char *PtrToData ){
	while((Get_Bit(UCSRA,7))==0);
	*PtrToData=UDR;
}

void UART_Transmit_String( unsigned char *str) {
	while(*str>0){
	UART_Transmit(*str);
	str++;}
	
}
void Hexa_UART(unsigned char data){
	unsigned char left_nibble_data,right_nibble_data ;
	unsigned char hexa_left_nibble,hexa_right_nibble;
	right_nibble_data =(data & 0x0f);
	left_nibble_data=(data & 0xf0)>>4;
	
	hexa_left_nibble=Hexa_return(left_nibble_data);
	UART_Transmit_String(hexa_left_nibble);
	hexa_right_nibble=Hexa_return(right_nibble_data);
	UART_Transmit_String(hexa_right_nibble);


}

unsigned char Hexa_return(unsigned char decimal){
	unsigned char hexa;
	switch(decimal){
		case 0:
		hexa="0";
		break;
		case 1:
		hexa="1";
		break;
		case 2:
		hexa="2";
		break;
		case 3:
		hexa="3";
		break;
		case 4:
		hexa="4";
		break;
		case 5:
		hexa="5";
		break;
		case 6:
		hexa="6";
		break;
		case 7:
		hexa="7";
		break;
		case 8:
		hexa="8";
		break;
		case 9:
		hexa="9";
		break;
		case 10:
		hexa="A";
		break;
		case 11:
		hexa="B";
		break;
		case 12:
		hexa="C";
		break;
		case 13:
		hexa="D";
		break;
		case 14:
		hexa="E";
		break;
		case 15:
		hexa="F";
		break;
		
	}
	return hexa;
}

