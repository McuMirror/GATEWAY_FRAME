#include "include.h"


unsigned char get_parameter_switch_value_info(P_S_Revc_Parameter_Info info,char* str)//���ؼ�ֵר�Ŵ���
{
	if(parameter_key_value_ul == get_parameter_type(str))
		{
			info->parameter_length = 1;
			//info->type= get_parameter_type("���ؼ�ֵ");
			info->type= parameter_key_value;
			info->info_hex[0] = cOperateCode_A;
			info->info_dec ++;
		}

	if(parameter_key_value_ur == get_parameter_type(str))
		{
			info->parameter_length = 1;
			//info->type= get_parameter_type("���ؼ�ֵ");
			info->type= parameter_key_value;
			info->info_hex[0] = cOperateCode_B;
			info->info_dec ++;
		}

	if(parameter_key_value_ll == get_parameter_type(str))
		{
			info->parameter_length = 1;
			//info->type= get_parameter_type("���ؼ�ֵ");
			info->type= parameter_key_value;
			info->info_hex[0] = cOperateCode_C;
			info->info_dec ++;
		}

	if(parameter_key_value_lr == get_parameter_type(str))
		{
			info->parameter_length = 1;
			//info->type= get_parameter_type("���ؼ�ֵ");
			info->type= parameter_key_value;
			info->info_hex[0] = cOperateCode_D;
			info->info_dec ++;
		}

	if(parameter_key_value_ud == get_parameter_type(str))
		{
			info->parameter_length = 1;
			//info->type= get_parameter_type("���ؼ�ֵ");
			info->type= parameter_key_value;
			info->info_hex[0] = cOperateCode_A;
			info->info_dec ++;
		}

	if(parameter_key_value_ld == get_parameter_type(str))
		{
			info->parameter_length = 1;
			//info->type= get_parameter_type("���ؼ�ֵ");
			info->type= parameter_key_value;
			info->info_hex[0] = cOperateCode_C;
			info->info_dec ++;
		}
	if(info->info_dec > 1)
		{
			printf("\r\nTo Many Switch_Value!! I Would Use The Last One! \r\npls check out!!\r\n");
			return 2;
		}
	if(info->info_dec)
		{
			return 1;
		}
	return 0;
}

unsigned char get_parameter_channel_info(P_S_Revc_Parameter_Info info,char* str)//ͨ��ר�Ŵ���
{
	info->parameter_length = 1;
	//info->type= get_parameter_type("ͨ��");
	info->type= parameter_channel;
		info->info_dec = str_to_int(str + sizeof("����ͨ��")-1);
		switch(info->info_dec)
			{
				case 1:
					info->info_hex[0] |=0X01;
					break;

				case 2:
					info->info_hex[0] |=0X02;
					break;

				case 3:
					info->info_hex[0] |=0X04;
					break;

				case 4:
					info->info_hex[0] |=0X08;
					break;

				default:
					break;
			}
      return 1;
}


void insert_replace_strA_into_strB(char*strA,char*strB,unsigned short offset,unsigned short length)
{
	unsigned short strB_length;
	unsigned short tmp_length;
	char* tmp_strA;
	char* tmp_strB;
	tmp_strA = strA;
	tmp_strB = (strB + offset);
	tmp_length = length;
	strB_length = TELEGRAPH_LENGTH;//����֮��
	if(strB_length <(offset + length))
		{
			printf("\r\nInsert_Replace ERROR!!!  Out Of Memory!!!\r\n");
			return;
		}
	while(tmp_length--)
		{
			*(tmp_strB++) = *(tmp_strA++);
		}
	return;
}

void insert_replace_hex_into_str(char hex,char*str,unsigned short offset)
{
	char* tmp_str;
	tmp_str = (str+(offset&0X3F));//offsetֻ�е�6λ��Ч ���ߵڰ�λΪ��־λ
	if(offset&0X80)//offset_h
		{
			*tmp_str &= 0X0F;
			*tmp_str |= ((hex<<4)&0XF0);
		}
	if(offset&0X40)//0ffset_l
		{
			*tmp_str &= 0XF0;
			*tmp_str |= (hex&0X0F);
			
		}
}


///�ѽ��յ���һ��������Ϣ��ӵ�������
unsigned char add_parameter_into_telegraph(char* reslut_tel,P_S_Telegraph telegraph,P_S_Revc_Parameter_Info parameter)
{
	unsigned char loopx;
	char* p_tmp;
	p_tmp = reslut_tel;
	for(loopx = 0;loopx < (telegraph->parameter_num); loopx ++)
		{
			if(parameter->type == telegraph->parameter[loopx].parameter.parameter_name)
				{
					if(parameter->parameter_length == telegraph->parameter[loopx].parameter.length)
						{
							if((telegraph->parameter[loopx].parameter.offset)&0XC0)//offset Ϊ��λ ����
								{
									insert_replace_hex_into_str((parameter->info_hex[0]),p_tmp,(telegraph->parameter[loopx].parameter.offset));
								}
							else
								{
									insert_replace_strA_into_strB((parameter->info_hex),p_tmp,(telegraph->parameter[loopx].parameter.offset),(telegraph->parameter[loopx].parameter.length));
								}
							return 1;
						}
					else
						{
							printf("\r\nParameter '%s' Need %d Byte Data Not %d Byte!!\r\nThis Parameter Was Ignored!!",get_parameter_name(parameter->type),telegraph->parameter[loopx].parameter.length,parameter->parameter_length);
							return 0;
						}
				}
		}
	return 0;
}



