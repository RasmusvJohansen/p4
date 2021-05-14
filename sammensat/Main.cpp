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
#include <opencv2/opencv.hpp>
using namespace cv;



const int mikrosekund = 1000000;
//Billede størrelse
const int m = 640;
const int n = 480;

int countSort = 0;
int countBrand = 0;

String filepath = "test";




//Struct til at gemme RGB data for hver pixel
struct pixel{
	volatile int R, G, B;
};
pixel billede[m][n];

struct brand{
	volatile int i, j;
};
brand brandPixels[m][n];

volatile int rawRGB555data[2*m*n];

void fakeReadFPGA(){
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			billede[i][j].R = rand() % 255 + 1;
		}
		for(int j=0; j<n; j++){
			billede[i][j].G = rand() % 255 + 1;
		}
		for(int j=0; j<n; j++){
			billede[i][j].B = rand() % 255 + 1;
		}
	}
	cout << "FPGA læst\n";
}

#define pin2 2
#define pin4 4
#define pin17 17
#define pin27 27
#define pin22 22
#define pin23 23
#define pin24 24
#define pin25 25


#define flagD 12
#define done 8
#define mem 6
#define rpi 7
//#define tx 26
//#define rx 16

volatile int tx = 26;
volatile int rx = 16;


volatile unsigned int number = 0;
char a[7];


void definePinMode(){
	wiringPiSetupGpio();
	pinMode(flagD, INPUT);
	pinMode(pin2, INPUT);
	pinMode(pin4, INPUT);
	pinMode(pin17, INPUT);
	pinMode(pin27, INPUT);
	pinMode(pin22, INPUT);
	pinMode(pin23, INPUT);
	pinMode(pin24, INPUT);
	pinMode(pin25, INPUT);
	//pinMode(PCLK, OUTPUT);
	pinMode(rpi, OUTPUT);
	pinMode(tx, OUTPUT);
	pinMode(rx, INPUT);
	pinMode(done, OUTPUT);
	pinMode(mem, OUTPUT);
}

void read(){
	//digitalWrite(PCLK,0);
	digitalWrite(rpi,1);
	//digitalWrite(pin1, 1);
	digitalWrite(tx,1);
	
}

void doneRead(){
	//digitalWrite(PCLK, 1);
	//digitalWrite(pin1, 0);	
	digitalWrite(rpi,0);
	digitalWrite(tx,0);
	//digitalWrite(mem,0);
}

void readFPGA(){
	
	for(int j = 0; j<1271*6; j++){
		//while(digitalRead(done2)==0){cout << "her\n";}
			while(digitalRead(rx) == 1){}
			
			read();
			//delay(3);
		
			while(digitalRead(rx) == 0){}
			a[0] = digitalRead(pin2);
			//delay(0.1);
			a[1] = digitalRead(pin4);
			//delay(0.1);
			a[2] = digitalRead(pin17);
			//delay(0.1);
			a[3] = digitalRead(pin27);
			//delay(0.1);
			a[4] = digitalRead(pin22);
			//delay(0.1);
			a[5] = digitalRead(pin23);
			//delay(0.1);
			a[6] = digitalRead(pin24);
			//delay(0.1);
			a[7] = digitalRead(pin25);
			//cout << a[0];
			number = 0b00000000;
			//delay(0.1);
			for (int i=0; i<8; i++){
				number += a[i] << i;
			}
			//cout << number << "\n";
			doneRead();
			rawRGB555data[j] = number;
			cout << rawRGB555data[j] << " ";
			//delay(3);
			//cout << "DEN ER HER\n";
		
		
	
	}
	//return number;
	cout << "\n\n";
	digitalWrite(done,1);
	
}

void convertToRGB888(){
	digitalWrite(done,0);
	for (int i=0; i<n; i++){
		int t = 0;
		for(int j=0; j<1271; j=j+2){
			billede[t][i].R = ((rawRGB555data[j] & 124) >> 2) * 8;
			//cout << billede[i][t].R << " ";
			billede[t][i].G = (((rawRGB555data[j] & 3) << 3) | ((rawRGB555data[j+1] & 224) >> 5))*8 ;
			//cout << billede[i][t].G << " ";
			billede[t][i].B = (rawRGB555data[j+1] & 31)*8;
			//cout << billede[i][t].B << "\n";
			t++;
		}
		
	}
	cout << "\n\n";
}



/*
void addToArray(){
	for (int i=0; i<m; i++){
		int t = 0;
		for(int j=0; j<n; j=j+2){
			readFPGA();
			billede[i][t].R = number;
		}
		for(int j=0; j<n; j=j+2){
			readFPGA();
			billede[i][t].G = number;
		}
		for(int j=0; j<n; j=j+2){
			readFPGA();
			billede[i][t].B = number;
		}
		t++;
	}
}*/


void billedebehandling(){
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(billede[i][j].R < 27 and billede[i][j].G < 27 and billede[i][j].B < 27){
				countSort = countSort + 1;
			}
			if(billede[i][j].R > 150 and billede[i][j].G > 50 and billede[i][j].B > 0){
				if(billede[i][j].R < 255 and billede[i][j].G < 233 and billede[i][j].B < 66){
					//cout << "brand ved: " << i << ", " << j << "\n";
					brandPixels[i][j].i = i;
					brandPixels[i][j].j = j;
					countBrand++;
				}
			}
			if(i != brandPixels[i][j].i and j != brandPixels[i][j].j){
				billede[i][j].R = 255;
				billede[i][j].G = 255;
				billede[i][j].B = 255;
			}
		}
	}
	cout << "Sorte pixels: " << countSort << "\n";
	if(countSort > (n*m)*0.4){
		cout << "Billedet kan ikke bruges\n";
	}
	cout << "Brand pixels: " << countBrand << "\n";
}

void lavBMP(){
	Image image(m, n);
	for (int i= 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
			image.SetColor(Color(billede[i][j].R,billede[i][j].G,billede[i][j].B), i, j);
        }	
    }
    image.Export("test2/main.bmp");

}

void skalerKomprimer(){
	Mat gemtBillede;
    gemtBillede = imread("test/random.bmp",IMREAD_COLOR);
    //imshow("Originalt billede",gemtBillede);
    //waitKey(0);
    resize(gemtBillede,gemtBillede,Size(192,144));    
    //imshow("nedskaleret",gemtBillede);
    //waitKey(0);
    //imwrite("test/random.jpg",gemtBillede);
    putText(gemtBillede,"57.01176883,9.983356667", Point(10,10),
	FONT_HERSHEY_PLAIN,0.7,Scalar(225,255,250),0.1,CV_AVX);
    imwrite("test2/skaleretMain.jpg", gemtBillede, {IMWRITE_JPEG_QUALITY, 15});
    imwrite("test2/skaleretMain.bmp",gemtBillede);
    cout << "Skaleret gemt .bmp\n";
    cout << "Komprimeret gemt .jpg\n";
    
}




int main(){	
	
	std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
	//fakeReadFPGA();
	definePinMode();
	//digitalWrite(rpi, 0);
	cout << "venter på at kamera når start" << "\n";
	//while(digitalRead(flagD) == 0);
	//while(digitalRead(flagD) == 1){cout <<"her\n";}
	cout << "kamera tager billede" << "\n";
	//while(digitalRead(flagD) == 0){cout <<"her2\n";}
	cout << "kamera er færdig med at tage billede";
	//digitalWrite(rpi, 1);
	readFPGA();
	convertToRGB888();
	//addToArray();
	lavBMP();
	billedebehandling();
	skalerKomprimer();
	std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
	cout << "\n";

}






