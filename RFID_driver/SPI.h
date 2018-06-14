
#ifndef SPI_H_
#define SPI_H_

#include "SPI_Cfg.h"
////////////////////////////////////////////////////////
////////// addresses /////////////////////////////////
//////////////////////////////////////////////////////
#define  SPDR *((volatile unsigned char*) 0x2f)
#define  SPSR *((volatile unsigned char*) 0x2e)
#define	 SPCR *((volatile unsigned char*) 0x2d)

////////////////////////////////////////////////////////
////////// pins /////////////////////////////////
//////////////////////////////////////////////////////
#define SS_SPI 12
#define MOSI 13
#define MISO 14
#define SCK 15

typedef struct
{
	/*Master/Slave Select*/
		/* Master --> 1
		 * Slave  --> 0
		 */
	unsigned char SPI_Type;
	/*Data Order*/
		/*
		 *LSB of data transmitted first --> 1
		 *MSB of data transmitted first --> 0
		  */
	unsigned char Data_Order;
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
	unsigned char Clock_Sel0;
	unsigned char Clock_Sel1;
	unsigned char Clock_Sel2;
	/*Clock Polarity*/
		/*
		  	  Leading Edge 		Trailing Edge
		  0     Rising 	     		Falling
		  1     Falling 	 		Rising
		 */
	unsigned char Clock_Polarity;
	/*Clock Phase*/
		/*
		  	  Leading Edge 		Trailing Edge
		  0 	Sample 		  		Setup
		  1 	Setup 		  		Sample
		 */
	unsigned char Clock_Phase;

}SPI_CfgType;

extern const SPI_CfgType SPI_ConfigParam [SPI_GROUPS_NUMBER];

////////////////////////////////////////////////////////
////////// prototypes /////////////////////////////////
//////////////////////////////////////////////////////
void SPI_masterInit(void);
unsigned char SPI_Transmit(unsigned char cData);
void SPI_Recieve(unsigned char *data);
#endif /* SPI_H_ */