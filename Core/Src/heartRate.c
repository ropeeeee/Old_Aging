#include "main.h"

uint8_t IIC_write(uint8_t addr,uint8_t data)
{

  if(HAL_I2C_Mem_Write(&hi2c1,WRITEADD,addr,1,&data,1,HAL_MAX_DELAY)!=HAL_OK)
  {
    return 1;
  }
  return 0;
}

uint8_t IIC_read(uint8_t addr,uint8_t* data)
{
  if(HAL_OK!=HAL_I2C_Mem_Read(&hi2c1,READADD,addr,1,data,1,HAL_MAX_DELAY))
  {
    return 1;
  }
  return 0;
}

uint8_t maxim_max30102_reset(void)
{
  if(IIC_write(0x09,0x40)==1)    //reset
  {
    return 1;  
  }
  return 0;
}

int heratRate_Init(void)
{
  //将max30102设置为关闭所有中断，FIFO满自动滚动，只开红光，100Hz速率，18bitADC
  IIC_write(INTE1,0x00);
  IIC_write(INTE2,0x00);
  IIC_write(FIFOWP,0x00);
  IIC_write(OVERFLOWCOUNTER,0x00);
  IIC_write(FIFORP,0x00);
  IIC_write(FIFOCONFIG,0x10);
  IIC_write(MODE,0x02);
  IIC_write(LEDAmp,0x1f);
  IIC_write(0x0A,0x27);
  return 0;
}

uint8_t read_FIFO(uint32_t* red)
{
  uint8_t raw_data[3];
  uint8_t max30102it;
  IIC_read(INTS1,&max30102it);
  IIC_read(INTS2,&max30102it);
  HAL_I2C_Mem_Read(&hi2c1,READADD,0x07,1,raw_data,3,HAL_MAX_DELAY);
  *red=0;
  *red=(raw_data[0]<<16)+(raw_data[1]<<8)+(raw_data[2]);
  *red&=0x03ffff;
  return 0;
}

