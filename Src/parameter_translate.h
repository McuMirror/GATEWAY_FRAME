#ifndef __PARAMETER_TRANSLATE_H__
#define __PARAMETER_TRANSLATE_H__
#include "include.h"

/*枚举的顺序不能随意改动 否则必将出现错误的情况!!!!!如果需要
添加新的枚举成员一定加在后面(parameter_num 之前);
但是与枚举一一对应的遍历结构体数组顺序可以随意改变,
那个遍历数组用于查找预设字符串参数,常用的建议放在前面*/

typedef enum{
	parameter_nothing = 0,
	parameter_controller_id,
	parameter_target_id,
	
	parameter_switch,
	parameter_windows_sensor,
	parameter_body_sensor,
	parameter_card,
	parameter_4_channel_ctrler,
	parameter_multiple_sensor, //小白
	
	parameter_temperature,
	parameter_humidity,
	parameter_illumination,
	parameter_co2,
	parameter_voc,
	parameter_pm25,
	
	parameter_turn_on,
	parameter_turn_off,
	parameter_set,
	parameter_pir_trig_on_delay,
	parameter_pir_trig_off_delay,
	
	parameter_windows_trig_on_delay,
	parameter_windows_trig_off_delay,
	
	parameter_door_trig_on_delay,
	parameter_door_trig_off_delay,
	
	parameter_check,
	parameter_node_state,
	
	parameter_trig_by_pir,
	parameter_trig_by_windows,
	parameter_trig_by_door,
	parameter_trig_by_time,
	
	parameter_crc_head,
	parameter_crc_data,
	parameter_s_normal_model,
	parameter_s_special_model,
	parameter_switch_value,	
	parameter_clear_data,
	parameter_channel,
	parameter_channel_1,
	parameter_channel_2,
	parameter_channel_3,
	parameter_channel_4,
	parameter_channel_5,
	parameter_channel_6,
	parameter_channel_7,
	parameter_channel_8,
	parameter_channel_9,
	parameter_channel_0,
	parameter_node,
	parameter_node_1,
	parameter_node_2,
	parameter_node_3,
	parameter_node_4,
	parameter_node_5,
	parameter_node_6,
	parameter_node_7,
	parameter_node_8,
	parameter_node_9,
	parameter_node_10,
	parameter_node_11,
	parameter_node_12,
	parameter_node_13,
	parameter_node_14,
	parameter_node_15,
	parameter_node_16,
	parameter_node_0,
	parameter_fan_speed_stop,
	parameter_fan_speed_low,
	parameter_fan_speed_mid,
	parameter_fan_speed_high,
	parameter_fan_speed_auto,
	parameter_fan_speed,
	parameter_heat,
	parameter_auto,
	parameter_dry,
	parameter_cool,
	parameter_lock,
	parameter_unlock,
	parameter_led_red_up,
	parameter_led_red_stop,
	parameter_led_red_down,
	parameter_led_green_up,
	parameter_led_green_stop,
	parameter_led_green_down,
	parameter_led_blue_up,
	parameter_led_blue_stop,
	parameter_led_blue_down,
	parameter_led,
	parameter_forbid_auto_on,
	parameter_delay_time,
	parameter_priority,
	parameter_priority_1,
	parameter_priority_2,
	parameter_priority_3,
	parameter_priority_4,
	parameter_priority_5,
	parameter_priority_6,
	parameter_priority_7,
	parameter_priority_8,
	parameter_priority_high,
	parameter_priority_common,
	parameter_priority_low,
	parameter_repeater_level,
	parameter_repeater_on,
	parameter_repeater_off,
	parameter_repeater_first_level,
	parameter_repeater_two_stage,
	parameter_repeater,
	
	parameter_key_value_ul,
	parameter_key_value_ur,
	parameter_key_value_ll,
	parameter_key_value_lr,
	parameter_key_value_ud,
	parameter_key_value_ld,
	parameter_key_value,

	parameter_common_channel,






	

	parameter_num//这个成员放在最后面用来指示目前有多少个PARAMETER_TYPE数据扩充这个枚举时必须在最后面在parameter_num之前添加,否则会使数据错乱
	
}PARAMETER_TYPE;//预设的常用参数名字

typedef struct
{
	char* parameter_name;
	PARAMETER_TYPE type;
}S_Parameter_Name,*P_S_Parameter_Name;//常用的参数名字以及其对应的编号

extern S_Parameter_Name parameter_list[];

#define PARAMETER_MAX_LENGTH 10
typedef struct
{
	PARAMETER_TYPE type;
	unsigned char parameter_length;
	char info_hex[PARAMETER_MAX_LENGTH];//16进制
	int info_dec;//十进制
}S_Revc_Parameter_Info,*P_S_Revc_Parameter_Info;


unsigned char get_parameter_info(P_S_Revc_Parameter_Info info,char* str);

unsigned char add_parameter_to_telegraph(P_S_Device_Telegraph tel,unsigned char operat_seek_num,unsigned parameter_point,U_parameter parameter);
void show_parameter(void);

PARAMETER_TYPE get_parameter_type(char* target_str);
char* get_parameter_name(PARAMETER_TYPE type);



#endif

