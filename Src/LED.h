/*
* File Name          : led.h
* Description       :∞Â‘ÿledøÿ÷∆∫Í
*                       
*
*
*
*
*
*/

#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
 extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////
#include "include.h"

#define LED_1_OFF     	HAL_GPIO_WritePin(LED_1_GPIO_Port,LED_1_Pin,GPIO_PIN_SET)
#define LED_1_ON		HAL_GPIO_WritePin(LED_1_GPIO_Port,LED_1_Pin,GPIO_PIN_RESET)
#define LED_1_TOG		HAL_GPIO_TogglePin(LED_1_GPIO_Port,LED_1_Pin)
#define SET_1_LED(X)       HAL_GPIO_WritePin(LED_1_GPIO_Port,LED_1_Pin,X)

#define LED_2_OFF     	HAL_GPIO_WritePin(LED_2_GPIO_Port,LED_2_Pin,GPIO_PIN_SET)
#define LED_2_ON		HAL_GPIO_WritePin(LED_2_GPIO_Port,LED_2_Pin,GPIO_PIN_RESET)
#define LED_2_TOG		HAL_GPIO_TogglePin(LED_2_GPIO_Port,LED_2_Pin)
#define SET_2_LED(X)       HAL_GPIO_WritePin(LED_2_GPIO_Port,LED_2_Pin,X)

#define LED_3_OFF     	HAL_GPIO_WritePin(LED_3_GPIO_Port,LED_3_Pin,GPIO_PIN_SET)
#define LED_3_ON		HAL_GPIO_WritePin(LED_3_GPIO_Port,LED_3_Pin,GPIO_PIN_RESET)
#define LED_3_TOG		HAL_GPIO_TogglePin(LED_3_GPIO_Port,LED_3_Pin)
#define SET_3_LED(X)       HAL_GPIO_WritePin(LED_3_GPIO_Port,LED_3_Pin,X)

#define LED_4_OFF     	HAL_GPIO_WritePin(LED_4_GPIO_Port,LED_4_Pin,GPIO_PIN_SET)
#define LED_4_ON		HAL_GPIO_WritePin(LED_4_GPIO_Port,LED_4_Pin,GPIO_PIN_RESET)
#define LED_4_TOG		HAL_GPIO_TogglePin(LED_4_GPIO_Port,LED_4_Pin)
#define SET_4_LED(X)       HAL_GPIO_WritePin(LED_4_GPIO_Port,LED_4_Pin,X)

#define LED_5_OFF     	HAL_GPIO_WritePin(LED_5_GPIO_Port,LED_5_Pin,GPIO_PIN_SET)
#define LED_5_ON		HAL_GPIO_WritePin(LED_5_GPIO_Port,LED_5_Pin,GPIO_PIN_RESET)
#define LED_5_TOG		HAL_GPIO_TogglePin(LED_5_GPIO_Port,LED_5_Pin)
#define SET_5_LED(X)       HAL_GPIO_WritePin(LED_5_GPIO_Port,LED_5_Pin,X)

#define LED_6_OFF     	HAL_GPIO_WritePin(LED_6_GPIO_Port,LED_6_Pin,GPIO_PIN_SET)
#define LED_6_ON		HAL_GPIO_WritePin(LED_6_GPIO_Port,LED_6_Pin,GPIO_PIN_RESET)
#define LED_6_TOG		HAL_GPIO_TogglePin(LED_6_GPIO_Port,LED_6_Pin)
#define SET_6_LED(X)       HAL_GPIO_WritePin(LED_6_GPIO_Port,LED_6_Pin,X)

#define LED_7_OFF     	HAL_GPIO_WritePin(LED_7_GPIO_Port,LED_7_Pin,GPIO_PIN_SET)
#define LED_7_ON		HAL_GPIO_WritePin(LED_7_GPIO_Port,LED_7_Pin,GPIO_PIN_RESET)
#define LED_7_TOG		HAL_GPIO_TogglePin(LED_7_GPIO_Port,LED_7_Pin)
#define SET_7_LED(X)       HAL_GPIO_WritePin(LED_7_GPIO_Port,LED_7_Pin,X)

#define LED_8_OFF     	HAL_GPIO_WritePin(LED_8_GPIO_Port,LED_8_Pin,GPIO_PIN_SET)
#define LED_8_ON		HAL_GPIO_WritePin(LED_8_GPIO_Port,LED_8_Pin,GPIO_PIN_RESET)
#define LED_8_TOG		HAL_GPIO_TogglePin(LED_8_GPIO_Port,LED_8_Pin)
#define SET_8_LED(X)       HAL_GPIO_WritePin(LED_8_GPIO_Port,LED_8_Pin,X)

#define LED_9_OFF     	HAL_GPIO_WritePin(LED_9_GPIO_Port,LED_9_Pin,GPIO_PIN_SET)
#define LED_9_ON		HAL_GPIO_WritePin(LED_9_GPIO_Port,LED_9_Pin,GPIO_PIN_RESET)
#define LED_9_TOG		HAL_GPIO_TogglePin(LED_9_GPIO_Port,LED_9_Pin)
#define SET_9_LED(X)       HAL_GPIO_WritePin(LED_9_GPIO_Port,LED_9_Pin,X)

#define LED_10_OFF     	HAL_GPIO_WritePin(LED_10_GPIO_Port,LED_10_Pin,GPIO_PIN_SET)
#define LED_10_ON		HAL_GPIO_WritePin(LED_10_GPIO_Port,LED_10_Pin,GPIO_PIN_RESET)
#define LED_10_TOG		HAL_GPIO_TogglePin(LED_10_GPIO_Port,LED_10_Pin)
#define SET_10_LED(X)       HAL_GPIO_WritePin(LED_10_GPIO_Port,LED_10_Pin,X)

#define LED_11_OFF     	HAL_GPIO_WritePin(LED_11_GPIO_Port,LED_11_Pin,GPIO_PIN_SET)
#define LED_11_ON		HAL_GPIO_WritePin(LED_11_GPIO_Port,LED_11_Pin,GPIO_PIN_RESET)
#define LED_11_TOG		HAL_GPIO_TogglePin(LED_11_GPIO_Port,LED_11_Pin)
#define SET_11_LED(X)       HAL_GPIO_WritePin(LED_11_GPIO_Port,LED_11_Pin,X)

#define LED_12_OFF     	HAL_GPIO_WritePin(LED_12_GPIO_Port,LED_12_Pin,GPIO_PIN_SET)
#define LED_12_ON		HAL_GPIO_WritePin(LED_12_GPIO_Port,LED_12_Pin,GPIO_PIN_RESET)
#define LED_12_TOG		HAL_GPIO_TogglePin(LED_12_GPIO_Port,LED_12_Pin)
#define SET_12_LED(X)       HAL_GPIO_WritePin(LED_12_GPIO_Port,LED_12_Pin,X)



void set_all_led_off(void);
void set_all_led_on(void);
void set_all_led_tog (void);

void set_led(unsigned char led,unsigned char operat);

////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
