/*
	GPS Interfacing with Raspberry Pi using C (WiringPi Library)
	http://www.electronicwings.com
*/

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

int i;

int main ()
{
  int serial_port; 
  char dat,buff[100],GGA_code[3];
  unsigned char IsitGGAstring=0;
  unsigned char GGA_index=0;
  unsigned char is_GGA_received_completely = 0;
  
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)		/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)							/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
string str;
ofstream myfile;
  while(1){
			
	  //cin >> i;
		if(serialDataAvail (serial_port) )		/* check for any data available on serial port */
		  { 
			dat = serialGetchar(serial_port);		/* receive character serially */		
			if(dat == '$'){
				IsitGGAstring = 0;
				GGA_index = 0;
			}
			else if(IsitGGAstring ==1){
				cout << dat;
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
			//printf("GGA: %s",buff);
			stringstream ss;  
			ss << buff;  
			ss >> str;  
			myfile.open("test.txt",ofstream::app);
			  if (myfile.is_open())
			  
			  {
				//istream fileData("data.txt", ifstream::binary);
				myfile.seekp (0,ios_base::end);  
				
				myfile << "GGA: %s" << str << "\n";
				//GotoLine(myfile, 8);
				myfile.close();
				
			  }
			  else cout << "Unable to open file";
			  
			  
			  
			is_GGA_received_completely = 0;
		
				
		}
	}
	return 0;
}



