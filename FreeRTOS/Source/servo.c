#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "servo.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define DETECTOR_bm (1<<10)

QueueHandle_t QueueServoParameters;

void DetectorInit(void){
	IO0DIR = IO0DIR & (~DETECTOR_bm);
}

enum DetectorState eReadDetector(){
	if((IO0PIN&DETECTOR_bm)==0){
		return ACTIVE;
	}
		return INACTIVE;
}

void ServoCallib(void){
	struct ServoControl sServo = {CALLIB_COM, 0, 0};
	xQueueSend(QueueServoParameters, &sServo, 0);
}

void Automat(void){
				static struct Servo sServo = {CALLIB, 0, 0};
				switch(sServo.eState){
					case CALLIB:
						if(eReadDetector()==INACTIVE){
							LedStepRight();
							sServo.eState=CALLIB;
						}
						else{
							LedStepRight();
							sServo.uiCurrentPosition=0;
							sServo.uiDesiredPosition=0;
							sServo.eState=IDLE;
						}
						break;
					case IDLE:
						if(sServo.uiDesiredPosition==sServo.uiCurrentPosition){
							struct ServoControl sServoReceiveParams;
							if(pdTRUE == xQueueReceive(QueueServoParameters, &sServoReceiveParams, 0)){
								switch(sServoReceiveParams.eCommand){
									case CALLIB_COM:
										sServo.eState = CALLIB;
										break;
									case GOTO:
										sServo.eState = IDLE;
										sServo.uiDesiredPosition = sServoReceiveParams.uiDesiredPosition;
										break;
									case WAIT:
										vTaskDelay(sServoReceiveParams.uiNumberOfTicks);
										break;
									default:
										break;
								}
							}
							else{
								sServo.eState=IDLE;
							}
						}
						else{
							sServo.eState=IN_PROGRESS;
						}
						break;
					case IN_PROGRESS:
						if(sServo.uiDesiredPosition<sServo.uiCurrentPosition){
							LedStepLeft();
							sServo.uiCurrentPosition--;
							sServo.eState=IN_PROGRESS;
						}
						else if(sServo.uiDesiredPosition>sServo.uiCurrentPosition){
							LedStepRight();
							sServo.uiCurrentPosition++;
							sServo.eState=IN_PROGRESS;
						}
						else{
							sServo.eState=IDLE;
						}
			}
}
		
void ServoInit(){
	LedInit();
	DetectorInit();
	QueueServoParameters = xQueueCreate(20, sizeof(struct ServoControl));
}

void ServoGoTo(unsigned int uiPosition){
	struct ServoControl sServo = {GOTO, 0, 0};
	sServo.uiDesiredPosition=uiPosition;
	xQueueSend(QueueServoParameters, &sServo, 0);
}

void ServoRun(void *pvParameters){
	while(1){
		Automat();
		vTaskDelay(*((TickType_t*)pvParameters));
	}
}

void ServoWait(unsigned int uiNumberOfTicks){
	struct ServoControl sServo = {WAIT, 0, 0};
	sServo.uiNumberOfTicks = uiNumberOfTicks;
	xQueueSend(QueueServoParameters, &sServo, 0);
}
