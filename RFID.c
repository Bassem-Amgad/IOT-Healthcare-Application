/*
 * RFID.c
 *
 * Created:  26/4
 *  Author: Menna
 */ 
#define F_CPU (8000000ul)
#include <util/delay.h>
#include "RFID.h"
#include "DIO.h"
#include "SPI.h"


void RFID_writeToRegister(unsigned char  addr, unsigned char  val) {
	
		DIO_WritePin(SS_SPI,LOW);  //RFID enable PIN
		SPI_Transmit(addr);
		SPI_Transmit(val);
		DIO_WritePin(SS_SPI,HIGH);	
}

unsigned char RFID_readFromRegister(unsigned char addr) {
	unsigned char val;
	DIO_WritePin(SS_SPI,LOW);
	SPI_Transmit(addr | 0x80);
	val = SPI_Transmit(0x00);
	DIO_WritePin(SS_SPI,HIGH);
	return val;
}


void RFID_readFromRegisterS(unsigned char reg,unsigned char count,unsigned char* values) {
	if(count=0){
		return;
	}
	
				// MSB == 1 is for reading. LSB is not used in address. Datasheet section 8.1.2.3.
	unsigned char index = 0;							// Index in values array.
	
	for(index=0;index<count;index++){

	values[index]=RFID_readFromRegister(reg);}
	
}
void RFID_writeToRegisterS(unsigned char reg,unsigned char count,unsigned char *val){
	//DIO_WritePin(SS_SPI,LOW);  //RFID enable PIN
	//SPI_Transmit(reg);
	for (char index = 0; index < count; index++) {
		//SPI_Transmit(val[index]);
		//DIO_WritePin(SS_SPI,HIGH);
		DIO_WritePin(SS_SPI,LOW);  //RFID enable PIN
		SPI_Transmit(reg);
		SPI_Transmit(val[index]);
		DIO_WritePin(SS_SPI,HIGH);
	}
	
}



