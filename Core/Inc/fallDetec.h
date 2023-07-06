#ifndef __FALLDETEC_H__
#define __FALLDETEC_H__

#include "main.h"

/*
6050 address--0x68

power manager

turn off all interrupts

reg59-64 read accele for 3 axis
*/

#define ADD6050W 0xD0
#define ADD6050R 0xD1
#define g 9.8
struct Falldet{
  int raw_acc_x;
  int raw_acc_y;
  int raw_acc_z;
  int raw_gyro_x;
  int raw_gyro_y;
  int raw_gyro_z;
  int raw_temp;
  float acc_x;
  float acc_y;
  float acc_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float temp;
};

extern struct Falldet Fallen;

uint8_t write6050(uint8_t add,uint8_t data);
uint8_t read6050(uint8_t add,uint8_t* data);
uint8_t reset6050(void);
uint8_t init6050(void);
uint8_t readDATA(struct Falldet* motion);


#endif
