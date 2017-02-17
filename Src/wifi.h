#ifndef __WIFI_H__
#define __WIFI_H__
#include "include.h"

#define	WIFI_RECV_BUFF_SIZE	1024
#define 	WIFI_SEND_BUFF_SIZE	1024


#define P_CURRENT_WIFI_RX_DATA 			(wifi_operat_data.recv_msg[wifi_operat_data.operat_point].rx_data)
#define CURRENT_WIFI_RX_DATA_LENGTH	(wifi_operat_data.recv_msg[wifi_operat_data.operat_point].len)
#define WIFI_RX_DATA(x)					(wifi_operat_data.recv_msg[wifi_operat_data.operat_point].rx_data[x])
#define FINISH_DEAL_WIFI_RX_DATA 		(wifi_operat_data.recv_msg[wifi_operat_data.operat_point++].this_data_effect = UNEFFECT)




#define READ_NREADY HAL_GPIO_ReadPin(WIFI_NREADY_GPIO_Port,WIFI_NREADY_Pin)
#define READ_NLINK HAL_GPIO_ReadPin(WIFI_NLINK_GPIO_Port,WIFI_NLINK_Pin)

#define PRESS_SMART_LINK HAL_GPIO_WritePin(WIFI_SMART_LINK_GPIO_Port,WIFI_SMART_LINK_Pin,GPIO_PIN_RESET)
#define RELEASE_SMART_LINK HAL_GPIO_WritePin(WIFI_SMART_LINK_GPIO_Port,WIFI_SMART_LINK_Pin,GPIO_PIN_SET)
#define SET_SMART_LINK {PRESS_SMART_LINK;HAL_Delay(1000);RELEASE_SMART_LINK;}
#define RESET_SMART_LINK {PRESS_SMART_LINK;HAL_Delay(5000);RELEASE_SMART_LINK;}

#define PRESS_WIFI_RESET HAL_GPIO_WritePin(WIFI_REST_GPIO_Port,WIFI_REST_Pin,GPIO_PIN_RESET)
#define RELEASE_WIFI_RESET HAL_GPIO_WritePin(WIFI_REST_GPIO_Port,WIFI_REST_Pin,GPIO_PIN_SET)
#define RESET_WIFI {PRESS_WIFI_RESET;HAL_Delay(20);RELEASE_WIFI_RESET;}






typedef struct
{
	unsigned short data_len;
	unsigned short dma_cndtr;
	unsigned char is_dma_tx_sending;
	unsigned char rx_data[WIFI_RECV_BUFF_SIZE];
	unsigned char tx_data[WIFI_SEND_BUFF_SIZE];
	
	unsigned char recv_ok;	
	unsigned short point;
	unsigned char enable_rxdata;
	unsigned char vBigRxMax;
}S_Wifi_Recv_Data,*p_S_Wifi_Recv_Data;
extern S_Wifi_Recv_Data data_from_wifi;



typedef struct
{
	unsigned short len;
	unsigned char this_data_effect;
	unsigned char rx_data[WIFI_RECV_BUFF_SIZE];
}S_Wifi_Recv_Msg,*P_S_Wifi_Recv_Msg;


typedef struct//
{
	unsigned char save_point:1;//用于指示要保存到的下一个暂存缓冲区位置
	unsigned char operat_point:1;//用于指示当前正在处理的缓存位置
	S_Wifi_Recv_Msg recv_msg[2];
}S_Wifi_Operat_buf,*P_S_Wifi_Operat_buf;

extern S_Wifi_Operat_buf wifi_operat_data;
extern unsigned int Wifi_Mesg;


void transfer_wifi_rxdata(void);

#endif

