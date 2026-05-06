
#include <stdint.h>
#include "stm32f407xx.h"

// USART3_TX → PC10
// USART3_RX → PC11

volatile uint8_t read_Ch;

void USART3_init(void);
//void USART3_write(char  ch);
uint8_t USART3_read(void);
void delayMs(int);


/*----------------------------------------------------------
                        MAIN
----------------------------------------------------------*/


/*----------------------------------------------------------
  USART3 Initialization
----------------------------------------------------------*/
void USART3_init(void)
{
    RCC->AHB1ENR |= (1 << 2);   // Enable GPIOC clock
    RCC->APB1ENR |= (1 << 18);  // Enable USART3 clock
    RCC->AHB1ENR |= (1 << 3);   // Enable GPIOC clock
    GPIOD->MODER &= ~(3 << 24); // pin10 =pin*2, claered the bits
    GPIOD->MODER |= (1 << 24); // pin10 =pin*2, claered the bits


    // PC10 → TX
    GPIOC->MODER &= ~(3 << 20); // pin10 =pin*2, claered the bits
    GPIOC->MODER |=  (2 << 20);   // Alternate function -10
    // created Array :AFR[2]  , AFR[0]=AFRL ,AFR[1]= AFRH
    GPIOC->AFR[1] &= ~(0xF << 8); // AFRH =AFR[1]- Clearing 4 bits
    GPIOC->AFR[1] |=  (7 << 8);   // AF7 (USART3) // 0111 for AF7

    // PC11 → RX
    GPIOC->MODER &= ~(3 << 22);
    GPIOC->MODER |=  (2 << 22);// 10 AFR mode
    GPIOC->AFR[1] &= ~(0xF << 12);// AFRH Register
    GPIOC->AFR[1] |=  (7 << 12); // AF7 -0111

    // USART settings
    USART3->BRR = 0x0683;      // 9600 baud @ 16 MHz(HSI)
    USART3->CR1 |= (1 << 3);   // TE
    USART3->CR1 |= (1 << 2);   // RE
    USART3->CR1 |= (1 << 13);  // UE - USART enable
}

/*----------------------------------------------------------
  Write one byte
----------------------------------------------------------*/


///*----------------------------------------------------------
//  Read one byte (blocking)
//----------------------------------------------------------*/
uint8_t USART3_read(void)
{
   while (!(USART3->SR & (1 << 5))); // RXNE
   return USART3->DR;
}



/*----------------------------------------------------------
  Delay
----------------------------------------------------------*/
void delayMs(int n)
{
    for (; n > 0; n--)
        for (volatile int i = 0; i < 2000; i++);
        }
