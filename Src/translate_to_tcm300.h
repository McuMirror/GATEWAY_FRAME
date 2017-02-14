#ifndef __TRANSLATE_TO_TCM300_H__
#define __TRANSLATE_TO_TCM300_H__
#include "include.h"

void insert_replace_strA_into_strB(char*strA,char*strB,unsigned short offset,unsigned short length);

unsigned char add_parameter_into_telegraph(char* reslut_tel,P_S_Telegraph telegraph,P_S_Revc_Parameter_Info parameter);
void translate_to_tcm300(char*buf,char* str);
void add_crc_into_telegraph(unsigned char* telegraph,unsigned char telegraph_length);
unsigned char complete_telegraph(unsigned char device_seek_num,unsigned char operat_seek_num,P_S_Device_Telegraph target_device,char* send_buf,P_S_Revc_Parameter_Info* recv_parameter,unsigned char parameter_num,S_Revc_Parameter_Info*  channel_info,S_Revc_Parameter_Info* key_value_info);


#endif
