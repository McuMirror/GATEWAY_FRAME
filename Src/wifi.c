#include "include.h"

S_Wifi_Recv_Data data_from_wifi;
S_Wifi_Operat_buf wifi_operat_data;
unsigned int Wifi_Mesg;


void transfer_wifi_rxdata(void)
{
	my_mem_copy((char*)(data_from_wifi.rx_data),(char*)(wifi_operat_data.recv_msg[wifi_operat_data.save_point].rx_data), data_from_wifi.data_len);
	wifi_operat_data.recv_msg[wifi_operat_data.save_point].this_data_effect = EFFECT;
	wifi_operat_data.recv_msg[wifi_operat_data.save_point++].len = data_from_wifi.data_len;
}

