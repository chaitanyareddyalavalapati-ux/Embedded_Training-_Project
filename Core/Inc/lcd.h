/*
 * lcd.h
 *
 *  Created on: 22-Apr-2026
 *      Author: mirafra
 */

#ifndef LCD_H_
#define LCD_H_
#include<cstdint>
class LCD
{
	void delay_ms(volatile int t);
	void LCD_RS(int state);
	void LCD_EN();
	void lcd_send(uint8_t data);
public:

	void lcd_contrl();
	void LCD_SendByte(int data,int isdata);
	void lcd_init();
	void set_cursor(int row,int col);
	void lcd_string(const char* str);
	void lcd_clear();
};




#endif /* LCD_H_ */
