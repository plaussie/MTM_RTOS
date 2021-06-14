#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "servo.h"
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
	struct ServoControl sServo = {CALLIB_COM, 0, 0, 0};
	xQueueSend(QueueServoParameters, &sServo, 0);
}

void Automat(void){
				static struct Servo sServo = {CALLIB, 0, 0};
				struct ServoControl sServoReceiveParams;
				static TickType_t ServoSpeed = 50;
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
							xQueueReceive(QueueServoParameters, &sServoReceiveParams, portMAX_DELAY);
							switch(sServoReceiveParams.eCommand){
								case CALLIB_COM:
									sServo.eState = CALLIB;
									break;
								case GOTO:
									sServo.eState = IN_PROGRESS;
									sServo.uiDesiredPosition = sServoReceiveParams.uiDesiredPosition;
									break;
								case WAIT:
									sServo.eState = IDLE;
									vTaskDelay(sServoReceiveParams.ttNumberOfTicks);
									break;
								case SPEED:
									sServo.eState = IDLE;
									ServoSpeed = sServoReceiveParams.ttSpeed;
									break;
								default:
									break;
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
			vTaskDelay(ServoSpeed);
}
		
void ServoInit(TickType_t ServoPeriod){
	LedInit();
	DetectorInit();
	QueueServoParameters = xQueueCreate(20, sizeof(struct ServoControl));
	xTaskCreate(ServoRun, NULL, 128, &ServoPeriod, 2, NULL);
}

void ServoGoTo(unsigned int uiPosition){
	struct ServoControl sServo = {GOTO, 0, 0, 0};
	sServo.uiDesiredPosition=uiPosition;
	xQueueSend(QueueServoParameters, &sServo, 0);
}

void ServoRun(void *pvParameters){
	while(1){
		Automat();
		vTaskDelay(*((TickType_t*)pvParameters));
	}
}

void ServoWait(TickType_t ttNumberOfTicks){
	struct ServoControl sServo = {WAIT, 0, 0, 0};
	sServo.ttNumberOfTicks = ttNumberOfTicks;
	xQueueSend(QueueServoParameters, &sServo, 0);
}

void ServoSpeed(TickType_t ttSpeedTick){
	struct ServoControl sServo = {SPEED, 0, 0, 0};
	sServo.ttSpeed = ttSpeedTick;
	xQueueSend(QueueServoParameters, &sServo, 0);
}
