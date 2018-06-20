/*
 * DIO.c
 *
 *  Created on: 26 Feb 2018
 *      Author: Bassem
 */



#include "DIO.h"
#include "Types.h"
#include "utilss.h"


//=========================================================================================
extern void DIO_voidSetDirection(u8 Copy_u8PinNum, u8 Copy_u8PinValue )
{
	/*
	 * This function is to set the direction of each that it could be O/P pin or I/P pin
	 * And it takes two input parameters :
	 * 			the first argument is the pin number which the user want to set its direction
	 *			the Second argument is the value (1 || 0) to set it to the selected pin
	 *	its return type is void that means it has no return value
	 */
	if( (Copy_u8PinNum>=0 && Copy_u8PinNum<=31) &&  (Copy_u8PinValue==0 || Copy_u8PinValue==1) )
	{
		//here is a switch case to specify which pin was passed to the function and assign the value to it
		if(Copy_u8PinNum/8==0)
		{
			assign_bit(DDRA,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		if(Copy_u8PinNum/8==1)
		{
			assign_bit(DDRB,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		if(Copy_u8PinNum/8==2)
		{
			assign_bit(DDRC,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		if(Copy_u8PinNum/8==3)
		{
			assign_bit(DDRD,Copy_u8PinNum%8,Copy_u8PinValue);
		}
	}
}
//=========================================================================================
extern void DIO_voidWritePIN(u8 Copy_u8PinNum, u8 Copy_u8PinValue)
{
	/*
	*in this function we are going to take 2 passing parameters
	*the 1st one is the number of the PIN
	*the 2nd one is the value that needed to be assigned to the pre-specified PIN
	*	its return type is void that means it has no return value
	*/

	if( (Copy_u8PinNum>=0 && Copy_u8PinNum<=31) &&  (Copy_u8PinValue==0 || Copy_u8PinValue==1) )
	{
		//the switch case to specify which pin was selected by the user
		if((Copy_u8PinNum/8)==0)
		{
			assign_bit(PORTA,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		if((Copy_u8PinNum/8)==1)
		{
			assign_bit(PORTB,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		if((Copy_u8PinNum)/8==2)
		{
			assign_bit(PORTC,Copy_u8PinNum%8,Copy_u8PinValue);
		}
		if((Copy_u8PinNum/8)==3)
		{
			assign_bit(PORTD,Copy_u8PinNum%8,Copy_u8PinValue);
		}
	}

}
//=======================================================================================
extern u8 DIO_u8ReadPIN(u8 Copy_u8PinNum)
{
	/*
		*in this function we are going to take 1 passing parameter
		*the passing parameter is the number of the PIN
		*	its return type is u8 that means it has a return value with data type (u8)
		*/

	//a u8 variable to store the read value and return it
	u8 Local_u8ReturnValue;
	if( Copy_u8PinNum>=0 && Copy_u8PinNum<=31)
		{
			if(Copy_u8PinNum/8==0)
			{
				Local_u8ReturnValue=get_bit(PINA,Copy_u8PinNum%8);
			}
			if(Copy_u8PinNum/8==1)
			{
				Local_u8ReturnValue=get_bit(PINB,Copy_u8PinNum%8);
			}
			if(Copy_u8PinNum/8==2)
			{
				Local_u8ReturnValue=get_bit(PINC,Copy_u8PinNum%8);
			}
			if(Copy_u8PinNum/8==3)
			{
				Local_u8ReturnValue=get_bit(PIND,Copy_u8PinNum%8);
			}
		}

	//return the output of the selected pin
	return Local_u8ReturnValue;
}
