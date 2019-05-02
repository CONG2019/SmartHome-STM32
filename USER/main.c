#include "includes.h"
#include "app_cfg.h"
#include "app.h"

		
	 int main(void)
	 {
		delay_init();	     //延时初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		LED_Init();		  	 //初始化与LED连接的硬件接口
		OSInit();   
		OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
		OSStart();
	 }




