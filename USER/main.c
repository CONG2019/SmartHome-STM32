#include "includes.h"
#include "app_cfg.h"
#include "app.h"

		
	 int main(void)
	 {
		delay_init();	     //��ʱ��ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
		OSInit();   
		OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
		OSStart();
	 }




