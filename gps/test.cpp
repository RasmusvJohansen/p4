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
//#include "decoder.h"

int i;

string gpsDATA;
string latt;
string la;
string lonn;
string lo;
string height;
bool pData = false;
float lattf;
float lonnf;
float heightf;


void NMEA_decoder2(string data){  // ny decoder. kan tage højde for komma tal
  int j = 0;
  int k = 0;
  string dataArray[14]; // er 14 da sætnings konstruktionen på et gps signal har 15 sætninger
  //String tmp[85]; // er 85 stor da et gps signal maks har 85 char

  /*for ( int i = 0 ; i <=85 ; i++){
    tmp[i] = data.substring(i, i+1);  // for loop der deler hver char op i et array, for kunne tjekke for "end bit" senere
  }*/  // fandt ud af dette ikke var nødvendigt
  
  if (data.substr(0,6) == "$GPGGA"){ // tjekker om det er positions data
	  cout << "godkendt\n";
  for (int i = 0 ; data[i] != '*' ; i++){ //for loop der køre indtil '' som er end bit 
    if(data[i] !=','){ // denne if sætning tæller hvor mange chars der er til næste komma
      j++;
    }
    else{
      dataArray[k] = data.substr(i-j,i);               // data bliver indsæt i array som er delt op i sætninger af k. 
      j = 0;                                              //Sætninger bliver definere ved i og j, hvor j har talt hvor mange char der er til et komma. 
      k++; // k tæller antal sætning der er indeholdet    //i holder hvor mange char der er talt i alt. j bliver sat til 0 igen så den tæller hvor mange chars der imellem to kommaer
    }
  }
  // << dataArray[13] << "   her\n";
  
  for(int i;i<15;i++){
  //cout << dataArray[i] << "   her\n";
  }
  float floatDataArray[14];
  //floatDataArray[0] = stof(dataArray[2].substr(0,2));
  //floatDataArray[1] = stof(dataArray[2].substr(2,8))/60;
  //floatDataArray[2] = stof(dataArray[2].substr(13,3));
  //floatDataArray[3] = stof(dataArray[2].substr(16,8))/60;
  float lat = floatDataArray[0] + floatDataArray[1];
  float lon = floatDataArray[2] + floatDataArray[3];
  cout << lat << "\n";
  cout << lon << "\n";
  height = dataArray[9]+dataArray[10]; //--//--
  pData = true; // boolean der sørger for overstående data kun bliver printet én gang i void loop
 }
}


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
string testArray[67];
stringstream ss;
int l = 0;
  while(1){
			
		if(serialDataAvail (serial_port) )		/* check for any data available on serial port */
		  { 
			dat = serialGetchar(serial_port);		/* receive character serially */		
			if(dat == '$'){
				IsitGGAstring = 0;
				GGA_index = 0;
			}
			else if(IsitGGAstring ==1){
				//cout << dat;
				testArray[l] = dat;
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
			l = 0;	
			for(int i = 0; i<67; i++){
				//cout << testArray[i];
				ss << testArray[i];
				//ss >> str;
			}
			string test;
			
			string strr(ss.str());
			//strr = "$GPGGA,"+strr;
			string test2;
			test2 = "$GPGGA,";
			string test3;
			test3 = test2 += strr;
			cout << test3;
			

			//cout << "\n" << str << "også her\n";
			//NMEA_decoder2(str);
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
		
				
		}
	}
	return 0;
}