void RFID_SetRegisterBitMask(unsigned char reg ,unsigned char mask){
		unsigned char tmp;
		tmp = RFID_readFromRegister(reg);
		RFID_writeToRegister(reg, tmp | mask);			// set bit mask
}
void RFID_ClearRegisterBitMask(unsigned char reg,unsigned char mask){
	unsigned char tmp;
	tmp = RFID_readFromRegister(reg);
	RFID_writeToRegister(reg, tmp & (~mask));		// clear bit mask
}
void RFID_Init(){
	char  hardReset = 0;
	

    DIO_PinDirection(SS_SPI,OUTPUT);
	DIO_WritePin(SS_SPI,HIGH);

	// First set the resetPowerDownPin as digital input, to check the MFRC522 power down mode.
	DIO_PinDirection(RST_PIN, INPUT);
	
	if (DIO_ReadPin(RST_PIN) == LOW) {	// The MFRC522 chip is in power down mode.
		DIO_PinDirection(RST_PIN, OUTPUT);		// Now set the resetPowerDownPin as digital output.
		DIO_WritePin(RST_PIN, HIGH);		// Exit power down mode. This triggers a hard reset.
		// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74?s. Let us be generous: 50ms.
		_delay_ms(50);
		hardReset = 1;
		
		//??? ?? ???
		DIO_PinDirection(30,HIGH);
		DIO_WritePin(30,HIGH);
		
	
}

if (!hardReset) { // Perform a soft reset if we haven't triggered a hard reset above.
	
	RFID_Reset();
	//??? ?? 
	DIO_PinDirection(31,HIGH);
	DIO_WritePin(31,HIGH);
}

// Reset baud rates
RFID_writeToRegister(TxModeReg, 0x00);
RFID_writeToRegister(RxModeReg, 0x00);
// Reset ModWidthReg
RFID_writeToRegister(ModWidthReg, 0x26);

// When communicating with a PICC we need a timeout if something goes wrong.
// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
RFID_writeToRegister(TModeReg, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
RFID_writeToRegister(TPrescalerReg, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25?s.
RFID_writeToRegister(TReloadRegH, 0x03);		// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
RFID_writeToRegister(TReloadRegL, 0xE8);

RFID_writeToRegister(TxASKReg, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
RFID_writeToRegister(ModeReg, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363 (ISO 14443-3 part 6.2.4)
RFID_AntennaOn();						// Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset)
} // End PCD_Init()



void RFID_Reset(void) {
	RFID_writeToRegister(CommandReg, PCD_SoftReset);	// Issue the SoftReset command.
	// The datasheet does not mention how long the SoftRest command takes to complete.
	// But the MFRC522 might have been in soft power-down mode (triggered by bit 4 of CommandReg)
	// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74?s. Let us be generous: 50ms.
	_delay_ms(50);
	// Wait for the PowerDown bit in CommandReg to be cleared
	while (RFID_readFromRegister(CommandReg) & (1<<4)) {
		// PCD still restarting - unlikely after waiting 50ms, but better safe than sorry.
	}
} // End PCD_Reset()

void RFID_AntennaOn(void) {
	unsigned char value = RFID_readFromRegister(TxControlReg);
	if ((value & 0x03) != 0x03) {
		RFID_writeToRegister(TxControlReg, value | 0x03);
	}
}

unsigned char getFirmwareVersion(void){
	unsigned char  response;
	response =  RFID_readFromRegister(VersionReg);
	return response;
}


unsigned char digitalSelfTestPass(void) {
	int i;
	unsigned char n;

	unsigned char selfTestResultV1[] = {0x00, 0xC6, 0x37, 0xD5, 0x32, 0xB7, 0x57, 0x5C,
		0xC2, 0xD8, 0x7C, 0x4D, 0xD9, 0x70, 0xC7, 0x73,
		0x10, 0xE6, 0xD2, 0xAA, 0x5E, 0xA1, 0x3E, 0x5A,
		0x14, 0xAF, 0x30, 0x61, 0xC9, 0x70, 0xDB, 0x2E,
		0x64, 0x22, 0x72, 0xB5, 0xBD, 0x65, 0xF4, 0xEC,
		0x22, 0xBC, 0xD3, 0x72, 0x35, 0xCD, 0xAA, 0x41,
		0x1F, 0xA7, 0xF3, 0x53, 0x14, 0xDE, 0x7E, 0x02,
	0xD9, 0x0F, 0xB5, 0x5E, 0x25, 0x1D, 0x29, 0x79};
	unsigned char selfTestResultV2[] = {0x00, 0xEB, 0x66, 0xBA, 0x57, 0xBF, 0x23, 0x95,
		0xD0, 0xE3, 0x0D, 0x3D, 0x27, 0x89, 0x5C, 0xDE,
		0x9D, 0x3B, 0xA7, 0x00, 0x21, 0x5B, 0x89, 0x82,
		0x51, 0x3A, 0xEB, 0x02, 0x0C, 0xA5, 0x00, 0x49,
		0x7C, 0x84, 0x4D, 0xB3, 0xCC, 0xD2, 0x1B, 0x81,
		0x5D, 0x48, 0x76, 0xD5, 0x71, 0x61, 0x21, 0xA9,
		0x86, 0x96, 0x83, 0x38, 0xCF, 0x9D, 0x5B, 0x6D,
	0xDC, 0x15, 0xBA, 0x3E, 0x7D, 0x95, 0x3B, 0x2F};
	unsigned char *selfTestResult;
	switch(getFirmwareVersion()) {
		case 0x91 :
		selfTestResult = selfTestResultV1;
		break;
		case 0x92 :
		selfTestResult = selfTestResultV2;
		break;
		default:
		return 0;
	}

	RFID_Reset();
	RFID_writeToRegister(FIFODataReg, 0x00);
	RFID_writeToRegister(CommandReg, PCD_Mem);
	RFID_writeToRegister(AutoTestReg, 0x09);
	RFID_writeToRegister(FIFODataReg, 0x00);
	RFID_writeToRegister(CommandReg, PCD_CalcCRC);

	// Wait for the self test to complete.
	i = 0xFF;
	do {
		n = RFID_readFromRegister(DivIrqReg);
		i--;
	} while ((i != 0) && !(n & 0x04));

	for (i=0; i < 64; i++) {
		if (RFID_readFromRegister(FIFODataReg) != selfTestResult[i]) {
			//Serial.println(i);
			return 0;
		}
	}
	return 1;
}



unsigned char mfrc522_to_card(unsigned char cmd, unsigned char *send_data, unsigned char send_data_len, unsigned char *back_data, unsigned int *back_data_len)
{
	unsigned char status = ERROR;
	unsigned char irqEn = 0x00;
	unsigned char waitIRq = 0x00;
	unsigned char lastBits;
	unsigned char n;
	unsigned char	tmp;
	unsigned int i;

	switch (cmd)
	{
		case PCD_MFAuthent :		//Certification cards close
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_Transceive:	//Transmit FIFO data
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
		break;
	}
	
	
	n=RFID_readFromRegister(ComIrqReg);
	RFID_writeToRegister(ComIrqReg,n&(~0x80));//clear all interrupt bits
	n=RFID_readFromRegister(FIFOLevelReg);
	RFID_writeToRegister(FIFOLevelReg,n|0x80);//flush FIFO data
	
	RFID_writeToRegister(CommandReg, PCD_Idle);	//NO action; Cancel the current cmd???

	//Writing data to the FIFO
	for (i=0; i<send_data_len; i++)
	{
		RFID_writeToRegister(FIFODataReg, send_data[i]);
	}

	//Execute the cmd
	RFID_writeToRegister(CommandReg, cmd);
	if (cmd == PCD_Transceive)
	{
		n=RFID_readFromRegister(BitFramingReg);
		RFID_writeToRegister(BitFramingReg,n|0x80);
	}
	
	//Waiting to receive data to complete
	i = 2000;	//i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
	do
	{
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = RFID_readFromRegister(ComIrqReg);
		i--;
	}
	while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	tmp=RFID_readFromRegister(BitFramingReg);
	RFID_writeToRegister(BitFramingReg,tmp&(~0x80));
	
	if (i != 0)
	{
		if(!(RFID_readFromRegister(ErrorReg) & 0x1B))	//BufferOvfl Collerr CRCErr ProtecolErr
		{
			status = CARD_FOUND;
			if (n & irqEn & 0x01)
			{
				status = CARD_NOT_FOUND;			//??
			}

			if (cmd == PCD_Transceive)
			{
				n = RFID_readFromRegister(FIFOLevelReg);
				lastBits = RFID_readFromRegister(ControlReg) & 0x07;
				if (lastBits)
				{
					*back_data_len = (n-1)*8 + lastBits;
				}
				else
				{
					*back_data_len = n*8;
				}

				if (n == 0)
				{
					n = 1;
				}
				if (n > MAX_LEN)
				{
					n = MAX_LEN;
				}
				
				//Reading the received data in FIFO
				for (i=0; i<n; i++)
				{
					back_data[i] = RFID_readFromRegister(FIFODataReg);
				}
			}
		}
		else
		{
			status = ERROR;
		}
		
	}
	


	return status;
}

unsigned char	mfrc522_request(unsigned char req_mode, unsigned char * tag_type)
{
	unsigned char  status;
	unsigned int backBits;//The received data bits

	RFID_writeToRegister(BitFramingReg, 0x07);//TxLastBists = BitFramingReg[2..0]	???
	
	tag_type[0] = req_mode;
	status = mfrc522_to_card(PCD_Transceive, tag_type, 1, tag_type, &backBits);

	if ((status != CARD_FOUND) || (backBits != 0x10))
	{
		status = ERROR;
	}
	
	return status;
}



unsigned char mfrc522_get_card_serial(unsigned char * serial_out)
{
	unsigned char status;
	unsigned char i;
	unsigned char serNumCheck=0;
	unsigned int unLen;
	
	RFID_writeToRegister(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
	
	serial_out[0] = PICC_CMD_SEL_CL1;
	serial_out[1] = 0x20;
	status = mfrc522_to_card(PCD_Transceive, serial_out, 2, serial_out, &unLen);

	if (status == CARD_FOUND)
	{
		//Check card serial number
		for (i=0; i<4; i++)
		{
			serNumCheck ^= serial_out[i];
		}
		if (serNumCheck != serial_out[i])
		{
			status = ERROR;
		}
	}
	return status;
}