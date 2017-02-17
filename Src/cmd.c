#include "include.h"
extern FRESULT res;
char operat_buf[1024];
extern S_String_Dict string_dict;
extern S_SYS_Task_Info SYS_Task_Info;

extern S_Save_Telegraph_cfg save_tel_cfg;//保存通信帧的配置保存信息
extern S_Device_Telegraph current_operat_telegraph;//用于修改(增删改查)
extern S_Static_RAM_Tele_Data RAM_static_tel;//查找通信帧
extern S_Dynamic_RAM_Tele_Data RAM_dynamic_tel;//查找通信帧


S_Cmd cmd_list[] = 
{
		{"helloworld",helloworld,\
			"just hello world"},
			
		{"help",help,\
			"show all the command"},
			
		{"led",led_operat,\
			"operat the led on the board"},
			
		{"reboot",reboot,\
			"reboot the system"},
			
		{"read_file",read_file,\
			"read file from sd_card or usb_dev format likes: read_file 0:1.txt offset=0 length=100"},
			
		{"write_file",write_file,\
			"write file to sd_card or usb_dev format likes: write_file 0:1.txt offset=0 length=100"},
			
		{"show_task",show_task,\
			"show current runing task information in system"},
			
		{"test",test_function,\
			"run the test_function where you can code inside"},
			
		{"save_dict",shell_save_string_dict,\
			"save the dictionary into sd_card"},
			
		{"load_dict",shell_load_string_dict,\
			"load dictionary into ram"},
			
		{"add_to_dict",shell_add_str_to_dict,\
			"add member into dictionary format likes: add_to_dict open operat auto"},
			
		{"delete_str_dict",shell_delete_str_to_dict,\
			"delete member which saved in dictionary format likes: delete_str_dict seek_num=11"},
			
		{"show_dict",shell_show_dict,\
			"show members which saved in dictionary format likes: show_dict all"},
		
		{"set_telegraph",shell_set_telegraph,\
			"set current telegraph into what you will format likes set_telegraph device"},//set_telegraph 四路控制器
			
		{"show_cur_tel",shell_show_cur_tel,\
			"show current telegraph information"},
			
		{"add_telegraph",shell_add_telegraph,\
			"add member into current telegraph format likes: add_telegraph close tel=5500..."},//add_telegraph 关闭通道 tel=55001100918182999988291239823983749727
			
		{"set_tel_parameter",shell_set_tel_parameter,\
			"set the parameter information of current telegraph format likes: set_tel_parameter close parameter1 offset=5 length=4 name=ID"},//set_tel_parameter 关闭通道 parameter1 offset=5 length=4 name=控制器ID
			
		{"save_telegraph",shell_save_telegraph,\
			"save telegraph into sd_card"},
			
		{"load_tel_cfg",shell_load_tele_cfg,\
			"load the config information into ram"},
			
		{"load_tel_to_ram",shell_load_tel_to_ram,\
			"load telegraph into ram as config"},
			

		{"start_server",shell_start_server,\
			"start tcp/udp server task"},
			
		{"kill_server",shell_kill_server,\
			"stop all tcp/udp server task"},
			
		{"tcm300",shell_start_tcm300_rx,\
			"tcm300 model start print recv data"},
			
		{"mem",shell_mem,\
			"show the heap and stack information"},
			
		{"show_parameter",shell_show_parameter,\
			"show all the preset parameter"},

		{"run_script",shell_run_script,\
			"run script"},
			

		/*未实现*/
		{"iap",help,\
			"haha just kidding"},
			
		{"ps",help,\
			"haha a kidding too"}
			
		
};

S_Cmd_Info recv_cmd;


char test_function(char* parameter)
{
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	char test_buff[40];
	//P_S_Revc_Parameter_Info p_test_buf;
	//p_test_buf = (P_S_Revc_Parameter_Info)malloc(sizeof(S_Revc_Parameter_Info));


	//char a_buf[5] = {1,1,1,1,1};
	//char b_buf[10] = {2,2,2,2,2,2,2,2,2,2};

	//insert_replace_strA_into_strB(a_buf,b_buf,3,5);
	//str_to_hex(cmd_info->parameter[1],test_buff,4);
	/*if(1 == str_cmp("write1", cmd_info->parameter[1]))
		{
			write_flash(0x08110000,operat_buf,100);
		}
	if(1 == str_cmp("write2", cmd_info->parameter[1]))
		{
			write_flash(0x08110064,operat_buf,100);
		}
	if(1 == str_cmp("erase", cmd_info->parameter[1]))
		{
			//write_flash(0x08100002,operat_buf,1024);
			erase_sector(GetSector(0x08110002));
		}
	if(1 == str_cmp("read", cmd_info->parameter[1]))
		{
			read_flash(0x08110002,operat_buf,1024);
		}*/
	//show_parameter();
	//printf("\r\n%s ->%d\r\n",cmd_info->parameter[1],get_parameter_type(cmd_info->parameter[1]));
	//printf("\r\n%d ->%s\r\n",str_to_int(cmd_info->parameter[2]),get_parameter_name(str_to_int(cmd_info->parameter[2])));

	//static unsigned char states = 0;
	//states = getSn_SR(0);
	//close(0);
	//tcp_server(0,8888);
	
	
	translate_to_tcm300(test_buff,cmd_info->recv_buf);

	return 0;
}

