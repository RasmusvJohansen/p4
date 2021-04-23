#include <iostream>
#include <wiringPiI2C.h>
#include <thread>
#include <chrono>
#include <errno.h>
#include <wiringPi.h>
using namespace std;

#define Device_ID 0x21


void i2c(int reg){
	int fd = wiringPiI2CSetup(Device_ID);
	cout << fd;
	cout << "\n";
	cout << wiringPiI2CReadReg8(fd, reg);
	cout << "\n";
	cout << "Du er her\n";
	cout << errno;
}

int main(){
	i2c(0x01);
}
