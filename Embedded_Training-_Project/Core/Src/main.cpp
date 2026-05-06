/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lcd.h"
#include "uart.h"
#include "semphr.h"
#include "event_groups.h"
#include "buzzer.h"
LCD &p=LCD::getinstance();
EventGroupHandle_t uart_safety_group;
SemaphoreHandle_t lcd_mutex;
#define uart 1<<0
#define safety 1<<1
#define Total_weight 10
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

#define DWT_CTRL    (*(volatile uint32_t*)0xE0001000)

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void WeighingTask(void*);
static void SensorTask(void* parameters);
static void TrackingTask(void* parameters);
static void SafetyTask(void* parameters);
static void ControlTask(void* parameters);
static void DisplayTask(void* parameters);
static void UartTask(void* parameters);
static void ControlTask(void* parameters);
//extern void SEGGER_UART_init(uint32_t);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
#include "stm32f407xx.h"
#define CH3_EVNT 1<<0
#define CH4_EVNT_RISING 1<<1
#define CH4_EVNT_FALLING 1<<2
#define D 800
typedef enum
{
	MISSING_OBJECT,
	SENSOR_GLITCH,
	JAM,
	INCONSISTENT,
	NO_FAULT
}faults;
typedef enum
{
	LIGHT,
	HEAVY
}loads;
typedef enum
{
	BINA,
	BINB,
	REJECT,
	FAULT
}states;
typedef struct
{
	const char *fault;
	const char *load;
	const char *state;
}indication;
indication str;
typedef struct
{
	uint32_t start;
	uint32_t end;
	uint32_t result;
	uint32_t end_stuck;

}sensorvalues;
typedef struct
{   uint32_t entry;
    uint32_t Arr;
	uint32_t time_ms;
	uint32_t stuck;
	uint32_t speed;
	uint32_t weight;
	loads load;
	faults fault;
	states state;
}decisionvalues ;
decisionvalues st2;
uint32_t BINA_weight=10,BINB_weight=10,flg=0;
uint32_t c=0;
#define TEMP_THRESHOLD 3000   // ADC2 threshold (adjust based on potentiometer)
TaskHandle_t task8_handle;
TaskHandle_t task0_handle;//weighingTask
TaskHandle_t task1_handle;//sensortask
TaskHandle_t task2_handle;//trackingtask
TaskHandle_t task3_handle;//controltask
TaskHandle_t task4_handle;//actuatortask
TaskHandle_t task5_handle;//displaytask
TaskHandle_t task6_handle;//uarttask
TaskHandle_t task7_handle;//safetytask
static void TemperatureTask(void* parameters);
void ADC2_Init(void)
{
    /* Enable ADC2 clock */
    RCC->APB2ENR |= (1<<9);

    /* Configure PA1 as analog (ADC2_IN1) */
    RCC->AHB1ENR |= (1<<0);      // GPIOA clock
    GPIOA->MODER |= (3<<2);      // PA1 analog mode

    /* ADC2 OFF first */
    ADC2->CR2 &= ~(1<<0);

    /* Sample time for Channel 1 */
    ADC2->SMPR2 |= (7<<3);

    /* Sequence length = 1 */
    ADC2->SQR1 &= ~(0xF<<20);

    /* Channel 1 as first conversion */
    ADC2->SQR3 &= ~(0x1F<<0);
    ADC2->SQR3 |= (1<<0);

    /* Enable ADC2 */
    ADC2->CR2 |= (1<<0);
}
static void TemperatureTask(void*)
{

    uint32_t adc_val;
    c++;

    while(1)
    {
        /* Start ADC2 conversion */
        ADC2->CR2 |= (1<<30);

        /* Wait until conversion complete */
        while(!(ADC2->SR & (1<<1)));

        /* Read ADC value */
        adc_val = ADC2->DR;
        flg=10;

        /* Threshold check */
        if(adc_val > TEMP_THRESHOLD)
        {
        	xSemaphoreTake(lcd_mutex, portMAX_DELAY);
            jam_buzzer();

        }

        /* Run every 200ms in background */
       // vTaskDelay(pdMS_TO_TICKS(200));
        xTaskNotifyGive( task0_handle);
    }
}


