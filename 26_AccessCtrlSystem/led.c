#include <wiringPi.h>
#include <stdio.h>
#include "led.h"

int ledInit(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(LedPin, OUTPUT);
}

void ledFlash(int n)
{
	int i;

	for(i = 0; i < n; i++){
		digitalWrite(LedPin, LOW);   //led on
		delay(100);
		digitalWrite(LedPin, HIGH);  //led off
		delay(100);
	}
}

