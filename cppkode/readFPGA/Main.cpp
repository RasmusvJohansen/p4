#include <iostream>
#include <memory.h>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;


const int mikrosekund = 1000000;
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

const int pin0 = 2;
const int pin1 = 22;
const int pin2 = 27;
const int pin3 = 26;
const int pin4 = 6;
const int pin5 = 5;
const int pin6 = 23;
const int pin7 = 24;
unsigned int number = 0b00000000;
int a[7];
void readFPGA(){
	pinMode(pin0, OUTPUT);
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	pinMode(pin5, OUTPUT);
	pinMode(pin6, OUTPUT);
	pinMode(pin7, OUTPUT);
	digitalWrite(pin0, LOW);
	digitalWrite(pin1, LOW);
	digitalWrite(pin2, LOW);
	digitalWrite(pin3, LOW);
	digitalWrite(pin4, LOW);
	digitalWrite(pin5, LOW);
	digitalWrite(pin6, LOW);
	digitalWrite(pin7, LOW);
	a[0] = digitalRead(pin0);
	a[1] = digitalRead(pin1);
	a[2] = digitalRead(pin2);
	a[3] = digitalRead(pin3);
	a[4] = digitalRead(pin4);
	a[5] = digitalRead(pin5);
	a[6] = digitalRead(pin6);
	a[7] = digitalRead(pin7);
	cout << pin0 << " :" << a[0] << "\n";
	cout << pin1 << " :" << a[1] << "\n";
	cout << pin2 << " :" << a[2] << "\n";
	cout << pin3 << " :" << a[3] << "\n";
	cout << pin4 << " :" << a[4] << "\n";
	cout << pin5 << " :" << a[5] << "\n";
	cout << pin6 << " :" << a[6] << "\n";
	cout << pin7 << " :" << a[7] << "\n \n";
	cout << "\n";
	number = 0b00000000;
	/*for (int i=0; i<8; i++){
		number += a[i] << i;
	}*/
}




int count = 0;
int main(){
	wiringPiSetup();
	
	while(1){
			pinMode(pin0, OUTPUT);
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	pinMode(pin5, OUTPUT);
	pinMode(pin6, OUTPUT);
	pinMode(pin7, OUTPUT);
	digitalWrite(pin0, HIGH);
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
	digitalWrite(pin3, HIGH);
	digitalWrite(pin4, HIGH);
	digitalWrite(pin5, HIGH);
	digitalWrite(pin6, HIGH);
	digitalWrite(pin7, HIGH);
	}
	/*
	while(1){
		for (int i=0; i<m; i++){
			for(int j=0; j<n; j++){
				readFPGA();
				if(count == 0){
					image[i][j].R = number;
					count++;
					//cout << number << "\n";
				}
			}
			for(int j=0; j<n; j++){
				readFPGA();
				if(count == 1){	
					image[i][j].G = number;
					count++;
					//cout << number << "\n";
				}
			}
			for(int j=0; j<n; j++){
				readFPGA();
				if(count == 2){	
					image[i][j].B = number;
					count = 0;
					//cout << number << "\n";
				}
			}
		}
		
		
		cout << "R: " << image[2][2].R << "\n";
		cout << "G: " << image[2][2].G << "\n";
		cout << "B: " << image[2][2].B << "\n";
		//number = a[7] << 7 | a[6] << 6 ;
		//cout << number << "\n";
		usleep(0.5*mikrosekund);
	}
*/
}



