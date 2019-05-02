	#include "led.h"
	#include "delay.h"
	#include "sys.h"
	#include "usart.h"	
	#include "includes.h"

		
	/////////////////////////UCOSII�����ջ����///////////////////////////////////
	//START ����
	//�����������ȼ�
	#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
	//���������ջ��С
	#define START_STK_SIZE  				64
	//���������ջ�ռ�	
	OS_STK START_TASK_STK[START_STK_SIZE];
	//�������ӿ�
	void start_task(void *pdata);	
					 
	//LED1����
	//�����������ȼ�
	#define LED1_TASK_PRIO       			7 
	//���������ջ��С
	#define LED1_STK_SIZE  		    		64
	//���������ջ�ռ�	
	OS_STK LED1_TASK_STK[LED1_STK_SIZE];
	//�������ӿ�
	void led1_task(void *pdata);


	//LED2����
	//�����������ȼ�
	#define LED2_TASK_PRIO       			6 
	//���������ջ��С
	#define LED2_STK_SIZE  					64
	//���������ջ�ռ�	
	OS_STK LED2_TASK_STK[LED2_STK_SIZE];
	//�������ӿ�
	void led2_task(void *pdata);

		
	 int main(void)
	 {
		delay_init();	     //��ʱ��ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
		OSInit();   
		OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
		OSStart();
	 }

	 
			
	//��ʼ����
	void start_task(void *pdata)
	{
		OS_CPU_SR cpu_sr=0;
		pdata = pdata; 
		OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
		OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
		OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);						   
		OSTaskCreate(led2_task,(void *)0,(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],LED2_TASK_PRIO);
		
		OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
		OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
	}

	//LED1����
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

	//LED2����
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



