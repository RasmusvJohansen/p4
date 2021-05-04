//MAIN

//Inkludere biblioteker til de andre funktioner

#include "GPS_lib.h"
#include "Image.h"
//#include "Image.cpp"



//Inkludere almindelige biblioteker

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "Image.h"
#include <memory.h>
#include <cstdlib>
#include <wiringPi.h>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <semaphore.h>
#include <string.h>
 
using namespace cv;
using namespace std;

const int mikrosekund = 1000000;
//Billede størrelse
const int m = 640;
const int n = 480;


const int width = 640;
const int height = 480;
Image image(width, height);
pthread_t tid[2];
int counter;
pthread_mutex_t lockz;
int i = 0;
int s = 0;
int picNumber = 0;
int billedeCounter = 0;
string randomName;
string skaleretName;
string jpgName;
char* c;


//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel billede[m][n];

struct brand{
	int i, j;
};
brand brandPixels[m][n];

int countSort = 0;

void fakeReadFPGA () {
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
	cout << billede[200][200].B << "\n";
	cout << "done\n";
	
}

void lavBMP(){
	Image image(width, height);
	for (int i= 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
			image.SetColor(Color(billede[i][j].R,billede[i][j].G,billede[i][j].B), j, i);
        }	
    }
    
    randomName = "random" + to_string(billedeCounter) + ".bmp";
    c = const_cast<char*>(randomName.c_str());
    
    
    
    image.Export(c);
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
	countSort = 0;
}

void skalerKomprimer(){
	Mat gemtBillede;
    gemtBillede = imread(c,IMREAD_COLOR);
    //imshow("Originalt billede",gemtBillede);
    //waitKey(0);
    resize(gemtBillede,gemtBillede,Size(192,144));    
    //imshow("nedskaleret",gemtBillede);
    //waitKey(0);
    //imwrite("test/random.jpg",gemtBillede);
    
    skaleretName = "Skaleret" + to_string(billedeCounter) + ".bmp";
    jpgName = "Skaleret" + to_string(billedeCounter) + ".jpg";
    
    imwrite(jpgName, gemtBillede, {IMWRITE_JPEG_QUALITY, 15});
    imwrite(skaleretName,gemtBillede);
    billedeCounter ++;
    
}


void* trythis(void* arg) {
	
	while(1) {
	pthread_mutex_lock(&lockz);
	

	counter = 1;
	printf("\n Billede program startet \n");

	fakeReadFPGA();
	lavBMP();
	billedebehandling();
	skalerKomprimer();
	
	
	counter = 1;
	printf("\n Billede program sluttet \n");
	
	pthread_mutex_unlock(&lockz);

}

	return NULL; 
}

void* testCounter(void* count) {
	
	pthread_mutex_lock(&lockz);
	

	counter = 2;
	printf("\n Job 2 starter \n");



	for (i = 0; i < 10; i++) {
	s += 1;
	cout << s << "\n"; 

	sleep(1);
	};
	
	
	
	
	counter = 2;
	printf("\n Job 2 slutter \n");
	
	pthread_mutex_unlock(&lockz);

	return NULL;
}


void almFunc() {;
    for(int g = 0; g < 10; g++) { //Bestemmer antallet af gange programmet kører
sleep(1);
printf("Program starter på ny \n");

    }}


int main () {
    pthread_t newthread, newthread2;
    printf("Program starter \n");
    
    pthread_create(&newthread2, NULL, trythis, NULL);    
    //pthread_create(&newthread, NULL, TestFuncGPS, NULL);
    //almFunc();
    pthread_join(newthread2, NULL);
    //pthread_join(newthread, NULL);

    
    

}
