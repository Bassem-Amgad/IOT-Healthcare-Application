/*
 * spi.h
 *
 * Created: 10/11/2016 9:18:47 PM
 *  Author: m.mamdooh
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "Types.h"
#include "SPI_Cfg.h"

#define  SPDR *((u8*) 0x2f)
#define  SPSR *((u8*) 0x2e)
#define	 SPCR *((u8*) 0x2d)
#define  SREG *((u8*) 0x5f)

#define MOSI DIO_u8PinB5
#define MISO DIO_u8PinB6
#define SS_Low DIO_u8PinB4
#define SCK DIO_u8PinB7

typedef struct
{
	/*Master/Slave Select*/
		/* Master --> 1
		 * Slave  --> 0
		 */
	u8 SPI_Type;
	/*Data Order*/
		/*
		 *LSB of data transmitted first --> 1
		 *MSB of data transmitted first --> 0
		  */
	u8 Data_Order;
	/*Clock Select */
		/*
		 * sel2 Sel1 Sel0     SCK Frequency
			0 	0 	 0 			fosc/4
			0 	0 	 1 			fosc/16
			0 	1 	 0 			fosc/64
			0 	1 	 1 			fosc/128
			1 	0 	 0 			fosc/2
			1 	0 	 1 			fosc/8
			1 	1 	 0 			fosc/32
			1 	1 	 1 			fosc/64
		 */
	u8 Clock_Sel0;
	u8 Clock_Sel1;
	u8 Clock_Sel2;
	/*Clock Polarity*/
		/*
		  	  Leading Edge 		Trailing Edge
		  0     Rising 	     		Falling
		  1     Falling 	 		Rising
		 */
	u8 Clock_Polarity;
	/*Clock Phase*/
		/*
		  	  Leading Edge 		Trailing Edge
		  0 	Sample 		  		Setup
		  1 	Setup 		  		Sample
		 */
	u8 Clock_Phase;

}SPI_CfgType;

extern const SPI_CfgType SPI_ConfigParam [SPI_GROUPS_NUMBER];

extern void SPI_Transmit (u8 data);
extern void SPI_Recieve (u8 *data);
extern void SPI_Init(void);

#endif /* SPI_H_ */