void TIMER_Init(void)
{
    RCC->APB1ENR |= (1<<0);

    TIM2->PSC = 15999;//1ms
    TIM2->ARR = 9999;//10sec overflow
    TIM2->CNT = 0;

    // CH3 input
    TIM2->CCMR2 &= ~(3<<8);
    TIM2->CCMR2 |= (1<<8);

    // CH4 input
    TIM2->CCMR2 &= ~(3<<0);
    TIM2->CCMR2 |= (1<<0);

    // Enable CH3 rising
    TIM2->CCER |= (1<<8);

    // Enable CH4 both edges
    TIM2->CCER &= ~((1<<13) | (1<<15));
    TIM2->CCER |= (1<<12) | (1<<13) | (1<<15);

    // Enable interrupts
    //TIM2->DIER |= (1<<3) | (1<<4);

    TIM2->SR = 0;  // clear flags

    //enable timer

    TIM2->CR1 |= (1<<0);
}
void GPIO_Init(void)
{
	RCC->AHB1ENR|=(1<<1);
	GPIOB->MODER&=~(3<<20);//PB10
	GPIOB->MODER&=~(3<<22);//PB11
	GPIOB->MODER|=(2<<20);
	GPIOB->MODER|=(2<<22);
	//GPIOB->PUPDR|=(1<<20);
	//GPIOB->PUPDR|=(1<<22);
	GPIOB->AFR[1]|=(0x1<<8);
	GPIOB->AFR[1]|=(0x1<<12);

	 /* 1. Enable GPIOC clock */
	    RCC->AHB1ENR |= (1<<3);
	    RCC->AHB1ENR |= (1<<2);

	    /* 2. Configure PD12 as OUTPUT (LED) */
	    GPIOD->MODER &= ~(3<<24);
	    GPIOD->MODER |=  (1<<24);   // 01 = output
	    /* 2. Configure PD14 as OUTPUT (LED) */

	    GPIOD->MODER &= ~(3<<28);
	     GPIOD->MODER |=  (1<<28);   // 01 = output
	     GPIOD->MODER &= ~(3<<26);
	      GPIOD->MODER |=  (1<<26);
	      GPIOD->MODER &= ~(3<<30);
	      GPIOD->MODER |=  (1<<30);
	      GPIOD->MODER &= ~(3<<20);
	     GPIOD->MODER |=  (1<<20);


	    /* 3. Configure PC2 as ANALOG (ADC input) */
	    GPIOC->MODER &= ~(3<<4);
	    GPIOC->MODER |=  (3<<4);    // 11 = analog

	    /* 4. Enable ADC1 clock */
	    RCC->APB2ENR |= (1<<8);

	    /* 5. Configure ADC */

	    ADC1->CR2 &= ~(1<<0);             // Ensure ADC is OFF

	    /* Sampling time for Channel 12 (PC2) */
	    ADC1->SMPR1 |= (7<<6);      // 480 cycles (CH12 → bits 6:8)

	    /* Conversion sequence length = 1 */
	    ADC1->SQR1 &= ~(0xF<<20);

	    /* Select Channel 12 */
	    ADC1->SQR3 &= ~(0xF<<0);
	    ADC1->SQR3 |= (12<<0);   //setting 12 channel as conversion 1

	    /* Enable ADC */
	    ADC1->CR2 |= (1<<0);

}
int cc;
/*void TIM2_IRQHandler(void)
{  BaseType_t xHighPriorityTaskWoken=pdFALSE;
   static uint8_t flag=0;
	GPIOD->ODR|=(1<<13);
    if(TIM2->SR&(1<<0))
    {
    	TIM2->SR&=~(1<<0);
		vTaskNotifyGiveFromISR(,CH3_EVNT,eSetBits,NULL,&xHighPriorityTaskWoken);
		portYIELD_FROM_ISR(xHighPriorityTaskWoken);

    }
   	if(TIM2->SR&(1<<3))
	{
		TIM2->SR&=~(1<<3);
		xTaskNotifyFromISR(task1_handle,CH3_EVNT,eSetBits,&xHighPriorityTaskWoken);
		portYIELD_FROM_ISR(xHighPriorityTaskWoken);
	}
	if(TIM2->SR&(1<<4))
	{  	TIM2->SR&=~(1<<4);
					if(flag==0)
					{
						xTaskNotifyFromISR(task1_handle,CH4_EVNT_RISING,eSetBits,&xHighPriorityTaskWoken);
						flag=1;
						portYIELD_FROM_ISR(xHighPriorityTaskWoken);
					}
					else
					{
						xTaskNotifyFromISR(task1_handle,CH4_EVNT_FALLING,eSetBits,&xHighPriorityTaskWoken);
						    flag=0;
							portYIELD_FROM_ISR(xHighPriorityTaskWoken);

					}

	   }
}*/
QueueHandle_t xQueue=xQueueCreate(1,sizeof(sensorvalues)),xQueue1=xQueueCreate(1,sizeof(decisionvalues)),xQueue2=xQueueCreate(1,sizeof(decisionvalues));
uint32_t unload(){


}
static void WeighingTask(void*)
{   while(1)
   {
	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	//vTaskDelay(pdMS_TO_TICKS(200));   // Delay task for 200 ms
	if(BINA_weight>=Total_weight&&BINB_weight>=Total_weight)
	 {
		//lcd print bina or binb is heavy please unload
			//if()
				p.LCD_SendByte(0x01,0);
				p.set_cursor(0,0);
				p.lcd_string("BINS FULL");
				p.set_cursor(1,0);
				p.lcd_string("PLEASE UNLOAD");
				//while(1){

					//if(BINA){
						BINA_weight-=5;
						BINB_weight-=5;
					//}
				//}

	 }
	else if(BINA_weight>=Total_weight)
		 {
			//lcd print bina or binb is heavy please unload
				//if()
					p.LCD_SendByte(0x01,0);
					p.set_cursor(0,0);
					p.lcd_string("BINA FULL");
					p.set_cursor(1,0);
					p.lcd_string("PLEASE UNLOAD");
					//while(1){

						//if(BINA){
							BINA_weight-=5;
							//BINB_weight-=20;
						//}
					//}

		 }
	else if(BINB_weight>=Total_weight)
		 {
			//lcd print bina or binb is heavy please unload
				//if()
					p.LCD_SendByte(0x01,0);
					p.set_cursor(0,0);
					p.lcd_string("BINB FULL");
					p.set_cursor(1,0);
					p.lcd_string("PLEASE UNLOAD");
					//while(1){

						//if(BINA){
							//BINA_weight-=20;
							BINB_weight-=5;
						//}
					//}

		 }
	else
	 {
		xTaskNotifyGive(task1_handle);
	 }
   }
}
static void SensorTask(void*)
{    static uint8_t sw=0;
     sensorvalues  st;
	while(1)
	{   ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	    GPIOD->ODR|=1<<10;
		if(TIM2->SR&(1<<3)&&(sw==0))
				{  //st.weight=0;
					TIM2->SR&=~(1<<3);//
					st.start=TIM2->CCR3;
					  GPIOD->ODR^=(1<<12);
					  ADC1->CR2 |= (1<<30);
                     while(!(ADC1->SR & (1<<1)))
                     {

                     }
					   /* Read result */
					 st.result = ADC1->DR;
					 st.result=st.result*(3.3/4095);
					sw=1;
				}
		  if(sw==1)
		  {   uint32_t tof=0;
		      uint32_t ptime=TIM2->CNT;
			  if(ptime>=st.start)
		         {
			       tof=ptime-st.start;
		         }
			  else
				  tof=(10000-st.start)+ptime;
			  if(tof>=8000)
			  {  //GPIOD->ODR^=(1<<15);
			    st.end=TIM2->CNT;
			    st.end_stuck=TIM2->CNT;
			    sw=0;
			     if(xQueueSend(xQueue,&st,portMAX_DELAY)!=pdPASS)
			       {
				    //lcd display unable to proceed to tracking ;
			       }
			  }
		  }
		    if(TIM2->SR&(1<<4)&&(sw==1))
		      {   TIM2->SR&=~(1<<4);
			      uint32_t cur=TIM2->CCR4;
					     st.end=cur;
					   // GPIOD->ODR^=(1<<13);
		  			   	  sw=2;
			   }
		    if(sw==2)
		    {
		    	uint32_t tof=0;
		    	uint32_t ptime=TIM2->CNT;
		    	if(ptime>=st.end)
		    	  {
		    	     tof=ptime-st.end;
		    	  }
		    	else
		    	  tof=(10000-st.end)+ptime;
		    	if(tof>=2000)
		    	 {  //GPIOD->ODR^=(1<<15);
		    		//st.end=TIM2->CNT;
		    		st.end_stuck=TIM2->CNT;
		    		sw=0;
		    		if(xQueueSend(xQueue,&st,portMAX_DELAY)!=pdPASS)
		    		 {
		    		     //lcd display unable to proceed to tracking ;
		    		  }
		    	}
		    }
		    if(TIM2->SR&(1<<4)&&(sw==2))
		    {         TIM2->SR&=~(1<<4);
		               uint32_t cur=TIM2->CCR4;
					   st.end_stuck=cur;
						//GPIOD->ODR^=(1<<14);
			 			  sw=0;
						    if(xQueueSend(xQueue,&st,portMAX_DELAY)!=pdPASS)
						       {
							    	//lcd display unable to proceed to tracking ;
							    }
   			  }
		}
  	}

