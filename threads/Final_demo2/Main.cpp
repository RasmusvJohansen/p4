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
using namespace std;
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
int x=0;

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




void laesGPS(){
  int serial_port; 
  char dat,buff[100],GGA_code[3];
  unsigned char IsitGGAstring=0;
  unsigned char GGA_index=0;
  unsigned char is_GGA_received_completely = 0;
  
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)		/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    //return 1 ;
  }

  if (wiringPiSetup () == -1)							/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    //return 1 ;
  }
string str;
ofstream myfile;
string gpsArray[67];
stringstream ss;
	int l = 0;
  while(x < 10){
  
		if(serialDataAvail (serial_port) )		/* check for any data available on serial port */
		  { 
			dat = serialGetchar(serial_port);		/* receive character serially */		
			if(dat == '$'){
				IsitGGAstring = 0;
				GGA_index = 0;
			}
			else if(IsitGGAstring ==1){
				//cout << dat;
				gpsArray[l] = dat;
				l++;
				//buff[GGA_index++] = dat;
				if(dat=='\r')
					is_GGA_received_completely = 1;
				}
			else if(GGA_code[0]=='G' && GGA_code[1]=='G' && GGA_code[2]=='A'){
				IsitGGAstring = 1;
				GGA_code[0]= 0; 
				GGA_code[0]= 0;
				GGA_code[0]= 0;		
				}
			else{
				GGA_code[0] = GGA_code[1];
				GGA_code[1] = GGA_code[2];
				GGA_code[2] = dat;
				}
			
		  }
		if(is_GGA_received_completely==1){
			//printf("$GPGGA,%s",buff);
			l = 0;	//array resettes
			ss.str("");
			ss.clear();
			for(int i = 0; i<67; i++){ //laver datarray om til en string, så den kan  bruges i decoderen.
				ss << gpsArray[i];
			}
			string test;
			string strr("$GPGGA,"+ss.str());
			//cout << strr;
			
			NMEA_decoder2(strr);

			//cout << "\n" << str << "også her\n";
			
			/*myfile.open("test.txt",ofstream::app);
			  if (myfile.is_open())
			  
			  {
				//istream fileData("data.txt", ifstream::binary);
				myfile.seekp (0,ios_base::end);  
				
				myfile << "GGA: %s" << str << "\n";
				//GotoLine(myfile, 8);
				myfile.close();
				
			  }
			  else cout << "Unable to open file";*/
			  
			  
			  
			is_GGA_received_completely = 0;
			x++;
			
			
				
		}
	}

}





void* T1 (void* arg) {
	
	for(int i = 0; i < 10; i++) {
	pthread_mutex_lock(&bLock);
	

	printf("\n Billede program startet \n");
	

	fakeReadFPGA();
	lavBMP();
	billedebehandling();
	skalerKomprimer();
	// put billede i queue

	
	printf("\n Billede program sluttet \n");
	
	pthread_mutex_unlock(&bLock);

}
	return NULL; 
}

void* T2 (void* arg) {
	while(1) {
		pthread_mutex_lock(&gLock);
		
		laesGPS();
		//Put GPS data i queue
		
		pthread_mutex_unlock(&gLock);

		pthread_exit(NULL);
		
	}
	return NULL;
}


void* T3(void* arg){
	while(1){
		//pthread_mutex_lock(&A_sig);
		//pthread_mutex_lock(&B_sig);
		
		//åben billede fra billede queue
		//åben gps fra gps queue
		//kombiner billede fra GPS og billede Q.
		
		//pthread_mutex_unlock(&block);
		//pthread_mutex_unlock(&T2_sig);
		
		
		//send billede. 
		
	
}}



void almFunc() {;
    for(int g = 0; g < 10; g++) { //Bestemmer antallet af gange programmet kører
sleep(1);
printf("Program starter på ny \n");

    }}


int main () {
	
    pthread_t newthread, newthread2;
    printf("Program starter \n");
    
    
    pthread_create(&newthread, NULL, T1, NULL);    
    pthread_create(&newthread2, NULL, T2, NULL);
    pthread_join(newthread, NULL);
    pthread_join(newthread2, NULL);
    

    printf("Program slutter \n");
	
    
    

}
