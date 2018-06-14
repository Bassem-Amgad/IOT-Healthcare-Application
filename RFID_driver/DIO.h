

#ifndef DIO_H_
#define DIO_H_


////////////////////////////////////////////////////////
////////// prototypes /////////////////////////////////
//////////////////////////////////////////////////////
void DIO_WritePin(char Pin_Num , char Val) ;
char DIO_ReadPin(char Pin_Num );
void DIO_WritePort(char Port_num , char Val) ;
void DIO_ReadPort(char Port_num , char *PtrToVal) ;
void DIO_PinDirection(char Pin_Num,char Val);
void DIO_PortDirection(char Port_num,char Val);

////////////////////////////////////////////////////////
////////// addresses /////////////////////////////////
//////////////////////////////////////////////////////

#define DDRA *((volatile char*)0x3A)
#define PINA *((volatile char*)0x39)
#define PORTA *((volatile char*)0x3B)

#define DDRB *((volatile char*)0x37)
#define PINB *((volatile char*)0x36)
#define PORTB *((volatile char*)0x38)

#define DDRC *((volatile char*)0x34)
#define PINC *((volatile char*)0x33)
#define PORTC *((volatile char*)0x35)

#define DDRD *((volatile char*)0x31)
#define PIND *((volatile char*)0x30)
#define PORTD *((volatile char*)0x32)
//////////////////////////////////////////////////////
//////////////// configuration ////////////////////////////
////////////////////////////////////////////////////
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0

#endif /* DIO_H_ */