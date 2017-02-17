#ifndef __TCM300_H__
#define __TCM300_H__
#include "include.h"


#define cOperateCode_A   0X50
#define cOperateCode_C   0X70

#define cOperateCode_B   0X10
#define cOperateCode_D   0X30

#define TCM300_RECV_BUFF_SIZE 300
#define TCM300_SEND_BUFF_SIZE 256


#define P_CURRENT_TCM300_RX_DATA 		(tcm300_operat_data.recv_msg[tcm300_operat_data.operat_point].rx_data)
#define CURRENT_TCM300_RX_DATA_LENGTH	(tcm300_operat_data.recv_msg[tcm300_operat_data.operat_point].len)
#define TCM300_RX_DATA(x)				(tcm300_operat_data.recv_msg[tcm300_operat_data.operat_point].rx_data[(x)])
#define FINISH_DEAL_TCM300_RX_DATA 		(tcm300_operat_data.recv_msg[tcm300_operat_data.operat_point++].this_data_effect = UNEFFECT)

typedef struct
{
	unsigned short len;
	unsigned char this_data_effect;
	unsigned char rx_data[TCM300_RECV_BUFF_SIZE];
}S_Tcm300_Recv_Msg,*PS_Tcm300_Recv_Msg;

/*这个结构体存在的意义是如果使用空闲中断接受不定长数据的话
data_from_tcm300中的接收缓存可能随时都会改变,如果直接对接收缓存操作的话
可能会产生意想不到的情况,所以建议在tcm300接受完成后第一时间将接受缓存中的
数据复制到本结构体中,在本结构体中进行数据处理
*/
typedef struct//
{
	unsigned char save_point:1;//用于指示要保存到的下一个暂存缓冲区位置
	unsigned char operat_point:1;//用于指示当前正在处理的缓存位置
	S_Tcm300_Recv_Msg recv_msg[2];
}S_Tcm300_Operat_buf,*P_S_Tcm300_Operat_buf;

extern S_Tcm300_Operat_buf tcm300_operat_data;


typedef struct
{
	unsigned short data_len;
	unsigned short dma_cndtr;
	unsigned char is_dma_tx_sending;
	unsigned char rx_data[TCM300_RECV_BUFF_SIZE];
	unsigned char tx_data[TCM300_SEND_BUFF_SIZE];
	
	unsigned char recv_ok;	
	unsigned short point;
	unsigned char enable_rxdata;
	unsigned char vBigRxMax;
}S_Tcm300_Recv_Data,*p_S_Tcm300_Recv_Data;

extern S_Tcm300_Recv_Data data_from_tcm300;
extern unsigned char G_Usart2_Buff;
extern unsigned int Tcm300_Mesg;

typedef struct
{
	unsigned char len;
	unsigned char this_data_effect;
	unsigned char tx_data[TCM300_SEND_BUFF_SIZE];
}S_Tcm300_Msg,*P_S_Tcm300_Msg;

typedef struct
{
	unsigned char point:3;
	unsigned int send_point;
	S_Tcm300_Msg msg[8];
}S_Tcm300_Msg_Ctrl,*P_S_Tcm300_Msg_Ctrl;


void send_data_to_tcm300(unsigned char len);
void send_data_by_tcm300(char* data,unsigned short lenth);
void read_tcm300_id(void);
void task_deal_tcm300(void);
/*void Deal_RPS_RadioSub(void);
unsigned char find_tcm_ID(P_S_Save_Learned_Device_Data P_DATA );
void Deal_4BS_RadioSub(void);
void deal_windows_sub(void);
void deal_pir_sub(void);
void send_data_to_tcm300_by_msg(unsigned char* data,unsigned short data_length);*/
void task_tcm300_send(unsigned int addr);
void transfer_tcm300_rxdata(void);

void save_tcm300_log(char* log,unsigned char log_length);

#endif
