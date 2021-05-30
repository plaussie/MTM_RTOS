#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

#define LEDS_QUANTITY 4

struct LedsParameters{
	unsigned char ucBlinkingFreq;
	unsigned char ucLedIndex;
	xTaskHandle MyHandle;
};

void LedBlink(void *pvParameters){
	while(1){
		LedToggle(((struct LedsParameters *)pvParameters)->ucLedIndex);
		vTaskDelay((1000/((struct LedsParameters *)pvParameters)->ucBlinkingFreq)/2);
	}
}

void BlinkCtrl(void *pvParameters){
	
	while(1){
		vTaskSuspend(((struct LedsParameters *)pvParameters)->MyHandle);
		vTaskDelay(1000);
		vTaskResume(((struct LedsParameters *)pvParameters)->MyHandle);
		vTaskDelay(1000);
	}
}

int main(void){ 
	
	struct LedsParameters LedsControl;
	LedsControl.ucBlinkingFreq = 3;
	LedsControl.ucLedIndex = 0;
	
	LedInit();
	xTaskCreate(LedBlink, NULL , 100 , &LedsControl, 2 , &LedsControl.MyHandle);
	xTaskCreate(BlinkCtrl, NULL , 100 , &LedsControl, 2 , NULL);
	vTaskStartScheduler();
	while(1);
}
