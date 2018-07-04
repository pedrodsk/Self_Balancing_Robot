    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
    int i=0;

void thread1(void *pvParameter)
{

   while(1)
   {
       printf("Thread1\n");
       vTaskDelay(3000 / portTICK_RATE_MS);
   }
}

void thread2(void *pvParameter)
{

    while(1) {
        printf("Thread2\n");
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}
void thread3(void *pvParameter)
{

   while(1)
   {
       printf("Thread3\n");
       vTaskDelay(3000 / portTICK_RATE_MS);
   }
}

void thread4(void *pvParameter)
{

    while(1) {
        printf("Thread4\n");
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}


void app_main()
{
    xTaskCreate(&thread1, "thread1", 2048, NULL, 3, NULL);
    xTaskCreate(&thread2, "thread2", 2048, NULL, 1, NULL);
    xTaskCreate(&thread3, "thread3", 2048, NULL, 2, NULL);
    xTaskCreate(&thread4, "thread4", 2048, NULL, 4, NULL);
    i++;
    printf(" Escalonador iniciado %i\n",i);
}
