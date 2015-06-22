/*
* File name   : passiveBuzzer.c
* Description : Make an passive buzzer sound with different frequency.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/22
*/
#include <softTone.h>
#include <stdio.h>

#define  BZRPin  0

int main(void)
{
	if(wiringPiSetup() < 0){
		printf("setup failed !\n");
		return -1;
	}
	
	if(softToneCreate(BZRPin) < 0){
		printf("SoftTone setup failed!\n");
		return -1;
	}

	while(1){
		softToneWrite(BZRPin, 200);	
		delay(200);
		softToneWrite(BZRPin, 400);	
		delay(200);
		softToneWrite(BZRPin, 600);	
		delay(200);
		softToneWrite(BZRPin, 800);	
		delay(200);
		softToneWrite(BZRPin, 900);	
		delay(200);
		softToneWrite(BZRPin, 1000);	
		delay(200);
		softToneWrite(BZRPin, 1100);	
		delay(200);
		
		softToneWrite(BZRPin, 1100);	
		delay(200);
		softToneWrite(BZRPin, 1000);	
		delay(200);
		softToneWrite(BZRPin, 900);	
		delay(200);
		softToneWrite(BZRPin, 800);	
		delay(200);
		softToneWrite(BZRPin, 600);	
		delay(200);
		softToneWrite(BZRPin, 400);	
		delay(200);
		softToneWrite(BZRPin, 200);	
		delay(200);
	}

	return 0;	
}
