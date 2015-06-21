/*
* File name   : tiltSwitch.c
* Description : Toggle the status of LED by tilt switch.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/26
*/
#include <wiringPi.h>
#include <stdio.h>

#define  LedPin    0
#define  TiltPin   1

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print messa    ge to screen
    	printf("setup wiringPi failed !\n");
    	return -1;
    }
         
    pinMode(LedPin, OUTPUT);
    pinMode(TiltPin, INPUT);
     
    while(1){
    	if(digitalRead(TiltPin) == 0){
    		digitalWrite(LedPin, LOW);   //led on
     		printf("led on...\n");
        }else{
        	digitalWrite(LedPin, HIGH);  //led off
            printf("...led off\n");
        }
    }
    
    return 0;
}
