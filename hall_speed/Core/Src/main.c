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

#include "retarget.h"
#include "bsp_bldc.h"
#include "bsp_hall.h"
#include "math.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define TIMECNT   800

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

float MotorSpeed  = 0.0f ;// 电机转速,这里是占空比,

_Bool isTimeUp    = 0;     // 计时标记
uint32_t timeTick = 0;   // 计时标记
extern MotorSta_Typedef Motor_State; // 电机使能状态
extern MotorDir_Typedef Motor_Dir;  // 电机方向 ,顺时针
extern float PWM_Duty;        // 25%占空比

extern MotorDir_Typedef RT_hallDir; // 霍尔顺序得到的电机转动方向
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

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
  MX_GPIO_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  RetargetInit(&huart1);
  printf("\r\nhall speed process start \n");
  printf(" <- 直流无刷电机基础驱动_HALL传感器测速 -> \n");
  printf(" <- 定时器的霍尔传感器接口功能,在CH1的比较器里面保存有两次边沿之间的\n");
  printf("计数值,根据这些计数值就可以测量出电机转速 -> \n");
  printf("正负代表方向 -> \n");
  timeTick = TIMECNT;
//    MotorSpeed = 0.15f;
//    BLDCMotor_SetSpeed(MotorSpeed);
//    BLDCMotor_Start();
//    printf("按键KEY1启动电机\n");
    /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if( isTimeUp )
      {
          uint32_t tmpCC = 0;
          if(RT_hallcnt == 0) // 避免除数为0
          {
              Speed_hz = 0;
          }
          else
          {
              tmpCC = RT_hallcomp / RT_hallcnt; // tmpCC:两次捕获之间的捕获值,
              Speed_hz = (float)HALL_TIM_FREQ/(float)(tmpCC);
          }
          RT_hallcomp = 0;
          RT_hallcnt  = 0;
          /* 霍尔信号的频率,转速rps,转速rpm */
          if(RT_hallDir == MOTOR_DIR_CW)
              Speed_hz = fabs(Speed_hz);
          else
              Speed_hz = -fabs(Speed_hz);
          /* 未做任何滤波的速度值 */
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
    __HAL_RCC_PWR_CLK_ENABLE();                                     // 使能PWR时钟
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  // 设置调压器输出电压级别1
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // 外部晶振，8MHz
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;                  // 打开HSE
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;                  // 打开PLL
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;           // PLL时钟源选择HSE
    RCC_OscInitStruct.PLL.PLLM = 8;                                 // 8分频MHz
    RCC_OscInitStruct.PLL.PLLN = 336;                               // 336倍频
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     // 2分频，得到168MHz主时钟
    RCC_OscInitStruct.PLL.PLLQ = 7;                                 // USB/SDIO/随机数产生器等的主PLL分频系数
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;     // 系统时钟：168MHz
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;             // AHB时钟： 168MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1时钟：42MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2时钟：84MHz
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
    HAL_RCC_EnableCSS();                                            // 使能CSS功能，优先使用外部晶振，内部时钟源为备用
    // HAL_RCC_GetHCLKFreq()/1000    1ms中断一次
    // HAL_RCC_GetHCLKFreq()/100000	 10us中断一次
    // HAL_RCC_GetHCLKFreq()/1000000 1us中断一次
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);               // 配置并启动系统滴答定时器
    /* 系统滴答定时器时钟源 */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    /* 系统滴答定时器中断优先级配置 */
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
