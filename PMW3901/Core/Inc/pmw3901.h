


// #include "M451Series.h"
// #include "sys.h"

#include "stm32f4xx_hal.h"
//typedef unsigned short INT16U;
//typedef unsigned int INT32U;
//
//typedef unsigned char u8;
//typedef unsigned short u16;
//typedef unsigned int u32;

#define PMW_MOTION 	12 //PD12
#define SPI_MOSI_1 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET) //PD13=1
#define SPI_MOSI_0 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET) //PD13=0
#define SPI_SCK_0 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET) //PD14=0
#define SPI_SCK_1 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET) //PD14=1
#define SPI_NCS_0 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET) //PD7=0
#define SPI_NCS_1 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)  //PD7=1
#define SPI_READ_MISO 15 //PD15


void PMWinit(void);
void readMotionCount(int16_t *deltax, int16_t *deltay);
uint16_t readMotionCount2();