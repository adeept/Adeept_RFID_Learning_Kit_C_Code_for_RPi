/*
* File name   : blinkingLed.c
* Description : Make an led blinking.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/02
*/
#include <wiringPi.h>
#include <stdio.h>

#define  LedPin    0

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(LedPin, OUTPUT);

	while(1){
		digitalWrite(LedPin, LOW);   //led on
		printf("led on...\n");
		delay(500);
		digitalWrite(LedPin, HIGH);  //led off
		printf("...led off\n");
		delay(500);
	}

	return 0;
}

