#include "common.h"
#include "UART.h"
#include "DIO.h"
#include <avr/io.h>

void UART_Init(void ){
	DIO_PinDirection(24,INPUT);
	DIO_PinDirection(25,OUTPUT);
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
