/*
 * UART.c
 *
 *  Created on: 7 Oct 2017
 *      Author: Bassem
 */

#include "Types.h"
#include "utilss.h"
#include "DIO.h"
#include "UART.h"

#define UDR *((u8*) 0x2c)
#define UCSRA *((u8*) 0x2b)
#define UCSRB *((u8*) 0x2a)
#define UBRRL *((u8*) 0x29)
#define UCSRC *((u8*) 0x40) //UBRRH
#define SREG *((u8*)0x5f)

#define OverRun_DelayTime 85
const UART_ConfigType* CfgPtr;
UART_State UART_CurrentState =UART_STATE_UNINIT;
u8 UART_NewValue=0;
u8 counter=0;

extern void  UART_voidInit (void)
{
	// Enable Global Interrupt
	set_bit(SREG,7);
	// UCSRB Bit 7 – RXCIE: RX Complete Interrupt Enable
	set_bit(UCSRB,7);
	// UCSRB Bit 6 – TXCIE: TX Complete Interrupt Enable
	set_bit(UCSRB,6);
	// UCSRB Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
	clr_bit(UCSRB,5);
	//UCSRB Bit 4 – RXEN: Receiver Enable
	set_bit(UCSRB,4);

	// UCSRA Bit 1 – U2X: Double the USART Transmission Speed
		/*
		 	  U2X			 Mode
				1 		Asynchronous Operation
				0 		Synchronous Operation
		 */
	UCSRA |= CfgPtr->Double_Asynch_Clock << 1;//set_bit(UCSRA,1);

	// UCSRC Bit 7 – URSEL: Register Select
		/*
			 This bit selects between accessing the UCSRC or the UBRRH Register
			 It is read as one when reading UCSRC.
			 It is read as zero when reading UBRRH
		 */
	set_bit(UCSRC,7);
	// UCSRC Bit 6 – UMSEL: USART Mode Select
		/*
		 UMSEL			 Mode
			0 		Asynchronous Operation
			1 		Synchronous Operation
		 */
	UCSRC |= CfgPtr->UART_Mode << 6;// clr_bit(UCSRC,6);

	//Bit 0 – UCPOL: Clock Polarity
	UCSRC |= CfgPtr->Clock_Polarity << 0;

	// UCSRC Bit 5:4 – UPM1:0: Parity Mode
		/*UPM1 UPM0 Parity Mode
		0 0 Disabled
		0 1 Reserved
		1 0 Enabled, Even Parity
		1 1 Enabled, Odd Parity*/
	UCSRC |= CfgPtr->Parity << 4; //clr_bit(UCSRC,5); clr_bit(UCSRC,4);
	// UCSRC Bit 3 – USBS: Stop Bit Select
		/*
		 USBS Stop Bit(s)
			0 1-bit
			1 2-bit
		 */
	UCSRC |= CfgPtr->Stop_Bits << 3;//clr_bit(UCSRC,3);
	// UCSRB Bit 2 – UCSZ2: Character Size
	// UCSRC Bit 2:1 – UCSZ1:0: Character Size    0 1 1 --> 8-bit
		 /*
		  UCSZ2 UCSZ1 UCSZ0 Character Size
			0 	 0 		0	 	5-bit
			0 	 0  	1 		6-bit
			0 	 1 		0 		7-bit
			0 	 1 		1 		8-bit
			1 	 0 		0 		Reserved
			1 	 0 		1 		Reserved
			1 	 1 		0 		Reserved
			1 	 1 		1		 9-bit
		  */
	clr_bit(UCSRB,2);
	UCSRC |= CfgPtr->Data_Size << 1;//set_bit(UCSRC,2); set_bit(UCSRC,1);
	if (CfgPtr->Data_Size == DATA_9)
	{
		set_bit(UCSRC,2);
		set_bit(UCSRC,1);
		set_bit(UCSRB,2);

	}
	// UCSRC Bit 7 – URSEL: Register Select
		/*
			 This bit selects between accessing the UCSRC or the UBRRH Register
			 It is read as one when reading UCSRC.
			 It is read as zero when reading UBRRH
		*/
	clr_bit(UCSRC,7);
	// Bit 14:12 – Reserved Bits
	/*
	 	 These bits are reserved for future use. For compatibility with future devices, these bit
		must be written to zero when UBRRH is written.
	 */
	clr_bit(UCSRC,6);
	clr_bit(UCSRC,5);
	clr_bit(UCSRC,4);
	//UBRRL and UBRRH Bit 11:0 – UBRR11:0: USART Baud Rate Register
			/*
			 BaudRate(bps) fosc = 8.0000 MHz
						U2X = 0 			U2X = 1

				2400		207					416
				4800		103					207
				9600		51  	      		103
				14400		34					68
				19200		25					51
				28800		16					34
				38400		12					25
				57600		8					16
				76800		6					12
				115200		3					8
				230400		1					3
				250000		1					3
				500000		0					1
			*/
	clr_bit(UCSRC,3);
	clr_bit(UCSRC,2);
	clr_bit(UCSRC,1);
	clr_bit(UCSRC,0);
	switch (CfgPtr->BaudRate)
	{
	case 2400:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=207;
			}
		else
			{
				set_bit(UCSRC,0); // 416-2^8 =160
				UBRRL=160;
			}
		break;
	case 4800:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=103;
			}
		else
			{
				UBRRL=207;
			}
		break;
	case 9600:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=51;
			}
		else
			{
				UBRRL=103;
			}
		break;
	case 14400:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=34;
			}
		else
			{
				UBRRL=68;
			}
		break;
	case 19200:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=25;
			}
		else
			{
				UBRRL=51;
			}
		break;
	case 28800:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=16;
			}
		else
			{
				UBRRL=34;
			}
		break;
	case 38400:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=12;
			}
		else
			{
				UBRRL=25;
			}
		break;
	case 57600:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=8;
			}
		else
			{
				UBRRL=16;
			}
		break;
	case 76800:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=6;
			}
		else
			{
				UBRRL=12;
			}
		break;
	case 115200:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=3;
			}
		else
			{
				UBRRL=8;
			}
		break;
	case 230400:
	case 250000:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=1;
			}
		else
			{
				UBRRL=3;
			}
		break;
	case 500000:
		if (CfgPtr->Double_Asynch_Clock ==0)
			{
				UBRRL=0;
			}
		else
			{
				UBRRL=1;
			}
		break;
	default:
		break;
	}
	UART_CurrentState =UART_STATE_INIT;
}

