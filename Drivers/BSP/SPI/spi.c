#include "spi.h"
 
 
SPI_HandleTypeDef hspi1;  // SPI 1
DMA_HandleTypeDef hdma1;
// SPI ? DMA???
void SPI_DMA_Init(void)
{
  hspi1.Instance               =  SPI1 ; // SPI1 ???
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16 ; //?????
  hspi1.Init.CLKPhase          = SPI_PHASE_2EDGE;           //????
  hspi1.Init.CLKPolarity       = SPI_POLARITY_HIGH;         //?????
  hspi1.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;//??CEC??
  hspi1.Init.CRCPolynomial     = 10;                        //?????
  hspi1.Init.DataSize          = SPI_DATASIZE_8BIT;         //???(8bit)
  hspi1.Init.Direction         = SPI_DIRECTION_2LINES;      //???
  hspi1.Init.FirstBit          = SPI_FIRSTBIT_MSB;          //??????
  hspi1.Init.Mode              = SPI_MODE_MASTER ;          //SPI??
  hspi1.Init.NSS               = SPI_NSS_SOFT;              // ????SS
  hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;        // ????Motorola?
  HAL_SPI_Init(&hspi1); //SPI1 ???
  
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn,0,0); //??????
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);// ????
}
 
// SPI ???????
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef GPIO_InitTypeSture ={0};
  
  __HAL_RCC_SPI1_CLK_ENABLE(); // ??SPI1??
  __HAL_RCC_GPIOA_CLK_ENABLE();// ??GPIOA??
  __DMA1_CLK_ENABLE();         // ??DMA1??
  
  if(hspi ->Instance ==SPI1) //????????SPI1
  {
    GPIO_InitTypeSture.Mode = GPIO_MODE_AF_PP;     //?????????
    GPIO_InitTypeSture.Pin  = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitTypeSture.Pull = GPIO_PULLUP;
    GPIO_InitTypeSture.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOA,&GPIO_InitTypeSture); //GPIO ???
    
    hdma1.Instance                 = DMA1_Channel3;         //????DMA1??3
    hdma1.Init.Direction           = DMA_MEMORY_TO_PERIPH;  // ?????
    hdma1.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE ;   //???
    hdma1.Init.MemInc              = DMA_MINC_ENABLE;       //????
    hdma1.Init.Mode                = DMA_NORMAL;            //???
    hdma1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE ;   //???
    hdma1.Init.PeriphInc           = DMA_PINC_DISABLE ;     //?????
    hdma1.Init.Priority            = DMA_PRIORITY_MEDIUM;   // ???
    HAL_DMA_Init(&hdma1); //DMA ???
    
    __HAL_LINKDMA(hspi,hdmatx,hdma1);  // SPI?DMA????
  }
}
 
// DMA1??3??????
void DMA1_Channel3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma1);  //??DMA??
}
 