char shell_mem(char* parameter)
{
	//P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;	
	char* p_malloc;
	//char* next_malloc;
	int stack_addr = *((int*)0X08000000);
	int heap_addr;
	
	int stack_set_size = 0X1400;
	int heap_set_size = 0X1000;
	
	int free_stack_size = stack_set_size;
	heap_addr = stack_addr-stack_set_size-heap_set_size;

	while(!(*((int*)(stack_addr - free_stack_size))))
		{
			free_stack_size -= 4;
		}

	p_malloc = (char*)malloc(1);

	printf("\r\n_heap start addr 0X%x _heap total size is %d byte _heap_used size is %d byte free size is %d byte\r\n",heap_addr,heap_set_size,heap_set_size-(stack_addr - stack_set_size-(int)p_malloc),(stack_addr - stack_set_size-(int)p_malloc));
	//printf("after malloc %d size\r\n",1);
	//next_malloc = (char*)malloc(10);
	printf("stack start addr 0X%x stack total size is %d byte stack_used size is %d byte free size is %d byte\n\r",stack_addr,stack_set_size,free_stack_size,(stack_set_size - free_stack_size));

	//DEBUG_USR_ErrLog("stack start addr 0X%x stack total size is %d byte stack_used size is %d byte free size is %d byte\n\r",stack_addr,stack_set_size,free_stack_size,(stack_set_size - free_stack_size));

	free(p_malloc);
	//free(next_malloc);
	return 0;
}

char shell_run_script(char* parameter)
{
	//P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;	

	run_script(&script_info);
	return 0;
}

char shell_start_tcm300_rx(char* parameter)
{
	//P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;	
	my_usart2_init();
	return 0;
}

char shell_show_parameter(char* parameter)
{
	//P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;	
	show_parameter();
	return 0;
}


char shell_start_server(char* parameter)
{
	//P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	//static unsigned char states = 0;
	//states = getSn_SR(0);
	tcp_server(0,8888);
	osDelay(20);
	tcp_server(1,8888);
	osDelay(20);
	tcp_server(2,8888);
	osDelay(20);
	tcp_server(3,8888);
	osDelay(20);
	
	S_Client_Info client;
	client.target_server.server_ip[0] = 192;
	client.target_server.server_ip[1] = 168;
	client.target_server.server_ip[2] = 1;
	client.target_server.server_ip[3] = 244;
	client.target_server.server_port = 3333;

	client.this_client_socket_num = 4;
	tcp_client(&client);
	osDelay(20);
	client.target_server.server_port = 3334;
	client.this_client_socket_num = 5;
	tcp_client(&client);
	osDelay(20);
	udp_server(6,8800);
	osDelay(20);
	//client.this_client_socket_num = 6;
	//tcp_client(&client);
	//osDelay(20);
	//client.this_client_socket_num = 7;
	//tcp_client(&client);
	//osDelay(20);	
	return 0;
}


char shell_kill_server(char* parameter)
{
	close_socket_server(0);
	close_socket_server(1);
	close_socket_server(2);
	close_socket_server(3);
	close_socket_server(4);
	close_socket_server(5);
	//close_socket_server(6);
	//close_socket_server(7);

	return 0;
}

char shell_save_string_dict(char* parameter)
{
	save_string_dict(position_sd_card);
	return 0;
}

char shell_load_string_dict(char* parameter)
{
	load_dict(position_sd_card);
	return 0;
}

