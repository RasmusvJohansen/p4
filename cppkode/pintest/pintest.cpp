#include <stdio.h> 
#include <wiringPi.h>
#include <iostream>
using namespace std;

#define pin2 2
#define pin3 3
#define pin4 4
#define pin17 17
#define pin27 27
#define pin22 22
#define pin14 14
#define pin15 15
int main(void)
{
	wiringPiSetupGpio();
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	pinMode(pin17, OUTPUT);
	pinMode(pin27, OUTPUT);
	pinMode(pin22, OUTPUT);
	pinMode(pin14, OUTPUT);
	pinMode(pin15, OUTPUT);
	cout << "Start";
	for (;;){
		cout << "pin a0 til gpio 2: " << digitalRead(pin2) << "\n";
		cout << "pin a1 til gpio 3: " << digitalRead(pin3) << "\n";
		cout << "pin a2 til gpio 4: " << digitalRead(pin4) << "\n";
		cout << "pin a3 til gpio 17: " << digitalRead(pin17) << "\n";
		cout << "pin a4 til gpio 27: " << digitalRead(pin27) << "\n";
		cout << "pin a5 til gpio 22: " << digitalRead(pin22) << "\n";
		cout << "pin a6 til gpio 14: " << digitalRead(pin14) << "\n";
		cout << "pin a7 til gpio 15: " << digitalRead(pin15) << "\n";
		delay(300);
		/*digitalWrite(LED,0);
		delay(5000);*/
	}
	return 0;
}
