/*
 * File name   : ledBar.c
 * Description : voltage intensity indicator 
 * Website     : www.adeept.com
 * E-mail      : support@adeept.com
 * Author      : Jason
 * Date        : 2015/06/22
 */
#include <wiringPi.h>
#include <stdio.h>

typedef unsigned char uchar;

#define    ADC_CS    8
#define    ADC_DIO   9
#define    ADC_CLK  10

const int ledNum[] = {0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};

void ledBarInit(void)
{
	int i;

	for(i = 0; i < 8; i++){
		pinMode(i, OUTPUT); //set pin0~7 as output mode
	}
}

void ledBarCtrl(int n)
{
	digitalWriteByte(ledNum[n]);	
}

int map(int x, int in_min, int in_max, int out_min, int out_max)     
{  
	return (x -in_min) * (out_max - out_min) / (in_max - in_min) + out_min;  
}  

int get_ADC_Result(void)
{
	//10:CH0
	//11:CH1
	uchar i;
	uchar dat1=0, dat2=0;

	digitalWrite(ADC_CS, 0);

	digitalWrite(ADC_CLK,0);
	digitalWrite(ADC_DIO,1);	delayMicroseconds(2);
	digitalWrite(ADC_CLK,1);	delayMicroseconds(2);
	digitalWrite(ADC_CLK,0);

	digitalWrite(ADC_DIO,1);    delayMicroseconds(2); //CH0 10
	digitalWrite(ADC_CLK,1);	delayMicroseconds(2);
	digitalWrite(ADC_CLK,0);

	digitalWrite(ADC_DIO,0);	delayMicroseconds(2); //CH0 0

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
	int analogVal;
	int num;

	if(wiringPiSetup() < 0){
		printf("setup wiringPi failed !\n");
		return -1; 
	}

	pinMode(ADC_CS,  OUTPUT);
	pinMode(ADC_CLK, OUTPUT);

	ledBarInit();

	while(1){
		pinMode(ADC_DIO, OUTPUT);
		analogVal = get_ADC_Result();
		printf("analog value : %d\n", analogVal);
		printf("current voltage : %d\n", analogVal/255.0*5);
		num = map(analogVal, 0, 255, 0, 8);
		ledBarCtrl(num);
		delay(200);
	}

	return 0;
}

