/*
* File name   : segment.c
* Description : display 0~9, A~F on 7-segment display
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/26
*/
#include <stdio.h>
#include <wiringPi.h>

typedef unsigned char uchar;

const uchar SegCode[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};

int main(void)
{
	int i;

	if(wiringPiSetup() < 0){ // setup wiringPi
		printf("wiringPi setup failed !\n");
		return -1;
	}

	for(i = 0; i < 8; i++){  // set pin mode as output(GPIO0~GPIO7)
		pinMode(i, OUTPUT);
	}

	while(1){
		for(i = 0; i < sizeof(SegCode)/sizeof(uchar); i++){ // display 0~9,A~F
			digitalWriteByte(SegCode[i]);
			delay(500);
		}
		digitalWriteByte(0x00);   //segment off
		delay(1000);
	}

	return 0;
}
