#include "include.h"
ID_def id;

void set_send_gateway_command_code(unsigned char manufacturer_id,unsigned char master_command,unsigned char command)
{
	data_from_tcm300.tx_data[6] = 0XD1;
	data_from_tcm300.tx_data[7] = manufacturer_id;	 ///
	data_from_tcm300.tx_data[8] = master_command;	///
	data_from_tcm300.tx_data[9] = command;
}

void set_send_gateway_data_replace_id_code(unsigned char **data,unsigned char* length)
{
	unsigned char loopx,tmp_loop;
	data_from_tcm300.tx_data[10] = 0; 
	data_from_tcm300.tx_data[11] = 0;
	data_from_tcm300.tx_data[12] = 0;
	data_from_tcm300.tx_data[13] = 0;
	data_from_tcm300.tx_data[14] = 0;
	tmp_loop = *length;
	tmp_loop = tmp_loop >5? 5: tmp_loop;
	for(loopx = 0;loopx < tmp_loop;loopx ++)
		{
			data_from_tcm300.tx_data[10+loopx] = *((*data)++); 
			(*length) --;
		}
}

void set_send_gateway_data_code(unsigned char *data, unsigned char* data_length)
{
	unsigned char* tmp_data;
	unsigned char length;
	unsigned char  vLoop;
	length = *data_length;
	tmp_data = data;	
	if(length ==0X00)
	{       return;                                           }

	for(vLoop=0X01;vLoop<=length;vLoop++)
	{
		data_from_tcm300.tx_data[vLoop+0X0E]=*tmp_data;
		tmp_data++;
        }
}

void set_send_gateway_head_code(unsigned char data_len)
{
	data_from_tcm300.tx_data[0] = 0X55;
	data_from_tcm300.tx_data[1] = 0x00;
	data_from_tcm300.tx_data[2] = 0X0E + data_len;
	data_from_tcm300.tx_data[3] = 0X06;
	data_from_tcm300.tx_data[4] = 0X01;
	SetCRC8Sub(&data_from_tcm300.tx_data[1],4);	
}
void set_send_gateway_end_code(unsigned char data_len)
{
	unsigned char vlong;
	data_from_tcm300.tx_data[data_len + 0X0F] = id.TCM300_ID[0];
	data_from_tcm300.tx_data[data_len + 0X10] = id.TCM300_ID[1];
	data_from_tcm300.tx_data[data_len + 0X11] = id.TCM300_ID[2];
	data_from_tcm300.tx_data[data_len + 0X12] = id.TCM300_ID[3];
	data_from_tcm300.tx_data[data_len + 0X13] = 0X00;
	data_from_tcm300.tx_data[data_len + 0X14] = 0X03;
	
	data_from_tcm300.tx_data[data_len + 0X15] = 0XFF;
	data_from_tcm300.tx_data[data_len + 0X16] = 0XFF;
	data_from_tcm300.tx_data[data_len + 0X17] = 0XFF;
	data_from_tcm300.tx_data[data_len + 0X18] = 0XFF;
	data_from_tcm300.tx_data[data_len + 0X19] = 0XFF;
	vlong = data_len+0X14;
	 SetCRC8Sub(&data_from_tcm300.tx_data[0X06],vlong);
}


void send_data_to_gateway_by_msc(unsigned char master_command,unsigned char salve_command,unsigned char* data,unsigned char length)
{
	unsigned char send_data_length;
	unsigned char** send_data;
	
	send_data_length = length;
	send_data = &data;	
	set_send_gateway_command_code(0X68,master_command,salve_command);
	set_send_gateway_data_replace_id_code(send_data, &send_data_length);
	set_send_gateway_data_code( *send_data,&send_data_length);
	if(length<6)
		{
			set_send_gateway_head_code(0);
			set_send_gateway_end_code(0);
			HAL_UART_Transmit(&huart2,(data_from_tcm300.tx_data),27,900);
		}
	else
		{
			set_send_gateway_head_code(length -5);
			set_send_gateway_end_code(length - 5);
			HAL_UART_Transmit(&huart2,data_from_tcm300.tx_data,length +22,900);
		}
	
}

