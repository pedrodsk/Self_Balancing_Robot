//Mudar prioridade da Thread
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
TaskHandle_t xTask2Handle = NULL;    
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

        i++;
        if (i == 4)
        {
          vTaskPrioritySet( xTask2Handle, 3);
          i=0;
        }
    }
}


void app_main()
{
    xTaskCreate(&thread1, "thread1", 2048, NULL, 2, NULL);
    xTaskCreate(&thread2, "thread2", 2048, NULL, 1, &xTask2Handle);
   // printf(" Escalonador iniciado\n");

}
