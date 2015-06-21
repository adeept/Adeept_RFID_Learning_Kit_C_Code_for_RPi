/*
* File name   : passiveBuzzer.c
* Description : Make an passive buzzer sound with different frequency.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/21
*/
#include <wiringPi.h>
#include <stdio.h>

#define BZRPin  0

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(BZRPin, OUTPUT);   //set pin mode as output mode

	while(1){
		digitalWrite(BeepPin, LOW);  //beep on
		delay(100);                  //delay
		digitalWrite(BeepPin, HIGH); //beep off
		delay(100);                  //delay
	}

	return 0;
}

