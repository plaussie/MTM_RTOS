#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "led.h"

xSemaphoreHandle xSemaphore;

void Pulse_LED0(void *pvParameters){
	while(1){
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		LedOn(0);
		vTaskDelay(100);
		LedOff(0);
	}
}

void Pulse_LED1(void *pvParameters){
	while(1){
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		LedOn(1);
		vTaskDelay(100);
		LedOff(1);
	}
}

void PulseTrigger_1000ms(void *pvParameters){
	
	while(1){
		vTaskDelay(1000);
		xSemaphoreGive(xSemaphore);
	}
}

int main(void){ 
	
	vSemaphoreCreateBinary(xSemaphore);
	LedInit();
	xTaskCreate(Pulse_LED0, NULL , 100 , NULL, 2 , NULL);
	xTaskCreate(Pulse_LED1, NULL , 100 , NULL, 2 , NULL);
	xTaskCreate(PulseTrigger_1000ms, NULL , 100 , NULL, 2 , NULL);
	vTaskStartScheduler();
	while(1);
}
