#ifdef TEST_H
#define TEST_H

#endif


#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include "ds1307_for_stm32_hal.h"



/*function */
void test_init();
void ds1307_test();
void buzzer_test();
void led_test();
void button_test();
void mpu6050_test();

