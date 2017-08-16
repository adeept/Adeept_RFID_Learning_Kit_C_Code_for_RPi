#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <wiringPi.h>

#define  BUZZERPin    1

int buzzerInit(void);
void buzzer(int n);


#endif