char shell_show_cur_tel(char* parameter)
{
	char* name;
	static char hex_str[80] = {0};
	unsigned char loopx,loop_inside;
	U_parameter parameter_reslut;
	name = get_str_name(current_operat_telegraph.device_seek_num);
	if((NULL == name)||(current_operat_telegraph.this_data_effect !=EFFECT))
		{
			printf("\r\n empty!!\r\n");
			return 0;
		}
	else
		{
			printf("\r\n name -> %s  saved %d telegraphs\r\n",name,(current_operat_telegraph.saved_num - current_operat_telegraph.delete_num));
		}
	printf("\r\n telegraph :\r\n");
	for(loopx = 0; loopx <current_operat_telegraph.saved_num ;loopx ++)
		{
			if(current_operat_telegraph.telegraphs[loopx].this_data_effect == EFFECT)
				{
					if((char*)2 == get_str_name(current_operat_telegraph.telegraphs[loopx].operat_seek_num))
						{
							printf("\r\nThis Operat seek_num'%d' Have Been Deleted!! It's Called '%s'\r\n",(current_operat_telegraph.telegraphs[loopx].operat_seek_num),(string_dict.string[string_dict.point].name));
						} 
					else
						{
							name = get_str_name(current_operat_telegraph.telegraphs[loopx].operat_seek_num);
							set_string(hex_str,80,0);
							hex_to_str(hex_str,(current_operat_telegraph.telegraphs[loopx].telegraph),current_operat_telegraph.telegraphs[loopx].telegraph_length);
							printf("\r\n'%s' ->  %s",name,hex_str);
							for(loop_inside = 0 ; loop_inside < current_operat_telegraph.telegraphs[loopx].parameter_num ; loop_inside ++)
								{
									parameter_reslut.parameter_code = current_operat_telegraph.telegraphs[loopx].parameter[loop_inside].parameter_code;
									if((parameter_reslut.parameter.offset)&0X80)
										{
											printf("\r\nparameter%d -> offset_h->%d, length->%d, name->%s ",loop_inside+1,((parameter_reslut.parameter.offset)&0X3F),(parameter_reslut.parameter.length),get_parameter_name((PARAMETER_TYPE)(parameter_reslut.parameter.parameter_name)));
										
										}
									if((parameter_reslut.parameter.offset)&0X40)
										{
											printf("\r\nparameter%d -> offset_l->%d, length->%d, name->%s ",loop_inside+1,((parameter_reslut.parameter.offset)&0X3F),(parameter_reslut.parameter.length),get_parameter_name((PARAMETER_TYPE)(parameter_reslut.parameter.parameter_name)));
										}
									if(0 ==((parameter_reslut.parameter.offset)&0XC0))
										{
											printf("\r\nparameter%d -> offset->%d, length->%d, name->%s ",loop_inside+1,(parameter_reslut.parameter.offset),(parameter_reslut.parameter.length),get_parameter_name((PARAMETER_TYPE)(parameter_reslut.parameter.parameter_name)));
										}
								}
							printf("\r\n");
						}
				}
		}
	return 0;
}
char shell_set_telegraph(char* parameter)
{
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	if(1 == find_str_in_dict(cmd_info->parameter[1]))
		{
			if(type_controller_device != string_dict.string[string_dict.point].type)
				{
					printf("\r\nerror!!!   '%s' is not a ctrl device!!\r\n",(cmd_info->parameter[1]));
					return 0;
				}
			else if(1==find_device_seek_num_in_map(string_dict.string[string_dict.point].seek_num,3)) //如果在SD卡中保存了则把SD卡中的数据取出
				{
					load_telegraph_to_current_operat_telegraph( string_dict.string[string_dict.point].seek_num);
				}
			else	//初始化
				{
					set_string((char*)&current_operat_telegraph,sizeof(current_operat_telegraph),0);
					current_operat_telegraph.device_seek_num = string_dict.string[string_dict.point].seek_num;
					current_operat_telegraph.this_data_effect = EFFECT;
				}
		}
	else
		{
			printf("\r\nunknow device '%s' !! try 'show_dict device'\r\n",cmd_info->parameter[1]);
		}
	return 0;
}




U_parameter shell_parameter_translate(P_S_Cmd_Info cmd)
{
	unsigned char loopx;
	U_parameter parameter_reslut;
	parameter_reslut.parameter_code = 0;
	for(loopx = 1 ;  loopx < cmd->parameter_num+1 ; loopx ++)
		{
			if(2 == str_cmp("offset=", cmd ->parameter[loopx]))
				{
					parameter_reslut.parameter.offset = str_to_int(&(cmd->parameter[loopx][sizeof("offset=")-1]));
					continue;
				}

			if(2 == str_cmp("offset_l=", cmd ->parameter[loopx]))
				{
					parameter_reslut.parameter.offset = str_to_int(&(cmd->parameter[loopx][sizeof("offset_l=")-1]));
					parameter_reslut.parameter.offset |= 0X40;					
					continue;
				}

			if(2 == str_cmp("offset_h=", cmd ->parameter[loopx]))
				{
					parameter_reslut.parameter.offset = str_to_int(&(cmd->parameter[loopx][sizeof("offset_h=")-1]));					
					parameter_reslut.parameter.offset |= 0X80;
					continue;
				}
			
			if(2 == str_cmp("length=", cmd ->parameter[loopx]))
				{
					parameter_reslut.parameter.length = str_to_int(&(cmd->parameter[loopx][sizeof("length=")-1]));
					continue;
				}
			if(2 == str_cmp("name=", cmd ->parameter[loopx]))
				{
					parameter_reslut.parameter.parameter_name = get_parameter_type(&(cmd->parameter[loopx][sizeof("name=")-1]));
					if(parameter_reslut.parameter.parameter_name == (unsigned char)parameter_nothing)
						{
							printf("\r\nunknow name!! please try again!\r\n");
						}
					continue;
				}
			//return (U_parameter)0;
		}
	return parameter_reslut;
}

unsigned char find_delete_num_in_cur_tel(void)
{
	unsigned char loopx;
	for(loopx= 0 ; loopx < current_operat_telegraph.saved_num ; loopx ++)
		{
			if(current_operat_telegraph.telegraphs[loopx].this_data_effect == UNEFFECT)
				{
					current_operat_telegraph.point = loopx;
					return loopx;
				}
		}
    return current_operat_telegraph.saved_num;
}

