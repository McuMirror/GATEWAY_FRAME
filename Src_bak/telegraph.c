#include "include.h"



S_Save_Telegraph_cfg save_tel_cfg;//保存通信帧的配置保存信息

S_Device_Telegraph current_operat_telegraph;//用于修改(增删改查)

S_Static_RAM_Tele_Data RAM_static_tel = {0};//查找通信帧
S_Dynamic_RAM_Tele_Data RAM_dynamic_tel = {0};//查找通信帧


unsigned char find_device_seek_num_in_info(unsigned char seek_num) //找出指定seek_num 在sd卡中的保存位置
{
	unsigned char loopx;
	for(loopx =0 ;loopx < save_tel_cfg.SD_card_save_info.saved_num;loopx ++)
		{
			if(save_tel_cfg.SD_card_save_info.telegraph[loopx].this_data_effect == EFFECT)
				{
					if(save_tel_cfg.SD_card_save_info.telegraph[loopx].device_seek_num == seek_num)
						{
							save_tel_cfg.SD_card_save_info.point = loopx;
							return 1;
						}
				}
		}
	return 0;
}

unsigned char find_operat_seek_num_in_telegraph(P_S_Device_Telegraph tel,unsigned char operat_seek_num)//在一个设备通讯协议里找指定的操作
{
	unsigned char loopx;
	for(loopx = 0; loopx < tel->saved_num; loopx ++)
		{
			if(operat_seek_num == tel->telegraphs[loopx].operat_seek_num)
				{
					tel->point = loopx;
					return 1;
				}
		}
	return 0;
}


void creat_flash_SDcard_map(void)
{
	unsigned char loopx;
	save_tel_cfg.search_map.flash_SDcard_save_num = 0;
	for(loopx = 0;loopx < save_tel_cfg.SD_card_save_info.saved_num ; loopx ++)
		{
			if(save_tel_cfg.SD_card_save_info.telegraph[loopx].this_data_effect == EFFECT)
				{
					save_tel_cfg.search_map.flash_SDcard[save_tel_cfg.search_map.flash_SDcard_save_num++] = save_tel_cfg.SD_card_save_info.telegraph[loopx].device_seek_num;
				}
		}
}

unsigned char find_device_seek_num_in_map(unsigned char seek_num,unsigned char from)//在参数指定的位置中查询参数指定的seek_num当前保存的位置
{
	unsigned char loopx;
	
	if(from == 1)//常驻ram
		{
			for(loopx = 0; loopx < save_tel_cfg.search_map.current_static_ram_save_num;loopx ++)
				{
					if(seek_num == save_tel_cfg.search_map.current_static_ram[loopx])
						{
							save_tel_cfg.search_map.point = loopx;
							return 1;
						}
				}
		}
	if(from == 2)//动态ram
		{
			for(loopx = 0; loopx < save_tel_cfg.search_map.current_dynamic_ram_save_num;loopx ++)
				{
					if(seek_num == save_tel_cfg.search_map.current_dynamic_ram[loopx])
						{
							save_tel_cfg.search_map.point = loopx;
							return 1;
						}
				}
		}
	if(from ==3)//sd卡
		{
			for(loopx = 0; loopx < save_tel_cfg.search_map.flash_SDcard_save_num;loopx ++)
				{
					if(seek_num == save_tel_cfg.search_map.flash_SDcard[loopx])
						{
							save_tel_cfg.search_map.point = loopx;
							return 1;
						}
				}
		}
	return 0;
}


unsigned char find_delete_num_in_SDcard(P_S_Save_Telegraph_cfg cfg)
{
	unsigned char loopx;
	for(loopx = 0; loopx < (cfg->SD_card_save_info.saved_num) ; loopx++)
		{
			if(cfg->SD_card_save_info.telegraph[loopx].this_data_effect == UNEFFECT)
				{
					cfg->SD_card_save_info.point = loopx;
					return 1;
				}
		}
	return 0;
}

