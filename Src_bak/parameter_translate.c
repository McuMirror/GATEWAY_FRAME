#include "include.h"

/*这个数组的顺序就是遍历的顺序 建议常用的放到前面
排列顺序有要求  参见  'led调光'     组排列顺序*/

S_Parameter_Name parameter_list[]={
	{"未发现",parameter_nothing},
	{"控制器ID",parameter_controller_id},
	{"目标设备ID",parameter_target_id},


	{"节点",parameter_node},

	
	{"通道",parameter_common_channel},
	{"复合通道",parameter_channel},
	
	{"有人延迟时间",parameter_pir_trig_on_delay},
	{"无人延迟时间",parameter_pir_trig_off_delay},
	{"开窗延迟时间",parameter_windows_trig_on_delay},
	{"关窗延迟时间",parameter_windows_trig_off_delay},
	{"开门延迟时间",parameter_door_trig_on_delay},
	{"关门延迟时间",parameter_door_trig_off_delay},

	
	{"温度",parameter_temperature},
	{"湿度",parameter_humidity},
	{"照度",parameter_illumination},
	{"二氧化碳",parameter_co2},
	{"VOC",parameter_voc},
	{"PM2.5",parameter_pm25},

	{"高优先级",parameter_priority_high},
	{"同优先级",parameter_priority_common},
	{"低优先级",parameter_priority_low},
	{"中继等级",parameter_repeater_level},
	{"开中继",parameter_repeater_on},
	{"关中继",parameter_repeater_off},
	{"一级中继",parameter_repeater_first_level},
	{"二级中继",parameter_repeater_two_stage},
	{"中继",parameter_repeater},
	{"开关左上键",parameter_key_value_ul},
	{"开关右上键",parameter_key_value_ur},
	{"开关左下键",parameter_key_value_ll},
	{"开关右下键",parameter_key_value_lr},
	{"开关上双键",parameter_key_value_ud},
	{"开关下双键",parameter_key_value_ld},
	{"开关键值",parameter_key_value},
		


	
	{"开关模式",parameter_s_normal_model},
	{"取反模式",parameter_s_special_model},
	{"开关键值",parameter_switch_value},
	{"清除数据",parameter_clear_data},

	
	{"禁止自动开",parameter_forbid_auto_on},
	
	
	{"优先级时长",parameter_delay_time},
	{"优先级",parameter_priority},	

	
	{"风速停",parameter_fan_speed_stop},
	{"风速低",parameter_fan_speed_low},
	{"风速中",parameter_fan_speed_mid},
	{"风速高",parameter_fan_speed_high},
	{"风速自动",parameter_fan_speed_auto},
	{"风速",parameter_fan_speed},
	{"制热",parameter_heat},
	{"自动",parameter_auto},
	{"除湿",parameter_dry},
	{"制冷",parameter_cool},
	{"加锁",parameter_lock},
	{"解锁",parameter_unlock},
	

	{"1通道",parameter_channel_1},
	{"2通道",parameter_channel_2},
	{"3通道",parameter_channel_3},
	{"4通道",parameter_channel_4},
	{"5通道",parameter_channel_5},
	{"6通道",parameter_channel_6},
	{"7通道",parameter_channel_7},
	{"8通道",parameter_channel_8},
	{"9通道",parameter_channel_9},
	{"0通道",parameter_channel_0},
	
	{"1优先级",parameter_priority_1},
	{"2优先级",parameter_priority_2},
	{"3优先级",parameter_priority_3},
	{"4优先级",parameter_priority_4},
	{"5优先级",parameter_priority_5},
	{"6优先级",parameter_priority_6},
	{"7优先级",parameter_priority_7},
	{"8优先级",parameter_priority_8},
	
	{"1节点",parameter_node_1},
	{"2节点",parameter_node_2},
	{"3节点",parameter_node_3},
	{"4节点",parameter_node_4},
	{"5节点",parameter_node_5},
	{"6节点",parameter_node_6},
	{"7节点",parameter_node_7},
	{"8节点",parameter_node_8},
	{"9节点",parameter_node_9},
	{"10节点",parameter_node_10},
	{"11节点",parameter_node_11},
	{"12节点",parameter_node_12},
	{"13节点",parameter_node_13},
	{"14节点",parameter_node_14},
	{"15节点",parameter_node_15},
	{"16节点",parameter_node_16},
	{"0节点",parameter_node_0},	

	
	{"打开",parameter_turn_on},
	{"关闭",parameter_turn_off},
	{"设置",parameter_set},



	
	{"获取",parameter_check},
	{"节点状态",parameter_node_state},
	{"人体触发",parameter_trig_by_pir},
	{"窗磁触发",parameter_trig_by_windows},
	{"门磁触发",parameter_trig_by_door},
	{"定时触发",parameter_trig_by_time},
	{"报头CRC",parameter_crc_head},
	{"数据CRC",parameter_crc_data},
	
	
	{"LED调光红调亮",parameter_led_red_up},
	{"LED调光红停止",parameter_led_red_stop},
	{"LED调光红调暗",parameter_led_red_down},
	{"LED调光绿调亮",parameter_led_green_up},
	{"LED调光绿停止",parameter_led_green_stop},
	{"LED调光绿调暗",parameter_led_green_down},
	{"LED调光蓝调亮",parameter_led_blue_up},
	{"LED调光蓝停止",parameter_led_blue_stop},
	{"LED调光蓝调暗",parameter_led_blue_down},
	{"LED调光",parameter_led},
	/* 短的 与长的开头一致的    将短的放到最后面 */


	
	{"无线开关",parameter_switch},
	{"窗磁传感器",parameter_windows_sensor},
	{"人体传感器",parameter_body_sensor},
	{"插卡器",parameter_card},
	{"四路控制器",parameter_4_channel_ctrler},
	{"小白",parameter_multiple_sensor}


	
};//必须要与PARAMETER_TYPE类型一一对应否则会发生意想不到的后果//列举出了常用的参数名字扩充这个枚举时必须在最后面添加否则会使数据错乱



