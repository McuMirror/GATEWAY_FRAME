/*
* File Name          : led.c
* Description       :°åÔØled¿ØÖÆº¯Êý
*                       
*
*
*
*
*
*/
#include "include.h"
void set_all_led_off (void)
{
		LED_1_OFF;
		LED_2_OFF;
		LED_3_OFF;
		LED_4_OFF;
		LED_5_OFF;
		LED_6_OFF;
		LED_7_OFF;
		LED_8_OFF;
		LED_9_OFF;
		LED_10_OFF;
		LED_11_OFF;
		LED_12_OFF;
}

void set_all_led_on (void)
{
		LED_1_ON;
		LED_2_ON;
		LED_3_ON;
		LED_4_ON;
		LED_5_ON;
		LED_6_ON;
		LED_7_ON;
		LED_8_ON;
		LED_9_ON;
		LED_10_ON;
		LED_11_ON;
		LED_12_ON;
}

void set_all_led_tog (void)
{
		LED_1_TOG;
		LED_2_TOG;
		LED_3_TOG;
		LED_4_TOG;
		LED_5_TOG;
		LED_6_TOG;
		LED_7_TOG;
		LED_8_TOG;
		LED_9_TOG;
		LED_10_TOG;
		LED_11_TOG;
		LED_12_TOG;
}

void set_led(unsigned char led,unsigned char operat)
{
	if(operat == 1)
		{
			switch(led)
				{
					case 1:
						LED_1_ON;
						break;
					case 2:
						LED_2_ON;
						break;
					case 3:
						LED_3_ON;
						break;
					case 4:
						LED_4_ON;
						break;
					case 5:
						LED_5_ON;
						break;
					case 6:
						LED_6_ON;
						break;
					case 7:
						LED_7_ON;
						break;
					case 8:
						LED_8_ON;
						break;
					case 9:
						LED_9_ON;
						break;
					case 10:
						LED_10_ON;
						break;
					case 11:
						LED_11_ON;
						break;
					case 12:
						LED_12_ON;
						break;
					case 13:
						
						break;
					case 14:
						
						break;
					case 15:
						
						break;
					case 16:
						
						break;
				}
		}
	if(operat == 0)
		{
		switch(led)
			{
				case 1:
					LED_1_OFF;
					break;
				case 2:
					LED_2_OFF;
					break;
				case 3:
					LED_3_OFF;
					break;
				case 4:
					LED_4_OFF;
					break;
				case 5:
					LED_5_OFF;
					break;
				case 6:
					LED_6_OFF;
					break;
				case 7:
					LED_7_OFF;
					break;
				case 8:
					LED_8_OFF;
					break;
				case 9:
					LED_9_OFF;
					break;
				case 10:
					LED_10_OFF;
					break;
				case 11:
					LED_11_OFF;
					break;
				case 12:
					LED_12_OFF;
					break;
				case 13:
					
					break;
				case 14:
					
					break;
				case 15:
					
					break;
				case 16:
					
					break;
			}
			
		}
	if(operat == 2)
		{
		switch(led)
			{
				case 1:
					LED_1_TOG;
					break;
				case 2:
					LED_2_TOG;
					break;
				case 3:
					LED_3_TOG;
					break;
				case 4:
					LED_4_TOG;
					break;
				case 5:
					LED_5_TOG;
					break;
				case 6:
					LED_6_TOG;
					break;
				case 7:
					LED_7_TOG;
					break;
				case 8:
					LED_8_TOG;
					break;
				case 9:
					LED_9_TOG;
					break;
				case 10:
					LED_10_TOG;
					break;
				case 11:
					LED_11_TOG;
					break;
				case 12:
					LED_12_TOG;
					break;
				case 13:
					
					break;
				case 14:
					
					break;
				case 15:
					
					break;
				case 16:
					
					break;
			}
			
		}
}

