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
				case BUTTON_3: 
					ServoSpeed(8);
					ServoGoTo(12);
					ServoSpeed(4);
					ServoGoTo(24);
					ServoSpeed(2);
					ServoGoTo(36);
					ServoSpeed(1);
					ServoGoTo(0);	
					break;
				default:
					break;
			}
			vTaskDelay(100);
		}
	}
}

int main( void ){
	TickType_t ServoPeriod = 5;
	KeyboardInit();
	ServoInit();
	xTaskCreate(Keyboard, NULL, 128, NULL, 2, NULL);
	xTaskCreate(ServoRun, NULL, 128, &ServoPeriod, 2, NULL);
	vTaskStartScheduler();
	while(1);
}
