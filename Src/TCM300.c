#include "include.h"

S_Tcm300_Recv_Data data_from_tcm300;
S_Tcm300_Operat_buf tcm300_operat_data;

S_Tcm300_Msg_Ctrl Tcm300_Msg_Ctrl;

unsigned char G_Usart2_Buff;
unsigned int Tcm300_Mesg;
extern osMessageQId serial_queueHandle;
extern osMessageQId flash_queueHandle;
extern osMessageQId tcm300_tx_queueHandle;



/*这个函数存在的意义是如果使用空闲中断接受不定长数据的话
data_from_tcm300中的接收缓存可能随时都会改变,如果直接对接收缓存操作的话
可能会产生意想不到的情况,所以建议在tcm300接受完成后第一时间将接受缓存中的
数据复制到处理缓存区
*/
void transfer_tcm300_rxdata(void)
{
	my_mem_copy((char*)(data_from_tcm300.rx_data),(char*)(tcm300_operat_data.recv_msg[tcm300_operat_data.save_point].rx_data), data_from_tcm300.data_len);
	tcm300_operat_data.recv_msg[tcm300_operat_data.save_point].this_data_effect = EFFECT;
	tcm300_operat_data.recv_msg[tcm300_operat_data.save_point++].len = data_from_tcm300.data_len;
}

void send_data_by_tcm300(char* data,unsigned short lenth)
{
	my_mem_copy(data,(char*)data_from_tcm300.tx_data,lenth);
	send_data_to_tcm300(lenth);
}

void send_data_to_tcm300(unsigned char len)
{	
	//while(data_from_tcm300.is_dma_tx_sending);//等待dma发送完成
	//data_from_tcm300.is_dma_tx_sending = 1;//dma发送完成中断中置为0
	HAL_UART_Transmit(&huart2,data_from_tcm300.tx_data,len,100);
}

void send_data_to_tcm300_by_msg(unsigned char* data,unsigned short data_length)
{
	my_mem_copy((char*)data,( char * )(Tcm300_Msg_Ctrl.msg[Tcm300_Msg_Ctrl.point].tx_data), data_length);
	Tcm300_Msg_Ctrl.msg[Tcm300_Msg_Ctrl.point].this_data_effect = EFFECT;
	Tcm300_Msg_Ctrl.msg[Tcm300_Msg_Ctrl.point].len = data_length;
	Tcm300_Msg_Ctrl.send_point = Tcm300_Msg_Ctrl.point;
	xQueueSend(tcm300_tx_queueHandle,(void*)(&Tcm300_Msg_Ctrl.send_point),100);
	Tcm300_Msg_Ctrl.point++;
}

void read_tcm300_id(void)
{
	data_from_tcm300.tx_data[0]= 0X55;
	data_from_tcm300.tx_data[1]= 0X00;
	data_from_tcm300.tx_data[2]= 0X01;
	data_from_tcm300.tx_data[3]= 0X00;
	data_from_tcm300.tx_data[4]= 0X05;
	data_from_tcm300.tx_data[5]= 0X70;
	data_from_tcm300.tx_data[6]= 0X03;
	data_from_tcm300.tx_data[7]= 0X09;
	send_data_to_tcm300(8);	
}

void task_deal_tcm300(void)//////因为使用dma接收,同步帧55没有丢弃,所以所有做判断的位向后移一位
{
	data_from_tcm300.recv_ok = 0;
	if(VerifyCRC8Sub(&data_from_tcm300.rx_data[6],(data_from_tcm300.rx_data[2]+data_from_tcm300.rx_data[3])) == 0XFF)
		{
			if((data_from_tcm300.rx_data[4] == 0X02)&&(id.read_tcm300_id_flag == 0))
				{	
					id.read_tcm300_id_flag = 1;
					id.TCM300_ID[0] = data_from_tcm300.rx_data[15];
					id.TCM300_ID[1] = data_from_tcm300.rx_data[16];
					id.TCM300_ID[2] = data_from_tcm300.rx_data[17];
					id.TCM300_ID[3] = data_from_tcm300.rx_data[18];
				}
			if(data_from_tcm300.rx_data[4] == 1)
				{
					switch(data_from_tcm300.rx_data[6])
						{
							case 0XF6:
						             	//Deal_RPS_RadioSub();
						             break;

						        case 0XA5:
						             	//Deal_4BS_RadioSub();
						             break;

						        case 0XC5:
						            	 //Deal_SYSEX_RadioSub();
						             break;

						        case 0XD1:
	                       					//Deal_Gateway_RadioSub();
						             break;

	                	                        default:
	                	                             break;
						}
				}
			if(data_from_tcm300.rx_data[4] == 7)
				{
					data_from_tcm300.vBigRxMax =data_from_tcm300.rx_data[2]-4;
					//DealBigdata();
				}
			
		}
}

