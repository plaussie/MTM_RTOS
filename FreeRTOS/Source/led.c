#include <LPC21xx.H>
#include "led.h"

#define Led0_bm (1<<16)
#define Led1_bm (1<<17)
#define Led2_bm (1<<18)
#define Led3_bm (1<<19)


void LedInit(){
		
		IO1DIR=IO1DIR | (Led0_bm | Led1_bm | Led2_bm | Led3_bm);
		
		IO1SET=Led0_bm;
	}


void LedStep(eDirectionState){
	switch(eDirectionState){
		case LEFT : 
			LedStepLeft();
		break;
		case RIGHT :
			LedStepRight();
	}
}


void LedToggle(unsigned char ucLedIndeks){
		
		if (ucLedIndeks == 0){
			if(IO1PIN&Led0_bm){
				IO1CLR=Led0_bm;
			}
			else{
				IO1SET=Led0_bm;
			}
		}
		else if(ucLedIndeks == 1){
			if(IO1PIN&Led1_bm){
				IO1CLR=Led1_bm;
			}
			else{
				IO1SET=Led1_bm;
			}
		}
		else if(ucLedIndeks == 2){
			if(IO1PIN&Led2_bm){
				IO1CLR=Led2_bm;
			}
			else{
				IO1SET=Led2_bm;
			}
		}
		else if(ucLedIndeks == 3){
			if(IO1PIN&Led3_bm){
				IO1CLR=Led3_bm;
			}
			else{
				IO1SET=Led3_bm;
			}
		}
}
	
	
unsigned int	uiLedStepCounter;
void LedStepLeft(){
	uiLedStepCounter++;
	LedOn(uiLedStepCounter%4);
}


void LedStepRight(){
	uiLedStepCounter--;
	LedOn(uiLedStepCounter%4);
}

void LedOn(unsigned char ucLedIndeks){
	
		IO1CLR=Led0_bm | Led1_bm | Led2_bm | Led3_bm;
		
		if (ucLedIndeks == 0){
			
			IO1SET=Led0_bm;
		}
		else if(ucLedIndeks == 1){
			IO1SET=Led1_bm;
		}
		else if(ucLedIndeks == 2){
			IO1SET=Led2_bm;
		}
		else if(ucLedIndeks == 3){
			IO1SET=Led3_bm;
		}
}
	