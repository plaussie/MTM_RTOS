#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "led.h"
#include "servo.h"
#include "string.h"
#include "keyboard.h"

void Keyboard(void *pvParameters){
	
	enum KeyboardState ePreviousState, eCurrentState = RELASED;
	
	while(1){
		ePreviousState = eCurrentState;
		eCurrentState = eKeyboardRead();
		if(ePreviousState != eCurrentState){
			switch(eCurrentState){
				case BUTTON_0: ServoCallib();
					break;
				case BUTTON_1: ServoGoTo(50);
					break;
				case BUTTON_2: ServoGoTo(100);
					break;
				case BUTTON_3: ServoGoTo(150);
					break;
				default:
					break;
			}
			vTaskDelay(100);
		}
	}
}

int main( void ){
	KeyboardInit();
	ServoInit(100);
	xTaskCreate(Keyboard, NULL, 128, NULL, 1, NULL);
	vTaskStartScheduler();
	while(1);
}
