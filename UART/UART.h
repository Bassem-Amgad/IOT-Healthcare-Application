/*
 * UART.h
 *
 *  Created on: 7 Oct 2017
 *      Author: Bassem
 */

#ifndef UART_H_
#define UART_H_
#include "Types.h"
#include "UART_cfg.h"

/*#define UART_STATE_INIT 0x01
#define UART_STATE_TX_DONE 0x02
#define UART_STATE_RX_DONE 0x03
*/
typedef enum {UART_STATE_UNINIT=0x00,UART_STATE_INIT=0x01, UART_STATE_TX_ONGOING=0x02, UART_STATE_RX_DONE=0x03} UART_State;
typedef enum {UART_OK =0, UART_NOK}UART_ChkType;
typedef enum {PARITY_DISABLED=0, PARITY_EVEN = 2 , PARITY_ODD = 3} UART_ParityType;
typedef enum {STOP_ONE =0, STOP_TWO=1}UART_StopBitsType;
typedef enum {DATA_5=0,DATA_6=1,DATA_7=2,DATA_8=3,DATA_9=7}UART_DataSizeType;
typedef struct
{
	/*USART Mode Select*/
		/*
			0 		Asynchronous Operation
			1 		Synchronous Operation
		 */
	u8 UART_Mode;
	/*Double the USART Transmission Speed
	only has effect for the asynchronous operation.
	Write this bit to zero when using synchronous operation.
	Writing this bit to one will reduce the divisor of the baud rate divider from 16 to 8 effectively
	doubling the transfer rate for asynchronous communication.*/
		/*
				1 		Asynchronous Operation
				0 		Synchronous Operation
		 */
	u8 Double_Asynch_Clock;
	/* Bit 0 – UCPOL: Clock Polarity
	 This bit is used for Synchronous mode only. Write this bit to zero when Asynchronous mode is used*/
		/*
				Transmitted Data Changed (Output ofTxD Pin)  Received Data Sampled (Input on RxD Pin)
			0 			Rising XCK Edge 							Falling XCK Edge
			1 			Falling XCK Edge 							Rising XCK Edge
		 */
	u8 Clock_Polarity;
	/*Parity Mode */
		/*
			0 0 Disabled
			0 1 Reserved
			1 0 Enabled, Even Parity
			1 1 Enabled, Odd Parity
		*/
	UART_ParityType Parity;
	/*Stop Bit Select */
		/*
			0 1-bit
			1 2-bit
		 */
	UART_StopBitsType Stop_Bits;
	/*Character Size */
		 /*
		  	S2 	S1 	 S0 	Character Size
			0 	 0 	 0	 	5-bit
			0 	 0   1 		6-bit
			0 	 1 	 0 		7-bit
			0 	 1 	 1 		8-bit
			1 	 0 	 0 		Reserved
			1 	 0 	 1 		Reserved
			1 	 1 	 0 		Reserved
			1 	 1 	 1		 9-bit
		  */
	UART_DataSizeType Data_Size;
	/*Baud RAte */
		/*
		 2400 -4800 - 9600 - 14400 - 19200 - 28800 - 38400 - 57600 - 76800 -
		 115200 - 230400 - 250000 - 500000
		*/
	u32 BaudRate;
}UART_ConfigType;

extern const UART_ConfigType UART_ConfigParam[UART_PERIF_NUM];

extern void  UART_voidInit (void);
extern u8  UART_u8Transmit (u8 data);

#endif /* UART_H_ */
