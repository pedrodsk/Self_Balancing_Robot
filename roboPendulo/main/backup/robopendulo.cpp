#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"
#include "I2Cbus.hpp"
#include "kalmanfilter.hpp"
#include <math.h>
#include <esp_system.h>
//variaveis globais


//Prototipos Threads
void vThread1(void *pvParameter);
void vThread2(void *pvParameter);
void vThread3(void *pvParameter);

//Main
extern "C" void app_main() {
	//calibração do sensor
	//configuração do I2C
	/*
	ESP_ERROR_CHECK( myI2C.begin(GPIO_NUM_21, GPIO_NUM_22, 400000));
	myI2C.setTimeout(20);
	myI2C.writeBit(0x68, 0x6B, 6, 0);
	vTaskDelay(200 / portTICK_PERIOD_MS);

	//ler dados
	while(myI2C.readBytes(0x68, 0x3b, 6, buffer));
	ax = (int16_t)((buffer[0] << 8) | buffer[1]); // ([ MSB ] [ LSB ])
	ay = (int16_t)((buffer[2] << 8) | buffer[3]); // ([ MSB ] [ LSB ])
	az = (int16_t)((buffer[4] << 8) | buffer[5]); // ([ MSB ] [ LSB ])
	pitch = atan(ax/sqrt(ay * ay + az * az)) * RAD_TO_DEG;
	roll = atan(ay/sqrt(ax * ax + az * az)) * RAD_TO_DEG;
*/
	//Criação de Threads
	xTaskCreate(&vThread1, "MPU6050", 2048, NULL, 1, NULL);
	xTaskCreate(&vThread2, "Motor Esquerda", 2048, NULL, 1, NULL);
	xTaskCreate(&vThread3, "Motor Direita", 2048, NULL, 1, NULL);
}

void vThread1(void *pvParameter)
{
	I2C_t& myI2C = i2c0;  // i2c0 and i2c1 are the default objects
	uint8_t buffer[14];
	double ax, ay, az;
	double gyrox, gyroy, gyroz,gx,gy,gz;
	double RAD_TO_DEG = 57.29577951;
	double pitch,roll,fpitch,froll;
	KALMAN pfilter(0.005);
	KALMAN rfilter(0.005);
	uint32_t lasttime = 0;
	int count = 0;


	while(1)
	{
		while(myI2C.readBytes(0x68, 0x3b, 12, buffer));
  		ax = (int16_t)((buffer[0] << 8) | buffer[1]); // ([ MSB ] [ LSB ])
  		ay = (int16_t)((buffer[2] << 8) | buffer[3]); // ([ MSB ] [ LSB ])
  		az = (int16_t)((buffer[4] << 8) | buffer[5]); // ([ MSB ] [ LSB ])

  		gyrox = (int16_t)((buffer[8] << 8) | buffer[9]); // ([ MSB ] [ LSB ])
  		gyroy = (int16_t)((buffer[10] << 8) | buffer[11]); // ([ MSB ] [ LSB ])
  	//	gyroz = (int16_t)((buffer[12] << 8) | buffer[13]); // ([ MSB ] [ LSB ])

  		pitch = atan(ax/sqrt(ay * ay + az * az)) * RAD_TO_DEG;
  		roll = atan(ay/sqrt(ax * ax + az * az)) * RAD_TO_DEG;

  		gy = gyroy / 131.0;
  		gx = gyrox / 131.0;
  	//	gz = gyroz / 131.0;

  		fpitch = pfilter.filter(pitch, gy);
  	//	froll = rfilter.filter(-roll, gx);
  		
  		count++;
  		if(esp_log_timestamp() / 1000 != lasttime) {
  			lasttime = esp_log_timestamp() / 1000;
  			ESP_LOGI("mpu6050", "Samples: %d", count);
  			count = 0;
  	//		ESP_LOGI("mpu6050", "Acc: ( %.3lf, %.3lf, %.3lf)", ax, ay, az);
  	//		ESP_LOGI("mpu6050", "Gyro: ( %.3f, %.3f, %.3f)", gx, gy, gz);
  	//		ESP_LOGI("mpu6050", "Pitch: %.3lf", pitch);
  	//		ESP_LOGI("mpu6050", "Roll: %.3f", roll);
  			ESP_LOGI("mpu6050", "FPitch: %.3f", fpitch);
  	//		ESP_LOGI("mpu6050", "FRoll: %.3lf", froll);

  		}
  		vTaskDelay(10 / portTICK_PERIOD_MS);
  	}
  }
  void vThread2(void *pvParameter) // Motor Esquerda
  {
//  configuração do timer0
    /*
     * Prepare and set configuration of timers
     * that will be used by LED Controller
     */
  	ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_11_BIT, // resolution of PWM duty
        .freq_hz = 20000,                      // frequency of PWM signal
        .speed_mode = LEDC_HIGH_SPEED_MODE,           // timer mode
        .timer_num = LEDC_TIMER_0 //index 
    } 

  // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);


      // Configurar canal PWM 0
    ledc_channel_config_t ledc_channel0 = {

    	.channel    = LEDC_CHANNEL_0,
    	.duty       = 500,
    	.gpio_num   = 4,
    	.speed_mode = LEDC_HIGH_SPEED_MODE,
    	.timer_sel  = LEDC_TIMER_0
    };
// Configurar canal PWM 1
    ledc_channel_config_t ledc_channel1 = {

    	.channel    = LEDC_CHANNEL_1,
    	.duty       = 500,
    	.gpio_num   = 5,
    	.speed_mode = LEDC_HIGH_SPEED_MODE,
    	.timer_sel  = LEDC_TIMER_0
    };

    //  Setar canais 
    ledc_channel_config(&ledc_channel0);
    ledc_channel_config(&ledc_channel1);

    //  Fade
    //    ledc_fade_func_install(0); 

    while(1) {
    	ESP_ERROR_CHECK( ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 700) ); 
    	ESP_ERROR_CHECK( ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0) );

        ESP_ERROR_CHECK( ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0) ); // 0 Para trás
        ESP_ERROR_CHECK( ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1) );

    }
}

    void vThread3(void *pvParameter) // Motor Direita
    {
        //configurar timer 1
    	ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_11_BIT, // resolution of PWM duty
        .freq_hz = 20000,                      // frequency of PWM signal
        .speed_mode = LEDC_HIGH_SPEED_MODE,           // timer mode
        .timer_num = LEDC_TIMER_1 //index 
    };

  // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);

        // Configurar canal PWM 2
    ledc_channel_config_t ledc_channel2 = {

    	.channel    = LEDC_CHANNEL_2,
    	.duty       = 500,
    	.gpio_num   = 18,
    	.speed_mode = LEDC_HIGH_SPEED_MODE,
    	.timer_sel  = LEDC_TIMER_1
    };
// Configurar canal PWM 3
    ledc_channel_config_t ledc_channel3 = {

    	.channel    = LEDC_CHANNEL_3,
    	.duty       = 500,
    	.gpio_num   = 19,
    	.speed_mode = LEDC_HIGH_SPEED_MODE,
    	.timer_sel  = LEDC_TIMER_1
    };
      //setar canais
    ledc_channel_config(&ledc_channel2);
    ledc_channel_config(&ledc_channel3);


    while(1){
    	ESP_ERROR_CHECK( ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 700) );
    	ESP_ERROR_CHECK( ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2) );

        ESP_ERROR_CHECK( ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, 0) ); //0 Para trás.
        ESP_ERROR_CHECK( ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3) );

    }
}