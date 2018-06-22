
#define BAUDRATE  9600UL
#define FCPU     8000000UL
////////////////////////////////////////////////////////
////////// prototypes /////////////////////////////////
//////////////////////////////////////////////////////
void UART_Init(void );
void UART_Transmit( int Data ) ;
void UART_Receive( char *PtrToData );
void UART_Transmit_String(unsigned char *str);
unsigned char Hexa_return(unsigned char decimal);
void Hexa_UART(unsigned char data);

//////////////////////////////////////////////////////
//////////////// Configuration //////////////////////
////////////////////////////////////////////////////
#define UBRR_INIT   ((FCPU)/(BAUDRATE*16UL)-1UL)
#define UCSRA_INIT   0b00000000
#define UCSRB_INIT   0b00011000
#define UCSRC_INIT   0b10000110	