static void TrackingTask(void*)
{sensorvalues recvdata;
    while(1)
    {
 	if(xQueueReceive(xQueue,&recvdata,portMAX_DELAY)==pdPASS)
	{   GPIOD->ODR&=~(1<<10);
 		st2.entry=recvdata.start;
	    st2.Arr=recvdata.end;
 		if(recvdata.start<=recvdata.end)
		{
	      st2.time_ms=recvdata.end-recvdata.start;
         }
	   else
        {
          st2.time_ms=((10000-recvdata.start)+recvdata.end);
         }
	    if(recvdata.end_stuck>=recvdata.end)
			 st2.stuck=recvdata.end_stuck-recvdata.end;
		else
			st2.stuck=(10000-recvdata.end)+recvdata.end_stuck;
	    st2.speed=D/(st2.time_ms/1000);
	    st2.weight=(recvdata.result-0.5)/0.5;
	    xTaskNotifyGive(task3_handle);
	}
    }
}
uint32_t count,c1;
static void ControlTask(void*)
{
    while(1)
    {
	 //if(xQueueReceive(xQueue1,&st3,portMAX_DELAY)==pdPASS)
	  //{
    	 ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		  if(st2.weight>3)
	      {
		  st2.load=HEAVY;
		  str.load="HEAVY";
	      }
	    else
	      {
		 st2.load=LIGHT;
		 str.load="LIGHT";
	      }
	    if(st2.time_ms>=8000)
	     {
		  st2.fault=MISSING_OBJECT;
		  str.fault="MISSING_OBJECT";
	      }
	    else if(st2.time_ms<50)
	      {
	    		  st2.fault=SENSOR_GLITCH;
	    		  str.fault="SENSOR_GLITCH";
	    	}
	    else  if(st2.stuck>=2000)
	     {
	     	  st2.fault=JAM;
	     	 str.fault="JAM";

	     }
	     else
	     {
	    	 st2.fault=NO_FAULT;
	    	 str.fault="NO_FAULT";

	     }
	    if(st2.fault==NO_FAULT)
	    {
	      if(st2.load==HEAVY && st2.speed<40){
	    				//GPIOD->ODR=(1<<13);
	    		st2.state=BINA;
	    		str.state="BINA";
	       }
	      else if(st2.load==LIGHT&&st2.speed>80){
	    				//GPIOD->ODR|=(1<<15);
	    	   st2.state=BINB;
	    	   str.state="BINB";
	          }
	      else {
	    	  st2.state=REJECT;
	    	  st2.fault=INCONSISTENT;
	    	  str.state="REJECT";
	    	  str.fault="INCONSISTENT";
	         }
	    }
	   else{
	    	st2.state=FAULT;
	        str.state="FAULT";

	    }
	    xTaskNotifyGive(task4_handle);
    }

	 //xTaskNotify(task4_handle,fault,eSetValueWithOverwrite);
	 //xQueueSend(xQueue2,&st3,portMAX_DELAY);
    //}

    //ControlTask(fault);
}
static void ActuatorTask(void*)
{
    while(1){
    	//cc=10;
    	//if(xQueueReceive(xQueue2,&st3,portMAX_DELAY)==pdPASS){
    	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
    	cc=11;
    		if(st2.state==BINA){
    			cc=9;
    			BINA_weight+=st2.weight;
    			GPIOD->ODR=(1<<13);
    			//str.state="BINA";
    			 xTaskNotifyGive(task5_handle);

    		}
    		else if(st2.state==BINB){
    			cc=8;
    			BINB_weight+=st2.weight;
    			GPIOD->ODR|=(1<<15);
    			//str.state="BINB";
    			 xTaskNotifyGive(task5_handle);
    		}
    		else if(st2.state==REJECT){
    			GPIOD->ODR|=(1<<14);
    			//str.state="REJECT";
    			 xTaskNotifyGive(task5_handle);
    		}
    		else if(st2.state==FAULT){
    			GPIOD->ODR^=(1<<14);
    			//str.state="FAULT";
    			//buzzer
    			 //xTaskNotifyGive(task7_handle);
    			 xEventGroupSetBits(uart_safety_group,uart|safety);
    		}
    		//xQueueSend(xQueue3,&st3,portMAX_DELAY);
    	//}
	}

}

