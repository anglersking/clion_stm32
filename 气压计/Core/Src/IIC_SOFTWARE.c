/***********************************************************************
 * desined by ZINС��
 * @param[in] 
 * @param[out] 
 * @return     
 	 �Ա���ַ��https://shop297229812.taobao.com/shop/view_shop.htm?mytmenu=mdianpu&user_number_id=2419305772
 **********************************************************************/
#include "i2c.h"

#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1

/******************************************************************************
 * ��������: I2c_delay
 * ��������: I2c ��ʱ����
 * ��ڲ���: ��
 ******************************************************************************/
#define I2c_delay()  {\
    volatile unsigned char i = 1;\
    while (i)\
        i--;\
}

/******************************************************************************
 * ��������: I2c_Init
 * ��������: I2c  GPIO��ʼ��
 * ��ڲ���: ��
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
// * ��������: I2c_SendByte
// * ��������: I2c  ����һ���ֽ�����
// * ��ڲ���: byte  ���͵�����
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
 *��������:	i2cWrite
 *��������:	д��ָ���豸 ָ���Ĵ���һ���ֽ�
 *��ڲ����� addr Ŀ���豸��ַ
 *		     reg   �Ĵ�����ַ
 *		     data ���������ݽ�Ҫ��ŵĵ�ַ
 *******************************************************************************/



