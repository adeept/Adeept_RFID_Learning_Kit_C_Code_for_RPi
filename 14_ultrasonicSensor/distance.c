/*
 * Filename    : distance.c
 * Description : Measure distance with ultrasonic sensor module.
 * Website     : www.adeept.com
 * E-mail      : support@adeept.com
 * Author      : Jason
 * Date        : 2015/06/21
 */
#include <wiringPi.h>  
#include <stdio.h>  
#include <sys/time.h>  

#define  Trig    4  
#define  Echo    5  

void ultraInit(void)  
{  
	pinMode(Echo, INPUT);  
	pinMode(Trig, OUTPUT);  
}  

float disMeasure(void)  
{  
	struct timeval tv1;  
	struct timeval tv2;  
	long start, stop;  
	float dis;  

	digitalWrite(Trig, LOW);  
	delayMicroseconds(2);  

	digitalWrite(Trig, HIGH);  //produce a pluse
	delayMicroseconds(10); 
	digitalWrite(Trig, LOW);  

	while(!(digitalRead(Echo) == 1));  
	gettimeofday(&tv1, NULL);           //current time 

	while(!(digitalRead(Echo) == 0));  
	gettimeofday(&tv2, NULL);           //current time  

	start = tv1.tv_sec * 1000000 + tv1.tv_usec; 
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;  

	dis = (float)(stop - start) / 1000000 * 34000 / 2;  //count the distance 

	return dis;  
}  

int main(void)  
{  
	float dis;  

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen  
		printf("setup wiringPi failed !\n");  
		return -1;   
	}  

	ultraInit();  

	while(1){  
		dis = disMeasure();  
		printf("Distance = %0.2f cm\n",dis);  
		delay(1000);  
	}  

	return 0;  
}  
