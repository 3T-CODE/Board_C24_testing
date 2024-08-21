#include "test.h"
#include "mpu6050.h" 
#include "stm32f1xx_hal_uart.h"
#include "usart.h"

#ifdef __cplusplus
extern "C"{
#endif


/*Initial peripherals*/
/*Put it before testting*/
void test_init()
{
    /*Initial for buzzer*/
    HAL_TIM_PWM_Start(&htim2 , TIM_CHANNEL_2);

    /*Initial for ds1307 */
    DS1307_Init(&hi2c2);
    DS1307_SetTimeZone(+8, 00);
    DS1307_SetDate(18);
    DS1307_SetMonth(8);
   	DS1307_SetYear(2024);
   	DS1307_SetDayOfWeek(7);
   	DS1307_SetHour(1);
   	DS1307_SetMinute(1);
   	DS1307_SetSecond(30);

    /*Initial for mpu6050*/

}
/*Start_testing*/


/*;*/

void buzzer_test()
{

    TIM2 -> CCR1 = 50;

}



void led_test()
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

void button_test()
{
    uint8_t a,b;
	  a = HAL_GPIO_ReadPin(GPIOB , GPIO_PIN_8);
    b = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
    char buffer[50];
    sprintf(buffer , "State Button 1 = %d, State Button 2 = %d \n\r" , a , b);
    HAL_UART_Transmit(&huart1 ,buffer ,50 ,100);

}


void ds1307_test()
{
    /*Ds1307*/
    char ds_buffer[100];
    uint8_t date = DS1307_GetDate();
   	uint8_t month = DS1307_GetMonth();
   	uint16_t year = DS1307_GetYear();
   	uint8_t dow = DS1307_GetDayOfWeek();
   	uint8_t hour = DS1307_GetHour();
   	uint8_t minute = DS1307_GetMinute();
   	uint8_t second = DS1307_GetSecond();
   	int8_t zone_hr = DS1307_GetTimeZoneHour();
   	uint8_t zone_min = DS1307_GetTimeZoneMin();
		sprintf(ds_buffer, "ISO8601 FORMAT: %04d-%02d-%02dT%02d:%02d:%02d%+03d:%02d \n \r",
				    year, month, date, hour, minute, second, zone_hr, zone_min);
		/* May show warning below. Ignore and proceed. */
    
	  HAL_UART_Transmit(&huart1, ds_buffer, strlen(ds_buffer), 1000);
}

void mpu6050_test()
{

    MPU6050_t MPU6050;
    char mpu_buffer[100] ;
    while (MPU6050_Init(&hi2c1) == 1); 
    MPU6050_Read_All(&hi2c1, &MPU6050);
    float Ax , Ay , Az ,Gx ,Gy ,Gz ;
    Ax = MPU6050.Ax;
    Ay = MPU6050.Ay;
    Az = MPU6050.Az;
    Gx = MPU6050.Gx;
    Gy = MPU6050.Gy;
    Gz = MPU6050.Gz;
    sprintf(mpu_buffer,"Ax = %.1f , Ay = %.1f , Az = %.1f , Gx = %.1f , Gy = %.1f , Gz = %.1f \n\r" , Ax , Ay , Az , Gx ,Gy , Gz);
    HAL_UART_Transmit(&huart1, mpu_buffer , strlen(mpu_buffer), 1000);

}
