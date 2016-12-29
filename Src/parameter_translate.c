#include "include.h"

/*��������˳����Ǳ�����˳�� ���鳣�õķŵ�ǰ��
����˳����Ҫ��  �μ�  'led����'     ������˳��*/

S_Parameter_Name parameter_list[]={
	{"δ����",parameter_nothing},
	{"������ID",parameter_controller_id},
	{"Ŀ���豸ID",parameter_target_id},


	{"�ڵ�",parameter_node},

	
	{"ͨ��",parameter_common_channel},
	{"����ͨ��",parameter_channel},
	
	{"�����ӳ�ʱ��",parameter_pir_trig_on_delay},
	{"�����ӳ�ʱ��",parameter_pir_trig_off_delay},
	{"�����ӳ�ʱ��",parameter_windows_trig_on_delay},
	{"�ش��ӳ�ʱ��",parameter_windows_trig_off_delay},
	{"�����ӳ�ʱ��",parameter_door_trig_on_delay},
	{"�����ӳ�ʱ��",parameter_door_trig_off_delay},

	
	{"�¶�",parameter_temperature},
	{"ʪ��",parameter_humidity},
	{"�ն�",parameter_illumination},
	{"������̼",parameter_co2},
	{"VOC",parameter_voc},
	{"PM2.5",parameter_pm25},

	{"�����ȼ�",parameter_priority_high},
	{"ͬ���ȼ�",parameter_priority_common},
	{"�����ȼ�",parameter_priority_low},
	{"�м̵ȼ�",parameter_repeater_level},
	{"���м�",parameter_repeater_on},
	{"���м�",parameter_repeater_off},
	{"һ���м�",parameter_repeater_first_level},
	{"�����м�",parameter_repeater_two_stage},
	{"�м�",parameter_repeater},
	{"�������ϼ�",parameter_key_value_ul},
	{"�������ϼ�",parameter_key_value_ur},
	{"�������¼�",parameter_key_value_ll},
	{"�������¼�",parameter_key_value_lr},
	{"������˫��",parameter_key_value_ud},
	{"������˫��",parameter_key_value_ld},
	{"���ؼ�ֵ",parameter_key_value},
		


	
	{"����ģʽ",parameter_s_normal_model},
	{"ȡ��ģʽ",parameter_s_special_model},
	{"���ؼ�ֵ",parameter_switch_value},
	{"�������",parameter_clear_data},

	
	{"��ֹ�Զ���",parameter_forbid_auto_on},
	
	
	{"���ȼ�ʱ��",parameter_delay_time},
	{"���ȼ�",parameter_priority},	

	
	{"����ͣ",parameter_fan_speed_stop},
	{"���ٵ�",parameter_fan_speed_low},
	{"������",parameter_fan_speed_mid},
	{"���ٸ�",parameter_fan_speed_high},
	{"�����Զ�",parameter_fan_speed_auto},
	{"����",parameter_fan_speed},
	{"����",parameter_heat},
	{"�Զ�",parameter_auto},
	{"��ʪ",parameter_dry},
	{"����",parameter_cool},
	{"����",parameter_lock},
	{"����",parameter_unlock},
	

	{"1ͨ��",parameter_channel_1},
	{"2ͨ��",parameter_channel_2},
	{"3ͨ��",parameter_channel_3},
	{"4ͨ��",parameter_channel_4},
	{"5ͨ��",parameter_channel_5},
	{"6ͨ��",parameter_channel_6},
	{"7ͨ��",parameter_channel_7},
	{"8ͨ��",parameter_channel_8},
	{"9ͨ��",parameter_channel_9},
	{"0ͨ��",parameter_channel_0},
	
	{"1���ȼ�",parameter_priority_1},
	{"2���ȼ�",parameter_priority_2},
	{"3���ȼ�",parameter_priority_3},
	{"4���ȼ�",parameter_priority_4},
	{"5���ȼ�",parameter_priority_5},
	{"6���ȼ�",parameter_priority_6},
	{"7���ȼ�",parameter_priority_7},
	{"8���ȼ�",parameter_priority_8},
	
	{"1�ڵ�",parameter_node_1},
	{"2�ڵ�",parameter_node_2},
	{"3�ڵ�",parameter_node_3},
	{"4�ڵ�",parameter_node_4},
	{"5�ڵ�",parameter_node_5},
	{"6�ڵ�",parameter_node_6},
	{"7�ڵ�",parameter_node_7},
	{"8�ڵ�",parameter_node_8},
	{"9�ڵ�",parameter_node_9},
	{"10�ڵ�",parameter_node_10},
	{"11�ڵ�",parameter_node_11},
	{"12�ڵ�",parameter_node_12},
	{"13�ڵ�",parameter_node_13},
	{"14�ڵ�",parameter_node_14},
	{"15�ڵ�",parameter_node_15},
	{"16�ڵ�",parameter_node_16},
	{"0�ڵ�",parameter_node_0},	

	
	{"��",parameter_turn_on},
	{"�ر�",parameter_turn_off},
	{"����",parameter_set},



	
	{"��ȡ",parameter_check},
	{"�ڵ�״̬",parameter_node_state},
	{"���崥��",parameter_trig_by_pir},
	{"���Ŵ���",parameter_trig_by_windows},
	{"�ŴŴ���",parameter_trig_by_door},
	{"��ʱ����",parameter_trig_by_time},
	{"��ͷCRC",parameter_crc_head},
	{"����CRC",parameter_crc_data},
	
	
	{"LED��������",parameter_led_red_up},
	{"LED�����ֹͣ",parameter_led_red_stop},
	{"LED��������",parameter_led_red_down},
	{"LED�����̵���",parameter_led_green_up},
	{"LED������ֹͣ",parameter_led_green_stop},
	{"LED�����̵���",parameter_led_green_down},
	{"LED����������",parameter_led_blue_up},
	{"LED������ֹͣ",parameter_led_blue_stop},
	{"LED����������",parameter_led_blue_down},
	{"LED����",parameter_led},
	/* �̵� �볤�Ŀ�ͷһ�µ�    ���̵ķŵ������ */


	
	{"���߿���",parameter_switch},
	{"���Ŵ�����",parameter_windows_sensor},
	{"���崫����",parameter_body_sensor},
	{"�忨��",parameter_card},
	{"��·������",parameter_4_channel_ctrler},
	{"С��",parameter_multiple_sensor}


	
};//����Ҫ��PARAMETER_TYPE����һһ��Ӧ����ᷢ�����벻���ĺ��//�оٳ��˳��õĲ��������������ö��ʱ�������������ӷ����ʹ���ݴ���



extern S_String_Dict string_dict;

extern S_Save_Telegraph_cfg save_tel_cfg;//����ͨ��֡�����ñ�����Ϣ

extern S_Device_Telegraph current_operat_telegraph;//�����޸�(��ɾ�Ĳ�)
extern S_Static_RAM_Tele_Data RAM_static_tel;//����ͨ��֡
extern S_Dynamic_RAM_Tele_Data RAM_dynamic_tel;//����ͨ��֡

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

