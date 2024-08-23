#include <stdint.h>
#include <stdio.h>
#include "driver/uart.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "hal/gpio_types.h"
#include "hal/uart_types.h"
#include "soc/clk_tree_defs.h"
#include <string.h>
#include "driver/gpio.h"
#include "esp_log.h"

static const int RX_BUFFER_SIZE = 2048 ;

/*User define*/
#define TX GPIO_NUM_1
#define RX GPIO_NUM_3
#define UART UART_NUM_0
#define UART1 UART_NUM_1

/*User function*/

void uart_init();
void gpio_init();


void app_main(void)
{
    uart_init();
    gpio_init();

    while(1)
    {
        gpio_set_level(2, 1);
        char  len [RX_BUFFER_SIZE];
        memset(len , 0,  sizeof(len) );
        uart_read_bytes(UART1, (uint8_t * )len , RX_BUFFER_SIZE, pdMS_TO_TICKS(50));
        printf("%s",len);
    }
}




void uart_init()
{
    const uart_config_t uart_config =
    {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(UART , RX_BUFFER_SIZE *2 , 0 ,0 ,NULL ,0);
    uart_param_config(UART, &uart_config);
    uart_set_pin(UART, TX, RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uart_driver_install(UART1 , RX_BUFFER_SIZE *2 , 0 ,0 ,NULL ,0);
    uart_param_config(UART1, &uart_config);
    uart_set_pin(UART1, 4, 5, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);


}

void gpio_init()
{
    gpio_reset_pin(2);
    gpio_set_direction(2,GPIO_MODE_OUTPUT);
}



