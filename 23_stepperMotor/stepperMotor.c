/*
 * File name   : stepperMotor.c
 * Description : control a stepper motor.
 * Website     : www.adeept.com
 * E-mail      : support@adeept.com
 * Author      : Jason
 * Date        : 2015/06/21
 */
#include <wiringPi.h>  
#include <stdio.h>  

#define IN1 0    // wiringPi GPIO0(pin11)  
#define IN2 1    // pin12 
#define IN3 2    // pin13
#define IN4 3    // pin15

void setStep(int a, int b, int c, int d)  
{  
	digitalWrite(IN1, a);     
	digitalWrite(IN2, b);     
	digitalWrite(IN3, c);     
	digitalWrite(IN4, d);     
}  

void stop(void)  
{  
	setStep(0, 0, 0, 0);      
}  

void forward(int t, int steps)  
{  
	int i;  

	for(i = 0; i < steps; i++){  
		setStep(1, 0, 0, 0);  
		delay(t);  
		setStep(0, 1, 0, 0);      
		delay(t);  
		setStep(0, 0, 1, 0);      
		delay(t);  
		setStep(0, 0, 0, 1);      
		delay(t);  
	}  
}  

void backward(int t, int steps)  
{  
	int i;  

	for(i = 0; i < steps; i++){  
		setStep(0, 0, 0, 1);  
		delay(t);  
		setStep(0, 0, 1, 0);      
		delay(t);  
		setStep(0, 1, 0, 0);      
		delay(t);  
		setStep(1, 0, 0, 0);      
		delay(t);  
	}  
}  

int main(void) 
{  
	if (wiringPiSetup() < 0) {  
		printf("Setup wiringPi failed!\n");  
		return -1;  
	}  

	/* set pins mode as output */  
	pinMode(IN1, OUTPUT);  
	pinMode(IN2, OUTPUT);  
	pinMode(IN3, OUTPUT);  
	pinMode(IN4, OUTPUT);  

	while (1){  
		printf("forward...\n");  
		forward(3, 512);      

		printf("stop...\n");  
		stop();  
		delay(2000);       // 2s  

		printf("backward...\n");  
		backward(3, 256);  // 512 steps ---- 360 angle    

		printf("stop...\n");  
		stop();  
		delay(2000);       // 2s  
	}  

	return 0;  
}  
