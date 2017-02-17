#ifndef __PRINTF_H__
#define __PRINTF_H__

#define COM huart6  //重定向到串口6

#define DEBUG_NONE  	0
#define DEBUG_USER	1
#define DEBUG_SYS	2

#define DEBUG DEBUG_NONE
#if (DEBUG > 0)

#define  DEBUG_USR_ErrLog(...)   printf("USR_DEBUG: ") ;\
                            printf(__VA_ARGS__);\
                            printf("\r\n");
#else
#define  DEBUG_USR_ErrLog(...) 
#endif

#if (DEBUG > 1)

#define  DEBUG_SYS_ErrLog(...)   printf("SYS_DEBUG: ") ;\
                            printf(__VA_ARGS__);\
                            printf("\r\n");
#else
#define  DEBUG_SYS_ErrLog(...) 
#endif


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&COM, (unsigned char *)&ch, 1, 0xFFFF);

  return ch;
}

#endif

