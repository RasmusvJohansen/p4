#include <stdio.h> 
#include <wiringPi.h>
#include <iostream>
using namespace std;

#define LED 17

int main(void)
{
	wiringPiSetupGpio();
	pinMode(LED, OUTPUT);
	cout << "Start";
	for (;;){
		digitalWrite(LED,1);
		delay(5);
		digitalWrite(LED,0);
		delay(5);
	}
	return 0;
}
