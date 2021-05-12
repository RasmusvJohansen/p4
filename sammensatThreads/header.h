//Inkludere almindelige biblioteker
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <memory.h>
#include <cstdlib>
#include <wiringPi.h>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <semaphore.h>
#include <sstream>
#include <iomanip>
#include <wiringSerial.h>
#include <errno.h>
#include <cstring>
#include <fstream>

//Definering af namespace
using namespace std;
using namespace cv; //benyttes til openCV

//Billede størrelse
const int m = 640; //bredde
const int n = 480; //højde

//Struct til at gemme RGB data for hver pixel
struct pixel{
	int R, G, B;
};
pixel billede[m][n];

struct brand{
	int i, j;
};
brand brandPixels[m][n];



//Andre header filer
//#include "decoder.h"
#include "Image.h"
#include "readFPGA.h"
#include "billedeBehandling.h"
#include "GPS.h"
#include <filesystem>
#include "threads.h"



