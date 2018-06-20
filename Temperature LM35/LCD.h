/*
 * LCD.h
 *
 *  Created on: 8 Sep 2017
 *      Author: Bassem
 */

#ifndef LCD_H_
#define LCD_H_

extern void LCD_voidInit (void);
extern void LCD_voidWriteCommand(u8 command);
extern void LCD_voidDisplay(u8 data);

#endif /* LCD_H_ */