extern u8  UART_u8Transmit (u8 data)
{
	UART_ChkType RetVar;
	if ((UART_CurrentState == UART_STATE_INIT) && (counter > OverRun_DelayTime))
		{
			UART_CurrentState =UART_STATE_TX_ONGOING;
			//UCSRB Bit 3 – TXEN: Transmitter Enable
			set_bit(UCSRB,3);
			UDR=data;
			counter=0;
			RetVar = UART_OK;
		}
	else
		{
			counter++;
			RetVar = UART_NOK;
		}
	return RetVar;

}

void __vector_13 (void)  __attribute__((signal,__INTR_ATTRS));
void __vector_13 (void)
{
	UART_CurrentState =UART_STATE_RX_DONE;
	UART_NewValue=UDR;
	//UCSRA Bit 7 – RXC: USART Receive Complete
	//set_bit(UCSRA,7);
}

void __vector_15 (void)  __attribute__((signal,__INTR_ATTRS));
void __vector_15 (void)
{
	UART_CurrentState =UART_STATE_INIT;
	//UCSRA Bit 6 – TXC: USART Transmit Complete
	set_bit(UCSRA,6);
		//flag_transmit=1;
	//UCSRB Bit 3 – TXEN: Transmitter Enable
	clr_bit(UCSRB,3);
}
