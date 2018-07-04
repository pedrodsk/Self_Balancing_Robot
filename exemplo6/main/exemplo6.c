#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/queue.h"

static void vSenderTask( void *pvParameters );
static void vReceiverTask( void *pvParameters );
QueueHandle_t xQueue;

typedef enum
{
  eSender1,
  eSender2
} DataSource_t;

typedef struct
{
  int ucValue;
  DataSource_t eDataSource;
} Data_t;

static const Data_t xStructsToSend[ 2 ] =
{
  { 100, eSender1 }, 
  { 200, eSender2 }  
};

static void vSenderTask( void *pvParameters )
{
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(550);

  for( ;; )
  {
    vTaskDelay(500 / portTICK_RATE_MS);
    xStatus = xQueueSendToBack( xQueue, pvParameters, xTicksToWait );

    if( xStatus != pdPASS )
    {
      printf( "Não pode enviar para a fila.\r\n" );
    }
  }
}

static void vReceiverTask( void *pvParameters )
{
  Data_t xReceivedStructure;
  BaseType_t xStatus;

  for( ;; )
  {
    xStatus = xQueueReceive( xQueue, &xReceivedStructure, 500 );

    if( xStatus == pdPASS ){
      if( xReceivedStructure.eDataSource == eSender1 )
      {
        printf( "From Sender 1 = %i\n", xReceivedStructure.ucValue );
      }
      else
      {
        printf( "From Sender 2 = %i\n", xReceivedStructure.ucValue );
      }
    }
    else
    {
      printf( "A fila esta cheia.\r\n" );
    }
  }
}
void app_main()
{
  xQueue = xQueueCreate( 3, sizeof( Data_t ) );

  if( xQueue != NULL )
  {
    xTaskCreate( vSenderTask, "Sender1", 2048, ( void * ) &( xStructsToSend[ 0 ] ), 2, NULL );
    xTaskCreate( vSenderTask, "Sender2", 2048, ( void * ) &( xStructsToSend[ 1 ] ), 2, NULL );
    xTaskCreate( vReceiverTask, "Receiver", 2048, NULL, 1, NULL );
    printf(" Escalonador iniciado\n");
  }
  else
  {
    vQueueDelete( xQueue );
  }

}
