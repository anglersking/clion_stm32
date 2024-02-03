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
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "retarget.h"
#include "pmw3901.h"
#include "w25qxx.h"
#include "SPL06_001.h"
#include <math.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
float temperature;//读取的温度值 单位℃摄氏度
float presure;//温度补偿后的气压值 单位mpar 毫帕
typedef uint32_t  u32;

int32_t baro_height;//解算后的气压高度值，单位mm毫米

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t RD_Buffer[5000] = {0};
uint8_t WR_Buffer[5000] = "SPI FLASH WRITE TEST\n";
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
    uint16_t FLASH_ID = 0;
    uint32_t i;
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
  MX_USART1_UART_Init();
  MX_SPI2_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  RetargetInit(&huart1);
//    MX_SPI1_Init();



    printf("init uart over\n");
    PMWinit();
    printf("chushihua");
    int16_t deltax, deltay;
    FLASH_ID = sFLASH_ReadID();

    printf("FLASH_ID = %x\n",FLASH_ID);
    if(spl0601_init() != 0)
    {
        printf("SPL06 init fail!\r\n\r\n\r\n");
//        while(1);
    } else{
        printf("SPL06 init suc!\r\n\r\n\r\n");
    }
//    temperature = user_spl0601_get_temperature();
//    presure = user_spl0601_get_presure();
//    baro_height = (uint32_t)((102000.0f	- presure) * 78.740f);  //?1mpar??????θ???78.740mm
//    float altitude = 44330.0 * (1 - pow(presure / 101325.0, 0.190284));

    /*???????*/
//    sFLASH_EraseSector(4096*0);
//    sFLASH_EraseSector(4096*1);
//    sFLASH_ReadBuffer(RD_Buffer,0,4096);
//    printf("????????\n");
//    for(i=0; i<4096; i++)
//    {
//        printf("%x ",RD_Buffer[i]);
//    }
//    printf("?????????\n");


//	/*????д????1*/
    //sFLASH_WritePage(WR_Buffer,0, 20);
    //sFLASH_ReadBuffer(RD_Buffer,0,20);
    //printf("READ DATA: %s\n",RD_Buffer);

    /*????д????2*/
//    for(i=0; i<4096; i++)
//    {
//        WR_Buffer[i] = 0x55;
//    }
//    sFLASH_WriteBuffer(WR_Buffer,4090, 1000);
//    sFLASH_ReadBuffer(RD_Buffer,4090,1000);
//    for(i=0; i<1000; i++)
//    {
//        printf("%x ",RD_Buffer[i]);
//    }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {




      temperature = user_spl0601_get_temperature();
      presure = user_spl0601_get_presure();
      baro_height = (int32_t)fabs(((102000.0f	- presure) * 78.740f));  //?1mpar??????θ???78.740mm
      printf("气压计内部温度为: %.1f\r\n",temperature);//发送海拔高度数据到串口助手
      printf("温度补偿后的气压值为: %.1fmpar\r\n",presure);//发送海拔高度数据到串口助手
      printf("当前的海拔高度为：%dmm\r\n", baro_height);//发送海拔高度数据到串口助手
//      printf("testtest=%f    %f    %d\n",(102000.0f	- 103541.5),(102000.0f	- 103541.5)*78.740f,(uint32_t)((102000.0f	- 103541.5) * 78.740f));
      printf("\r\n\r\n\r\n");


//      printf("%f,%f,%f\n",(102000.0f	- presure),78.740f,(uint32_t)((102000.0f	- presure) * 78.740f));

//      HAL_Delay(10);

      HAL_Delay(1000);
//      readMotionCount(&deltax, &deltay);
//
//      printf("xx%d ,yy%d\n",deltax,deltay);
//      HAL_Delay(100);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
