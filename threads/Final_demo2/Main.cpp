//MAIN

//Inkludere biblioteker til de andre funktioner
#include "decoder.h"
#include "Image.h"
#include <filesystem>



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
#include <sstream>
#include <iomanip>
#include <wiringSerial.h>
#include <errno.h>
#include <cstring>
#include <fstream>



#include <stdio.h>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <iomanip>




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
pthread_mutex_t bLock;
pthread_mutex_t gLock;
int i = 0;
int s = 0;
int picNumber = 0;
int billedeCounter = 0;
string randomName;
string skaleretName;
string jpgName;
char* c;
int countSort = 0;
bool storage = true;



//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel billede[m][n];

struct brand{
	int i, j;
};
brand brandPixels[m][n];






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
	//cout << billede[200][200].B << "\n";
	cout << "FPGA læst \n";
	
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
    
    randomName = "/home/pi/Desktop/Storage/0RAW/random" + to_string(billedeCounter) + ".bmp";
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
    
    skaleretName = "/home/pi/Desktop/Storage/1Skaleret/Skaleret" + to_string(billedeCounter) + ".bmp";
    jpgName = "/home/pi/Desktop/Storage/2Komprimeret/Komprimeret" + to_string(billedeCounter) + ".jpg";
    
    imwrite(jpgName, gemtBillede, {IMWRITE_JPEG_QUALITY, 15});
    imwrite(skaleretName,gemtBillede);
    billedeCounter ++;
    
}

void* T1 (void* arg) { //Thread til billede delen
	while(storage == true) {
	//for(int i = 0; i < 10; i++) {
	
	pthread_mutex_lock(&gLock);
	

	printf("\n Billede program startet \n");


	fakeReadFPGA();
	lavBMP();
	billedebehandling();
	skalerKomprimer();
	// put billede i queue

	
	printf("\n Billede program sluttet \n");
	cout << storage << "\n";
	//sleep(2.5);
	
	pthread_mutex_unlock(&gLock);


}
	return NULL; 
}

void* T2 (void* arg) { //Thread til GPS delen
	while(1) {
		
		pthread_mutex_lock(&bLock);
		
		laesGPS();
		//Put GPS data i queue
		
		pthread_mutex_unlock(&bLock);
		

	}
	pthread_exit(NULL);
	return NULL;
}

void* T3(void* arg){ //Thread til sende delen
	
	while(1){
		pthread_mutex_lock(&gLock);
		pthread_mutex_lock(&bLock);
		
		printf("Sover i 5 \n");
		sleep(5);
		
		//åben billede fra billede queue
		//åben gps fra gps queue
		//kombiner billede fra GPS og billede Q.
		
		pthread_mutex_unlock(&gLock);
		pthread_mutex_unlock(&bLock);
		
		
		//send billede. 
		
	
}}

void* T4(void* arg) { //Threda til failsafe med mængden af billeder
	for(int i; i < 10; i++) {
		sleep(1);
		cout << "FAILSAFE VÆRDI: " << i << "\n ";
		
		
	}
	storage = false;
	return NULL;
}


int main () {
	
    pthread_t newthread, newthread2, newthread3, newthread4;
    printf("Program starter \n");
    
    
    pthread_create(&newthread, NULL, T1, NULL);    
    pthread_create(&newthread2, NULL, T2, NULL);
    //pthread_create(&newthread3, NULL, T3, NULL);
    pthread_create(&newthread4, NULL, T4, NULL);
    pthread_join(newthread, NULL);
    pthread_join(newthread2, NULL);
    //pthread_join(newthread3, NULL);
    pthread_join(newthread4, NULL);
    
    

    printf("Program slutter \n");
    sleep(5);
}
