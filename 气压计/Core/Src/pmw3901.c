
#include "pmw3901.h"
#include "main.h"
#include "retarget.h"
#include "w25qxx.h"
//pmw3901.h文件中替换IO脚位
//延时函数可以自己写，确保延时准确代入此页	HAL_Delay(100000);中
//这里延时100000代表10ms

uint16_t chipId=0,dIpihc=0;
extern SPI_HandleTypeDef hspi2;
//光流模块写数据函数
//输入location 地址  byte 数据
uint8_t SPI_PMW_SendByte(uint8_t location ,uint8_t byte )
{

    uint8_t dataTx[2];
    uint8_t datarx[2];
    dataTx[0] = location | 0x80u; // Set MSB high for write operation
    dataTx[1] = byte;

    sFLASH_CS_LOW();
    HAL_Delay(1);


    HAL_SPI_Transmit(&hspi2, dataTx, 2, 10); // Transmit data
//    HAL_SPI_TransmitReceive(&hspi2, &dataTx ,&datarx , 2, 1000);


//    HAL_Delay(1000);
//    SPI_ReadWriteByte(location);
//    SPI_ReadWriteByte(byte);
    sFLASH_CS_HIGH();
    return 0;
}
//光流模块读数据函数
//byte 地址
uint8_t SPI_PMW_ReadByte(uint8_t byte) {
    uint8_t TX_DATA = byte;
    uint8_t RX_DATA = 0;
    sFLASH_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, &TX_DATA ,&RX_DATA , 1, 1000);
    HAL_SPI_TransmitReceive(&hspi2, &TX_DATA ,&RX_DATA , 1, 1000);
    sFLASH_CS_HIGH();
    return RX_DATA;
}
//寄存器初始化
void initRegisters()
{
  SPI_PMW_SendByte(0x7F, 0x00);
  SPI_PMW_SendByte(0x61, 0xAD);
  SPI_PMW_SendByte(0x7F, 0x03);
  SPI_PMW_SendByte(0x40, 0x00);
  SPI_PMW_SendByte(0x7F, 0x05);
  SPI_PMW_SendByte(0x41, 0xB3);
  SPI_PMW_SendByte(0x43, 0xF1);
  SPI_PMW_SendByte(0x45, 0x14);
  SPI_PMW_SendByte(0x5B, 0x32);
  SPI_PMW_SendByte(0x5F, 0x34);
  SPI_PMW_SendByte(0x7B, 0x08);
  SPI_PMW_SendByte(0x7F, 0x06);
  SPI_PMW_SendByte(0x44, 0x1B);
  SPI_PMW_SendByte(0x40, 0xBF);
  SPI_PMW_SendByte(0x4E, 0x3F);
  SPI_PMW_SendByte(0x7F, 0x08);
  SPI_PMW_SendByte(0x65, 0x20);
  SPI_PMW_SendByte(0x6A, 0x18);
  SPI_PMW_SendByte(0x7F, 0x09);
  SPI_PMW_SendByte(0x4F, 0xAF);
  SPI_PMW_SendByte(0x5F, 0x40);
  SPI_PMW_SendByte(0x48, 0x80);
  SPI_PMW_SendByte(0x49, 0x80);
  SPI_PMW_SendByte(0x57, 0x77);
  SPI_PMW_SendByte(0x60, 0x78);
  SPI_PMW_SendByte(0x61, 0x78);
  SPI_PMW_SendByte(0x62, 0x08);
  SPI_PMW_SendByte(0x63, 0x50);
  SPI_PMW_SendByte(0x7F, 0x0A);
  SPI_PMW_SendByte(0x45, 0x60);
  SPI_PMW_SendByte(0x7F, 0x00);
  SPI_PMW_SendByte(0x4D, 0x11);
  SPI_PMW_SendByte(0x55, 0x80);
  SPI_PMW_SendByte(0x74, 0x1F);
  SPI_PMW_SendByte(0x75, 0x1F);
  SPI_PMW_SendByte(0x4A, 0x78);
  SPI_PMW_SendByte(0x4B, 0x78);
  SPI_PMW_SendByte(0x44, 0x08);
  SPI_PMW_SendByte(0x45, 0x50);
  SPI_PMW_SendByte(0x64, 0xFF);
  SPI_PMW_SendByte(0x65, 0x1F);
  SPI_PMW_SendByte(0x7F, 0x14);
  SPI_PMW_SendByte(0x65, 0x60);
  SPI_PMW_SendByte(0x66, 0x08);
  SPI_PMW_SendByte(0x63, 0x78);
  SPI_PMW_SendByte(0x7F, 0x15);
  SPI_PMW_SendByte(0x48, 0x58);
  SPI_PMW_SendByte(0x7F, 0x07);
  SPI_PMW_SendByte(0x41, 0x0D);
  SPI_PMW_SendByte(0x43, 0x14);
  SPI_PMW_SendByte(0x4B, 0x0E);
  SPI_PMW_SendByte(0x45, 0x0F);
  SPI_PMW_SendByte(0x44, 0x42);
  SPI_PMW_SendByte(0x4C, 0x80);
  SPI_PMW_SendByte(0x7F, 0x10);
  SPI_PMW_SendByte(0x5B, 0x02);
  SPI_PMW_SendByte(0x7F, 0x07);
  SPI_PMW_SendByte(0x40, 0x41);
  SPI_PMW_SendByte(0x70, 0x00);

  HAL_Delay(10);
  SPI_PMW_SendByte(0x32, 0x44);
  SPI_PMW_SendByte(0x7F, 0x07);
  SPI_PMW_SendByte(0x40, 0x40);
  SPI_PMW_SendByte(0x7F, 0x06);
  SPI_PMW_SendByte(0x62, 0xf0);
  SPI_PMW_SendByte(0x63, 0x00);
  SPI_PMW_SendByte(0x7F, 0x0D);
  SPI_PMW_SendByte(0x48, 0xC0);
  SPI_PMW_SendByte(0x6F, 0xd5);
  SPI_PMW_SendByte(0x7F, 0x00);
  SPI_PMW_SendByte(0x5B, 0xa0);
  SPI_PMW_SendByte(0x4E, 0xA8);
  SPI_PMW_SendByte(0x5A, 0x50);
  SPI_PMW_SendByte(0x40, 0x80);

}

