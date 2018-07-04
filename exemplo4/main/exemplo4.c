// Criação de Thread assíncrona.
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
TaskHandle_t xTask2Handle = NULL;
TaskHandle_t xTask1Handle = NULL;    
int i=0;

void thread1(void *pvParameter)
{

 while(1)
 {
   printf("Thread1\n");

   vTaskDelete( xTask1Handle);
 }
}

void thread2(void *pvParameter)
{

  while(1) {
    printf("Thread2\n");
    vTaskDelay(3000 / portTICK_RATE_MS);

    i++;
    if (i == 4)
    {
      xTaskCreate(&thread1, "thread1", 2048, NULL, 2, &xTask1Handle);
      vTaskDelete( xTask2Handle);

      i=0;
    }
  }
}


void app_main()
{

  xTaskCreate(&thread2, "thread2", 2048, NULL, 1, &xTask2Handle);
  printf(" Escalonador iniciado\n");

}
