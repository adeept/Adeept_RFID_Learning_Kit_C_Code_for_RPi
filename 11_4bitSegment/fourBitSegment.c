/*
* Filename    : fourBitSegment.c
* Description : display 1,2,3,4...
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/21
*/
#include <wiringPi.h>
#include <stdio.h>

#define   Bit0    8
#define   Bit1    9
#define   Bit2   10
#define   Bit3   11

unsigned char const SegCode[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

unsigned char DatBuf[4] = {0,0,0,0};

int cnt = 0;

void sysInit(void)
{
	int i;

	for(i = 0; i < 12; i++){
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}	
}

void do_cnt(void)
{
	DatBuf[0] = SegCode[cnt % 10];
	DatBuf[1] = SegCode[cnt % 100 / 10];
	DatBuf[2] = SegCode[cnt % 1000 / 100];
	DatBuf[3] = SegCode[cnt / 1000];
}

void display(void)
{
	int i;

	for(i = 0;i < 100; i++){
		digitalWrite(Bit0, 0);
		digitalWrite(Bit1, 1);
		digitalWrite(Bit2, 1);
		digitalWrite(Bit3, 1);
		digitalWriteByte(DatBuf[0]);

		delay(1);

		digitalWrite(Bit0, 1);
		digitalWrite(Bit1, 0);
		digitalWrite(Bit2, 1);
		digitalWrite(Bit3, 1);
		digitalWriteByte(DatBuf[1]);

		delay(1);

		digitalWrite(Bit0, 1);
		digitalWrite(Bit1, 1);
		digitalWrite(Bit2, 0);
		digitalWrite(Bit3, 1);
		digitalWriteByte(DatBuf[2]);

		delay(1);

		digitalWrite(Bit0, 1);
		digitalWrite(Bit1, 1);
		digitalWrite(Bit2, 1);
		digitalWrite(Bit3, 0);
		digitalWriteByte(DatBuf[3]);

		delay(1);
	}
	cnt++;
	if(cnt == 10000){
		cnt = 0;
	}
}

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}

	sysInit();

	while(1){
		do_cnt();
		display();
	}

	return 0;
}
