/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include "ds1307_for_stm32_hal.h"
#include "mpu6050.h" 
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
const char *DAYS_OF_WEEK[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
MPU6050_t MPU6050;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void test_led();
void test_ds1307();
void button_test();
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
    DS1307_Init(&hi2c1);
  /* To test leap year correction. */
   	DS1307_SetTimeZone(+8, 00);
   	DS1307_SetDate(29);
   	DS1307_SetMonth(2);
   	DS1307_SetYear(2024);
   	DS1307_SetDayOfWeek(4);
   	DS1307_SetHour(23);
   	DS1307_SetMinute(59);
   	DS1307_SetSecond(30);
    
    HAL_TIM_PWM_Start(&htim2 , TIM_CHANNEL_1);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  while (MPU6050_Init(&hi2c2) == 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
 	 	  HAL_Delay (100);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*Test code*/
void test_led()
{
    HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 ,SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 ,SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 ,SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,SET);
    HAL_Delay(100);

}

void test_ds1307()
{
    /*Ds1307*/
    uint8_t date = DS1307_GetDate();
   	uint8_t month = DS1307_GetMonth();
   	uint16_t year = DS1307_GetYear();
   	uint8_t dow = DS1307_GetDayOfWeek();
   	uint8_t hour = DS1307_GetHour();
   	uint8_t minute = DS1307_GetMinute();
   	uint8_t second = DS1307_GetSecond();
   	int8_t zone_hr = DS1307_GetTimeZoneHour();
   	uint8_t zone_min = DS1307_GetTimeZoneMin();
   	char buffer[100] = { 0 };
		sprintf(buffer, "ISO8601 FORMAT: %04d-%02d-%02dT%02d:%02d:%02d%+03d:%02d \n \r",
				year, month, date, hour, minute, second, zone_hr, zone_min);
		/* May show warning below. Ignore and proceed. */
	  HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 1000);
}

void button_test()
{
    uint8_t a,b;
	  a = HAL_GPIO_ReadPin(GPIOB , GPIO_PIN_8);
    b = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
    char buffer[50];
    sprintf(buffer , "State Button 1 = %d, State Button 2 = %d \n\r" , a , b);
    HAL_UART_Transmit(&huart1 ,buffer ,50 ,100);

}

void buzzer_test()
{
    TIM2 -> CCR1 = 300;

}

void mpu6050_test()
{
    MPU6050_Read_All(&hi2c2, &MPU6050);
    float Ax , Ay , Az ,Gx ,Gy ,Gz ;
    Ax = MPU6050.Ax;
    Ay = MPU6050.Ay;
    Az = MPU6050.Az;
    Gx = MPU6050.Gx;
    Gy = MPU6050.Gy;
    Gz = MPU6050.Gz;


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