char shell_add_telegraph(char* parameter)
{
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	unsigned char loopx;
	unsigned char current_point;
	if(1 == find_str_in_dict(cmd_info->parameter[1]))
		{
			if(type_operat == string_dict.string[string_dict.point].type)
				{
					if(1 == find_operat_seek_num_in_telegraph(&current_operat_telegraph,string_dict.string[string_dict.point].seek_num))
						{
							current_point = current_operat_telegraph.point;//已经存储了这个操作  进行更改
							current_operat_telegraph.telegraphs[current_point].operat_seek_num = string_dict.string[string_dict.point].seek_num;
							for(loopx = 1; loopx < cmd_info->parameter_num+1 ; loopx ++)
								{
									if(2 == str_cmp("tel", cmd_info->parameter[loopx]))//添加成功
										{
											current_operat_telegraph.telegraphs[current_point].telegraph_length = str_to_hex(&(cmd_info->parameter[loopx][4]), (unsigned char *) &current_operat_telegraph.telegraphs[current_point].telegraph, 40);
											current_operat_telegraph.telegraphs[current_point].this_data_effect = EFFECT;										
										}
									
								}
						}
					else//未保存这个操作 进行增加
						{
							{
								if(0 == current_operat_telegraph.delete_num)
									{
										current_point = current_operat_telegraph.saved_num;//之前为删除过操作在最后添加
									}
								else
									{
										current_point = find_delete_num_in_cur_tel();//之前删除过操作   在删除的位置添加
									}
							}
							current_operat_telegraph.telegraphs[current_point].operat_seek_num = string_dict.string[string_dict.point].seek_num;
							for(loopx = 1; loopx < cmd_info->parameter_num+1 ; loopx ++)
								{
									if(2 == str_cmp("tel", cmd_info->parameter[loopx]))//添加成功
										{
											current_operat_telegraph.telegraphs[current_point].telegraph_length = str_to_hex(&(cmd_info->parameter[loopx][4]), (unsigned char *) &current_operat_telegraph.telegraphs[current_point].telegraph, 40);
											current_operat_telegraph.telegraphs[current_point].this_data_effect = EFFECT;
											if(0 == current_operat_telegraph.delete_num)
												{
													current_operat_telegraph.saved_num ++;
												}
											else
												{
													current_operat_telegraph.delete_num --;
												}
										}
									
								}
						}
				}
			else
				{
					printf("\r\n'%s' is not  type_operat!!\r\n",cmd_info->parameter[1]);
				}
		}
	else
		{
			printf("\r\nunknow '%s'   this parameter must type_operat!\r\n",cmd_info->parameter[1]);
		}
	return 0;
}

char shell_set_tel_parameter(char* parameter)
{
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	unsigned char loopx;
	unsigned char current_point;
	unsigned char parameter_point;
	U_parameter parameter_tmp;
	if(1 == find_str_in_dict(cmd_info->parameter[1]))
		{
			if(1 == find_operat_seek_num_in_telegraph(&current_operat_telegraph,string_dict.string[string_dict.point].seek_num))
				{
					current_point = current_operat_telegraph.point;
				}
			else
				{
					printf("\r\nCan Not Find '%s' In Current Device Telegraph\r\n",cmd_info->parameter[1]);
					return 0;
				}
				
			for(loopx = 1; loopx < cmd_info->parameter_num+1 ; loopx ++)
				{
					if(2 == str_cmp("parameter", cmd_info->parameter[loopx]))
						{
							parameter_point = str_to_int(&(cmd_info->parameter[loopx][sizeof("parameter")-1]));
							if((0 == parameter_point)||(parameter_point > 10))
								{
									printf("\r\nI Don't Know Which Parameter You Want To Opeart!\r\npls check out 'parameter' it looks like 'paratemer1'~'parameter10'\r\n");
									return 0;
								}
							parameter_point --;
							
							parameter_tmp.parameter_code= (shell_parameter_translate(cmd_info).parameter_code);
							if(parameter_tmp.parameter.length)
								{
									current_operat_telegraph.telegraphs[current_point].parameter[parameter_point].parameter.length = parameter_tmp.parameter.length;
								}
							if(parameter_tmp.parameter.offset)
								{
									current_operat_telegraph.telegraphs[current_point].parameter[parameter_point].parameter.offset= parameter_tmp.parameter.offset;
								}
							if(parameter_tmp.parameter.parameter_name)
								{
									current_operat_telegraph.telegraphs[current_point].parameter[parameter_point].parameter.parameter_name = parameter_tmp.parameter.parameter_name;
								}
							//current_operat_telegraph.telegraphs[current_point].parameter[0].parameter_code = (shell_parameter_translate(cmd_info).parameter_code);
							if(current_operat_telegraph.telegraphs[current_point].parameter[parameter_point].parameter_code)
								{
									current_operat_telegraph.telegraphs[current_point].parameter_num = current_operat_telegraph.telegraphs[current_point].parameter_num>(parameter_point+1)? current_operat_telegraph.telegraphs[current_point].parameter_num : (parameter_point+1);
								}
							break;
						}


				/*
					if(1 == str_cmp("parameter1", cmd_info->parameter[loopx]))
						{
							parameter_tmp.parameter_code= (shell_parameter_translate(cmd_info).parameter_code);
							if(parameter_tmp.parameter.length)
								{
									current_operat_telegraph.telegraphs[current_point].parameter[0].parameter.length = parameter_tmp.parameter.length;
								}
							if(parameter_tmp.parameter.offset)
								{
									current_operat_telegraph.telegraphs[current_point].parameter[0].parameter.offset= parameter_tmp.parameter.offset;
								}
							if(parameter_tmp.parameter.parameter_name)
								{
									current_operat_telegraph.telegraphs[current_point].parameter[0].parameter.parameter_name = parameter_tmp.parameter.parameter_name;
								}
							//current_operat_telegraph.telegraphs[current_point].parameter[0].parameter_code = (shell_parameter_translate(cmd_info).parameter_code);
							if(current_operat_telegraph.telegraphs[current_point].parameter[0].parameter_code)
								{
									current_operat_telegraph.telegraphs[current_point].parameter_num = current_operat_telegraph.telegraphs[current_point].parameter_num>1? current_operat_telegraph.telegraphs[current_point].parameter_num : 1;
								}
							continue;
						}
					*/
				}
		}
	else
		{
			printf("\r\nI Can't Find %s In Dict!\r\n",cmd_info->parameter[1]);
			printf("This Command format like: \r\n\r\nadd_tel_parameter 学习开关 parameter1 offset=6 length=1 name=报头CRC\r\n");
		}
	return 0;
}


