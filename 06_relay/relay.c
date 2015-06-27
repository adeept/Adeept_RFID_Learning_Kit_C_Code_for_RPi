/*
* File name   : relay.c
* Description : toggle a relay.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/21
*/
#include <wiringPi.h>
#include <stdio.h>

#define  RelayPin  1

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	pinMode(RelayPin, OUTPUT);

	while(1){
		digitalWrite(RelayPin, 0);   //close
		printf("close...\n");
		delay(1000);
		digitalWrite(RelayPin, 1);  //open
		printf("...open\n");
		delay(1000);
	}

	return 0;
}

