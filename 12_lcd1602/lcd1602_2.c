/*
* File name   : lcd1602_2.c
* Description : lcd1602 display
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/05/02
*/
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>

const unsigned char Buf[] = ">>---Adeept---<<";
const unsigned char myBuf[] = "  adeept.com    ";

int main(void)
{
	int fd;
	int i;
	
	if(wiringPiSetup() == -1){
		exit(1);
	}
	
	fd = lcdInit(2,16,4, 5,4,  0,1,2,3,4,5,6,7); //see /usr/local/include/lcd.h
	if (fd == -1){
		printf("lcdInit 1 failed\n") ;
		return 1;
	}
	sleep(1);

	lcdClear(fd);
	lcdPosition(fd, 0, 0); 
	lcdPuts(fd, "Welcom To--->");

	lcdPosition(fd, 0, 1); 
	lcdPuts(fd, "  adeept.com");

	sleep(1);
//	lcdClear(fd);
	
	while(1){
		for(i=0;i<sizeof(Buf)-1;i++){
			lcdPosition(fd, i, 1);
			lcdPutchar(fd, *(Buf+i));
			delay(200);
		}
		lcdPosition(fd, 0, 1); 
		lcdClear(fd);
		sleep(0.5);
		for(i=0; i<16; i++){
			lcdPosition(fd, i, 0);
			lcdPutchar(fd, *(myBuf+i));
			delay(100);
		}
	}

	return 0;
}
