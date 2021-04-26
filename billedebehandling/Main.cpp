#include <iostream>
#include <memory.h>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <stdio.h>
using namespace std;	
#include <opencv2/opencv.hpp>


const int mikrosekund = 1000000;
//Billede størrelse
const int m = 640;
const int n = 480;

//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel billede[m][n];


struct brand{
	int i, j;
};

brand brandPixels[m][n];

void TESTreadFPGA(){
	int count;
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			billede[i][j].R = count;
			count++;
		}
		for(int j=0; j<n; j++){
			billede[i][j].G = count;
			count++;
		}
		for(int j=0; j<n; j++){
			billede[i][j].B = count;
			count++;
		}
	}
}



int main(){
	int count;
	for (int i=0; i<m; i++){
		if(count > 255){
			count = 0;
		}
		for(int j=0; j<n; j++){
			//billede[i][j].R = count;
			//billede[i][j].R = rand() % 255 + 1;
			billede[i][j].R = 0;
			count++;
		}
		for(int j=0; j<n; j++){
			//billede[i][j].G = count;
			//billede[i][j].G = rand() % 255 + 1;
			billede[i][j].G = 0;
			count++;
		}
		for(int j=0; j<n; j++){
			//billede[i][j].B = count;
			//billede[i][j].B = rand() % 255 + 1;
			billede[i][j].B = 0;
			count++;
		}
	}
	cout << billede[400][3].R << "\n";
	cout << billede[400][3].G << "\n";
	cout << billede[400][3].B << "\n";
	
	std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
	int countSort = 0;
	for (int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(billede[i][j].R < 27 and billede[i][j].G < 27 and billede[i][j].B < 27){
				countSort = countSort + 1;
				
			}
			if(billede[i][j].R > 150 and billede[i][j].G > 50 and billede[i][j].B > 0){
				if(billede[i][j].R < 255 and billede[i][j].G < 233 and billede[i][j].B < 66){
					cout << "brand ved: " << i << ", " << j << "\n";
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
	std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
	cout << "\n";
	

	cout << billede[100][200].R << "\n";
	cout << billede[100][200].G << "\n";
	cout << billede[100][200].B << "\n";

}






