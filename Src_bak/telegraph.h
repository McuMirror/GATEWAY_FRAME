#ifndef __TELEGRAPH_H__
#define __TELEGRAPH_H__
#include"include.h"

///////////////////////////////////////////////////////////
/* ͨ��֡����� ���ݽṹ:*/

#define 	TELEGRAPH_LENGTH 40
#define	TELEGRAPH_PARAMETER_NUM 10

typedef struct //һ������84byte
{
	unsigned char operat_seek_num;//�������Ĳ�����ѯ��
	unsigned char this_data_effect;
	unsigned char telegraph_length;
	unsigned char parameter_num;
	unsigned char telegraph[TELEGRAPH_LENGTH];// ���ı���
	U_parameter parameter[TELEGRAPH_PARAMETER_NUM];//���Ĳ���  ������10�����
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

typedef struct //���ڲ���ָʾһ���豸ͨ��֡�ı���λ��(SD��)
{
	unsigned char device_seek_num;
	unsigned char save_point;
	unsigned char this_data_effect;
}S_Save_Telegraph,*P_S_Save_Telegraph;

typedef struct	//����ȫ���豸ͨ��Э��ı���λ��
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
	unsigned char set_static_ram[MAX_STATIC_RAM_SAVE_NUM];  //device_seek_num  ���ó�פram��seek_num
	unsigned char set_dynamic_ram[8]; //device_seek_num
	unsigned char current_static_ram[MAX_STATIC_RAM_SAVE_NUM];  //device_seek_numʵ�ʵ�ǰ�����ڳ�פram�� seek_num
	unsigned char current_dynamic_ram[8]; //device_seek_num	
	unsigned char flash_SDcard[255];  //device_seek_num
}S_Save_Telegraph_Map,*P_S_Save_Telegraph_Map;


typedef struct
{
	S_Device_Save_Telegraph_Info SD_card_save_info;//
	S_Save_Telegraph_Map search_map;
}S_Save_Telegraph_cfg,*P_S_Save_Telegraph_cfg;

typedef struct //��פram�е�ͨ��Э��
{
	unsigned char saved_num;
	unsigned char delete_num;
	unsigned char point;
	S_Device_Telegraph telegraph[MAX_STATIC_RAM_SAVE_NUM];
}S_Static_RAM_Tele_Data,*P_S_Static_RAM_Tele_Data;

typedef struct //��̬�洢��ͨ��Э��
{
	unsigned char point:3;
	unsigned char current_saved_seek_num[8];
	S_Device_Telegraph telegraph[8];
}S_Dynamic_RAM_Tele_Data,*P_S_Dynamic_RAM_Tele_Data;




extern S_Save_Telegraph_cfg save_tel_cfg;//����ͨ��֡�����ñ�����Ϣ

extern S_Device_Telegraph current_operat_telegraph;//�����޸�(��ɾ�Ĳ�)
extern S_Static_RAM_Tele_Data RAM_static_tel;//����ͨ��֡
extern S_Dynamic_RAM_Tele_Data RAM_dynamic_tel;//����ͨ��֡


unsigned char find_device_seek_num_in_info(unsigned char seek_num);
unsigned char find_device_seek_num_in_map(unsigned char seek_num,unsigned char from);
unsigned char find_operat_seek_num_in_telegraph(P_S_Device_Telegraph tel,unsigned char operat_seek_num);//��һ���豸ͨѶЭ������ָ���Ĳ���

void creat_flash_SDcard_map(void);//����SD��������Ϣ����SD��������Ϣ

unsigned char find_delete_num_in_SDcard(P_S_Save_Telegraph_cfg cfg);//����SD����һ��֮ǰ��ɾ���Ľڵ�ռ�
unsigned char insert_telegraph_to_SDcard(P_S_Device_Telegraph telegraph,unsigned char point);//���豸ͨ��Э����뵽ָ����λ����
unsigned char load_telegraph(FIL*fp,P_S_Device_Telegraph target,unsigned char point);//��SD����ָ��λ���ϵ���Ϣ���뵽����2��λ����
void load_telegraph_to_ram_as_map(void);//��SD����������ݰ����趨���뵽ram�е���Ӧλ��
void load_telegraph_dynamic(unsigned char device_seek_num);//��̬�����豸ͨ��Э�鵽��̬ram��
void load_telegraph_to_current_operat_telegraph(unsigned char seek_num);//��SD���в���ָ�����豸Э�����뵽Э��������

unsigned char save_telegraph_to_SDcard(P_S_Device_Telegraph telegraph);//��Ŀ���豸Э�鱣����SD����
void save_telegraph_to_ram(P_S_Device_Telegraph telegraph);//��Ŀ���豸Э�鱣���ram��,���ram��û��������豸�򲻻ᱣ��

unsigned char save_telegraph_cfg_to_SDcard(P_S_Save_Telegraph_cfg telegraphcfg);//��Э��������Ϣ���浽SD��
unsigned char load_telegraph_cfg_to_ram(P_S_Save_Telegraph_cfg telegraphcfg);//��SD���б����Э��������Ϣ����

#endif

