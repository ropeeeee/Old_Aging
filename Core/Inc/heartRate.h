#ifndef __HEARTRATE_H__
#define __HEARTRATE_H__

#include "main.h"

#define WRITEADD 0xAE
#define READADD 0xAF
#define INTS1 0x00
#define INTS2 0x01
#define INTE1 0x02
#define INTE2 0x03
#define FIFOWP 0x04
#define OVERFLOWCOUNTER 0x05
#define FIFORP 0x06
#define FIFODR 0x07
#define FIFOCONFIG 0x08
#define MODE 0x09
#define LEDAmp 0x0C


int heratRate_Init(void);
uint8_t IIC_write(uint8_t addr,uint8_t data);
uint8_t IIC_read(uint8_t addr,uint8_t* data);
uint8_t maxim_max30102_reset(void);
uint8_t read_FIFO(uint32_t* red);

#endif