///////////////////////////////////////////////////////////////////////////////////////////////
void Set_2_GatewayHeadCode(P_S_Send_To_Gateway_Message message)
{
	data_from_tcm300.tx_data[0X00]=0X55;
        data_from_tcm300.tx_data[0X01]=0X00;
        data_from_tcm300.tx_data[0X02]=message ->data_length+0X04;
        data_from_tcm300.tx_data[0X03]=0X0A;
	data_from_tcm300.tx_data[0X04]=0X07;
	SetCRC8Sub(&data_from_tcm300.tx_data[0X01],0X04);
}

void Set_2_GatewayCommandCode(P_S_Send_To_Gateway_Message message)
{
	data_from_tcm300.tx_data[0X06]=message ->function_code[0];                      ///RORG
	data_from_tcm300.tx_data[0X07]=message ->function_code[1];  
	data_from_tcm300.tx_data[0X08]=message ->manufacturer_ID[0];
	data_from_tcm300.tx_data[0X09]=message ->manufacturer_ID[1];
	
}

void Set_2_GatewayEndCode(P_S_Send_To_Gateway_Message message)
{
	
	unsigned char* p_tmp;
	p_tmp = message ->destination_ID;
	
	if(message ->is_broadcast == 1)
		{
			data_from_tcm300.tx_data[message ->data_length+0X0A]=0XFF;             ///TCM300 ID
		        data_from_tcm300.tx_data[message ->data_length+0X0B]=0XFF;
		        data_from_tcm300.tx_data[message ->data_length+0X0C]=0XFF;
		        data_from_tcm300.tx_data[message ->data_length+0X0D]=0XFF;
		}
	else
		{
		        data_from_tcm300.tx_data[message ->data_length+0X0A]=*(p_tmp++);             ///TCM300 ID
		        data_from_tcm300.tx_data[message ->data_length+0X0B]=*(p_tmp++);
		        data_from_tcm300.tx_data[message ->data_length+0X0C]=*(p_tmp++);
		        data_from_tcm300.tx_data[message ->data_length+0X0D]=*p_tmp;
		}
        data_from_tcm300.tx_data[message ->data_length+0X0E]=id.TCM300_ID[0];
        data_from_tcm300.tx_data[message ->data_length+0X0F]=id.TCM300_ID[1];
        data_from_tcm300.tx_data[message ->data_length+0X10]=id.TCM300_ID[2];
        data_from_tcm300.tx_data[message ->data_length+0X11]=id.TCM300_ID[3];		
        data_from_tcm300.tx_data[message ->data_length+0X12]=0X22;
		
	if(message->is_delayed_send == 1)
		{
			 data_from_tcm300.tx_data[message ->data_length+0X13]=0X01;
		}
	else
		{
			data_from_tcm300.tx_data[message ->data_length+0X13]=0X00;
		}        

        SetCRC8Sub(&data_from_tcm300.tx_data[0X06],message ->data_length+14);
}

void Set_2_GatewayDataCode(P_S_Send_To_Gateway_Message message)
{
	unsigned char *data;
	unsigned char length;
	data = message->data;
	length = message->data_length;	
	unsigned char  vLoop;
	 
	if(length==0X00)
	{       return;                                           }

	for(vLoop=0X01;vLoop<=length;vLoop++)
	{
		data_from_tcm300.tx_data[vLoop+0X09]=*data;
		data++;
        }
}
void send_data_2_gateway(P_S_Send_To_Gateway_Message message)
{
	Set_2_GatewayHeadCode(message);
	Set_2_GatewayCommandCode(message);	
	Set_2_GatewayDataCode(message);
	Set_2_GatewayEndCode(message);
	HAL_UART_Transmit(&huart2,data_from_tcm300.tx_data,message->data_length +21,400);
}

