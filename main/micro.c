#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_err.h"
#include "esp_mac.h"

char buffer[128] = "hello world!";
uint8_t mac[8];

void app_main(void)
{
    esp_read_mac(mac, ESP_MAC_IEEE802154);
    for(;;){
        printf("%s, MAC: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", buffer, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], mac[6], mac[7]);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("bye\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
