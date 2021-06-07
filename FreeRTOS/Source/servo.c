#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "servo.h"

#define DETECTOR_bm (1<<10)

struct Servo sServo;

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
	sServo.eState=CALLIB;
}

void Automat(void){
	
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
							sServo.eState=IDLE;
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
		
void ServoInit(unsigned int uiServoFrequency){
	LedInit();
	DetectorInit();
	sServo.eState=CALLIB;
	Timer1Interrupts_Init((10000000/uiServoFrequency), &Automat);
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition=uiPosition;
}

