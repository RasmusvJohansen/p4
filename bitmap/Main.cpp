#include <iostream>
#include <memory.h>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;	
#include <chrono>
#include "Image.h"  


const int mikrosekund = 1000000;
//Billede størrelse
const int m = 20;
const int n = 20;

//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel billede[m][n];

void TESTreadFPGA(){
	int count;
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			billede[i][j].R = count;
			usleep(0.0001);
			count++;
		}
		for(int j=0; j<n; j++){
			billede[i][j].G = count;
			usleep(0.0001);
			count++;
		}
		for(int j=0; j<n; j++){
			billede[i][j].B = count;
			usleep(0.0001);
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
	//cout << a[0];
	number = 0b00000000;
	for (int i=0; i<8; i++){
		number += a[i] << i;
	}
}

int array[m*n]={255,128,255,128,255,128,247,128,139,115,19,140,0,96,0,153,71,96,143,126,255,128,255,128,255,128,247,128,138,115,19,140,0,96,0,153,71,96,143,126,255,128,255,128,255,128,247,128,139,115,19,140,0,95,0,153,71,95,143,127,255,128,255,128,255,128,247,128,139,115,19,140,0,95,0,153,71,95,143,127,255,128,255,128,255,128,247,128,139,115,19,140,0,96,0,153,72,96,143,126,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,72,95,143,132,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,71,95,143,127,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,71,95,143,128,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,71,95,143,127,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,71,95,143,127,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,72,95,143,131,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,72,95,143,127,255,128,255,128,255,128,246,128,138,115,19,140,0,95,0,153,71,95,143,128,255,128,255,128,255,128,247,128,139,115,19,140,0,95,0,153,71,95,143,128,255,128,255,128,255,128,247,128,139,115,19,140,0,95,0,153,71,95,143,128,255,128,255,128,255,128,246,128,138,115,19,140,0,95,0,153,71,95,143,129,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,71,95,143,125,255,128,255,128,255,128,246,128,139,115,19,140,0,95,0,153,71,95,143,125,255,128,255,128,255,128,247,128,139,115,20,140,0,96,0,154,71,96,143,125};



int main(){
	int k = 0;
//	wiringPiSetup();
	//cout << "her";
	for(int i = 0; i<19; i++){
		for(int j = 0; j<6; j++){
			billede[i][j].R = array[k];
			cout << array[k] << "R\n";
			k++;
			billede[i][j].G = array[k];
			cout << array[k] << "G\n";
			k++;
			billede[i][j].B = array[k];
			k++;
			cout << array[k] << "B\n";
		}
		//k=0;
		cout << i << "den er her  \n";
	}
	
	
	
	
	
	
		
	/*	int count = 0;
		
		for(int i=0; i<m;i++){
			for(int j=0; j<n;j++){
				readFPGA();
				//cout << number;
				if(count == 0){
					billede[i][j].R = number;
					count = 1;
					//cout << billede[i][j].R;
					//usleep(0.00001);
				}
				readFPGA();
				if(count == 1){
					billede[i][j].G = number;
					count = 2;
					//usleep(0.00001);
				}
				readFPGA();
				if(count == 2){
					billede[i][j].B = number;
					count = 0;
					//usleep(0.00001);
				}
			}
		}*/
		/*cout << "R: " << billede[2][2].R << "\n";
		cout << "G: " << billede[2][2].G << "\n";
		cout << "B: " << billede[2][2].B << "\n";
		cout << "R: " << billede[200][200].R << "\n";
		cout << "G: " << billede[200][200].G << "\n";
		cout << "B: " << billede[200][200].B << "\n";
		cout << "R: " << billede[400][400].R << "\n";
		cout << "G: " << billede[400][400].G << "\n";
		cout << "B: " << billede[400][400].B << "\n"; */
	
    const int width = 19;
    const int height = 19;

    Image image(width, height);
	
    for (int x= 0; x < width; x++)
    {
        for (int y = 0; y < width; y++)
        {
			image.SetColor(Color(billede[x][y].R,billede[x][y].G,billede[x][y].B), x, y);
			//cout << billede[x][y].R << "\n";
			//cout << billede[x][y].G << "\n";
			//cout << billede[x][y].B << "\n";
        }
    }
    image.Export("arduino.bmp");
    /*std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
    for (int y= 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
			image.SetColor(Color(rand() % 255 + 1,rand() % 255 + 1,rand() % 255 + 1), x, y);
        }
    }
    image.Export("image10.bmp");
	std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
	cout << "\n";*/


}





