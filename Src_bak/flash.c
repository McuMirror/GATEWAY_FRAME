#include "include.h"

//HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
uint32_t Address = 0, PAGEError = 0;
uint32_t PageError = 0;
__IO TestStatus MemoryProgramStatus = PASSED;

uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
 
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0; 
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1; 
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2; 
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3; 
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4; 
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5; 
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6; 
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7; 
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8; 
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9; 
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10; 
  }
  else if((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
  {
    sector = FLASH_SECTOR_11; 
  }
  if((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
  {
    sector = FLASH_SECTOR_12; 
  }
  else if((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
  {
    sector = FLASH_SECTOR_13; 
  }
  else if((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
  {
    sector = FLASH_SECTOR_14; 
  }
  else if((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
  {
    sector = FLASH_SECTOR_15; 
  }
  else if((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
  {
    sector = FLASH_SECTOR_16; 
  }
  else if((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
  {
    sector = FLASH_SECTOR_17; 
  }
  else if((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
  {
    sector = FLASH_SECTOR_18; 
  }
  else if((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
  {
    sector = FLASH_SECTOR_19; 
  }
  else if((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
  {
    sector = FLASH_SECTOR_20; 
  }
  else if((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
  {
    sector = FLASH_SECTOR_21; 
  }
  else if((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
  {
    sector = FLASH_SECTOR_22; 
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_SECTOR_23; 
  }

  return sector;
}



unsigned char erase_sector(unsigned char sector_num)
{
	unsigned int error_num;
	FLASH_EraseInitTypeDef erase_init;
	erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
	erase_init.Banks = FLASH_BANK_2;
	erase_init.Sector = sector_num;
	erase_init.NbSectors = 1;
	erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	HAL_FLASH_Unlock();
	if(HAL_OK == HAL_FLASHEx_Erase(&erase_init,&error_num))
		{
			HAL_FLASH_Lock();
			return 0X88;
		}
	else
		{
			HAL_FLASH_Lock();
			return error_num;
		}
}

unsigned char write_flash(unsigned address,char* data,unsigned int len)
{
	__disable_irq();
	//erase_flash(address);
	MemoryProgramStatus = PASSED;
	unsigned int count = 0;
	char* data_tmp;
	data_tmp = data;
	HAL_FLASH_Unlock();
	Address = address;
	    while (count < len)
	    {
	      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, *(short*)data_tmp) == HAL_OK)
	      {
	        Address = Address + 2;
		data_tmp= data_tmp+ 2;
		count = count +2;
	      }
	      else
	      {
	        /* Error occurred while writing data in Flash memory. 
	           User can add here some code to deal with this error */	        
	      }
	    }
	
	__enable_irq();
	    /* Check the correctness of written data */
	    Address = address;
		data_tmp = data;
		count = 0;
		while (count < len)				
		    {
		      if((*(__IO uint16_t*) Address) != *(short*)data_tmp)
		      {
		        MemoryProgramStatus = FAILED;
		      }
		      Address += 2;			  
			data_tmp= data_tmp+ 2;
			count = count +2;
		    }
				
	  HAL_FLASH_Lock();
	   if (MemoryProgramStatus == PASSED)
	    	{
	    		return 1;
	    	}
	   else
	   	{
	   		return 0;
	   	}
 
}

unsigned char read_flash(unsigned address,char* data,unsigned int len)
{
	  char* data_tmp;
	 data_tmp = data;
	 unsigned int count = 0;
	 MemoryProgramStatus = PASSED;
	 Address = address;
	 while (count < len)				
		    {
		      *data_tmp = (*(__IO uint8_t*) Address);
		      Address += 1;			  
			data_tmp= data_tmp+ 1;
			count = count +1;
		    }
	 
	    /* Check the correctness of read data */
	    Address = address;
		data_tmp = data;
		count = 0;
		while (count < len)				
		    {
		      if((*(__IO uint8_t*) Address) != *data_tmp)
		      {
		        MemoryProgramStatus = FAILED;
		      }
		      Address += 1;			  
			data_tmp= data_tmp+ 1;
			count = count +1;
		    }
		
	  if (MemoryProgramStatus == PASSED)
	    	{
	    		return 1;
	    	}
	   else
	   	{
	   		return 0;
	   	}
}

