/*
* File name   : breathingLed.c
* Description : control the brightness of led by PWM.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/02
*/
#include <wiringPi.h>
#include <stdio.h>

#define LedPin    1

int main(void)
{
	int i;

	if(wiringPiSetup() < 0){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(LedPin, PWM_OUTPUT);//pwm output mode

	while(1){
		for(i=0;i<1024;i++){
			pwmWrite(LedPin, i);
			delay(2);
		}
		delay(1000);
		for(i=1023;i>=0;i--){
			pwmWrite(LedPin, i);
			delay(2);
		}
	}

	return 0;
}
