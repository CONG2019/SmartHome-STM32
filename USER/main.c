	#include "led.h"
	#include "delay.h"
	#include "sys.h"
	#include "usart.h"	
	#include "includes.h"

		
	/////////////////////////UCOSII任务堆栈设置///////////////////////////////////
	//START 任务
	//设置任务优先级
	#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
	//设置任务堆栈大小
	#define START_STK_SIZE  				64
	//创建任务堆栈空间	
	OS_STK START_TASK_STK[START_STK_SIZE];
	//任务函数接口
	void start_task(void *pdata);	
					 
	//LED1任务
	//设置任务优先级
	#define LED1_TASK_PRIO       			7 
	//设置任务堆栈大小
	#define LED1_STK_SIZE  		    		64
	//创建任务堆栈空间	
	OS_STK LED1_TASK_STK[LED1_STK_SIZE];
	//任务函数接口
	void led1_task(void *pdata);


	//LED2任务
	//设置任务优先级
	#define LED2_TASK_PRIO       			6 
	//设置任务堆栈大小
	#define LED2_STK_SIZE  					64
	//创建任务堆栈空间	
	OS_STK LED2_TASK_STK[LED2_STK_SIZE];
	//任务函数接口
	void led2_task(void *pdata);

		
	 int main(void)
	 {
		delay_init();	     //延时初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		LED_Init();		  	 //初始化与LED连接的硬件接口
		OSInit();   
		OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
		OSStart();
	 }

	 
			
	//开始任务
	void start_task(void *pdata)
	{
		OS_CPU_SR cpu_sr=0;
		pdata = pdata; 
		OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
		OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
		OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);						   
		OSTaskCreate(led2_task,(void *)0,(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],LED2_TASK_PRIO);
		
		OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
		OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
	}

	//LED1任务
	void led1_task(void *pdata)
	{	 	
		while(1)
		{
			LED0=0;
			delay_ms(80);
			LED0=1;
			delay_ms(920);
		};
	}

	//LED2任务
	void led2_task(void *pdata)
	{	  
		while(1)
		{
			LED1=0;
			delay_ms(500);
			LED1=1;
			delay_ms(500);
		};
	}



