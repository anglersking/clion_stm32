//
//#include "soft_pmw3901.h"
//#include "stm32f4xx_hal.h"
//#include "retarget.h"
////pmw3901.h文件中替换IO脚位
////延时函数可以自己写，确保延时准确代入此页	HAL_Delay(10);中
////这里延时100000代表10ms
//uint16_t chipId=0,dIpihc=0;
////光流模块写数据函数
////输入location 地址  byte 数据
//uint8_t SPI_PMW_SendByte(uint8_t location ,uint8_t byte )
//{
//    uint8_t i;
////    uint8_t rxData = 0;
//    location |= 0x80u;
//    SPI_NCS_0;
//
//    HAL_Delay(1);
//    SPI_SCK_1;
//    HAL_Delay(1);
//    for(i = 0; i < 16; i++)
//    {
//        SPI_SCK_0;
//        HAL_Delay(1);
//
//        if(i<8)
//        {
//            if(location & 0x80){
//                SPI_MOSI_1;
//            }else{
//                SPI_MOSI_0;
//            }
//            location<<=1;
//        }
//        else
//        {
//            if(byte & 0x80){
//                SPI_MOSI_1;
//            }else{
//                SPI_MOSI_0;
//            }
//            byte<<=1;
//        }
//        SPI_SCK_1;
////			rxData <<= 1;
//
////			if(SPI_READ_MISO){
////						rxData |= 0x01;
////				}
//        HAL_Delay(1);
//    }
//    SPI_NCS_1;
//
////    SPI_ReadWriteByte(location);
////    SPI_ReadWriteByte(byte);
//    return 0;
//}
////光流模块读数据函数
////byte 地址
//uint8_t SPI_PMW_ReadByte(uint8_t byte)
//{
//    uint8_t  test=0,i,send_tx=0;
//    byte &= ~0x80u;
//    SPI_NCS_0;
//    HAL_Delay(1);
//    SPI_SCK_1;
//    HAL_Delay(1);
//    for(i = 0; i < 16; i++)
//    {
//        SPI_SCK_0;
//        HAL_Delay(1);
//        if(i<8)
//        {
//            if(byte & 0x80){
//                SPI_MOSI_1;
//            }else{
//                SPI_MOSI_0;
//            }
//            byte<<=1;
//        }
//        else
//        {
//            if(send_tx & 0x80){
//                SPI_MOSI_1;
//            }else{
//                SPI_MOSI_0;
//            }
//            send_tx<<=1;
//        }
//        SPI_SCK_1;
//        test <<= 1;
//        if(SPI_READ_MISO==1){
//            test |= 0x01;
//        }
//        HAL_Delay(1);
//
//        if(i==7)
//        {
//            HAL_Delay(45);
//        }
//        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
//    }
//    SPI_NCS_1;
////    test = SPI_ReadWriteByte(byte);
////    HAL_Delay(35);
////    test = SPI_ReadWriteByte(0);
//    return test;
//}
////寄存器初始化
//void initRegisters()
//{
//    SPI_PMW_SendByte(0x7F, 0x00);
//    SPI_PMW_SendByte(0x61, 0xAD);
//    SPI_PMW_SendByte(0x7F, 0x03);
//    SPI_PMW_SendByte(0x40, 0x00);
//    SPI_PMW_SendByte(0x7F, 0x05);
//    SPI_PMW_SendByte(0x41, 0xB3);
//    SPI_PMW_SendByte(0x43, 0xF1);
//    SPI_PMW_SendByte(0x45, 0x14);
//    SPI_PMW_SendByte(0x5B, 0x32);
//    SPI_PMW_SendByte(0x5F, 0x34);
//    SPI_PMW_SendByte(0x7B, 0x08);
//    SPI_PMW_SendByte(0x7F, 0x06);
//    SPI_PMW_SendByte(0x44, 0x1B);
//    SPI_PMW_SendByte(0x40, 0xBF);
//    SPI_PMW_SendByte(0x4E, 0x3F);
//    SPI_PMW_SendByte(0x7F, 0x08);
//    SPI_PMW_SendByte(0x65, 0x20);
//    SPI_PMW_SendByte(0x6A, 0x18);
//    SPI_PMW_SendByte(0x7F, 0x09);
//    SPI_PMW_SendByte(0x4F, 0xAF);
//    SPI_PMW_SendByte(0x5F, 0x40);
//    SPI_PMW_SendByte(0x48, 0x80);
//    SPI_PMW_SendByte(0x49, 0x80);
//    SPI_PMW_SendByte(0x57, 0x77);
//    SPI_PMW_SendByte(0x60, 0x78);
//    SPI_PMW_SendByte(0x61, 0x78);
//    SPI_PMW_SendByte(0x62, 0x08);
//    SPI_PMW_SendByte(0x63, 0x50);
//    SPI_PMW_SendByte(0x7F, 0x0A);
//    SPI_PMW_SendByte(0x45, 0x60);
//    SPI_PMW_SendByte(0x7F, 0x00);
//    SPI_PMW_SendByte(0x4D, 0x11);
//    SPI_PMW_SendByte(0x55, 0x80);
//    SPI_PMW_SendByte(0x74, 0x1F);
//    SPI_PMW_SendByte(0x75, 0x1F);
//    SPI_PMW_SendByte(0x4A, 0x78);
//    SPI_PMW_SendByte(0x4B, 0x78);
//    SPI_PMW_SendByte(0x44, 0x08);
//    SPI_PMW_SendByte(0x45, 0x50);
//    SPI_PMW_SendByte(0x64, 0xFF);
//    SPI_PMW_SendByte(0x65, 0x1F);
//    SPI_PMW_SendByte(0x7F, 0x14);
//    SPI_PMW_SendByte(0x65, 0x60);
//    SPI_PMW_SendByte(0x66, 0x08);
//    SPI_PMW_SendByte(0x63, 0x78);
//    SPI_PMW_SendByte(0x7F, 0x15);
//    SPI_PMW_SendByte(0x48, 0x58);
//    SPI_PMW_SendByte(0x7F, 0x07);
//    SPI_PMW_SendByte(0x41, 0x0D);
//    SPI_PMW_SendByte(0x43, 0x14);
//    SPI_PMW_SendByte(0x4B, 0x0E);
//    SPI_PMW_SendByte(0x45, 0x0F);
//    SPI_PMW_SendByte(0x44, 0x42);
//    SPI_PMW_SendByte(0x4C, 0x80);
//    SPI_PMW_SendByte(0x7F, 0x10);
//    SPI_PMW_SendByte(0x5B, 0x02);
//    SPI_PMW_SendByte(0x7F, 0x07);
//    SPI_PMW_SendByte(0x40, 0x41);
//    SPI_PMW_SendByte(0x70, 0x00);
//
//    HAL_Delay(10);
//    SPI_PMW_SendByte(0x32, 0x44);
//    SPI_PMW_SendByte(0x7F, 0x07);
//    SPI_PMW_SendByte(0x40, 0x40);
//    SPI_PMW_SendByte(0x7F, 0x06);
//    SPI_PMW_SendByte(0x62, 0xf0);
//    SPI_PMW_SendByte(0x63, 0x00);
//    SPI_PMW_SendByte(0x7F, 0x0D);
//    SPI_PMW_SendByte(0x48, 0xC0);
//    SPI_PMW_SendByte(0x6F, 0xd5);
//    SPI_PMW_SendByte(0x7F, 0x00);
//    SPI_PMW_SendByte(0x5B, 0xa0);
//    SPI_PMW_SendByte(0x4E, 0xA8);
//    SPI_PMW_SendByte(0x5A, 0x50);
//    SPI_PMW_SendByte(0x40, 0x80);
//
//}
////模块初始化
//void PMWinit(void) {
//    SPI_NCS_1;
//    HAL_Delay(10);
//    SPI_NCS_0;
//    HAL_Delay(10);
//    SPI_PMW_SendByte(0x3A,0x5A);
//    HAL_Delay(10);
//    chipId = SPI_PMW_ReadByte(0x00);
//    HAL_Delay(30);
//    printf("%d",chipId);
////	while(1)
////	{
////		SPI_PMW_SendByte(0x3A,0x5A);
////		HAL_Delay(10000);
////		chipId = SPI_PMW_ReadByte(0x00);
////		HAL_Delay(30000);
////		dIpihc = SPI_PMW_ReadByte(0x5F);
////		HAL_Delay(10000);
////	}
//
//    dIpihc = SPI_PMW_ReadByte(0x5F);
//
//
//    SPI_PMW_ReadByte(0x02);
//    SPI_PMW_ReadByte(0x03);
//    SPI_PMW_ReadByte(0x04);
//    SPI_PMW_ReadByte(0x05);
//    SPI_PMW_ReadByte(0x06);
//
//    HAL_Delay(10);
//    initRegisters();
//}
//
//void readMotionCount(int16_t *deltax, int16_t *deltay){
//    SPI_PMW_ReadByte(0x02);
//    *deltax  =  ((int16_t)SPI_PMW_ReadByte(0x04) << 8) | SPI_PMW_ReadByte(0x03);
//    *deltay  =  ((int16_t)SPI_PMW_ReadByte(0x06) << 8) | SPI_PMW_ReadByte(0x05);
//
//}
//
