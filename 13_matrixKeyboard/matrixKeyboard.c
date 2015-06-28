#include <wiringPi.h>
#include <stdio.h>

const int ROW[]    = {0, 1, 2, 3};
const int COLUMN[] = {4, 5, 6, 7};

int getKey(void)
{
	int i;
	int tmpRead;
	int rowVal = -1;
	int colVal = -1;
	char keyVal;

	for(i = 0; i < 4; i++){
		pinMode(COLUMN[i], OUTPUT);
		digitalWrite(COLUMN[i], LOW);
	}

	for(i = 0; i < 4; i++){
		pinMode(ROW[i], INPUT);
		pullUpDnControl(ROW[i], PUD_UP);
	}
	
	for(i = 0; i < 4; i++){
		tmpRead = digitalRead(ROW[i]);
		if(tmpRead == 0){
			rowVal = i;
		}
	}

	if(rowVal < 0 || rowVal > 3){
		return -1;
	}
	
	for(i = 0; i < 4; i++){
		pinMode(COLUMN[i], INPUT);
		pullUpDnControl(COLUMN[i], PUD_UP);
	}

	pinMode(ROW[rowVal], OUTPUT);
	digitalWrite(ROW[rowVal], LOW);

	for(i = 0; i < 4; i++){
		tmpRead = digitalRead(COLUMN[i]);
		if(tmpRead == 0){
			colVal = i;
		}
	}
	
	if(colVal < 0 || colVal > 3){
		return -1;
	}

	//printf("%d, %d\n", rowVal, colVal);
	switch(rowVal){
		case 0:
			switch(colVal){
				case 0: keyVal = 0; break; 
				case 1: keyVal = 1; break;
				case 2: keyVal = 2; break;
				case 3: keyVal = 3; break;
				default:
					break;
			}
			break;
		case 1:
			switch(colVal){
				case 0: keyVal = 4; break;
				case 1: keyVal = 5; break;
				case 2: keyVal = 6; break;
				case 3: keyVal = 7; break;
				default:
					break;
			}
			break;
		case 2:
			switch(colVal){
				case 0: keyVal = 8; break;
				case 1: keyVal = 9; break;
				case 2: keyVal = 10; break;
				case 3: keyVal = 11; break;
				default:
					break;
			}
			break;
		case 3:
			switch(colVal){
				case 0: keyVal = 12; break;
				case 1: keyVal = 13; break;
				case 2: keyVal = 14; break;
				case 3: keyVal = 15; break;
				default:
					break;
				
			}
			break;
		default: 
			break;
	}

	return keyVal;
}

int main(void)
{
	int i;
	int key = -1;

	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	while(1){
		key = getKey();
		if(key != -1){
			switch(key){
				case 0: printf("1\n"); break;
				case 1: printf("2\n"); break;
				case 2: printf("3\n"); break;
				case 3: printf("A\n"); break;
				case 4: printf("4\n"); break;
				case 5: printf("5\n"); break;
				case 6: printf("6\n"); break;
				case 7: printf("B\n"); break;
				case 8: printf("7\n"); break;
				case 9: printf("8\n"); break;
				case 10: printf("9\n"); break;
				case 11: printf("C\n"); break;
				case 12: printf("*\n"); break;
				case 13: printf("0\n"); break;
				case 14: printf("#\n"); break;
				case 15: printf("D\n"); break;
				default: 
					break;
			}
		}
		delay(200);
	}

	return 0;
}