char shell_save_telegraph(char* parameter)
{
	//P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	save_telegraph_to_SDcard(&current_operat_telegraph);
	save_telegraph_cfg_to_SDcard(&save_tel_cfg);
	return 0;
}

char shell_load_tele_cfg(char* parameter)
{
	load_telegraph_cfg_to_ram(&save_tel_cfg);
	return 0;
}
char shell_load_tel_to_ram(char* parameter)
{
	load_telegraph_to_ram_as_map();
	return 0;
}






















char shell_add_str_to_dict(char* parameter)
{
	S_String_Info tmp;
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	my_mem_copy(cmd_info->parameter[1],tmp.name,40);
	if(cmd_info->parameter[2][0] == 0)
	{
		printf("\r\n format error!! try  \r\n\r\n     add_to_dict 设置 operat auto \r\n     add_to_dict 四路控制器 ctrl_device auto\r\n     add_to_dict 无线开关 redio_device 123\r\n     add_to_dict 人体传感器 sensor 122\r\n     add_to_dict 温度 parameter auto\r\n");
		return 0;
	}
	if(1 == str_cmp("ctrl_device", cmd_info->parameter[2]))
		{
			tmp.type = type_controller_device;
		}
	else if(1 == str_cmp("operat", cmd_info->parameter[2]))
		{
			tmp.type = type_operat;
		}
	else if(1 == str_cmp("sensor", cmd_info->parameter[2]))
		{
			tmp.type = type_sensor_decice;
		}
	else if(1 == str_cmp("redio_device", cmd_info->parameter[2]))
		{
			tmp.type = type_radio_device;
		}
	else if(1 == str_cmp("parameter", cmd_info->parameter[2]))
		{
			tmp.type = type_parameter;
		}
	else
		{
			printf("\r\n format error!! try  \r\n\r\n     add_to_dict 设置 operat auto \r\n     add_to_dict 四路控制器 ctrl_device auto\r\n     add_to_dict 无线开关 redio_device 123\r\n     add_to_dict 人体传感器 sensor 122\r\n     add_to_dict 温度 parameter auto\r\n");
			return 0;
		}
	if(cmd_info->parameter[3][0] == 0)
	{
			printf("\r\n format error!! try  \r\n\r\n     add_to_dict 设置 operat auto \r\n     add_to_dict 四路控制器 ctrl_device auto\r\n     add_to_dict 无线开关 redio_device 123\r\n     add_to_dict 人体传感器 sensor 122\r\n     add_to_dict 温度 parameter auto\r\n");
			return 0;
	}
	if(1 == str_cmp("auto", cmd_info->parameter[3]))
		{
			tmp.seek_num = 0XFF;
		}
	else
		{
			tmp.seek_num = str_to_int(cmd_info->parameter[3]);
			if(tmp.seek_num == 0)
				{
					printf("\r\n '0' is illegal number! please try another number !!\r\n");
					return 0;
				}
		}
	tmp.this_data_effect = EFFECT;
	add_string_to_dict(&tmp);
	return 0;
}

char shell_show_dict(char* parameter)
{
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	if(1 == str_cmp("all",cmd_info->parameter[1]))
		{
			show_dict(0);
		}
	else if(1 == str_cmp("operat",cmd_info->parameter[1]))
		{
			show_dict(1);
		}
	else if(1 == str_cmp("device",cmd_info->parameter[1]))
		{
			show_dict(2);
		}
	else if(1 == str_cmp("parameter",cmd_info->parameter[1]))
		{
			show_dict(3);
		}
	else
		{
			printf("\r\nformat error  please try  'show_dict all/operat/device/parameter' \r\n");
		}
	return 0;
}

char shell_delete_str_to_dict(char* parameter)
{

	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	unsigned char seek_num;
	if(2 == str_cmp("seek_num=",cmd_info->parameter[1]))
		{
			seek_num = str_to_int(&(cmd_info->parameter[1][sizeof("seek_num=")-1]));
			if(get_str_name(seek_num))
				{
					delete_str_in_dict(get_str_name(seek_num));
				}
			else
				{
					printf("\r\nI Don't Know The seek_num '%d'!!\r\n",seek_num);
					printf("this command format like: delete_str_dict 四路控制器/seek_num=100\r\n");
				}
			return 0;
		}
	else
		{
			delete_str_in_dict(cmd_info->parameter[1]);
			return 0;
		}
}
unsigned char str_cmp(char * model,char* target)
{
	while(*model)
		{
			if(*(model++) != *(target++))
				{
					return 0; //不一样
				}
		}
	if(*target)
		{
			return 2;  //目标比模板长
		}
	else
		{
			return 1; //完全一样
		}
}


P_S_Cmd find_cmd(char *cmd)
{
	unsigned char loopx = 0;
	unsigned char cmd_num = sizeof(cmd_list)/sizeof(cmd_list[0]);
	for(;loopx<cmd_num;loopx++)
		{
			if(1 == str_cmp(cmd,cmd_list[loopx].cmd_name))
				{
					return &(cmd_list[loopx]);
				}
		}
	return (P_S_Cmd) 0;
}


