#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

void Delay(unsigned int uiMiliSec) {
	unsigned int uiLoopCtr, uiDelayLoopCount;
	uiDelayLoopCount = uiMiliSec*12000;
	for(uiLoopCtr=0;uiLoopCtr<uiDelayLoopCount;uiLoopCtr++) {}
}

void Led0Blink( void *pvParameters ){
	
	unsigned char ucFreq = *((unsigned char*)pvParameters);
	
	while(1){
		LedToggle(0);
		vTaskDelay((1000/ucFreq)/2);
	}
}

void Led1Blink( void *pvParameters ){
	while(1){
		LedToggle(1);
		Delay(500);
	}
}

int main(void){
	
	unsigned char ucBlinkingFreq = 10;
	
	LedInit();
	xTaskCreate(Led0Blink, NULL , 100 , &ucBlinkingFreq, 2 , NULL );
	vTaskStartScheduler();
	while(1);
}
