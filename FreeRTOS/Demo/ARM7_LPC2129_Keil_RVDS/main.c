#include <lpc21xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "keyboard.h"

#define QUEUE_SIZE 5
#define ITEM_SIZE 25

QueueHandle_t xQueue;

void Rtos_Transmiter_SendString(void *pvParameters){
	char pcStringTx[ITEM_SIZE];
	while(1){
		xQueueReceive(xQueue, &pcStringTx, 0);
		Transmiter_SendString(pcStringTx);
		while(Transmiter_GetStatus()!=FREE){};
	}
}

void LettersTx (void *pvParameters){
	TickType_t StartTime, Duration = 0;
	char pcStringTx[ITEM_SIZE];
	while(1){
		CopyString("-ABCDEEFGH-", pcStringTx);
		AppendUIntToString(Duration, pcStringTx);
		AppendString("\n", pcStringTx);
		StartTime = xTaskGetTickCount();
		if(xQueueSend(xQueue, &pcStringTx, 0) != pdTRUE){
			LedToggle(0);
		}
		Duration = xTaskGetTickCount() - StartTime;
		vTaskDelay(300);
	}
}

void KeyboardTx (void *pvParameters){
	char pcStringTx[] = "-Keyboard-\n";
	while(1){
		if(eKeyboardRead() != RELASED){
			xQueueSend(xQueue, &pcStringTx, 0);
		}
	}
}

int main( void ){
	UART_InitWithInt(300);
	KeyboardInit();
	LedInit();
	xQueue = xQueueCreate(QUEUE_SIZE, ITEM_SIZE);
	xTaskCreate(LettersTx, NULL, 128, NULL, 1, NULL);
	xTaskCreate(KeyboardTx, NULL, 128, NULL, 1, NULL);
	xTaskCreate(Rtos_Transmiter_SendString, NULL, 128, NULL, 1, NULL);
	vTaskStartScheduler();
	while(1);
}
