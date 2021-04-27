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
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/tracking.hpp>
using namespace cv;





   int main() { 
	Mat LoadedImage;
      LoadedImage = imread("lemur.jpeg",IMREAD_COLOR);
      imshow("Originalt billede",LoadedImage);
      //waitKey(0);
      resize(LoadedImage,LoadedImage,Size(192,144));    
      imshow("nedskaleret",LoadedImage);
      //waitKey(0);
      std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());
      imwrite("scaledlemur.jpg",LoadedImage);
      imwrite("testkompr.jpg", LoadedImage, {IMWRITE_JPEG_QUALITY, 15});
      imwrite("scaledlemur.bmp",LoadedImage);
      std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());
	  std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
      cout << "\n";
      return 0; 
    } 
