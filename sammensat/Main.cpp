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
    imwrite("test/skaleretRandom.jpg", gemtBillede, {IMWRITE_JPEG_QUALITY, 15});
    imwrite("test/skalretRandom.bmp",gemtBillede);
    cout << "Skaleret gemt .bmp\n";
    cout << "Komprimeret gemt .jpg\n";
    
}




int main(){
	std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
	fakeReadFPGA();
	lavBMP();
	billedebehandling();
	skalerKomprimer();
	std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
	cout << "\n";

}