char helloworld(char* parameter)
{
	printf("\n\rhello world! my name is stm32!\n\r");
	return 0;
}
char help(char* parameter)
{
	unsigned char loopx;
	unsigned char cmd_num = sizeof(cmd_list)/sizeof(cmd_list[0]);
	printf("\n\r\n\rcurrent version have %d commands,they are :\n\r",cmd_num);
	for(loopx = 0;loopx <cmd_num;loopx++)
		{
			printf("command : %s\n\r",cmd_list[loopx].cmd_name);
		}
	return 0;
}
char led_operat(char* parameter)
{
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	unsigned int parameter_num;
	if(0 == string_length(cmd_info->parameter[1]))
		{
			printf("\n\rcommand format error!  try:  led  all/1/2/...  on/off/tog  \n\r ");
			return 0;
		}
	if(1 == str_cmp(cmd_info->parameter[1],"all"))
		{
			if(1 == str_cmp(cmd_info->parameter[2],"on"))
				{
					set_all_led_on();
					return 0;
				}
			if(1 == str_cmp(cmd_info->parameter[2],"off"))
				{
					set_all_led_off();
					return 0;
				}
			if(1 == str_cmp(cmd_info->parameter[2],"tog"))
				{
					set_all_led_tog();
					return 0;
				}
		}
	
	parameter_num = str_to_int(cmd_info->parameter[1]);
	if(parameter_num == 0)
		{
			printf("\n\rcommand format error! parameter  can't be zero!! try:  led  all/1/2/...  on/off/tog   \n\r ");
			return 0;
		}
	if(parameter_num > 12)
		{
			printf("\n\rcommand format error!  too big parameter!! try a samll one! \n\r ");
			return 0;
		}
	if(1 == str_cmp(cmd_info->parameter[2],"on"))
		{
			set_led(parameter_num,1);
			return 0;
		}
	if(1 == str_cmp(cmd_info->parameter[2],"off"))
		{
			set_led(parameter_num,0);
			return 0;
		}
	if(1 == str_cmp(cmd_info->parameter[2],"tog"))
		{
			set_led(parameter_num,2);
			return 0;
		}
	printf("\n\rcommand format error!  try:  led  all/1/2/...  on/off/tog   \n\r ");
	return 0;
}

char reboot(char* parameter)
{
	printf("\n\rsystem will reboot after 3 second\n\r");
	osDelay(1000);
	printf("\n\rsystem will reboot after 2 second\n\r");
	osDelay(1000);
	printf("\n\rsystem will reboot after 1 second\n\r");
	osDelay(1000);
	printf("\n\rsystem reboot now ...\n\r");
	NVIC_SystemReset();
	return 0;
}

char read_file(char* parameter)
{
	unsigned char loopx,loop_num;
	unsigned int offset,length;
	FIL doc;
	unsigned int operat_num;
	res = (FRESULT)1;
	//unsigned char operat_buf[400];
	
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	loop_num = cmd_info->parameter_num+1;
	for(loopx = 1; loopx < loop_num ; loopx ++)
		{
			if(2 == str_cmp("offset=",cmd_info->parameter[loopx]))
				{
					offset = str_to_int(&(cmd_info->parameter[loopx][sizeof("offset=")-1]));
					continue;
				}
			if(2 == str_cmp("length=",cmd_info->parameter[loopx]))
				{
					length = str_to_int(&(cmd_info->parameter[loopx][sizeof("offset=")-1]));
					continue;
				}
			if(res)
				{
					__disable_irq();
					res = f_open(&doc,cmd_info->parameter[loopx],FA_READ);
					__enable_irq();
				}
		}
		if(res)
			{
				printf("\r\n open file failed ! please check the filename!\r\n read_file path length=xx offset=xx\r\n");
				//__disable_irq();
				f_close(&doc);
				//__disable_irq();
				return 0;
			}
		f_lseek(&doc,offset);
		__disable_irq();
		res = f_read(&doc,operat_buf,length,&operat_num);
		__enable_irq();
		if(res)
			{
				printf("\r\n read file failed ! !!!\r\n");
				f_close(&doc);
				return 0;
			}
		printf("\r\nread success!! read %d byte -> :\r\n ",operat_num);
		printf("%s\r\n",operat_buf);
		f_close(&doc);
		printf("\r\n file close !\r\n");				
		
	return offset+length;

}
char write_file(char* parameter)
{
	unsigned char loopx,loop_num;
	unsigned int offset,length;
	FIL doc;
	unsigned int operat_num;
	P_S_Cmd_Info cmd_info = (P_S_Cmd_Info)parameter;
	loop_num = cmd_info->parameter_num+1;
	res = (FRESULT)1;
	for(loopx = 1; loopx < loop_num ; loopx ++)
		{
			if(2 == str_cmp("offset=",cmd_info->parameter[loopx]))
				{
					offset = str_to_int(&(cmd_info->parameter[loopx][sizeof("offset=")-1]));
					continue;
				}
			if(2 == str_cmp("length=",cmd_info->parameter[loopx]))
				{
					length = str_to_int(&(cmd_info->parameter[loopx][sizeof("offset=")-1]));
					continue;
				}
			if(res)
				{
					__disable_irq();
					res = f_open(&doc,cmd_info->parameter[loopx],FA_WRITE|FA_OPEN_ALWAYS);
					__enable_irq();
				}
		}
		if(res)
			{
				printf("\r\n open file filed ! please check the filename!\r\n read_file path length=xx offset=xx\r\n");
				f_close(&doc);
				return 0;
			}
		f_lseek(&doc,offset);
		__disable_irq();
		res = f_write(&doc,operat_buf,length,&operat_num);
		__enable_irq();
		printf("\r\nwrite success \r\n");
		f_close(&doc);
		
	return offset+length;

}

