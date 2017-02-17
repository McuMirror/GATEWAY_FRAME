/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>
/* USER CODE BEGIN Includes */     
#include "include.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId shellHandle;
osThreadId system_coreHandle;
osThreadId serial_operatHandle;
osThreadId flash_serverHandle;
osThreadId fatfs_operaterHandle;
osThreadId watcher_testHandle;
osThreadId web_serverHandle;
osMessageQId serial_queueHandle;
osMessageQId flash_queueHandle;
osMessageQId fatfs_queueHandle;
osMessageQId shell_queueHandle;
osMessageQId core_queueHandle;
osMessageQId tcm300_tx_queueHandle;

/* USER CODE BEGIN Variables */
extern S_Save_Telegraph_cfg save_tel_cfg;
extern unsigned char G_Usart1_Buff,G_Usart2_Buff,G_Usart3_Buff,G_Usart4_Buff,G_Usart5_Buff,G_Usart6_Buff;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void shellTask(void const * argument);
void system_core_task(void const * argument);
void serial_operat_task(void const * argument);
void flash_server_task(void const * argument);
void fatfs_operater_task(void const * argument);
void watcher_task(void const * argument);
void web_server_task(void const * argument);

extern void MX_FATFS_Init(void);
extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

/* USER CODE BEGIN 2 */

void test_func(void)
{
	unsigned char loop100;
	char buf[10];
	for(loop100 = 0 ; loop100 <10 ; loop100++)
		{
			buf[loop100] = loop100;
			printf("func_buf[%d]->%p\r\n",loop100,&buf[loop100]);
		}	
	//return buf;
}


/* USER CODE END 2 */

/* USER CODE BEGIN 3 */


