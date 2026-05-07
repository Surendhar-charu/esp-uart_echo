#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h" 
#include "string.h"
/* UART Echo Example */

static void echo_task(void *arg)
{
    /* Configure UART parameters */
    const uart_port_t uart_num = UART_NUM_2;
    uart_config_t uart_config = {
        .baud_rate = 115200,  
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    }; 

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));


    /* Set UART pins */
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));  // ✅ Fixed macro

    const int uart_buffer_size = (1024*2);
    QueueHandle_t uart_queue;
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, \
                                            uart_buffer_size, pdMS_TO_TICKS(10), &uart_queue, 0));  // ✅ Fixed macro
    
    
    uint8_t data[128];

    while(1)
    {
    int len = uart_read_bytes(uart_num, data, 128-1, 10);
    uart_write_bytes(uart_num, (const char*)data, len);

    if (len>0) {
        data[len] = '\0';
        ESP_LOGI("UART TEST", "Recv str: %s", (char*)data);
    }
}


}

void app_main(void)
{
    xTaskCreate(echo_task, "uart_echo_task", CONFIG_EXAMPLE_TASK_STACK_SIZE, NULL, 10, NULL);
}
