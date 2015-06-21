/*
* File name   : segment_595.c
* Description : display 0~9, A~F on 7-segment display
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/26
*/
#include <wiringPi.h>
#include <stdio.h>

unsigned char SegCode[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};

int main(void)
{
	int i;
	int bit;

	if(wiringPiSetup() < 0){
		printf("wiringPi setup failed !\n");
		return -1;
	}

	sr595Setup(100, 10, 2, 1, 0);

	while(1){
		for(i = 0; i < sizeof(SegCode); i++){
			for(bit = 0; bit < 8; bit++){
				digitalWrite(100+bit, SegCode[i] & (1<<bit));
				delay(1);
			}	
			delay(500);
		}
	}

	return 0;
}