static void DisplayTask(void*)
{

	while(1){

			ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
			/*count=4;
			GPIOD->ODR|=(1<<14);
			p.initGPIO();
		    p.init();
 			p.set_cursor(0,0);
			char buf[20];
			sprintf(buf,"%ld",st2.speed);
			p.set_cursor(0,0);
			p.lcd_string("SPEED:");
			p.set_cursor(0,7);
			p.lcd_string(buf);
			p.set_cursor(1,0);
			p.lcd_string("STATE:");
			p.set_cursor(1,7);
			p.lcd_string("STATE");*/
			//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
						xSemaphoreTake(lcd_mutex, portMAX_DELAY);
						p.LCD_SendByte(0x01,0);
						p.set_cursor(0,0);
						char buf[20];
						sprintf(buf,"%ld",st2.speed);
						//char *state_str;
						p.set_cursor(0,0);
						p.lcd_string("SPD");
						p.set_cursor(0,4);
						p.lcd_string(buf);
						p.set_cursor(0,8);
						p.lcd_string("ST");
						p.set_cursor(0,11);
						p.lcd_string(str.state);
						p.set_cursor(1,0);
						p.lcd_string("LOAD");
						p.set_cursor(1,6);
						p.lcd_string(str.load);

						//p.lcd_string(state_str);
						xSemaphoreGive(lcd_mutex);
	}
}
/*ENTRY=1000ms ARR=1200ms TOF=200ms SPD=100cm/s LOAD=LIGHT BIN=A
FAULT=JAM DETECTED*/
static void SafetyTask(void*){
	while(1){
		//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		xEventGroupWaitBits(uart_safety_group,safety,pdTRUE,pdFALSE,portMAX_DELAY);
		c1=6;
		p.LCD_SendByte(0x01,0);
		if(st2.fault==MISSING_OBJECT){
			//buzzer
			//lcd
			//uart
			p.set_cursor(1,0);
			p.lcd_string("MISSING_OBJECT");
			missing_buzzer();
		}
		else if(st2.fault==SENSOR_GLITCH){
					//buzzer
					//lcd
					//uart
				p.set_cursor(1,0);
				p.lcd_string("SENSOR_GLITCH");
				glitch_buzzer();
		}
		else if(st2.fault==JAM){
					//buzzer
					//uart
				p.set_cursor(1,0);
				p.lcd_string("JAM");
				jam_buzzer();
		}
		else{
				p.set_cursor(1,0);
				p.lcd_string("INCONSISTENT");

		}
		//xTaskNotifyGive(task6_handle);

	}

}
static void UartTask(void*)
{  while(1)
    {
	//ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	xEventGroupWaitBits(uart_safety_group,uart,pdTRUE,pdFALSE,portMAX_DELAY);
	count=5;
	 printf("ENTRY=%ldms ",st2.entry);
	 printf("ARR=%ldms ",st2.Arr);
	 printf("TOF=%ldms ",st2.time_ms);
	 printf("SPEED=%ldcm/s ",st2.speed);
	 printf("LOAD=%s \n\r",str.load);
	 printf("BIN=%s ",str.state);
	 printf("FAULT=%s\n\r",str.fault);
    }

}