/*
unsigned char find_tcm_ID(P_S_Save_Learned_Device_Data P_DATA )
{
	unsigned loop8,loop4;
	for(loop8 = 0;loop8<8;loop8++)
		{
			for(loop4 = 0;loop4<4;loop4++)
				{
					if(P_DATA->device[loop8].tcm300_ID[loop4] == id.TARGAT_ID[loop4])
						{
							if(loop4 == 3)
								{
									if(P_DATA->device[loop8].tcm300_ID[4] == 0X55) //YOUXIAO
										{
											P_DATA->find_point = loop8;
											return 1;
										}
								}
							continue;
						}
					else
						{
							break;
						}
				}
		}
	return 0;
}






void Deal_RPS_RadioSub(void)
{
	unsigned char command;
	command = data_from_tcm300.rx_data[7];
	id.TARGAT_ID[0] = data_from_tcm300.rx_data[8];
	id.TARGAT_ID[1] = data_from_tcm300.rx_data[9];
	id.TARGAT_ID[2] = data_from_tcm300.rx_data[10];
	id.TARGAT_ID[3] = data_from_tcm300.rx_data[11];
	if((command == cOperateCode_A)||(command == cOperateCode_B)||(command == cOperateCode_C)||(command == cOperateCode_D))
		{
			if(find_tcm_ID(&Enocean_Switch))
				{
					Enocean_Switch.device[Enocean_Switch.find_point].this_device_effect = EFFECT;
					Enocean_Switch.G_last_time_recv_data = 0;
					Enocean_Switch.device[Enocean_Switch.find_point].last_time_recv_data = 0;
					Enocean_Switch.device[Enocean_Switch.find_point].count_trigger_on_time = 0;
					Enocean_Switch.device[Enocean_Switch.find_point].trigger_on = 1;//计时count_trigger_on_time
										
					switch(command)
						{
							case cOperateCode_A:
								break;
								
							case cOperateCode_B:							
								
								break;
								
							case cOperateCode_C:							

								break;
								
							case cOperateCode_D:							
								break;
							
						}
				}
		}
}

void Deal_4BS_RadioSub(void)
{
	id.TARGAT_DATA[3] = data_from_tcm300.rx_data[7];
	id.TARGAT_DATA[2] = data_from_tcm300.rx_data[8];
	id.TARGAT_DATA[1] = data_from_tcm300.rx_data[9]; ////FF KAI   00 GUAN
	id.TARGAT_DATA[0] = data_from_tcm300.rx_data[10];
	id.TARGAT_ID[0] =  data_from_tcm300.rx_data[11];
	id.TARGAT_ID[1] =  data_from_tcm300.rx_data[12];
	id.TARGAT_ID[2] =  data_from_tcm300.rx_data[13];
	id.TARGAT_ID[3] =  data_from_tcm300.rx_data[14];
	
	if(find_tcm_ID(& Wireless_Windows_Sensor) == 1)
		{
			deal_windows_sub();
		}

	if(find_tcm_ID(& Wireless_Body_Sensor) == 1)
		{
			deal_pir_sub();
		}
}


void deal_windows_sub(void)
{

}


void deal_pir_sub(void)
{

}

*/
void task_tcm300_send(unsigned int addr)
{
	if(addr > 7)
		{
			return;
		}
	Tcm300_Msg_Ctrl.msg[addr].this_data_effect = UNEFFECT;
	HAL_UART_Transmit_DMA(&huart1,(Tcm300_Msg_Ctrl.msg[addr].tx_data),(Tcm300_Msg_Ctrl.msg[addr].len));
}