char show_task(char* parameter)
{
	unsigned char loopx;
	printf("\n\r system have %d tasks ,cpu use rate-> %d%%  \n\r",SYS_Task_Info.save_number,SYS_Task_Info.cur_cpu_use_rate);
	printf("\n\r+-----------------------------------------------------------------------------------------------+\n\r");
	for(loopx = 0; loopx < MAX_SAVE_TASK_INFO_NUM ; loopx ++)
		{
			if(SYS_Task_Info.task[loopx].task_handle)
				{
					SYS_Task_Info.task[loopx].empty_stack = (uxTaskGetStackHighWaterMark(SYS_Task_Info.task[loopx].task_handle)*4);
					printf("|task name : %-16s |  priority : %d | free stack :%-4d byte|run %4d times in 1 second| ",SYS_Task_Info.task[loopx].name,SYS_Task_Info.task[loopx].priority,SYS_Task_Info.task[loopx].empty_stack,SYS_Task_Info.task[loopx].run_time.curr_run_time);
					printf("\n\r+-----------------------------------------------------------------------------------------------+\n\r");
				}
			else
				{
					continue;
				}
		}
	return 0;
}



unsigned int pow10(unsigned char data)
{
	unsigned int return_num = 1;
	unsigned char loopx = data;
	while(loopx --)
		{
			return_num *= 10;
		}
	return return_num;
}


unsigned int str_to_int(char* str)
{
	unsigned char loopx,change_loop;
	unsigned char int_num[20] = {0};
	unsigned int return_num = 0;
	unsigned char str_num;
	char* tmp = str;
	str_num = string_length(tmp);
	for(loopx = 0; loopx < str_num ; loopx++)
		{
			if((*tmp >= '0')&&(*tmp <='9'))
				{
					int_num[loopx] = *(tmp++) - '0';
				}
			else
				{
					break;
				}
		}
	for(change_loop = 0; change_loop < loopx ;change_loop ++)
		{
			return_num += int_num[change_loop]*pow10(loopx - change_loop -1);
		}
	return return_num;
}

unsigned char str_to_hex(char* str,unsigned char* target,unsigned int max_length)//返回值就是转换的长度
{
	char* tmp_str = str;
	unsigned char* tmp_target = target;
	unsigned int loopx,loop_last,tmp = 0;
	CHANGE_TO_HEX change_buff;	
	//unsigned char reslut;
	
	tmp = string_length(str);
	if(tmp > 2*max_length)  //需要转换的长度大于设置的目标最大保存超度时   截去多余的转换长度防止段错误
		{
			tmp =  2*max_length;
		}
	
	loop_last = tmp%2;
	loopx = tmp/2;

	for(tmp = 0; tmp< loopx; tmp++)
		{
			if((*tmp_str) >= '0' && (*tmp_str) <= '9' )
				{
					change_buff.BYTE.byte_h = *tmp_str - '0';
				}
			else if((*tmp_str) >= 'A' && (*tmp_str) <= 'F' )
				{
					change_buff.BYTE.byte_h = *tmp_str - 'A' + 10;
				}
			else if((*tmp_str) >= 'a' && (*tmp_str) <= 'f' )
				{
					change_buff.BYTE.byte_h = *tmp_str - 'a' + 10;
				}
			else
				{
					change_buff.BYTE.byte_h = 0;
					//reslut = 0;
				}
			tmp_str++;
			if((*tmp_str) >= '0' && (*tmp_str) <= '9' )
				{
					change_buff.BYTE.byte_l = *tmp_str - '0';
				}
			else if((*tmp_str) >= 'A' && (*tmp_str) <= 'F' )
				{
					change_buff.BYTE.byte_l = *tmp_str - 'A' +10;
				}
			else if((*tmp_str) >= 'a' && (*tmp_str) <= 'f' )
				{
					change_buff.BYTE.byte_l = *tmp_str - 'a' +10;
				}
			else
				{
					change_buff.BYTE.byte_l = 0;
					//reslut = 0;
				}
			tmp_str++;
			*tmp_target++ = change_buff.reslut;
		}
	if(loop_last)
		{
			if((*tmp_str) >= '0' && (*tmp_str) <= '9' )
				{
					change_buff.BYTE.byte_l = *tmp_str - '0';
				}
			else if((*tmp_str) >= 'A' && (*tmp_str) <= 'F' )
				{
					change_buff.BYTE.byte_l = *tmp_str - 'A' + 10;
				}
			else if((*tmp_str) >= 'a' && (*tmp_str) <= 'f' )
				{
					change_buff.BYTE.byte_l = *tmp_str - 'a' +10;
				}
			else
				{
					change_buff.BYTE.byte_l =0;
					//reslut = 0;
				}
			change_buff.BYTE.byte_h =0;
			*tmp_target = change_buff.reslut;
			loopx++;
		}
	return loopx;
}

