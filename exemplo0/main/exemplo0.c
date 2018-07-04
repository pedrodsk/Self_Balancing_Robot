//#PARALELISMO
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

void thread1(void *pvParameter)
{

 while(1)
 {
   printf("Thread1\n");
   vTaskDelay(pdMS_TO_TICKS(1000));
 }
}

void thread2(void *pvParameter)
{
  
  while(1) {
    printf("Thread2\n");
    vTaskDelay(2000 / portTICK_RATE_MS);
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
    vTaskDelay(4000 / portTICK_RATE_MS);
  }
}


void app_main()
{
  xTaskCreate(&thread1, "thread1", 2048, NULL, 1, NULL);
  xTaskCreate(&thread2, "thread2", 2048, NULL, 1, NULL);
  xTaskCreate(&thread3, "thread3", 2048, NULL, 1, NULL);
  xTaskCreate(&thread4, "thread4", 2048, NULL, 1, NULL);

  printf(" Escalonador iniciado\n"); 
  vTaskStartScheduler();
}
