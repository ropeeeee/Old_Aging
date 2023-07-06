#include "main.h"


struct Falldet Fallen;

uint8_t write6050(uint8_t add,uint8_t data)
{
  HAL_I2C_GetState(&hi2c1);//用HAL库读写最好都加上这一句，不然可能会出现读写失败的情况
  if(HAL_I2C_Mem_Write(&hi2c1,ADD6050W ,add,1,&data,1,HAL_MAX_DELAY)!=HAL_OK)
  {
    printf("write addr %d fail\r\n",add);
    return 1;
  }
  return 0;
}
uint8_t read6050(uint8_t add,uint8_t* data)
{
  HAL_I2C_GetState(&hi2c1);
  if(HAL_I2C_Mem_Read(&hi2c1,ADD6050R ,add,1,data,1,HAL_MAX_DELAY)!=HAL_OK)
  {
    printf("read addr %d fail\r\n",add);
    return 1;
  }
  return 0;
  
}
uint8_t reset6050(void)
{
  if(write6050(0x6b,0x80))
  {
    return 1;
  }
  return 0;
}


uint8_t init6050(void)
{
  //reset6050();
  uint8_t address;
  read6050(0x75,&address);
  if(address!=0x68)
  {
    printf("address=%d",address);
    return 1;
  }
  write6050(0x6b,0x01);
  write6050(0x6c,0x00);
  write6050(0x1a,0x03);//set DLPF 
  write6050(0x19,0x09);//sample rate=1kHz/(1+9)=100Hz
  write6050(0x1b,0x00);//gyro range:+-250°/s
  write6050(0x1c,0x01);//acc range:+-2g, set g=9.8
  //write6050(0x38,0x00);//turn off all interrupts
  printf("MPU6050 Init OK!\r\n");
  return 0;
}
uint8_t readDATA(struct Falldet* motion)
{
  uint8_t dataL,dataH;
  read6050(0x3b,&dataH);
  read6050(0x3c,&dataL);
  if(dataH>100)
  {
    dataH=~dataH;
    
  }
  motion->raw_acc_x=(dataH<<8)|dataL;
  motion->acc_x=(float)motion->raw_acc_x*1.0/(65536/2)*(2*g);
  printf("%d,%d,%d,%f\r\n",dataH,dataL,motion->raw_acc_x,motion->acc_x);
  return 0;
}
