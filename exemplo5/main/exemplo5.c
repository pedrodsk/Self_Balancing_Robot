#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/queue.h"

QueueHandle_t xQueue; //identificador da fila

void vSenderTask( void *pvParameters )
{
  int32_t *lValueToSend;
  BaseType_t xStatus;
  lValueToSend = ( int32_t * ) pvParameters;

  while(1)
  {
    vTaskDelay(1000 / portTICK_RATE_MS);
    xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );
    
    if( xStatus != pdPASS )
    {
      printf( "A fila esta cheia!\r\n" );
    }
  }
}
/*-----------------------------------------------------------*/

static void vReceiverTask( void *pvParameters )
{
  int32_t lReceivedValue;
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS( 1500 );

  while(1)
  {
    if( uxQueueMessagesWaiting( xQueue ) != 0 )
    {
      printf( "A fila esta vazia!\r\n" );
    }
    xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );

    if( xStatus == pdPASS )
    {
      printf( "Valor recebido = %i\r\n", lReceivedValue );
    }
    else
    {
      printf( "Nenhum valor foi recebido da fila.\r\n" );
    }
  }
}


void app_main()
{
  xQueue = xQueueCreate( 1, sizeof( int32_t ) );

  if( xQueue != NULL )
  {
    xTaskCreate( vSenderTask, "Sender1", 2048, ( void * ) 100, 1, NULL );
    xTaskCreate( vSenderTask, "Sender2", 2048, ( void * ) 200, 1, NULL );
    xTaskCreate( vSenderTask, "Sender3", 2048, ( void * ) 300, 1, NULL );
    xTaskCreate( vSenderTask, "Sender4", 2048, ( void * ) 400, 1, NULL );
    xTaskCreate( vReceiverTask, "Receiver", 2048, NULL, 2, NULL );
    printf(" Escalonador iniciado\n");

    
  }
  else
  {
  }

}
