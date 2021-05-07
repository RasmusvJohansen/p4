#include <stdio.h> 
#include <wiringPi.h>
#include <iostream>
using namespace std;

#define pin2 2
#define pin3 3
#define pin17 17
#define pin27 27
#define pin22 22
#define pin23 23
#define pin24 24
#define pin25 25
unsigned int number = 0b00000000;
int a[7];
int main(void)
{
	wiringPiSetupGpio();
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin17, INPUT);
	pinMode(pin27, INPUT);
	pinMode(pin22, INPUT);
	pinMode(pin23, INPUT);
	pinMode(pin24, INPUT);
	pinMode(pin25, INPUT);
	
	cout << "Start";
	for (;;){
		/*cout << "pio 17: " << digitalRead(pin17) << "\n";
		cout << "gpio 27: " << digitalRead(pin27) << "\n";
		cout << "gpio 22: " << digitalRead(pin22) << "\n";
		cout << "gpio 2: " << digitalRead(pin2) << "\n";
		cout << "gpio 3: " << digitalRead(pin3) << "\n";
		cout << "gpio 23: " << digitalRead(pin23) << "\n";
		cout << "gpio 24: " << digitalRead(pin24) << "\n";
		cout << "gpio 25: " << digitalRead(pin25) << "\n";*/
		delay(20);
		a[0] = digitalRead(pin2);
		a[1] = digitalRead(pin3);
		a[2] = digitalRead(pin17);
		a[3] = digitalRead(pin27);
		a[4] = digitalRead(pin22);
		a[5] = digitalRead(pin23);
		a[6] = digitalRead(pin24);
		a[7] = digitalRead(pin25);
		//cout << a[0];
		number = 0b00000000;
		for (int i=0; i<8; i++){
			number += a[i] << i;
		}
		cout << number << "\n";
	}
	return 0;
}
