#ifndef __GATEWAY_H__
#define __GATEWAY_H__
#include "include.h"
typedef struct
{
	unsigned char read_tcm300_id_flag;
	unsigned char TCM300_ID[4];
	unsigned char GATE_WAY_ID[4];
	unsigned char SET_LEARN_CLEAR_ID[4];
	unsigned char TARGAT_ID[4];
	unsigned char TARGAT_DATA[4];
	unsigned char NET_MAC_ID[6];
}ID_def;
extern ID_def id;

typedef struct
{
	unsigned char is_broadcast;
	unsigned char is_delayed_send;
	unsigned char manufacturer_ID[2];   //0 ~ 0x07ff
	unsigned char function_code[2]; //0 ~ 0x0fff
	unsigned char destination_ID[4];
	unsigned char data_length;
	unsigned char* data;
}S_Send_To_Gateway_Message,*P_S_Send_To_Gateway_Message;

/**
send_data_to_gateway_by_msc 通过短码发送信息

**/
void send_data_to_gateway_by_msc(unsigned char master_command,unsigned char salve_command,unsigned char* data,unsigned char length);

//////////////////////////////////////////////////////////////////////////////////////////

/**
send_data_2_gateway 通过长码发送信息

**/
void send_data_2_gateway(P_S_Send_To_Gateway_Message message);

#endif

