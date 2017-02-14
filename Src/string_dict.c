#include "include.h"


S_String_Dict string_dict;
void save_string_dict(E_Save_Position position)
{
	FIL fd_dict;
	unsigned int operat_num;
	if(position == position_flash)
		{
			
		}
	if(position == position_sd_card)
		{
			__disable_irq();
			if(FR_OK == f_open(&fd_dict,"seco.dict",FA_READ|FA_WRITE|FA_OPEN_ALWAYS))
				{
					if(FR_OK ==  f_write(&fd_dict,(void*)&string_dict, sizeof(string_dict), &operat_num))
						{
							printf("\r\n write success!! write %d bytes\r\n",operat_num);
						}
					else
						{
							printf("\r\n write error! \r\n");
						}
					f_close(&fd_dict);
				}
			else
				{
					printf("\r\n  can not open file 'seco.dict'  please check the sd_card!!\r\n");
				}
			__enable_irq();
		}
}

void load_dict(E_Save_Position position)
{
	FIL fd_dict;
	unsigned int operat_num;
	if(position == position_flash)
		{
			
		}
	if(position == position_sd_card)
		{
		__disable_irq();
		res = f_open(&fd_dict,"seco.dict",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
			if(FR_OK == res)
				{
					if(FR_OK ==  f_read(&fd_dict,(void*)&string_dict, sizeof(string_dict), &operat_num))
						{
							printf("\r\n load 'seco.dict' success!! load %d bytes\r\n",operat_num);
						}
					else
						{
							printf("\r\n load 'seco.dict' error! \r\n");
						}
					f_close(&fd_dict);
				}
			else
				{
					printf("\r\n  can not open file 'seco.dict'  please check the sd_card!!\r\n");
				}
			__enable_irq();
		}
}

char* get_str_name(unsigned char seek_num)
{
	unsigned char loopx;
	for(loopx = 0 ; loopx < string_dict.save_number ; loopx ++)
		{
			if(seek_num == string_dict.string[loopx].seek_num)
				{
					if(string_dict.string[loopx].this_data_effect == UNEFFECT)
						{
							string_dict.point = loopx;
							return (char*)2;//这个seek_num被删除
						}
					return string_dict.string[loopx].name;
				}
		}
	return NULL;
}

unsigned char find_str_in_dict(char* target_str)//返回值为1时,表示字符串已保存于字典中,可以根据point成员找到相关信息(name,seek_num)返回2时表示没有完全一样的,但是有比字符串长,且前面与字符串相同的
{
	unsigned char loopx;
	unsigned char reslut;
	unsigned char tmp_reslut = 0;
	for(loopx = 0; loopx < string_dict.save_number ;loopx ++)
		{
			if(string_dict.string[loopx].this_data_effect == EFFECT)
				{
					reslut = str_cmp(string_dict.string[loopx].name,target_str);
					if(reslut == 0)
						{
							continue;
						}
					if(reslut == 1)
						{
							string_dict.point = loopx;
							return 1;
						}
					if(reslut == 2)
						{
							string_dict.point = loopx;
							tmp_reslut = 2;
							//return 2;
						}
				}
			else
				{
					continue;
				}
		}
	return tmp_reslut;
}

unsigned char find_empty_in_dict(void)
{
	unsigned char loopx;
	for(loopx = 0;loopx < string_dict.save_number ; loopx ++)
		{
			if(string_dict.string[loopx].this_data_effect == UNEFFECT)
				{
					string_dict.point = loopx;
					return loopx;
				}
		}
	return  string_dict.save_number;
}


unsigned char add_string_to_dict(P_S_String_Info str_info)
{
	if(1 != find_str_in_dict(str_info->name))
		{
		if(string_dict.delete_number == 0)
			{
				if(string_dict.save_number == MAX_DICT_SAVE_NUM)
					{
						printf("\r\n save space full!\r\n");
						return 2;  //数据满
					}
				else
					{
						if(1 == seek_num_in_dict(str_info->seek_num))
							{
								printf("\r\n seek_num %d had defined in dictionary!!   please try another number or 'auto'\r\n ",str_info->seek_num);
								return 0;
							}
						if(str_info->type == type_controller_device)
							{
								if(str_info->seek_num == 0XFF)
								{
									str_info->seek_num = get_auto_seek_num();
								}
								string_dict.save_device_num ++;
							}
						if(str_info->type == type_sensor_decice)
							{
								if(str_info->seek_num == 0XFF)
								{
									str_info->seek_num = get_auto_seek_num();
								}
								string_dict.save_device_num ++;
							}
						if(str_info->type == type_radio_device)
							{
								if(str_info->seek_num == 0XFF)
								{
									str_info->seek_num = get_auto_seek_num();
								}
								string_dict.save_device_num ++;
							}
						if(str_info->type == type_operat)
							{
								if(str_info->seek_num == 0XFF)
								{
									str_info->seek_num = get_auto_seek_num();
								}
								string_dict.save_operate_num ++;
							}
						if(str_info->type == type_parameter)
							{
								if(str_info->seek_num == 0XFF)
								{
									str_info->seek_num = get_auto_seek_num();
								}
								string_dict.save_parameter_num++;
							}
						my_mem_copy((char*)str_info,(char*)&string_dict.string[string_dict.save_number],sizeof(S_String_Info));	
						string_dict.save_number ++;
						printf("\r\n add success !\r\n");
						return 1;
					}
			}
		else	//存储到已经删除的位置上去
			{
				find_empty_in_dict();
				
				if(str_info->type == type_controller_device)
					{
						if(str_info->seek_num == 0XFF)
							{
								str_info->seek_num = get_auto_seek_num();		//自动获取seek编号
							}
						string_dict.save_device_num ++;
					}
				if(str_info->type == type_sensor_decice)
					{
						if(str_info->seek_num == 0XFF)
							{
								str_info->seek_num = get_auto_seek_num();
							}
						string_dict.save_device_num ++;
					}
				if(str_info->type == type_operat)
					{
						if(str_info->seek_num == 0XFF)
							{
								str_info->seek_num = get_auto_seek_num();
							}
						string_dict.save_operate_num ++;
					}
				if(str_info->type == type_parameter)
					{
						if(str_info->seek_num == 0XFF)
						{
							str_info->seek_num = get_auto_seek_num();
						}
						string_dict.save_parameter_num++;
					}
				my_mem_copy((char*)str_info,(char*)&string_dict.string[string_dict.point],sizeof(S_String_Info));	
				string_dict.delete_number --;
				printf("\r\n add success !\r\n");
				return 1;
			}
		}
	else//更改数据
		{
			if(str_info->seek_num == 0XFF)
				{
					str_info->seek_num = get_auto_seek_num();
				}
			my_mem_copy((char*)str_info,(char*)&string_dict.string[string_dict.point],sizeof(S_String_Info));
			printf("\r\n data had changed !!\r\n");
			return 3;
		}
}

unsigned char delete_str_in_dict(char* target_str)
{
	if(1 == find_str_in_dict(target_str))
		{
			string_dict.string[string_dict.point].this_data_effect = UNEFFECT;
			string_dict.delete_number ++;
			/*if(string_dict.string[string_dict.point].type == type_controller_device)
				{
					string_dict.save_device_num --;
				}
			if(string_dict.string[string_dict.point].type == type_sensor_decice)
				{
					string_dict.save_device_num --;
				}
			if(string_dict.string[string_dict.point].type == type_operat)
				{
					string_dict.save_operate_num--;
				}*/
			printf("\r\ndelete success!\r\n");
			return 1;
		}
	else
		{
			printf("\r\n can not find '%s' in the dictionary\r\n",target_str);
			printf("this command format like: delete_str_dict 四路控制器/seek_num=100\r\n");
			return 0;
		}
}

void show_dict(unsigned char type)
{
	//unsigned char operat[];
	//DICT_TYPE type;
	unsigned char loopx;
	unsigned char tmp;
	if(type == 0) //all
		{
			tmp = string_dict.save_number-string_dict.delete_number;
			printf("\r\n\r\n     there is %d / %d datas in the dict\r\n",tmp,MAX_DICT_SAVE_NUM);
			printf("\r\n type%d->ctrl_device   type%d->sensor   type%d->redio_device   type%d->operat   type%d->parameter\r\n",type_controller_device,type_sensor_decice,type_radio_device,type_operat,type_parameter);
			for(loopx = 0; loopx < string_dict.save_number ; loopx ++)
				{
					if( EFFECT == string_dict.string[loopx].this_data_effect )
						{
							printf("\r\nname '%s' ->seek_num '%d'  type :%d\r\n",string_dict.string[loopx].name,string_dict.string[loopx].seek_num,string_dict.string[loopx].type);
						}
				}
		}
	if(type == 1) //operat
		{
			printf("\r\n  operat datas :\r\n");
			for(loopx = 0; loopx < string_dict.save_number ; loopx ++)
				{
					if((EFFECT == string_dict.string[loopx].this_data_effect )&&(type_operat == string_dict.string[loopx].type))
						{
							printf("\r\nname '%s' ->seek_num '%d'  type :%d(operat)\r\n",string_dict.string[loopx].name,string_dict.string[loopx].seek_num,string_dict.string[loopx].type);
						}
				}
		}
	if(type == 2)  //device
		{
			printf("\r\n  device datas :\r\n");
			printf("\r\n type%d->ctrl_device   type%d->sensor   type%d->redio_device \r\n",type_controller_device,type_sensor_decice,type_radio_device);
			for(loopx = 0; loopx < string_dict.save_number ; loopx ++)
				{
					if((EFFECT == string_dict.string[loopx].this_data_effect )&&(type_operat != string_dict.string[loopx].type) &&(type_parameter!= string_dict.string[loopx].type))
						{
							printf("\r\nname '%s' ->seek_num '%d'  type :%d\r\n",string_dict.string[loopx].name,string_dict.string[loopx].seek_num,string_dict.string[loopx].type);
						}
				}
		}
	if(type == 3)  //parameter
	{
		printf("\r\n  parameter datas :\r\n");
		for(loopx = 0; loopx < string_dict.save_number ; loopx ++)
			{
				if((EFFECT == string_dict.string[loopx].this_data_effect )&&(type_parameter == string_dict.string[loopx].type))
					{
						printf("\r\nname '%s' ->seek_num '%d'  type :%d (parameter)\r\n",string_dict.string[loopx].name,string_dict.string[loopx].seek_num,string_dict.string[loopx].type);
					}
			}
	}
}

unsigned char seek_num_in_dict(unsigned char num)
{
	unsigned char loopx;
	for(loopx = 0; loopx < string_dict.save_number; loopx++)
		{
			if(string_dict.string[loopx].this_data_effect == EFFECT)  //保存的数据有效
				{
					if(num == string_dict.string[loopx].seek_num)
						{
							return 1;
						}
				}
		}
	return 0;
}

unsigned char get_auto_seek_num(void)
{
	unsigned char reslut = 0;
	for(reslut = 1; reslut < MAX_DICT_SAVE_NUM; reslut ++)
		{
			if(0 == seek_num_in_dict(reslut))
				{
					return reslut;
				}
		}
	return 0XFF;
}


