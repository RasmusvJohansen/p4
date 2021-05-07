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
const int m = 100;
const int n = 100;

int countSort = 0;
int countBrand = 0;

String filepath = "test";




//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel billede[m][n];

struct brand{
	int i, j;
};
brand brandPixels[m][n];



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
#define pin3 3
#define pin17 17
#define pin27 27
#define pin22 22
#define pin23 23
#define pin24 24
#define pin25 25

unsigned int number = 0b00000000;
int a[7];

int readFPGA(){
	wiringPiSetupGpio();
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin17, INPUT);
	pinMode(pin27, INPUT);
	pinMode(pin22, INPUT);
	pinMode(pin23, INPUT);
	pinMode(pin24, INPUT);
	pinMode(pin25, INPUT);
	//delay(20);
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
	return number;
	
}

void addToArray(){
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			readFPGA();
			billede[i][j].R = number;
		}
		for(int j=0; j<n; j++){
			readFPGA();
			billede[i][j].G = number;
		}
		for(int j=0; j<n; j++){
			readFPGA();
			billede[i][j].B = number;
		}
	}
}



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
    image.Export("test/random.bmp");

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
    imwrite("test/skaleretRandom.jpg", gemtBillede, {IMWRITE_JPEG_QUALITY, 15});
    imwrite("test/skalretRandom.bmp",gemtBillede);
    cout << "Skaleret gemt .bmp\n";
    cout << "Komprimeret gemt .jpg\n";
    
}




int main(){
	std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
	//fakeReadFPGA();
	addToArray();
	lavBMP();
	billedebehandling();
	skalerKomprimer();
	std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
	cout << "\n";

}






