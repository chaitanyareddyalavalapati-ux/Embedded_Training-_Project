 #include <cstdio>
//#include "STM32F407.h"

class LCD {
private:
    LCD() {

    }

public:
    static LCD& getInstance() {
        static LCD instance;
        return instance;
    }

    // 🚀 Enable GPIO clock
    void initGPIO() {
        RCC->AHB1ENR |= (1 << 1); // Enable GPIOB clock

        // PB0 → RS, PB1 → EN, PB4–PB7 → D4–D7
        GPIOB->MODER &= ~(0xFFFF);       // Clear PB0–PB7
        GPIOB->MODER |=  (0x5555);       // Set as output

        // Optional: set speed
        GPIOB->OSPEEDR |= (0xFFFF);
    }

    // 🔁 Simple delay (works for 168 MHz)
    void delay_ms(uint32_t ms) {
        for(uint32_t i = 0; i < ms * 8000; i++);
    }

    // ⚙️ Control pins
    void RS(int state) {
        if(state)
            GPIOB->ODR |= (1 << 0);
        else
            GPIOB->ODR &= ~(1 << 0);
    }

    void EN_pulse() {
        GPIOB->ODR |= (1 << 1);
        for(volatile int i = 0; i < 1000; i++);
        GPIOB->ODR &= ~(1 << 1);
        for(volatile int i = 0; i < 1000; i++);
    }

    // 📤 Send 4-bit nibble
    void send4bit(uint8_t data) {
        GPIOB->ODR &= ~(0xF << 4);             // Clear D4–D7
        GPIOB->ODR |= ((data & 0x0F) << 4);    // Set new data
        EN_pulse();
    }

    // 📤 Send full byte
    void sendByte(uint8_t data, int isData) {
        RS(isData);

        send4bit(data >> 4);   // upper nibble
        delay_ms(1);

        send4bit(data & 0x0F); // lower nibble
        delay_ms(2);
    }

    // 🧠 LCD Initialization
    void init() {
        delay_ms(20);

        send4bit(0x03);
        delay_ms(5);

        send4bit(0x03);
        delay_ms(1);

        send4bit(0x03);
        delay_ms(1);

        send4bit(0x02); // 4-bit mode

        sendByte(0x28, 0); // 2 lines, 4-bit
        sendByte(0x0C, 0); // Display ON
        sendByte(0x01, 0); // Clear
        delay_ms(5);
        sendByte(0x06, 0); // Entry mode
    }

    // 📍 Set cursor
    void set_cursor(int row, int col) {
        uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
        sendByte(addr, 0);
    }

    // 📝 Print string
    void lcd_string(const char* str) {
        while(*str) {
            sendByte(*str++, 1);
        }
    }
};
LCD& p = LCD::getInstance();
