#include "include.h"

S_Cmd_Info script_cmd;
S_Script_Info script_info;
unsigned char explain_script(char *script,unsigned short length)
{
	P_S_Cmd current_cmd;
	my_mem_copy(script,script_cmd.recv_buf,length);
	if(1 == split_string(&script_cmd))
		{
			current_cmd = find_cmd(script_cmd.parameter[0]);
			if(current_cmd)
				{
					if((1 == str_cmp("-h",(script_cmd.parameter[1])))||(1 == str_cmp("-H",(script_cmd.parameter[1]))))
						{
							printf("\r\n%s\r\n",current_cmd->help);
						}
					else
						{
							current_cmd ->cmd_func((char*)&script_cmd);
						}
				}
			else
				{
					printf("\n\runknow command '%s' ,try  to  command  'help'\n\r",script_cmd.parameter[0]);
				}					
		}
	if(split_string(&script_cmd) == 2)
		{
			printf("Beside I Can't recv More Than %d Parts !\n\r       OUT OF MEMORY!  Please Check out!!\n\r  ",CMD_PARAMETER_NUM);
		}
	script_cmd.point = 0;
	set_string(script_cmd.recv_buf,CMD_REVC_BUF_SIZE,0);
	set_string((char*)script_cmd.parameter,CMD_REVC_BUF_SIZE,0);
	return 0;
}

unsigned char run_script(P_S_Script_Info script)
{
	FIL doc;
	char* read_point;
	read_point = script_cmd.recv_buf;
	unsigned int operat_num;
	res = (FRESULT)1;
	__disable_irq();
	res = f_open(&doc,"0:add_tel.scp",FA_READ);
	__enable_irq();
	if(res)
		{
			//open failed
			f_close(&doc);
			return 0;
		}
	while(1)
		{
			res = f_read(&doc,(read_point++),1,&operat_num);
			script_info.current_script_point++;
			if((*(read_point-2) ==0X0D) && (*(read_point-1)==0X0A))
				{
					script_info.current_script_length  = script_info.current_script_point - 2;
					*(read_point-2) =0X00;
					*(read_point-1) =0X00;
					explain_script((char*)(script_cmd.recv_buf),script_info.current_script_length);
					read_point = script_cmd.recv_buf;
					//break;
				}
			if(operat_num == 0)
				{
					break;
				}
		}
	f_close(&doc);
  return 0;
}
