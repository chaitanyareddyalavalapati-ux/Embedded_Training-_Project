 #ifndef LCD_H
#define LCD_H

#include <cstdio>
#include "stm32f4xx.h"

class LCD {
private:
    LCD();   // constructor

public:
    // delete copy
    LCD(const LCD&) = delete;
    LCD& operator=(const LCD&) = delete;

    static LCD& getinstance();

    void GPIO_ENB();
    void delay_ms(volatile int t);
    void lcd_contrl();

    void LCD_RS(int state);
    void LCD_EN();
    void lcd_send(uint8_t data);
    void LCD_SendByte(int data, int isdata);

    void lcd_init();
    void set_cursor(int row, int col);
    void lcd_string(const char* str);

    ~LCD();
};

#endif
