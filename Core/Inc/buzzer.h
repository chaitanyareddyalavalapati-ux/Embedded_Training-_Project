//buzzer.h
#include<stm32f407xx.h>
#include<stdint.h>
void BUZZER_Init()
{
	RCC->AHB1ENR|=1<<4;
	GPIOE->MODER&=~(1<<(2*1));
	GPIOE->MODER|=(1<<(2*1));
}
uint32_t var;
void delay_ms(uint32_t delay)
{
	for( uint32_t i=0;i<delay;i++)
	{
       //var++;
	}
}
void missing_buzzer()
{  //var=1;
	while(1)
	{   // var=1;
		GPIOE->ODR|=(1<<1);
		delay_ms(500000);
		GPIOE->ODR&=~(1<<1);
		delay_ms(500000);
		if(GPIOC->IDR&(1<<4))
		{
			break;
		}

	}
}
void glitch_buzzer()
{
	while(1)
		{
			GPIOE->ODR|=(1<<1);
			delay_ms(50000);
			GPIOE->ODR&=~(1<<1);
			delay_ms(100000);
			if(GPIOC->IDR&(1<<4))
					{
						break;
					}

		}
}
void jam_buzzer()
{
	while(1)
		{
			GPIOE->ODR|=(1<<1);
			delay_ms(10000);
			GPIOE->ODR&=~(1<<1);
			delay_ms(10000);
			if(GPIOC->IDR&(1<<4))
					{
						break;
					}

		}
}

/*#include "stm32f407xx.h"
#include<stdint.h>

uint32_t c=0;

void buzzer_init()
{
	RCC->AHB1ENR|=(1<<4);
	GPIOE->MODER&=~(3<<4);
	GPIOE->MODER|=(1<<4);
}
void delay(uint32_t d)
{
uint32_t i;
	for(i=0;i<d;i++);
}
void beep_low()
{
    GPIOE->BSRR = (1<<2);          // ON
    delay(500000);
    GPIOE->BSRR = (1<<(2+16));     // OFF
    delay(2000000);
}
void beep_medium()
{
    GPIOE->BSRR = (1<<2);
    delay(300000);
    GPIOE->BSRR = (1<<(2+16));
    delay(300000);
}
void beep_high()
{
    for(int i=0;i<10;i++)
    {
        GPIOE->BSRR = (1<<2);
        delay(100000);
        GPIOE->BSRR = (1<<(2+16));
        delay(100000);
    }
}
int main()
{
	buzzer_init();
	while(1)
	{
		c++;
	   if(c<10)
	   {
		   beep_low();
	   }
	   else if(c>=10 && c<30)
	   {
		   beep_medium();
	   }
	   else if(c>=30)
	   {
		   beep_high();
	   }

	}
}*/
