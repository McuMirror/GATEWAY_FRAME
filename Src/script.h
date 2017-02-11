#ifndef __SCRIPT_H__
#define __SCRIPT_H__
#include "include.h"

typedef struct
{
	char name[30];
	unsigned short current_script_point;
	unsigned short current_script_length;
}S_Script_Info,*P_S_Script_Info;

extern S_Cmd_Info script_cmd;
extern S_Script_Info script_info;

unsigned char explain_script(char *script,unsigned short length);
unsigned char run_script(P_S_Script_Info script);

#endif