uint16_t PMW3901_ReadID(void)
{
    uint16_t FLASH_ID;
    uint8_t temp0,temp1;


//    sFLASH_CS_LOW();

//    SPI_PMW_ReadByte(W25X_ManufactDeviceID);
//
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);

    temp0 = SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
    temp1 = SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
    printf("%x %x\n", temp0,temp1);
//    sFLASH_CS_HIGH();

    FLASH_ID = (temp0 << 8) | temp1;

    return FLASH_ID;
}

uint16_t PMW3901_dIpihc(void)
{
    uint16_t FLASH_ID;
    uint8_t temp0,temp1;


    sFLASH_CS_LOW();

//    SPI_PMW_ReadByte(W25X_ManufactDeviceID);
//
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);

    temp0 = SPI_PMW_ReadByte(0x5f);
    temp1 = SPI_PMW_ReadByte(0x5f);

    sFLASH_CS_HIGH();

    FLASH_ID = (temp0 << 8) | temp1;

    return FLASH_ID;
}

//模块初始化
void PMWinit(void) {
    sFLASH_CS_LOW();

    sFLASH_CS_HIGH();
	HAL_Delay(10);
    sFLASH_CS_LOW();
	HAL_Delay(10);
	SPI_PMW_SendByte(0x3A,0x5A);
    SPI_PMW_SendByte(0x3A,0x5A);
	HAL_Delay(10);

//    sFLASH_CS_LOW();
//	chipId = SPI_PMW_ReadByte(0x00);
//    printf("%x-----------\n",chipId);
//    chipId = SPI_PMW_ReadByte(0x00);
//    printf("%x-----------\n",chipId);
//    chipId = SPI_PMW_ReadByte(0x00);
//    printf("%x-----------\n",chipId);
//    chipId = SPI_PMW_ReadByte(0x00);
//    printf("%x-----------\n",chipId);
//	HAL_Delay(10);
    chipId=PMW3901_ReadID();
    printf("%x-----------\n",chipId);
    HAL_Delay(30);

//    printf("%x-----------\n",chipId);
//	while(1)
//	{
//		SPI_PMW_SendByte(0x3A,0x5A);
//		HAL_Delay(10000);
//		chipId = SPI_PMW_ReadByte(0x00);
//		HAL_Delay(30000);
//		dIpihc = SPI_PMW_ReadByte(0x5F);
//		HAL_Delay(10000);
//	}

    dIpihc = PMW3901_dIpihc();
//    printf("%x-----------\n",dIpihc);
//    dIpihc = SPI_PMW_ReadByte(0x5F);
//    printf("%x-----------\n",dIpihc);
//    dIpihc = SPI_PMW_ReadByte(0x5F);
//    printf("%x-----------\n",dIpihc);
//    dIpihc = SPI_PMW_ReadByte(0x5F);
//    printf("%x-----------\n",dIpihc);
//    dIpihc = SPI_PMW_ReadByte(0x5F);
    printf("%x-----------\n",dIpihc);

//    printf("%d-----------\n",dIpihc);
	SPI_PMW_ReadByte(0x02);
	SPI_PMW_ReadByte(0x03);
	SPI_PMW_ReadByte(0x04);
	SPI_PMW_ReadByte(0x05);
	SPI_PMW_ReadByte(0x06);

	HAL_Delay(10);
	initRegisters();
    printf("chushihua wancheng1\n");
}

void readMotionCount(int16_t *deltax, int16_t *deltay){


    sFLASH_CS_LOW();
    SPI_PMW_ReadByte(0x02);
	*deltax  =  ((int16_t)SPI_PMW_ReadByte(0x04) << 8) | SPI_PMW_ReadByte(0x03);
//    sFLASH_CS_LOW();
//    SPI_PMW_ReadByte(0x02);
//    HAL_Delay(10);
	*deltay  =  ((int16_t)SPI_PMW_ReadByte(0x06) << 8) | SPI_PMW_ReadByte(0x05);
    sFLASH_CS_HIGH();
}

uint16_t readMotionCount2(){


    uint16_t FLASH_ID;
    uint8_t temp0,temp1;


    sFLASH_CS_LOW();

//    SPI_PMW_ReadByte(W25X_ManufactDeviceID);
//
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);
//    SPI_PMW_ReadByte(sFLASH_DUMMY_BYTE);

    temp0 = SPI_PMW_ReadByte(0x06);
    temp1 = SPI_PMW_ReadByte(0x05);

    sFLASH_CS_HIGH();

    FLASH_ID = (temp0 << 8) | temp1;

    return (uint8_t)FLASH_ID;



}