unsigned char insert_telegraph_to_SDcard(P_S_Device_Telegraph telegraph,unsigned char point)
{
	FIL doc;
	FRESULT reslut;
	unsigned int operat_num;
	__disable_irq();
	reslut = f_open(&doc,"telegraph.db",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	if(reslut != FR_OK)
		{
			printf("\r\n open file'telegraph.db' error error_number : %d\r\n",reslut);
		}
	f_lseek(&doc,(point*(sizeof(S_Device_Telegraph))));
	reslut = f_write(&doc,(void*)telegraph,(sizeof(S_Device_Telegraph)),&operat_num);
	if(reslut != FR_OK)
		{
			printf("\r\n write file'telegraph.db' error error_number : %d\r\n",reslut);
		}
	else
		{
			printf("\r\n write success !! write %d bytes\r\n",operat_num);
		}
	f_close(&doc);
	__enable_irq();
	return 1;
}

unsigned char save_telegraph_to_SDcard(P_S_Device_Telegraph telegraph)
{
	//P_S_Device_Telegraph tmp = telegraph;
	if(save_tel_cfg.SD_card_save_info.saved_num > 254)
		{
			return 3; //full
		}
	if(telegraph->this_data_effect != EFFECT)
		{
			return 0;//数据无效
		}
	if(1 == find_device_seek_num_in_info(telegraph->device_seek_num))
		{
			insert_telegraph_to_SDcard(telegraph,save_tel_cfg.SD_card_save_info.point);			
			//telegraph->this_data_effect = UNEFFECT;
			return 2; //数据更改
		}
	else
		{
			if(save_tel_cfg.SD_card_save_info.delete_num == 0)//没有删除过数据 保存在文件尾部
				{
					insert_telegraph_to_SDcard(telegraph,save_tel_cfg.SD_card_save_info.saved_num);
					//save_tel_cfg.search_map.flash_SDcard[save_tel_cfg.search_map.flash_SDcard_save_num] = telegraph->device_seek_num;
					//save_tel_cfg.search_map.flash_SDcard_save_num ++;				
					
					save_tel_cfg.SD_card_save_info.telegraph[save_tel_cfg.SD_card_save_info.saved_num].device_seek_num = telegraph->device_seek_num;
					save_tel_cfg.SD_card_save_info.telegraph[save_tel_cfg.SD_card_save_info.saved_num].save_point = save_tel_cfg.SD_card_save_info.saved_num;
					save_tel_cfg.SD_card_save_info.telegraph[save_tel_cfg.SD_card_save_info.saved_num].this_data_effect = EFFECT;
					save_tel_cfg.SD_card_save_info.saved_num ++;
					creat_flash_SDcard_map();
					//telegraph->this_data_effect = UNEFFECT;
					return 1;//保存成功
				}
			else//之前删除过数据保存在删除的位置上
				{
					find_delete_num_in_SDcard(&save_tel_cfg);
					insert_telegraph_to_SDcard(telegraph,save_tel_cfg.SD_card_save_info.point);
					save_tel_cfg.SD_card_save_info.telegraph[save_tel_cfg.SD_card_save_info.point].device_seek_num = telegraph->device_seek_num;
					save_tel_cfg.SD_card_save_info.telegraph[save_tel_cfg.SD_card_save_info.point].save_point = save_tel_cfg.SD_card_save_info.point;
					save_tel_cfg.SD_card_save_info.telegraph[save_tel_cfg.SD_card_save_info.point].this_data_effect = EFFECT;
					save_tel_cfg.SD_card_save_info.delete_num --;
					creat_flash_SDcard_map();
					//telegraph->this_data_effect = UNEFFECT;
					return 1;//保存成功
				}
		}
}

void save_telegraph_to_ram(P_S_Device_Telegraph telegraph)//将目标设备通信协议保存到ram中(前提是如果此设备保存在ram中,包括常驻ram与动态ram)
{
	unsigned char loopx;
	for(loopx = 0 ; loopx < MAX_STATIC_RAM_SAVE_NUM ; loopx ++)
		{
			if(RAM_static_tel.telegraph[loopx].device_seek_num == telegraph->device_seek_num)
				{
					my_mem_copy((char*)telegraph,(char*)&RAM_static_tel.telegraph[loopx],sizeof(S_Device_Telegraph));
					return;
				}
		}
	for(loopx = 0 ; loopx < 8 ;loopx ++)
		{
			if(RAM_dynamic_tel.telegraph[loopx].device_seek_num == telegraph->device_seek_num)
				{
					my_mem_copy((char*)telegraph,(char*)&RAM_dynamic_tel.telegraph[loopx],sizeof(S_Device_Telegraph));
					return;
				}
		}
}

unsigned char load_telegraph(FIL*fp,P_S_Device_Telegraph target,unsigned char point)
{
	if(point > save_tel_cfg.SD_card_save_info.saved_num)
		{
			printf("\r\n please check the parameter!!\r\n");
			return 0;
		}
	//FIL doc;
	FRESULT reslut;
	unsigned int operat_num;
	__disable_irq();
	f_lseek(fp,(point*(sizeof(S_Device_Telegraph))));
	reslut = f_read(fp,(void*)target,(sizeof(S_Device_Telegraph)),&operat_num);
	__enable_irq();
	if(reslut != FR_OK)
		{
			printf("\r\n load file'telegraph.db' error error_number : %d\r\n",reslut);
			return 2;
		}
	else
		{
			printf("\r\n load '%s' success !! read %d bytes\r\n",get_str_name(target->device_seek_num),operat_num);
			return 1;
		}
	//f_close(&doc);
}

void load_telegraph_to_ram_as_map(void)
{
	unsigned char loopx;
	FIL doc;
	FRESULT res;
	__disable_irq();
	res = f_open(&doc,"telegraph.db",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	__enable_irq();
	if(res != FR_OK)
		{
			printf("\r\n open file'telegraph.db' error error_number : %d\r\n",res);
		}
	if(res == FR_OK)
	{
		save_tel_cfg.search_map.current_static_ram_save_num = 0;
		if(save_tel_cfg.search_map.set_static_ram_save_num < MAX_STATIC_RAM_SAVE_NUM)
			{
				for(loopx = 0 ;loopx < save_tel_cfg.search_map.set_static_ram_save_num; loopx ++)  //保存指定必须存在常驻ram中的通信帧数据
					{
						find_device_seek_num_in_info(save_tel_cfg.search_map.set_static_ram[loopx]);
						if(1 == load_telegraph(&doc,&(RAM_static_tel.telegraph[save_tel_cfg.search_map.current_static_ram_save_num]),save_tel_cfg.SD_card_save_info.point))
							{
								save_tel_cfg.search_map.current_static_ram[save_tel_cfg.search_map.current_static_ram_save_num] = save_tel_cfg.search_map.set_static_ram[loopx];
								save_tel_cfg.search_map.current_static_ram_save_num++;
							}
					}
			}
		else
			{
				for(loopx = 0 ;loopx < MAX_STATIC_RAM_SAVE_NUM; loopx ++)  //保存指定必须存在常驻ram中的通信帧数据
					{
						find_device_seek_num_in_info(save_tel_cfg.search_map.set_static_ram[loopx]);
						if(1 == load_telegraph(&doc,&(RAM_static_tel.telegraph[save_tel_cfg.search_map.current_static_ram_save_num]),save_tel_cfg.SD_card_save_info.point))
							{
								save_tel_cfg.search_map.current_static_ram[save_tel_cfg.search_map.current_static_ram_save_num] = save_tel_cfg.search_map.set_static_ram[loopx];
								save_tel_cfg.search_map.current_static_ram_save_num++;
							}
					}
			}
		if(save_tel_cfg.search_map.current_static_ram_save_num< MAX_STATIC_RAM_SAVE_NUM)  //常驻ram区没存满
			{
				for(loopx = 0; loopx < save_tel_cfg.search_map.flash_SDcard_save_num ; loopx++)
					{
						if(0 == find_device_seek_num_in_map(save_tel_cfg.search_map.flash_SDcard[loopx],1)) //此seek_num 没有在常驻ram区找到
							{
								find_device_seek_num_in_info(save_tel_cfg.search_map.flash_SDcard[loopx]);
								if(1 == load_telegraph(&doc,&(RAM_static_tel.telegraph[save_tel_cfg.search_map.current_static_ram_save_num]),save_tel_cfg.SD_card_save_info.point))
									{
										save_tel_cfg.search_map.current_static_ram[save_tel_cfg.search_map.current_static_ram_save_num] = save_tel_cfg.search_map.flash_SDcard[loopx];
										save_tel_cfg.search_map.current_static_ram_save_num++;
										if(save_tel_cfg.search_map.current_static_ram_save_num == MAX_STATIC_RAM_SAVE_NUM)
											{
												goto next;//常驻ram区空间用完
											}
									}
							}
					}
				goto end;//全部信息均保存在了常驻ram区
			}
		next:
		save_tel_cfg.search_map.current_dynamic_ram_save_num = 0;
		for(loopx = 0 ;loopx < save_tel_cfg.search_map.flash_SDcard_save_num ; loopx ++)
			{
				if(0 == find_device_seek_num_in_map(save_tel_cfg.search_map.flash_SDcard[loopx],1)) //此seek_num 没有在常驻ram区找到
				{
					find_device_seek_num_in_info(save_tel_cfg.search_map.flash_SDcard[loopx]);
					if(1 == load_telegraph(&doc,&(RAM_dynamic_tel.telegraph[save_tel_cfg.search_map.current_dynamic_ram_save_num]),save_tel_cfg.SD_card_save_info.point))
						{
							save_tel_cfg.search_map.current_dynamic_ram_save_num++;
							if(save_tel_cfg.search_map.current_dynamic_ram_save_num == 8)
								{
									goto end; //动态ram区存满
								}
						}
				}
			}
	end:
	f_close(&doc);
	}
}
void load_telegraph_dynamic(unsigned char device_seek_num)
{
	FIL doc;
	FRESULT res;
	__disable_irq();
	res = f_open(&doc,"telegraph.db",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	__enable_irq();
	if(res != FR_OK)
		{
			printf("\r\n open file'telegraph.db' error error_number : %d\r\n",res);
		}

	if(1 == find_device_seek_num_in_info(device_seek_num))
		{
			save_tel_cfg.search_map.current_dynamic_ram[RAM_dynamic_tel.point] = device_seek_num;	
			RAM_dynamic_tel.current_saved_seek_num[RAM_dynamic_tel.point] = device_seek_num;	
			load_telegraph(&doc,&(RAM_dynamic_tel.telegraph[ RAM_dynamic_tel.point]),save_tel_cfg.SD_card_save_info.point);
			RAM_dynamic_tel.point ++; //point  占3个bit位 值域为0-7
			printf("\r\nload success!!\r\n");
		}
	else
		{
			printf("\r\n can not find device in SDcard please check out!\r\n");
		}
	f_close(&doc);
}
void load_telegraph_to_current_operat_telegraph(unsigned char seek_num)//进入这个函数的前提seek_num已经在sd卡存储信息中找到
{
	FIL doc;
	FRESULT res;
	__disable_irq();
	res = f_open(&doc,"telegraph.db",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	__enable_irq();
	if(res != FR_OK)
		{
			printf("\r\n open file'telegraph.db' error error_number : %d\r\n",res);
		}
	
	find_device_seek_num_in_info(seek_num);
	load_telegraph(&doc,&current_operat_telegraph,save_tel_cfg.SD_card_save_info.point);

	f_close(&doc);	
}

unsigned char save_telegraph_cfg_to_SDcard(P_S_Save_Telegraph_cfg telegraphcfg)
{
	FIL doc;
	FRESULT reslut;
	unsigned int operat_num;
	__disable_irq();
	reslut = f_open(&doc,"telegraph.cfg",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	if(reslut != FR_OK)
		{
			printf("\r\n open file'telegraph.cfg' error error_number : %d\r\n",reslut);
		}
	reslut = f_write(&doc,(void*)telegraphcfg,(sizeof(S_Save_Telegraph_cfg)),&operat_num);
	if(reslut != FR_OK)
		{
			printf("\r\n write file'telegraph.cfg' error error_number : %d\r\n",reslut);
		}
	else
		{
			printf("\r\n write success !! write %d bytes\r\n",operat_num);
		}
	f_close(&doc);
	__enable_irq();
	if(reslut == FR_OK)
		{
			return 1;
		}
	else
		{
			return 0;
		}
}

unsigned char load_telegraph_cfg_to_ram(P_S_Save_Telegraph_cfg telegraphcfg)
{
	FIL doc;
	FRESULT reslut;
	unsigned int operat_num;
	__disable_irq();
	reslut = f_open(&doc,"telegraph.cfg",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	if(reslut != FR_OK)
		{
			printf("\r\n open file'telegraph.cfg' error error_number : %d\r\n",reslut);
		}
	reslut = f_read(&doc,(void*)telegraphcfg,(sizeof(S_Save_Telegraph_cfg)),&operat_num);
	if(reslut != FR_OK)
		{
			printf("\r\n load file'telegraph.cfg' error error_number : %d\r\n",reslut);
		}
	else
		{
			printf("\r\n load 'telegraph.cfg' success !! read %d bytes\r\n",operat_num);
		}
	f_close(&doc);
	__enable_irq();
	creat_flash_SDcard_map();
	if(reslut == FR_OK)
		{
			return 1;
		}
	else
		{
			return 0;
		}
}



