/*
* File name   : motor.c
* Description : controlling a 5V DC motor
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/04
*/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define BTN_RUN_STOP        0
#define BTN_DIRECTION       1
#define BTN_SPEED_INCREASE  2
#define BTN_SPEED_DECREASE  3

#define MotorPin_A          4
#define MotorPin_B          5
    
#define STATUS_LED         16

int g_sta  = 1;
int g_dir  = 1;
int speed  = 50;

void motor(int status, int dir, int speed)
{
	if(1 == status){//run
		digitalWrite(STATUS_LED, 0);  //led on
		if(1 == dir){  //clockwise
			digitalWrite(MotorPin_A, HIGH);
			softPwmWrite(MotorPin_B, 100-speed);
		}else{  //anticlockwise
			digitalWrite(MotorPin_A, LOW);
			softPwmWrite(MotorPin_B, speed);
		}
	}else{  //stop
		digitalWrite(STATUS_LED, 1);  //led off
		digitalWrite(MotorPin_A, HIGH);
		digitalWrite(MotorPin_B, HIGH);
	}	
}

void buttonScan(void)
{
	if(digitalRead(BTN_RUN_STOP) == 0){
		delay(10);
		if(digitalRead(BTN_RUN_STOP) == 0){
			g_sta = !g_sta;
			printf("g_sta = %d\n", g_sta);
		}
		while(!digitalRead(BTN_RUN_STOP));
	}
	
	if(digitalRead(BTN_DIRECTION) == 0){
		delay(10);
		if(digitalRead(BTN_DIRECTION) == 0){
			g_dir = !g_dir;
			printf("g_dir = %d\n", g_dir);
		}
		while(!digitalRead(BTN_DIRECTION));
	}
	
	if(digitalRead(BTN_SPEED_INCREASE) == 0){
		delay(10);
		if(digitalRead(BTN_SPEED_INCREASE) == 0){
			speed++;
			if(speed > 100){
				speed = 100;		
			}
			printf("speed = %d\n", speed);
		}
		while(!digitalRead(BTN_SPEED_INCREASE));
	}
	
	if(digitalRead(BTN_SPEED_DECREASE) == 0){
		delay(10);
		if(digitalRead(BTN_SPEED_DECREASE) == 0){
			speed--;
			if(speed < 0){
				speed = 0;		
			}
			printf("speed = %d\n", speed);
		}
		while(!digitalRead(BTN_SPEED_DECREASE));
	}
}

int main(void)
{
	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !\n");
		return -1; 
	}

	pinMode(MotorPin_A, OUTPUT);
	pinMode(MotorPin_B, OUTPUT);
	pinMode(STATUS_LED, OUTPUT);

	pinMode(BTN_RUN_STOP, INPUT);
	pinMode(BTN_DIRECTION, INPUT);
	pinMode(BTN_SPEED_DECREASE, INPUT);
	pinMode(BTN_SPEED_INCREASE, INPUT);

	pullUpDnControl(BTN_RUN_STOP, PUD_UP);
	pullUpDnControl(BTN_DIRECTION, PUD_UP);
	pullUpDnControl(BTN_SPEED_DECREASE, PUD_UP);
	pullUpDnControl(BTN_SPEED_INCREASE, PUD_UP);

	softPwmCreate(MotorPin_B, 0, 100);

	while(1){
		buttonScan();
		motor(g_sta, g_dir, speed);
	}

	return 0;
}
