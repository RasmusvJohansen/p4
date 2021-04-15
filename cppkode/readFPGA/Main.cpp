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
const int pin1 = 3;
const int pin2 = 4;
const int pin3 = 17;
const int pin4 = 27;
const int pin5 = 22;
const int pin6 = 14;
const int pin7 = 15;
unsigned int number = 0b00000000;
int a[7];
void readFPGA(){
	pinMode(pin0, INPUT);
	pinMode(pin1, INPUT);
	pinMode(pin2, INPUT);
	pinMode(pin3, INPUT);
	pinMode(pin4, INPUT);
	pinMode(pin5, INPUT);
	pinMode(pin6, INPUT);
	pinMode(pin7, INPUT);
	a[0] = digitalRead(pin0);
	a[1] = digitalRead(pin1);
	a[2] = digitalRead(pin2);
	a[3] = digitalRead(pin3);
	a[4] = digitalRead(pin4);
	a[5] = digitalRead(pin5);
	a[6] = digitalRead(pin6);
	a[7] = digitalRead(pin7);
	number = 0b00000000;
	for (int i=0; i<8; i++){
		number += a[i] << i;
	}
	//usleep(0.001);
}





int main(){
	wiringPiSetup();
	while(1){
		int count = 0;
		for (int i=0; i<m; i++){
			for(int j=0; j<n; j++){
				readFPGA();
				
				if(count == 0){
					image[i][j].R = number;
					count = 1;
					cout << "også her";
					break;
				}
				if(count == 1){
					image[i][j].G = number;
					count = 2;
					cout << "den er " << "\n";
					break;
				}	
				if(count == 2){
					image[i][j].B = number;
					count = 0;
					cout << "den er her" << "\n";
					break;
				}
			}cout << "helloooo" << "\n";
		}
		
		/*
		
		for (int i=0; i<m; i++){
			for(int j=0; j<n; j++){
				readFPGA();
				if(count == 0){
					image[i][j].R = number;
					count = 1;
					
					//cout << number << "\n";
				}
			}
			for(int j=0; j<n; j++){
				cout << "her";
				readFPGA();
				if(count == 1){	
					image[i][j].G = number;
					count = 2;
					
					//cout << number << "\n";
				}
			}
			
			for(int j=0; j<n; j++){
				cout << count;
				readFPGA();
				if(count == 2){	
					image[i][j].B = number;
					count = 100;
					cout << "den er erh";
					//cout << number << "\n";
				}
			}
		}*/
		//number = a[7] << 7 | a[6] << 6 ;
		//cout << number << "\n";
		//usleep(0.5*mikrosekund);
		break;
	}

		cout << "R: " << image[2][2].R << "\n";
		cout << "G: " << image[2][2].G << "\n";
		cout << "B: " << image[2][2].B << "\n";

}



