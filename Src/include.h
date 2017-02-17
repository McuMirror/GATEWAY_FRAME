#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#define SOCKET_BUFF_SIZE 	256

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef char int8;

#include <stdio.h>
#include <string.h>
#include <math.h>


#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "my_it.h"

#include "can.h"
#include "fatfs.h"
#include "rtc.h"
#include "sdio.h"
#include "spi.h"
#include "usart.h"
//#include "usb_otg.h"
#include "gpio.h"

#include "shell.h"
#include "led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "StackMacros.h"
#include "cpu.h"

#include "object.h"
#include "w5500.h"
#include "socket.h"
#include "w5500_driver.h"
#include "wizchip_conf.h"
#include "cmd.h"
#include "string_dict.h"
#include "flash.h"
#include "telegraph.h"
#include "parameter_translate.h"


#include "tcm300.h"
#include "wifi.h"
#include "gateway.h"
#include "translate_to_tcm300.h"
#include "CRC.h"
#include "ult.h" 
#include "httpd.h"
#include "httpult.h"
#include "script.h"

#endif



