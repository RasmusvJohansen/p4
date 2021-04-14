#include <iostream>
#include <memory.h>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;



//Billede størrelse
const int m = 640;
const int n = 480;

//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel image[m][n];

void TESTreadFPGA(){
	int count;
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			image[i][j].R = count;
			count++;
		}
		for(int j=0; j<n; j++){
			image[i][j].G = count;
			count++;
		}
		for(int j=0; j<n; j++){
			image[i][j].B = count;
			count++;
		}
	}
}



int a[7];
void readFPGA(){
	
}

const int pin0 = 0;
const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 1;
const int pin4 = 4;
const int pin5 = 5;
const int pin6 = 6;
const int pin7 = 26;

const int mikrosekund = 1000000;

int main(){
	wiringPiSetup();
	pinMode(pin0, INPUT);
	pinMode(pin1, INPUT);
	pinMode(pin2, INPUT);
	pinMode(pin3, INPUT);
	pinMode(pin4, INPUT);
	pinMode(pin5, INPUT);
	pinMode(pin6, INPUT);
	pinMode(pin7, INPUT);
	
	
	
	
	while(1){
		cout << pin0 << " :" << digitalRead(pin0) << "\n";
		cout << pin1 << " :" << digitalRead(pin1) << "\n";
		cout << pin2 << " :" << digitalRead(pin2) << "\n";
		cout << pin3 << " :" << digitalRead(pin3) << "\n";
		cout << pin4 << " :" << digitalRead(pin4) << "\n";
		cout << pin5 << " :" << digitalRead(pin5) << "\n";
		cout << pin6 << " :" << digitalRead(pin6) << "\n";
		cout << pin7 << " :" << digitalRead(pin7) << "\n \n";
		cout << "\n";
		usleep(0.2*mikrosekund);
		a[0] = digitalRead(pin0);
		a[1] = digitalRead(pin1);
		a[2] = digitalRead(pin2);
		a[3] = digitalRead(pin3);
		a[4] = digitalRead(pin4);
		a[5] = digitalRead(pin5);
		a[6] = digitalRead(pin6);
		a[7] = digitalRead(pin7);
		
		unsigned int number = 0b00000000;
		for (int i=0; i<8; i++){
			number += a[i] << i;
		}
		
		//number = a[7] << 7 | a[6] << 6 ;
		
		cout << number << "\n";
		usleep(5*mikrosekund);
		
	}
}



