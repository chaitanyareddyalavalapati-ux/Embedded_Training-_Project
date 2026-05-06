 #include "lcd.h"

// Constructor
LCD::LCD() {}

// Singleton instance
LCD& LCD::getinstance() {
    static LCD instance;
    return instance;
}

// Enable GPIO
void LCD::GPIO_ENB() {
    RCC->AHB1ENR |= (1<<1); // GPIOB
}

// Delay
void LCD::delay_ms(volatile int t) {
    for(int i=0; i<t*8000; i++);
}

// Configure pins
void LCD::lcd_contrl() {
    // PB0 RS, PB1 EN, PB4-7 DATA
    GPIOB->MODER &= ~(0xFFFF);
    GPIOB->MODER |=  (0x5555);
}

// RS control
void LCD::LCD_RS(int state) {
    if(state)
        GPIOB->ODR |= (1<<0);
    else
        GPIOB->ODR &= ~(1<<0);
}

// EN pulse
void LCD::LCD_EN() {
    GPIOB->ODR |= (1<<1);
    for(volatile int i=0;i<1000;i++);
    GPIOB->ODR &= ~(1<<1);
    for(volatile int i=0;i<1000;i++);
}

// Send 4-bit
void LCD::lcd_send(uint8_t data) {
    GPIOB->ODR &= ~(0xF<<4);
    GPIOB->ODR |= ((data & 0x0F)<<4);
    LCD_EN();
}

// Send byte
void LCD::LCD_SendByte(int data, int isdata) {
    LCD_RS(isdata);

    lcd_send(data >> 4);
    delay_ms(1);

    lcd_send(data & 0x0F);
    delay_ms(2);
}

// Init LCD
void LCD::lcd_init() {
    delay_ms(20);

    lcd_send(0x03);
    delay_ms(5);

    lcd_send(0x03);
    delay_ms(1);

    lcd_send(0x03);
    delay_ms(1);

    lcd_send(0x02);

    LCD_SendByte(0x28,0);
    LCD_SendByte(0x0C,0);
    LCD_SendByte(0x01,0);
    delay_ms(5);
    LCD_SendByte(0x06,0);
}

// Cursor
void LCD::set_cursor(int row, int col) {
    int addr = (row==0) ? (0x80+col) : (0xC0+col);
    LCD_SendByte(addr,0);
}

// Print string
void LCD::lcd_string(const char* str) {
    while(*str) {
        LCD_SendByte(*str++,1);
    }
}

// Destructor
LCD::~LCD() {}