int main(void)
{
  /* USER CODE BEGIN 1 */

	BaseType_t status;

  /* USER CODE END 1 */


  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
     HAL_Init();
     USART3_init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
 // MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  GPIO_Init();
  ADC2_Init();

      TIMER_Init();
      BUZZER_Init();
      p.GPIO_ENB();
      p.lcd_contrl();
      p.lcd_init();
 lcd_mutex=xSemaphoreCreateMutex();
 uart_safety_group=xEventGroupCreate();



   status = xTaskCreate(WeighingTask, "weighing_task", 200, NULL, 1, &task0_handle);

   configASSERT(status == pdPASS);

   status = xTaskCreate(SensorTask, "sensor_task", 200, NULL, 2, &task1_handle);

  configASSERT(status == pdPASS);

  status = xTaskCreate(TrackingTask, "Tracking_task", 200,NULL, 3, &task2_handle);

  configASSERT(status == pdPASS);

  status = xTaskCreate(ActuatorTask, "Actuator_task", 200, NULL, 5, &task4_handle);

  configASSERT(status == pdPASS);
  status = xTaskCreate(ControlTask, "control_task", 200, NULL, 4, &task3_handle);

  configASSERT(status == pdPASS);
  status = xTaskCreate(DisplayTask, "Display_task", 200, NULL, 6, &task5_handle);

  configASSERT(status == pdPASS);
  status = xTaskCreate(UartTask, "uart_task", 200, NULL, 7, &task6_handle);

  configASSERT(status == pdPASS);
  status = xTaskCreate(SafetyTask, "Safety_task", 200, NULL, 8, &task7_handle);

    configASSERT(status == pdPASS);

    status = xTaskCreate(TemperatureTask, "Temp_Task", 200, NULL, 0, &task8_handle);
    configASSERT(status == pdPASS);

  //start the freeRTOS scheduler
  vTaskStartScheduler();

  /* USER CODE END 2 */



  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}





/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
