/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_bldc.h"
#include "bsp_hall.h"
#include "retarget.h"
#include <math.h>
#include "bsp_key.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define TIMECNT   800
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
float MotorSpeed  = 0.0f ;// ???????,?????????,

_Bool isTimeUp    = 0;     // ??????
uint32_t timeTick = 0;   // ??????

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern MotorSta_Typedef Motor_State; // ??????????
extern MotorDir_Typedef Motor_Dir;  // ?????? ,?????
extern float PWM_Duty;        // 25%?????

extern MotorDir_Typedef RT_hallDir; // ????????????????????
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    float Speed_hz  = 0 ;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  KEY_GPIO_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
//    BLDCMOTOR_TIMx_Init();
    HALLSensor_TIMx_Init();
    RetargetInit(&huart1);


    printf("\r\nhall speed process start \n");
    printf(" <- ֱ����ˢ�����������_HALL���������� -> \n");
    printf(" <- ��ʱ���Ļ����������ӿڹ���,��CH1�ıȽ������汣�������α���֮���\n");
    printf("����ֵ,������Щ����ֵ�Ϳ��Բ��������ת�� -> \n");
    printf("���������� -> \n");
    Motor_Dir = MOTOR_DIR_CW;
    timeTick = TIMECNT;
    MotorSpeed = 0.15f;
    BLDCMotor_SetSpeed(MotorSpeed);
    BLDCMotor_Start();
    printf("����KEY1�������\n");
//    MotorSpeed = 0.15f;
//    BLDCMotor_SetSpeed(MotorSpeed);
//    BLDCMotor_Start();
//    printf("����KEY1�������\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      /* ������� */
      if(KEY1_StateRead() == KEY_DOWN)
      {
          MotorSpeed = 0.15f;
          BLDCMotor_SetSpeed(MotorSpeed);
          BLDCMotor_Start();
          printf("����KEY1�������\n");
      }
      /* ������� */
      if(KEY3_StateRead() == KEY_DOWN)
      {
          MotorSpeed += 0.05f;
          BLDCMotor_SetSpeed(MotorSpeed);
          printf("�������\n");
      }
      /* ������� */
      if(KEY4_StateRead() == KEY_DOWN)
      {
          MotorSpeed -= 0.05f;
          BLDCMotor_SetSpeed(MotorSpeed);
          printf("�������\n");
      }
      /* ����������� */
      if(KEY2_StateRead() == KEY_DOWN)
      {
          /* ������ֹͣ,Ȼ�������� */
          if(Motor_State == MOTOR_DISABLE)
          {
              if(Motor_Dir == MOTOR_DIR_CW)
                  Motor_Dir = MOTOR_DIR_CCW;
              else
                  Motor_Dir = MOTOR_DIR_CW;
              printf("��Ҫ�����������\n");
          }
          else
              printf("�����������,������ֹͣ\n");
      }
      /* ɲ��ֹͣ */
      if(KEY5_StateRead() == KEY_DOWN)
      {
          BLDCMotor_braking_LowerShort();
          HAL_Delay(100);// ��100ms, ���ͣ����֮���ȡ��ɲ������
          BLDCMotor_unbraking_LS();
          printf("ɲ��ֹͣ\n");
      }
      if( isTimeUp )
      {
          uint32_t tmpCC = 0;
          if(RT_hallcnt == 0) // �������Ϊ0
          {
              Speed_hz = 0;
          }
          else
          {
              tmpCC = RT_hallcomp / RT_hallcnt; // tmpCC:���β���֮��Ĳ���ֵ,
              Speed_hz = (float)HALL_TIM_FREQ/(float)(tmpCC);
          }
          RT_hallcomp = 0;
          RT_hallcnt  = 0;
          /* �����źŵ�Ƶ��,ת��rps,ת��rpm */
          if(RT_hallDir == MOTOR_DIR_CW)
              Speed_hz = fabs(Speed_hz);
          else
              Speed_hz = -fabs(Speed_hz);
          /* δ���κ��˲����ٶ�ֵ */
          printf("%.3f Hz, %.2f RPS, %.2fRPM\n", Speed_hz, Speed_hz/PPR, (Speed_hz/PPR)*60);

          isTimeUp = 0;
          timeTick = TIMECNT;
      }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    __HAL_RCC_PWR_CLK_ENABLE();                                     // ʹ��PWRʱ��
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  // ���õ�ѹ�������ѹ����1
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // �ⲿ����8MHz
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;                  // ��HSE
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;                  // ��PLL
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;           // PLLʱ��Դѡ��HSE
    RCC_OscInitStruct.PLL.PLLM = 8;                                 // 8��ƵMHz
    RCC_OscInitStruct.PLL.PLLN = 336;                               // 336��Ƶ
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     // 2��Ƶ���õ�168MHz��ʱ��
    RCC_OscInitStruct.PLL.PLLQ = 7;                                 // USB/SDIO/������������ȵ���PLL��Ƶϵ��
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;     // ϵͳʱ�ӣ�168MHz
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;             // AHBʱ�ӣ� 168MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1ʱ�ӣ�42MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2ʱ�ӣ�84MHz
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
    HAL_RCC_EnableCSS();                                            // ʹ��CSS���ܣ�����ʹ���ⲿ�����ڲ�ʱ��ԴΪ����
    // HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ��
    // HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ��
    // HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ��
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);               // ���ò�����ϵͳ�δ�ʱ��
    /* ϵͳ�δ�ʱ��ʱ��Դ */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    /* ϵͳ�δ�ʱ���ж����ȼ����� */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void HAL_SYSTICK_Callback()
{
    if(timeTick != 0)
        timeTick--;
    if(timeTick == 0)
    {
        isTimeUp = 1;
    }

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
