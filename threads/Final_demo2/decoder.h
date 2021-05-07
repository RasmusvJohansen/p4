#include <stdio.h>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

string gpsDATA;
string latt;
string la;
string lonn;
string lo;
string Height;
bool pData = false;
double lattf;
double lonnf;
double heightf;
int x = 0;
double lat;
double lon;
int GPSCounter = 0;






void NMEA_decoder2(string data){  // ny decoder. kan tage højde for komma tal
  int j = 0;
  int k = 0;
  string dataArray[14]; // er 14 da sætnings konstruktionen på et gps signal har 15 sætninger
  //String tmp[85]; // er 85 stor da et gps signal maks har 85 char
  
  if (data.substr(0,6) == "$GPGGA"){ // tjekker om det er positions data
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
 
  double floatDataArray[14]; //benyttes til at konvertere dataen til floats (nu doubles).
  floatDataArray[0] = stod(dataArray[2].substr(0,2));
  floatDataArray[1] = stod(dataArray[2].substr(2,8))/60.0;
  floatDataArray[2] = stod(dataArray[2].substr(13,3));
  floatDataArray[3] = stod(dataArray[2].substr(16,8))/60.0;
  lat = floatDataArray[0] + floatDataArray[1];
  lon = floatDataArray[2] + floatDataArray[3];
  
  
  //cout << "\n" << setprecision(9) << lat << "\n";
  //cout << setprecision(9) << lon << "\n";
  //cout << dataArray[9].substr(0,4) << "\n";
  //Height = dataArray[9]+dataArray[10]; //--//--
  Height = dataArray[9].substr(0,4);
  
  
  pData = true; // boolean der sørger for overstående data kun bliver printet én gang i void loop
 }
}




void laesGPS(){
  x = 0;
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
  while(x < 1){
  
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

			cout << "\n" << str << "GPS læst\n";
			cout << "Lat: " << setprecision(9) << lat << endl;
			cout << "Lon: " << setprecision(9) << lon  << endl;
			cout << "Højde: "<< Height << endl;
			//cout << GPSCounter << endl;
			
			
			myfile.open("/home/pi/Desktop/Storage/3GPSData/GPSData"+to_string(GPSCounter) +".txt",ofstream::trunc);
			  if (myfile.is_open())
			  
			  {
			    
				//istream fileData("data.txt", ifstream::binary);
				myfile.seekp (0,ios_base::end);  
				
				//myfile << "GGA: %s" << strr << " \n \n";
				myfile << "Lat: " << setprecision(9) << lat << endl;
				myfile << "Lon: " << setprecision(9) << lon  << endl;
				myfile << "Højde: " << Height << endl;
				//GotoLine(myfile, 8);
				myfile.close();
				cout << "GPS gemt" <<endl;
				GPSCounter ++;
				
			  }
			  else cout << "Unable to open file";
			  
			  
			  
			is_GGA_received_completely = 0;
			x++;
			
			
				
		}
	}

}
