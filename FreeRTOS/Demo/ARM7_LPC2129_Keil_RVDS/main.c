#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

#define LEDS_QUANTITY 4

struct LedsParameters{
	unsigned char ucBlinkingFreq;
	unsigned char ucLedIndex;
};

void Delay(unsigned int uiMiliSec) {
	unsigned int uiLoopCtr, uiDelayLoopCount;
	uiDelayLoopCount = uiMiliSec*12000;
	for(uiLoopCtr=0;uiLoopCtr<uiDelayLoopCount;uiLoopCtr++) {}
}

void LedBlink(void *pvParameters){
	while(1){
		LedToggle(((struct LedsParameters *)pvParameters)->ucLedIndex);
		vTaskDelay((1000/((struct LedsParameters *)pvParameters)->ucBlinkingFreq)/2);
	}
}

void LedCtrl(void *pvParameters){
	
	unsigned char LedCounter = 0;
	unsigned char SecCounter = 0;
	
	while(1){
		if(!(SecCounter++ % 2)){
			((struct LedsParameters *)pvParameters)->ucLedIndex = LedCounter++ % LEDS_QUANTITY;
		}
		((struct LedsParameters *)pvParameters)->ucBlinkingFreq = ((struct LedsParameters *)pvParameters)->ucBlinkingFreq + 1;
		vTaskDelay(1000);
	}
}

int main(void){
	
	struct LedsParameters LedsControl;
	LedsControl.ucBlinkingFreq = 1;
	LedsControl.ucLedIndex = 0;
	
	LedInit();
	xTaskCreate(LedBlink, NULL , 100 , &LedsControl, 2 , NULL );
	xTaskCreate(LedCtrl, NULL , 100 , &LedsControl, 2 , NULL );
	vTaskStartScheduler();
	while(1);
}