void translate_to_tcm300(char*buf,char* str)
{ 	
  	char test_buf[100];
	char send_buf[60];
	unsigned char device_seek_num = 0,operat_seek_num = 0,device_have_found = 0,operat_have_found = 0;
	P_S_Device_Telegraph target_device;
	
	S_Revc_Parameter_Info channel_info = {.parameter_length = 0,.type = (PARAMETER_TYPE)0};//�������ͨ������Ϣ�򱣴�������ṹ����
	S_Revc_Parameter_Info key_value_info = {.parameter_length = 0,.type = (PARAMETER_TYPE)0,.info_dec = 0};//����������߿��ذ��������Ϣ�򱣴�������ṹ����
	
	P_S_Revc_Parameter_Info revc_parameter[15];
	unsigned char parameter_num = 0;
	unsigned char loopx,loopx_inside;
	revc_parameter[0] = (P_S_Revc_Parameter_Info)malloc(sizeof(S_Revc_Parameter_Info));
	char * nexttok;
	nexttok = strtok((char*)str," ");
	while(nexttok)
		{
			if(1 == find_str_in_dict(nexttok))//���ֵ����ҵ��ַ���
				{
					switch((string_dict.string[string_dict.point].type))
						{
							case type_controller_device:
								if(0 ==device_have_found)
									{
										device_have_found = 1;
										device_seek_num = string_dict.string[string_dict.point].seek_num;
									}
								else
									{
										printf("\r\nI Don't Know Which Device You Want To Operat %s or %s\r\n",get_str_name(device_seek_num),get_str_name(string_dict.string[string_dict.point].seek_num));
										return;
									}
								break;

							case type_operat:
								if(0 == operat_have_found)
									{
										operat_have_found = 1;
										operat_seek_num = string_dict.string[string_dict.point].seek_num;
									}
								else
									{
										printf("\r\nI Don't Know Which Operat You Want To do %s or %s\r\n",get_str_name(operat_seek_num),get_str_name(string_dict.string[string_dict.point].seek_num));
										return;
									}
								break;

							case type_parameter:// �������ֵ��ﱣ���������
								/*if(get_parameter_info(revc_parameter[parameter_num],nexttok))
								{
									parameter_num ++;
									revc_parameter[parameter_num] = (P_S_Revc_Parameter_Info)malloc(sizeof(S_Revc_Parameter_Info));
								}*/
								
								break;
							case type_radio_device:
								break;
							case type_sensor_decice:
								break;

							default:
								break;
						}
				}
			else//�ֵ���û�ҵ��ַ����͵�Ԥ��������������ַ���
				{
					if(2 == str_cmp("����ͨ��",nexttok)) //bit ͨ����Ϣ�������� ��������
						{
							get_parameter_channel_info(&channel_info,nexttok);
						}
					
					else if(get_parameter_switch_value_info(&key_value_info,nexttok))//����ַ����ǿ��ؼ�ֵ��Ϣ
						{
						
						}
					
					else
						{
							if(get_parameter_info(revc_parameter[parameter_num],nexttok))
								{
									parameter_num ++;
									revc_parameter[parameter_num] = (P_S_Revc_Parameter_Info)malloc(sizeof(S_Revc_Parameter_Info));
								}
						}
				}
			nexttok = strtok(NULL," ");		
		}

	if(0 == device_seek_num)
		{
			printf("\r\nUnknow Device !!\r\n");
			for(loopx = 0;loopx < (parameter_num +1);loopx ++)
				{
					free(revc_parameter[loopx]);
				}
			
			return;
		}
	if(0 == operat_seek_num)
		{
			printf("\r\nUnknow Operat !!\r\n");
			for(loopx = 0;loopx < (parameter_num +1);loopx ++)
				{
					free(revc_parameter[loopx]);
				}
			
			return;
		}
	
	if(1== find_device_seek_num_in_map(device_seek_num,1))//Э����Ϣ�����ڳ�פ�ڴ���
		{
			target_device = (&(RAM_static_tel.telegraph[save_tel_cfg.search_map.point]));//��¼��ǰ�ַ�����Ӧ��Э�鱣���ַ
			if(1 == find_operat_seek_num_in_telegraph(target_device,operat_seek_num))//��ǰ�豸Э���б�����Ŀ�����Э����Ϣ
				{
					set_string(test_buf,100,0);	
					my_mem_copy((char*)(target_device->telegraphs[target_device->point].telegraph),send_buf,(target_device->telegraphs[target_device->point].telegraph_length));

					if((target_device->telegraphs[target_device->point].parameter_num) != (parameter_num+channel_info.parameter_length+key_value_info.parameter_length))//�жϽ��յĲ����Ƿ�ϸ�
						{
							printf("\r\n'%s' Need %d Paratemers :",get_str_name(operat_seek_num),((target_device->telegraphs[target_device->point]).parameter_num));
							for(loopx = 0 ; loopx < (target_device->telegraphs[target_device->point].parameter_num); loopx++)
								{
									printf("  '%s'  ",get_parameter_name((PARAMETER_TYPE)(target_device->telegraphs[target_device->point].parameter[loopx].parameter.parameter_name)));
								}
							printf("\r\n Please Check Out!!!\r\n");
						}
					else
						{
							for(loopx = 0 ; loopx < parameter_num ; loopx++)
								{
									for(loopx_inside = 0; loopx_inside < (target_device->telegraphs[target_device->point].parameter_num) ; loopx_inside++)
										{
											if(revc_parameter[loopx]->type == (PARAMETER_TYPE)(target_device->telegraphs[target_device->point].parameter[loopx_inside].parameter.parameter_name))
												{
													break;
												}
											else
												{
													if(loopx_inside == (target_device->telegraphs[target_device->point].parameter_num -1))
														{
															printf("\r\n\r\nParameter ERROR!!  Don't Need  '%s' pls check out!!\r\n ",get_parameter_name(revc_parameter[loopx]->type ));															
														}
												}
										}
								}
						}
					
					for(loopx = 0; loopx < parameter_num;loopx++)
						{
							add_parameter_into_telegraph(send_buf,&(target_device->telegraphs[target_device->point]),revc_parameter[loopx]);//��ӽ��յ��Ĳ�����Ϣ
						}
					if(channel_info.type)
						{
							add_parameter_into_telegraph(send_buf,&(target_device->telegraphs[target_device->point]),&channel_info);//���ͨ����Ϣ
						}
					if(key_value_info.type)
						{
							add_parameter_into_telegraph(send_buf,&(target_device->telegraphs[target_device->point]),&key_value_info);//������߿��ؼ�ֵ��Ϣ
						}
					
					add_crc_into_telegraph((unsigned char*)send_buf,target_device->telegraphs[target_device->point].telegraph_length);
					hex_to_str(test_buf,(unsigned char*)send_buf,target_device->telegraphs[target_device->point].telegraph_length);
					printf("\r\nfind telegraph : %s",test_buf);
				}
			else
				{
					printf("\r\nI Can't Find '%s' In '%s'\r\n",get_str_name(operat_seek_num),get_str_name(device_seek_num));
				}
		}
	else if(1== find_device_seek_num_in_map(device_seek_num,2))//Э�鱣���ڶ�̬�ڴ���
		{
			target_device = (&(RAM_dynamic_tel.telegraph[save_tel_cfg.search_map.point]));
			if(1 == find_operat_seek_num_in_telegraph(target_device,operat_seek_num))
				{
					set_string(test_buf,100,0);					
					hex_to_str(test_buf,target_device->telegraphs[target_device->point].telegraph,target_device->telegraphs[target_device->point].telegraph_length);
					printf("find telegraph : %s",test_buf);
				}
			else
				{
					printf("\r\nI Can't Find '%s' In '%s'\r\n",get_str_name(operat_seek_num),get_str_name(device_seek_num));
				}
		}
	else if(1== find_device_seek_num_in_map(device_seek_num,3))//Э�鱣����SD���� ��δ���ص��ڴ���
		{
			load_telegraph_dynamic(device_seek_num);//��Э����Ϣ���ص��ڴ���
			find_device_seek_num_in_map(device_seek_num,2);
			target_device = (&(RAM_dynamic_tel.telegraph[save_tel_cfg.search_map.point]));
			if(1 == find_operat_seek_num_in_telegraph(target_device,operat_seek_num))
				{
					set_string(test_buf,100,0);					
					hex_to_str(test_buf,target_device->telegraphs[target_device->point].telegraph,target_device->telegraphs[target_device->point].telegraph_length);
					printf("find telegraph : %s",test_buf);
				}
			else
				{
					printf("\r\nI Can't Find '%s' In '%s'\r\n",get_str_name(operat_seek_num),get_str_name(device_seek_num));
				}
			
		}
	else
		{
			printf("Can't Find Device In Memory!\r\n");
		}
	
	for(loopx = 0;loopx < (parameter_num +1);loopx ++)
				{
					free(revc_parameter[loopx]);
				}
}


void add_crc_into_telegraph(unsigned char* telegraph,unsigned char telegraph_length)
{
	SetCRC8Sub((telegraph+1),4);
	SetCRC8Sub((telegraph+6),(telegraph_length-7));
}




