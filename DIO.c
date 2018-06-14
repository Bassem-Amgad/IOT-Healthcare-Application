
#include  "common.h"
#include "DIO.h"

void DIO_PinDirection(char Pin_Num,char Val){
	char loc_port_num=Pin_Num/8;
	char loc_pin_index=Pin_Num%8;
	switch(loc_port_num){
		case 0:
		if(Val==INPUT){
			Clear_Bit(DDRA,loc_pin_index);
		}
		else if(Val==OUTPUT){
			Set_Bit(DDRA,loc_pin_index);
		}
		break;
		case 1:
		if(Val==INPUT){
			Clear_Bit(DDRB,loc_pin_index);
		}
		else if(Val==OUTPUT){
			Set_Bit(DDRB,loc_pin_index);
		}
		break;
		case 2:
		if(Val==INPUT){
			Clear_Bit(DDRC,loc_pin_index);
		}
		else if(Val==OUTPUT){
			Set_Bit(DDRC,loc_pin_index);
		}
		break;
		case 3:
		if(Val==INPUT){
			Clear_Bit(DDRD,loc_pin_index);
		}
		else if(Val==OUTPUT){
			Set_Bit(DDRD,loc_pin_index);
		}
		break;
	}
	
}
void DIO_PortDirection(char port_num,char Val){
	switch(port_num){
		case 0:
		if(Val==INPUT){
			DDRA=0x00;
		}
		else if(Val==OUTPUT){
			DDRA=0xff;
		}
		break;
		case 1:
		if(Val==INPUT){
			DDRB=0x00;
		}
		else if(Val==OUTPUT){
			DDRB=0xff;
		}
		break;
		case 2:
		if(Val==INPUT){
			DDRC=0x00;
		}
		else if(Val==OUTPUT){
			DDRC=0xff;
		}
		break;
		case 3:
		if(Val==INPUT){
			DDRD=0x00;
		}
		else if(Val==OUTPUT){
			DDRD=0xff;
		}
		break;
	}
}


	

void DIO_WritePin(char Pin_Num , char Val){
	char loc_port_num=Pin_Num/8;
	char loc_pin_index=Pin_Num%8;
	switch(loc_port_num){
		case 0:
		if(Val==0){
			Clear_Bit(PORTA,loc_pin_index);
			}
		else if(Val==1){
			Set_Bit(PORTA,loc_pin_index);
		}
		break;
		case 1:
		if(Val==0){
			Clear_Bit(PORTB,loc_pin_index);
		}
		else if(Val==1){
			Set_Bit(PORTB,loc_pin_index);
		}
		break;
		case 2:
		if(Val==0){
			Clear_Bit(PORTC,loc_pin_index);
		}
		else if(Val==1){
			Set_Bit(PORTC,loc_pin_index);
		}
		break;
		case 3:
		if(Val==0){
			Clear_Bit(PORTD,loc_pin_index);
		}
		else if(Val==1){
			Set_Bit(PORTD,loc_pin_index);
		}
		break;
	}
	
}
void DIO_WritePort(char Port_num , char Val){

        
		 switch(Port_num){
			 case 0:
			 break;
			 PORTA=Val;
			 case 1:
			 PORTB=Val;
			 break;
			 case 2:
			 PORTC=Val;
			 break;
			 case 3:
			 PORTD=Val;
			 break;
}
}
char DIO_ReadPin(char Pin_Num ) {
	char loc_port_num=Pin_Num/8;
	char loc_pin_index=Pin_Num%8;
	char val ;
	switch(loc_port_num){
		case 0:
		val=Get_Bit(PINA,loc_pin_index);
		break;
		case 1:
		val=Get_Bit(PINB,loc_pin_index);
		break;
		case 2:
		val=Get_Bit(PINC,loc_pin_index);
		break;
		case 3:
		val=Get_Bit(PIND,loc_pin_index);
		break;
	}
	return val;
}
