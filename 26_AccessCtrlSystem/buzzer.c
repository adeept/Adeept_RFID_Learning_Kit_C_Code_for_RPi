#include <wiringPi.h>
#include <stdio.h>
#include "buzzer.h"

int buzzerInit(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(BUZZERPin, OUTPUT);
}

void buzzer(int n)
{
	int i;

	for(i = 0; i < n; i++){
		digitalWrite(BUZZERPin, LOW);
		delay(100);
		digitalWrite(BUZZERPin, HIGH);
		delay(100);
	}
}

