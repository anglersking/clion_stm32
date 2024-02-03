/***********************************************************************
 * desined by ZIN小店
 * @param[in] 
 * @param[out] 
 * @return     
 	 淘宝地址：https://shop297229812.taobao.com/shop/view_shop.htm?mytmenu=mdianpu&user_number_id=2419305772
 **********************************************************************/
#include "i2c.h"

#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1

/******************************************************************************
 * 函数名称: I2c_delay
 * 函数功能: I2c 延时函数
 * 入口参数: 无
 ******************************************************************************/
#define I2c_delay()  {\
    volatile unsigned char i = 1;\
    while (i)\
        i--;\
}

/******************************************************************************
 * 函数名称: I2c_Init
 * 函数功能: I2c  GPIO初始化
 * 入口参数: 无
 ******************************************************************************/
// void IIC_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStrucSUCCESS;
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  , ENABLE);
//
//    GPIO_InitStrucSUCCESS.GPIO_Pin = SCL_PIN | SDA_PIN;
//    GPIO_InitStrucSUCCESS.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStrucSUCCESS.GPIO_Mode = GPIO_Mode_Out_OD;
//    GPIO_Init(IIC_GPIO, &GPIO_InitStrucSUCCESS);
//}

///******************************************************************************
// * 函数名称: I2c_SendByte
// * 函数功能: I2c  发送一个字节数据
// * 入口参数: byte  发送的数据
// ******************************************************************************/
//
//
//uint8_t IIC_Read_1Byte(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t *REG_data)
//{
//    if (HAL_I2C_IsDeviceReady(&hi2c1, SlaveAddress << 1, 1, 1000) != HAL_OK)
//        return FAILED;
//
//    if (HAL_I2C_Mem_Write(&hi2c1, SlaveAddress << 1, REG_Address, I2C_MEMADD_SIZE_8BIT, NULL, 0, 1000) != HAL_OK)
//    {
//        HAL_I2C_DeInit(&hi2c1);
//        return FAILED;
//    }
//
//    if (HAL_I2C_Mem_Read(&hi2c1, (SlaveAddress << 1) | 1, REG_Address, I2C_MEMADD_SIZE_8BIT, REG_data, 1, 1000) != HAL_OK)
//    {
//        HAL_I2C_DeInit(&hi2c1);
//        return FAILED;
//    }
//
//    return SUCCESS;
//}
/*****************************************************************************
 *函数名称:	i2cWrite
 *函数功能:	写入指定设备 指定寄存器一个字节
 *入口参数： addr 目标设备地址
 *		     reg   寄存器地址
 *		     data 读出的数据将要存放的地址
 *******************************************************************************/



