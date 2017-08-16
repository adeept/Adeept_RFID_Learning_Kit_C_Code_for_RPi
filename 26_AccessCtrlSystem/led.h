#ifndef _LED_H_
#define _LED_H_

#include <wiringPi.h>

#define  LedPin    0

int ledInit(void);
void ledFlash(int n);


#endif
