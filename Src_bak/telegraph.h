#ifndef __TELEGRAPH_H__
#define __TELEGRAPH_H__
#include"include.h"

///////////////////////////////////////////////////////////
/* 通信帧保存的 数据结构:*/

#define 	TELEGRAPH_LENGTH 40
#define	TELEGRAPH_PARAMETER_NUM 10

typedef struct //一条报文84byte
{
	unsigned char operat_seek_num;//本条报文操作查询码
	unsigned char this_data_effect;
	unsigned char telegraph_length;
	unsigned char parameter_num;
	unsigned char telegraph[TELEGRAPH_LENGTH];// 报文本体
	U_parameter parameter[TELEGRAPH_PARAMETER_NUM];//报文参数  最多添加10组参数
}S_Telegraph,*P_S_Telegraph;

typedef struct	//2528byte
{
	unsigned char device_seek_num;
	unsigned char saved_num;
	unsigned char delete_num;
	unsigned char point;
	unsigned char this_data_effect;
	S_Telegraph telegraphs[30];
}S_Device_Telegraph,*P_S_Device_Telegraph;

typedef struct //用于查找指示一个设备通信帧的保存位置(SD卡)
{
	unsigned char device_seek_num;
	unsigned char save_point;
	unsigned char this_data_effect;
}S_Save_Telegraph,*P_S_Save_Telegraph;

typedef struct	//保存全部设备通信协议的保存位置
{
	unsigned char saved_num;
	unsigned char delete_num;
	unsigned char point;
	S_Save_Telegraph telegraph[255];
}S_Device_Save_Telegraph_Info,*P_S_Device_Save_Telegraph_Info;

typedef struct
{
	unsigned char point;
	unsigned char set_static_ram_save_num;
	unsigned char set_dynamic_ram_save_num;
	unsigned char current_static_ram_save_num;
	unsigned char current_dynamic_ram_save_num;
	unsigned char flash_SDcard_save_num;
	unsigned char set_static_ram[MAX_STATIC_RAM_SAVE_NUM];  //device_seek_num  设置常驻ram的seek_num
	unsigned char set_dynamic_ram[8]; //device_seek_num
	unsigned char current_static_ram[MAX_STATIC_RAM_SAVE_NUM];  //device_seek_num实际当前保存于常驻ram的 seek_num
	unsigned char current_dynamic_ram[8]; //device_seek_num	
	unsigned char flash_SDcard[255];  //device_seek_num
}S_Save_Telegraph_Map,*P_S_Save_Telegraph_Map;


typedef struct
{
	S_Device_Save_Telegraph_Info SD_card_save_info;//
	S_Save_Telegraph_Map search_map;
}S_Save_Telegraph_cfg,*P_S_Save_Telegraph_cfg;

typedef struct //常驻ram中的通信协议
{
	unsigned char saved_num;
	unsigned char delete_num;
	unsigned char point;
	S_Device_Telegraph telegraph[MAX_STATIC_RAM_SAVE_NUM];
}S_Static_RAM_Tele_Data,*P_S_Static_RAM_Tele_Data;

typedef struct //动态存储的通信协议
{
	unsigned char point:3;
	unsigned char current_saved_seek_num[8];
	S_Device_Telegraph telegraph[8];
}S_Dynamic_RAM_Tele_Data,*P_S_Dynamic_RAM_Tele_Data;




extern S_Save_Telegraph_cfg save_tel_cfg;//保存通信帧的配置保存信息

extern S_Device_Telegraph current_operat_telegraph;//用于修改(增删改查)
extern S_Static_RAM_Tele_Data RAM_static_tel;//查找通信帧
extern S_Dynamic_RAM_Tele_Data RAM_dynamic_tel;//查找通信帧


unsigned char find_device_seek_num_in_info(unsigned char seek_num);
unsigned char find_device_seek_num_in_map(unsigned char seek_num,unsigned char from);
unsigned char find_operat_seek_num_in_telegraph(P_S_Device_Telegraph tel,unsigned char operat_seek_num);//在一个设备通讯协议里找指定的操作

void creat_flash_SDcard_map(void);//根据SD卡保存信息生成SD卡索引信息

unsigned char find_delete_num_in_SDcard(P_S_Save_Telegraph_cfg cfg);//查找SD卡中一个之前被删除的节点空间
unsigned char insert_telegraph_to_SDcard(P_S_Device_Telegraph telegraph,unsigned char point);//将设备通信协议插入到指定的位置上
unsigned char load_telegraph(FIL*fp,P_S_Device_Telegraph target,unsigned char point);//将SD卡中指定位置上的信息载入到参数2的位置上
void load_telegraph_to_ram_as_map(void);//将SD卡保存的数据按照设定载入到ram中的相应位置
void load_telegraph_dynamic(unsigned char device_seek_num);//动态载入设备通信协议到动态ram区
void load_telegraph_to_current_operat_telegraph(unsigned char seek_num);//将SD卡中参数指定的设备协议载入到协议设置区

unsigned char save_telegraph_to_SDcard(P_S_Device_Telegraph telegraph);//将目标设备协议保存在SD卡中
void save_telegraph_to_ram(P_S_Device_Telegraph telegraph);//将目标设备协议保存的ram中,如果ram中没保存这个设备则不会保存

unsigned char save_telegraph_cfg_to_SDcard(P_S_Save_Telegraph_cfg telegraphcfg);//将协议配置信息保存到SD卡
unsigned char load_telegraph_cfg_to_ram(P_S_Save_Telegraph_cfg telegraphcfg);//将SD卡中保存的协议配置信息读出

#endif

