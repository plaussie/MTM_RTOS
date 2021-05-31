#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "keyboard.h"

xSemaphoreHandle xSemaphore;

void LettersTx (void *pvParameters){
	while(1){
		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		Transmiter_SendString("-ABCDEEFGH-\n");
		while(Transmiter_GetStatus()!=FREE){};
		xSemaphoreGive(xSemaphore);
		vTaskDelay(300);
	}
}

void KeyboardTx (void *pvParameters){
	while(1){
		if(eKeyboardRead() != RELASED){
			xSemaphoreTake(xSemaphore,portMAX_DELAY);
			Transmiter_SendString("-Keyboard-\n");
			while(Transmiter_GetStatus()!=FREE){};
			xSemaphoreGive(xSemaphore);
		}
	}
}

int main( void ){
	KeyboardInit();
	UART_InitWithInt(300);
	vSemaphoreCreateBinary(xSemaphore);
	xTaskCreate(LettersTx, NULL, 128, NULL, 1, NULL);
	xTaskCreate(KeyboardTx, NULL, 128, NULL, 1, NULL);
	vTaskStartScheduler();
	while(1);
}