extern S_String_Dict string_dict;

extern S_Save_Telegraph_cfg save_tel_cfg;//保存通信帧的配置保存信息

extern S_Device_Telegraph current_operat_telegraph;//用于修改(增删改查)
extern S_Static_RAM_Tele_Data RAM_static_tel;//查找通信帧
extern S_Dynamic_RAM_Tele_Data RAM_dynamic_tel;//查找通信帧

unsigned char add_parameter_to_telegraph(P_S_Device_Telegraph tel,unsigned char operat_seek_num,unsigned parameter_point,U_parameter parameter)
{
	if(find_operat_seek_num_in_telegraph(tel,operat_seek_num))
		{
			tel->telegraphs[tel->point].parameter[parameter_point] = parameter;
			return 1;
		}
	else
		{
			printf("\r\n can not find this operat! please check out!!  \r\ntry command 'show_cur_tel'\r\n");
			return 0;
		}

}


void show_parameter(void)
{
	unsigned char loopx;
	for(loopx = 0; loopx < (unsigned char)parameter_num; loopx ++)
		{
			printf("\r\nparameter_type%d->%s",parameter_list[loopx].type,parameter_list[loopx].parameter_name);
		}
	printf("\r\n\r\n");
}

PARAMETER_TYPE get_parameter_type(char* target_str)
	{
		unsigned char loopx;
		for(loopx = 0; loopx < ((unsigned char)parameter_num) ; loopx ++)
			{
				if(1 == str_cmp(parameter_list[loopx].parameter_name,target_str))
					{
						return parameter_list[loopx].type;
					}
			}
		return parameter_nothing;
	}

char* get_parameter_name(PARAMETER_TYPE type)
{
	unsigned char loopx;
	for(loopx = 0; loopx < ((unsigned char)parameter_num) ; loopx ++)
		{
			if(type == (parameter_list[loopx].type))
				{
					return parameter_list[loopx].parameter_name;
				}
		}
	return parameter_list[0].parameter_name;	
}


unsigned char get_parameter_info(P_S_Revc_Parameter_Info info,char* str)
{
	unsigned char loopx;
	char* target_str;
	for(loopx = 0; loopx < ((unsigned char)parameter_num) ; loopx ++)
		{
			if(2 == str_cmp(parameter_list[loopx].parameter_name,str))
				{
					target_str = parameter_list[loopx].parameter_name;
					info->parameter_length = str_to_hex((str + string_length(target_str)),(unsigned char*)(info->info_hex),PARAMETER_MAX_LENGTH);
					info->info_dec = str_to_int((str + string_length(target_str)));
					info->type = parameter_list[loopx].type;
					return 1;
				}
		}
	return 0;
}

