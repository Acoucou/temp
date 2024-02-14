#ifndef __SPI_DMA_H
#define __SPI_DMA_H
 
 
#include  "sys.h"
 
extern SPI_HandleTypeDef hspi1;  // SPI 2
extern DMA_HandleTypeDef hdma1;  // DMA 1
 
void SPI_DMA_Init(void);         // SPI 和 DMA初始化
 
#endif