/* USER CODE END 3 */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of shell */
  osThreadDef(shell, shellTask, osPriorityNormal, 0, 600);
  shellHandle = osThreadCreate(osThread(shell), NULL);

  /* definition and creation of system_core */
  osThreadDef(system_core, system_core_task, osPriorityNormal, 0, 300);
  system_coreHandle = osThreadCreate(osThread(system_core), NULL);

  /* definition and creation of serial_operat */
  osThreadDef(serial_operat, serial_operat_task, osPriorityHigh, 0, 400);
  serial_operatHandle = osThreadCreate(osThread(serial_operat), NULL);

  /* definition and creation of flash_server */
  osThreadDef(flash_server, flash_server_task, osPriorityHigh, 0, 600);
  flash_serverHandle = osThreadCreate(osThread(flash_server), NULL);

  /* definition and creation of fatfs_operater */
  osThreadDef(fatfs_operater, fatfs_operater_task, osPriorityHigh, 0, 600);
  fatfs_operaterHandle = osThreadCreate(osThread(fatfs_operater), NULL);

  /* definition and creation of watcher_test */
  osThreadDef(watcher_test, watcher_task, osPriorityNormal, 0, 300);
  watcher_testHandle = osThreadCreate(osThread(watcher_test), NULL);

  /* definition and creation of web_server */
  osThreadDef(web_server, web_server_task, osPriorityNormal, 0, 128);
  web_serverHandle = osThreadCreate(osThread(web_server), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of serial_queue */
  osMessageQDef(serial_queue, 8, uint8_t);
  serial_queueHandle = osMessageCreate(osMessageQ(serial_queue), NULL);

  /* definition and creation of flash_queue */
  osMessageQDef(flash_queue, 5, uint32_t);
  flash_queueHandle = osMessageCreate(osMessageQ(flash_queue), NULL);

  /* definition and creation of fatfs_queue */
  osMessageQDef(fatfs_queue, 8, uint32_t);
  fatfs_queueHandle = osMessageCreate(osMessageQ(fatfs_queue), NULL);

  /* definition and creation of shell_queue */
  osMessageQDef(shell_queue, 10, uint32_t);
  shell_queueHandle = osMessageCreate(osMessageQ(shell_queue), NULL);

  /* definition and creation of core_queue */
  osMessageQDef(core_queue, 10, uint32_t);
  core_queueHandle = osMessageCreate(osMessageQ(core_queue), NULL);

  /* definition and creation of tcm300_tx_queue */
  osMessageQDef(tcm300_tx_queue, 10, uint32_t);
  tcm300_tx_queueHandle = osMessageCreate(osMessageQ(tcm300_tx_queue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* shellTask function */
void shellTask(void const * argument)
{
  /* init code for FATFS */
  MX_FATFS_Init();

  /* init code for USB_HOST */
  MX_USB_HOST_Init();

  /* USER CODE BEGIN shellTask */
  	save_task_info();	
	printf("\n\r\n\r        kernel start success!\n\r");
	printf("        stm32 shell strat!\n\r\n\r");

	load_dict(position_sd_card);
	load_telegraph_cfg_to_ram(&save_tel_cfg);
	load_telegraph_to_ram_as_map();
	
  	InitW5500();
	printf("SD Card information : total size :%ldMb  freesize : %ldMb\n\r",((SDCard.n_fatent*SDCard.csize/2)/1024),((SDCard.free_clust*SDCard.csize/2)/1024));

	unsigned char recv_data;

  /* USER CODE BEGIN shellTask */
  /* Infinite loop */
  for(;;)
  {
	xQueueReceive(shell_queueHandle, &recv_data, portMAX_DELAY);
	while(HAL_UART_Receive_IT(&huart6,&G_Usart6_Buff,1)==HAL_OK);
	//printf("%c",recv_data);
	explain_cmd(recv_data);
  }
  /* USER CODE END shellTask */
}

/* system_core_task function */
void system_core_task(void const * argument)
{
  /* USER CODE BEGIN system_core_task */
  	save_task_info();	
  	//unsigned short led_data = 0,data;
  /* Infinite loop */
  for(;;)
  {
	/*led_data ++;
	data = led_data << 8;
	HAL_GPIO_WritePin(GPIOD,0XFF00,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,data,GPIO_PIN_RESET);*/
	osDelay(20);   
	while(HAL_UART_Receive_IT(&huart6,&G_Usart6_Buff,1)==HAL_OK);
  }
  /* USER CODE END system_core_task */
}

/* serial_operat_task function */
void serial_operat_task(void const * argument)
{
  /* USER CODE BEGIN serial_operat_task */
  unsigned char serial_value;
  save_task_info();
  char task_buf[100];
  char log_buf[100];
  static char save_buf[1024];
  static char recv_num = 0;
  /* Infinite loop */
  for(;;)
  {
  	xQueueReceive(serial_queueHandle, &serial_value, portMAX_DELAY);
	switch(serial_value)
		{
			case USART1_RECV_DATA:
				//send(1,data_from_tcm300.rx_data,data_from_tcm300.data_len);//通过socket1 发送信息
				HAL_UART_Transmit(&huart1,P_CURRENT_WIFI_RX_DATA, CURRENT_WIFI_RX_DATA_LENGTH, 200);
				FINISH_DEAL_WIFI_RX_DATA;
				
				break;
			case USART2_RECV_DATA:
				task_deal_tcm300();
				//send(4,P_CURRENT_TCM300_RX_DATA,CURRENT_TCM300_RX_DATA_LENGTH);
				set_string(task_buf,100,0);
				set_string(log_buf,100,0);
				hex_to_str(task_buf,P_CURRENT_TCM300_RX_DATA,CURRENT_TCM300_RX_DATA_LENGTH);
				sprintf(log_buf,"recv : %s\r\n",task_buf);
				printf("%s",log_buf);
				if(recv_num < 10)
					{
						strcat(save_buf,log_buf);
						recv_num++;
					}
				else
					{
						recv_num = 0;
						save_tcm300_log(save_buf,string_length(save_buf));
						set_string(save_buf,1024,0);
					}
				FINISH_DEAL_TCM300_RX_DATA;
				break;

			case USART3_RECV_DATA:
				break;

			case USART4_RECV_DATA:
				break;

			case USART5_RECV_DATA:
				break;

			case USART6_RECV_DATA:
				break;
				
		}
  }
  /* USER CODE END serial_operat_task */
}

/* flash_server_task function */
void flash_server_task(void const * argument)
{
  /* USER CODE BEGIN flash_server_task */
  	osDelay(100);
	save_task_info();	
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END flash_server_task */
}

/* fatfs_operater_task function */
void fatfs_operater_task(void const * argument)
{
  /* USER CODE BEGIN fatfs_operater_task */
	save_task_info();		
	osDelay(1000);
	 unsigned char num = 10;
 	 //__disable_irq();
 	 do
 	 	{
			res = f_mount(&USB_device, USBH_Path,1);
 	 	}while(res!=0 && num--);
	 
	//__enable_irq();
	if(res != 0)
		{
			printf("\r\nUSB_device mount error !!\r\n");			
			printf("stm32->");
		}
	else
		{
			printf("USB Dev information : total size :%ldMb  freesize : %ldMb\n\r",((USB_device.n_fatent*USB_device.csize/2)/1024),((USB_device.free_clust*USB_device.csize/2)/1024));
			printf("stm32->");
		}
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END fatfs_operater_task */
}

/* watcher_task function */
void watcher_task(void const * argument)
{
  /* USER CODE BEGIN watcher_task */
	save_task_info();	
//static My_tskTCB* this_handle;
//this_handle = (My_tskTCB*)xTaskGetCurrentTaskHandle();

//char buf2[10];

//char buf[10];
//unsigned loop100;
//for(loop100 = 0 ; loop100 <10 ; loop100++)
//{
	//buf[loop100] = loop100;
	//printf("buf1_p[%d] -> %p\r\n",loop100,&buf[loop100]);
//}


//for(loop100 = 0 ; loop100 <10 ; loop100++)
//{
	//buf2[loop100] = loop100;
	//printf("buf2_p[%d] -> %p\r\n",loop100,&buf2[loop100]);
//}


//test_func();

//test_func();


  osDelay(5000);
  //read_tcm300_id();
  /* Infinite loop */
  for(;;)
  {
 	osDelay(50);
  }
  /* USER CODE END watcher_task */
}

/* web_server_task function */
void web_server_task(void const * argument)
{
  /* USER CODE BEGIN web_server_task */
  save_task_info();	
  osDelay(5000);
  /* Infinite loop */
  for(;;)
  {
	do_http();
	osDelay(20);
  }
  /* USER CODE END web_server_task */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
