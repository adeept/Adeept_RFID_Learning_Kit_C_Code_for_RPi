/*
 * File name   : joystick.c
 * Description : PS2 joystick programming.
 * Website     : www.adeept.com
 * E-mail      : support@adeept.com
 * Author      : Jason
 * Date        : 2015/06/21
 */
#include <wiringPi.h>
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define      ADC_CS    0
#define      ADC_CLK   1
#define      ADC_DIO   2
#define  JoyStick_SW   3

uchar get_ADC_Result(uchar xyVal)
{
	//10:CH0
	//11:CH1
	uchar i;
	uchar dat1=0, dat2=0;

	pinMode(ADC_DIO, OUTPUT);
	
	digitalWrite(ADC_CS, 0);

	digitalWrite(ADC_CLK,0);
	digitalWrite(ADC_DIO,1);	delayMicroseconds(2);
	digitalWrite(ADC_CLK,1);	delayMicroseconds(2);
	digitalWrite(ADC_CLK,0);

	digitalWrite(ADC_DIO,1);    delayMicroseconds(2); //CH0 10
	digitalWrite(ADC_CLK,1);	delayMicroseconds(2);
	digitalWrite(ADC_CLK,0);

	if(xyVal == 'x'){
		digitalWrite(ADC_DIO,0);	delayMicroseconds(2); //CH0 0
	}
	if(xyVal == 'y'){
		digitalWrite(ADC_DIO,1);	delayMicroseconds(2); //CH1 1
	}
	digitalWrite(ADC_CLK,1);	
	digitalWrite(ADC_DIO,1);    delayMicroseconds(2);
	digitalWrite(ADC_CLK,0);	
	digitalWrite(ADC_DIO,1);    delayMicroseconds(2);

	for(i=0;i<8;i++)
	{
		digitalWrite(ADC_CLK,1);	delayMicroseconds(2);
		digitalWrite(ADC_CLK,0);    delayMicroseconds(2);

		pinMode(ADC_DIO, INPUT);
		dat1=dat1<<1 | digitalRead(ADC_DIO);
	}

	for(i=0;i<8;i++)
	{
		dat2 = dat2 | ((uchar)(digitalRead(ADC_DIO))<<i);
		digitalWrite(ADC_CLK,1); 	delayMicroseconds(2);
		digitalWrite(ADC_CLK,0);    delayMicroseconds(2);
	}

	digitalWrite(ADC_CS,1);

	pinMode(ADC_DIO, OUTPUT);

	return(dat1==dat2) ? dat1 : 0;
}

int main(void)
{
	uchar tmp;
	uchar xVal = 0, yVal = 0, zVal = 0;

	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !\n");
		return -1; 
	}

	pinMode(ADC_CS,  OUTPUT);
	pinMode(ADC_CLK, OUTPUT);
	pinMode(JoyStick_SW, INPUT);

	pullUpDnControl(JoyStick_SW, PUD_UP);

	while(1){
		xVal = get_ADC_Result('x');
		printf("%d\n", xVal);
		delay(100);
		if(xVal == 0){
			tmp = 1;	
		}
		if(xVal == 255){
			tmp = 2;
		}

		yVal = get_ADC_Result('y');
		if(yVal == 0){
			tmp = 3;
		}
		if(yVal == 255){
			tmp = 4;
		}

		zVal = digitalRead(JoyStick_SW);
		if(zVal == 0){
			printf("Button is pressed !\n");
		}

		switch(tmp){
			case 1: printf("dowm\n"); break;
			case 2: printf("up\n"); break;
			case 3: printf("left\n"); break;
			case 4: printf("right\n"); break;
			default:
					break;
		}

		//delay(500);
	}

	return 0;
}
