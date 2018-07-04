
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

static const char *pcTextoTask1 = "Task 1\r\n";
static const char *pcTextoTask2 = "Task 2\r\n";
static const char *pcTextoTask3 = "Task 3\r\n";
static const char *pcTextoTask4 = "Task 4\r\n";


void vTaskStrings(void *pvParametros)
{
  char *pcNomeTask;
  pcNomeTask = ( char * ) pvParametros;

  while(1)
  {
   printf(pcNomeTask);
   vTaskDelay(3000 / portTICK_RATE_MS);
 }
}


void app_main()
{
  xTaskCreate( vTaskStrings, "Task 1", 2048, (void*)pcTextoTask1, 0, NULL );
  xTaskCreate( vTaskStrings, "Task 2", 2048, (void*)pcTextoTask2, 0, NULL );
  xTaskCreate( vTaskStrings, "Task 3", 2048, (void*)pcTextoTask3, 0, NULL );
  xTaskCreate( vTaskStrings, "Task 4", 2048, (void*)pcTextoTask4, 0, NULL );
  printf(" Escalonador iniciado\n");
}
