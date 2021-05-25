#include <lpc21xx.h>
#include "led.h"

void Delay(unsigned int uiMiliSec) {
	unsigned int uiLoopCtr, uiDelayLoopCount;
	uiDelayLoopCount = uiMiliSec*12000;
	for(uiLoopCtr=0;uiLoopCtr<uiDelayLoopCount;uiLoopCtr++) {}
}

int main( void ){
	char Counter = 0;
	LedInit();
	
	while(1){
		if(!(Counter%4)){
			LedToggle(0);
		}
		if(!(Counter%3)){
			LedToggle(1);
		}
		Delay(83);
		Counter++;
	}
}