void hex_to_str(char* target_str,unsigned char* hex,unsigned int hex_length)
{
	unsigned char* hex_tmp = hex;
	unsigned char loopx;
	CHANGE_TO_HEX change_buff;
	for(loopx = 0; loopx < hex_length ; loopx ++)
		{
			change_buff.reslut = *hex_tmp;
			if(change_buff.BYTE.byte_h <= 9)
				{
					*target_str = '0' + change_buff.BYTE.byte_h;
				}
			else
				{
					*target_str = 'A' + (change_buff.BYTE.byte_h - 10);
				}
			target_str++;
			
			if(change_buff.BYTE.byte_l <= 9)
				{
					*target_str = '0' + change_buff.BYTE.byte_l;
				}
			else 
				{
					*target_str = 'A' + (change_buff.BYTE.byte_l - 10);
				}
			target_str++;
			hex_tmp++;
		}
}

void set_string(char* string,unsigned int length,unsigned char data)
{
	unsigned int loopx = length;
	char* tmp = string;
	while(loopx --)
		{
			*(tmp++) = data;
		}
}

unsigned char string_length(char* string)
{
	char* tmp = string;
	unsigned char length = 0;
	while(*tmp++)
		{
			length ++; 
		}
	return length;
}

void my_mem_copy(char* from,char* to,unsigned int cnt)
{
	unsigned loopx=cnt;
	char* from_tmp = from;
	char* to_tmp = to;
	while(loopx --)
		{
			*(to_tmp++) = *(from_tmp ++);
		}
}

unsigned char split_string(P_S_Cmd_Info cmd)
{
	unsigned char loopx;
	unsigned char inside_loopx = 0;
	unsigned char space_num = 0;
	char* tmp = cmd->recv_buf;
	
	loopx = string_length(tmp);
	if(loopx == 0)
		{
			return 0;
		}
	while(loopx --)
		{
			if(*(tmp) != 0X20)
				{
					cmd->parameter[space_num][inside_loopx++] = *(tmp++);
					if(space_num == (CMD_PARAMETER_NUM-1))
						{
							if(inside_loopx >= CMD_PARAMETER_SIZE)
								{
									cmd->parameter_num = space_num;
									return 2;//内存溢出
								}
						}
				}
			else
				{
					inside_loopx = 0;
					tmp++;
					space_num ++;
					if(space_num >= CMD_PARAMETER_NUM)
						{
							cmd->parameter_num = space_num;
							return 2;//内存溢出
						}
				}
		}
	cmd->parameter_num = space_num;
	return 1;
}


void explain_cmd(unsigned char recv_data)
{
	P_S_Cmd current_cmd;
	if(recv_data == 0X0D) //回车
		{
			if(1 == split_string(&recv_cmd))
				{
					current_cmd = find_cmd(recv_cmd.parameter[0]);
					if(current_cmd)
						{
							my_mem_copy(recv_cmd.recv_buf,recv_cmd.save_buf,CMD_REVC_BUF_SIZE);
							if((1 == str_cmp("-h",(recv_cmd.parameter[1])))||(1 == str_cmp("-H",(recv_cmd.parameter[1]))))
								{
									printf("\r\n%s\r\n",current_cmd->help);
								}
							else
								{
									current_cmd ->cmd_func((char*)&recv_cmd);
								}
						}
					else
						{
							printf("\n\runknow command '%s' ,try  to  command  'help'\n\r",recv_cmd.parameter[0]);
						}					
				}
			if(split_string(&recv_cmd) == 2)
				{
					printf("I Can't recv More Than %d Parts !\n\r       OUT OF MEMORY!  Please Check out!!\n\r  ",CMD_PARAMETER_NUM);
				}
			recv_cmd.point = 0;
			set_string(recv_cmd.recv_buf,CMD_REVC_BUF_SIZE,0);
			set_string((char*)recv_cmd.parameter,CMD_REVC_BUF_SIZE,0);
			printf("\n\r");
			printf("stm32->");
			return;
		}
	if(recv_data == 0X08) //退格
		{
			if(recv_cmd.point < 1)
				{
					recv_cmd.point = 0;
					set_string(recv_cmd.recv_buf,CMD_REVC_BUF_SIZE,0);
					set_string((char*)recv_cmd.parameter,CMD_REVC_BUF_SIZE,0);
					//printf("\n\r");
					//printf("stm32->");
					return;
				}
			else
				{
					/*set_string(recv_cmd.back_buf,80,0);
					my_mem_copy(recv_cmd.recv_buf,recv_cmd.back_buf,--recv_cmd.point);*/
					recv_cmd.recv_buf[--recv_cmd.point] = 0;
					//printf("\n\r");
					printf("\b \b");
					//printf("stm32->%s",recv_cmd.back_buf);
					//printf("stm32->%s",recv_cmd.recv_buf);
					return;
				}
		}
	if(recv_data == 0X7C)// '|'  表示上一条命令
		{
			if(1 == str_cmp(recv_cmd.save_buf,recv_cmd.recv_buf))
				{
					return;
				}
			else
				{
					my_mem_copy(recv_cmd.save_buf,recv_cmd.recv_buf,CMD_REVC_BUF_SIZE);
					recv_cmd.point = string_length(recv_cmd.recv_buf);
					printf("%s",recv_cmd.recv_buf);
					return;
				}
		}
	recv_cmd.recv_buf[recv_cmd.point ++] = recv_data;
	printf("%c",recv_data);
			
}




