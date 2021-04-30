#include <stdio.h>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
using namespace std;

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
  cout << dataArray[2] << "\n";
  float floatDataArray[14];
  floatDataArray[0] = stof(dataArray[2].substr(0,2));
  floatDataArray[1] = stof(dataArray[2].substr(2,8))/60;
  floatDataArray[2] = stof(dataArray[2].substr(13,3));
  floatDataArray[3] = stof(dataArray[2].substr(16,8))/60;
  float lat = floatDataArray[0] + floatDataArray[1];
  float lon = floatDataArray[2] + floatDataArray[3];
  cout << lat << "\n";
  cout << lon << "\n";
  height = dataArray[9]+dataArray[10]; //--//--
  pData = true; // boolean der sørger for overstående data kun bliver printet én gang i void loop
 }
}


/*
int main ()
{
		gpsDATA =  "$GPGGA,104940.00,5700.84436,N,00959.13150,E,1,09,1.11,29.8,M,42.4,M,,*61";//skal læses fra pi promt
		//Serial.println(gpsDATA);
		//NMEA_decoder(gpsDATA);
		NMEA_decoder2(gpsDATA);
  
	if ( pData == true){
	  cout << latt << "\n";
	  cout << lonn << "\n";
	  cout << height << "\n";
	  pData = false;
	} 


}*/
