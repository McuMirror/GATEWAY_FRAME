#ifndef __STRING_DICT__
#define __STRING_DICT__
#include "include.h"

///////////////////////////////////////////////////////////////
/**
*  字符串查询字典数据结构
*/
#define MAX_DICT_SAVE_NUM	254
#define MAX_STATIC_RAM_SAVE_NUM 	20

#define EFFECT 		0XAA
#define UNEFFECT		0X55

typedef enum
{
	type_controller_device = 1,
	type_sensor_decice,
	type_operat,
	type_parameter,
	type_radio_device
}DICT_TYPE;


typedef struct
{
unsigned char test_h:3;
unsigned char test_l:5;
}test;


typedef struct
{
	unsigned char seek_num;
	DICT_TYPE type;
	unsigned char this_data_effect;
	char name[40];
}S_String_Info,*P_S_String_Info;


typedef struct //字典数据结构(本体)
{
	S_String_Info string[MAX_DICT_SAVE_NUM];   //为了保持兼容性   需要添加新成员时  在此结构体后面加
	unsigned char save_device_num;//保存的设备数量
	unsigned char save_operate_num;//保存的 操作 数量
	unsigned char save_parameter_num; //保存的参数 数量
	unsigned char point;//调用find_str_in_dict函数后找的的符合条件的字的位置
	unsigned char save_number; //保存的最大数量
	unsigned char delete_number;//删除的个数
	
	//unsigned char save_sensor_num;
}S_String_Dict,*P_S_String_Dict;



typedef enum
{
	position_flash = 1,
	position_sd_card
}E_Save_Position;



extern S_String_Dict string_dict;


void save_string_dict(E_Save_Position position);
void load_dict(E_Save_Position position);
unsigned char seek_num_in_dict(unsigned char num);
unsigned char get_auto_seek_num(void);
char* get_str_name(unsigned char seek_num); //获取seek_num 的name


unsigned char find_str_in_dict(char* target_str);
unsigned char find_empty_in_dict(void);
unsigned char add_string_to_dict(P_S_String_Info str_info);
unsigned char delete_str_in_dict(char* target_str);
void show_dict(unsigned char type);


#endif

