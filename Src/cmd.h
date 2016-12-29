
#ifndef __CMD_H__
#define __CMD_H__
#include "include.h"



typedef struct
	{
		unsigned int device_seek_num :8;
		unsigned int operate_seek_num :8;
		unsigned int node:4;			
		unsigned int channel1:1;
		unsigned int channel2:1;
		unsigned int channel3:1;
		unsigned int channel4:1;			
	}S_Command_Info,*P_S_Command_Info;

#pragma anon_unions 
typedef union//�����������ݽṹ
{
	S_Command_Info info;
	unsigned int code;
}command_code;
typedef struct 
{
	unsigned char offset;
	unsigned char length;
	unsigned char parameter_name;
	unsigned char re;
}S_Parameter;

#pragma anon_unions 
typedef union//������Ϣ����   λ�� +����short��С
{
	S_Parameter parameter;
	unsigned int parameter_code;
}U_parameter;


typedef struct
{
	U_parameter parameter_reslut;
	unsigned char parameter_array[6];
}S_Message_Parameter,*p_S_Message_Parameter;

typedef struct		//���ڴӽ�������ִ����֮�䴫��������Ϣ
{
	command_code code;//�ں�device_seek_num��operat_seek_num�����ҵ�����(����ָʾ�ڵ�ͨ��)
	unsigned char parameter_num;
	unsigned char parameter_point;
	S_Message_Parameter parameters[10];//����������,���֧�ֵĲ�������Ϊ�������ڵ�����
	//unsigned char split_parameter[5];
	//unsigned char parameter[30];
	
}S_Command_Message,*P_S_Command_Message;


typedef struct		//����������Ϣ ͨ�����н���ͨ��,���ݵ�ַ
{
	unsigned char current_message_struct:2;//����ָʾ�Ǹ���Ϣ��������ʹ��,ռ��2��bitλ,ֵ��Ϊ0-3
	S_Command_Message message[4];
}S_Command_Communion,*P_S_Command_Communion;
//////////////////////////////////////////////////////////////////////////////



typedef struct 
{
	unsigned char byte_l:4;  //ʮ�����Ƶ���λ
	unsigned char byte_h:4;//ʮ�����Ƹ���λ
}HEX_BYTE;

#pragma anon_unions 
typedef union  //ת��ʮ���������ݽṹ
{
	HEX_BYTE BYTE;
	unsigned char reslut;	
}CHANGE_TO_HEX;


typedef struct
{
	char* cmd_name;
	char (*cmd_func)(char* parameter);
	char* help;
}S_Cmd,*P_S_Cmd;


#define CMD_REVC_BUF_SIZE 	600
#define CMD_SAVE_BUF_SIZE 	CMD_REVC_BUF_SIZE
#define CMD_PARAMETER_NUM	12
#define CMD_PARAMETER_SIZE	((CMD_REVC_BUF_SIZE)/(CMD_PARAMETER_NUM))
typedef struct
{
	unsigned char point;
	unsigned char parameter_num;
	char recv_buf[CMD_REVC_BUF_SIZE];
	char save_buf[CMD_REVC_BUF_SIZE];
	char parameter[CMD_PARAMETER_NUM][CMD_PARAMETER_SIZE];
}S_Cmd_Info,*P_S_Cmd_Info;



unsigned char str_cmp(char * model,char* target);
P_S_Cmd find_cmd(char *cmd);
char helloworld(char* parameter);
void set_string(char* string,unsigned int length,unsigned char data);
void my_mem_copy(char* from,char* to,unsigned int cnt);
unsigned char string_length(char* string);
unsigned char split_string(P_S_Cmd_Info cmd);
char help(char* parameter);
char reboot(char* parameter);
char read_file(char* parameter);
char write_file(char* parameter);
char show_task(char* parameter);
char test_function(char* parameter);

char shell_mem(char* parameter);
char shell_show_parameter(char* parameter);

char shell_save_string_dict(char* parameter);
char shell_add_str_to_dict(char* parameter);
char shell_show_dict(char* parameter);
char shell_delete_str_to_dict(char* parameter);
char shell_load_string_dict(char* parameter);

char shell_set_telegraph(char* parameter);
char shell_show_cur_tel(char* parameter);
char shell_add_telegraph(char* parameter);
char shell_set_tel_parameter(char* parameter);
char shell_save_telegraph(char* parameter);
char shell_load_tele_cfg(char* parameter);
char shell_load_tel_to_ram(char* parameter);


char shell_start_server(char* parameter);
char shell_kill_server(char* parameter);




char shell_start_tcm300_rx(char* parameter);


unsigned int pow10(unsigned char data);
char led_operat(char* parameter);
unsigned int str_to_int(char* str);
unsigned char str_to_hex(char* str,unsigned char* target,unsigned int max_length);
void hex_to_str(char* target_str,unsigned char* hex,unsigned int hex_length);

U_parameter shell_parameter_translate(P_S_Cmd_Info cmd);


void explain_cmd(unsigned char recv_data);


#endif

