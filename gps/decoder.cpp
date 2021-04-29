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
void NMEA_decoder(string GPS){

if (GPS.substr(0,6) == "$GPGGA"){ //Gammel Decoder. Kan ikke tage højde for komma tal
  //Serial.flush();
  latt = GPS.substr(18,27);
  la = GPS.substr(28,29);
  lonn = GPS.substr(31,40);
  lo = GPS.substr(41, 42);
  height = GPS.substr(48, 51);
  cout << latt << "\n";
  cout << la << "\n";
  cout << lonn << "\n"; 
  cout << lo << "\n";
  cout << height << "\n";
  
  } 
}

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
  /*for ( int i = 0; i<=k ; i++){ // for loop der printer alt data indtil talte sætninger. 
    cout << dataArray[i] << "\n"; 
  }*/
  //Serial.print("latitude: "); 
  latt = dataArray[2]; // +dataArray[3]; // printer lattitude
  //lattf = dataArray[2].toFloat();   // konverterer lattitude til float
  lonn = dataArray[4]; //+dataArray[5]; //--//--
  //lonnf = dataArray[3].toFloat();   //--//--
  height = dataArray[9]+dataArray[10]; //--//--
  //heightf = dataArray[9].toFloat();    //--//--
  pData = true; // boolean der sørger for overstående data kun bliver printet én gang i void loop
 }
}

/* disse tal svarer til posisiotner af dataen i dataArray, så dataArray[6] giver "GPS quality indicator" 
  eg3. $GPGGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh
  1    = UTC of Position
  2    = Latitude
  3    = N or S
  4    = Longitude
  5    = E or W
  6    = GPS quality indicator (0=invalid; 1=GPS fix; 2=Diff. GPS fix)
  7    = Number of satellites in use [not those in view]
  8    = Horizontal dilution of position
  9    = Antenna altitude above/below mean sea level (geoid)
  10   = Meters  (Antenna height unit)
  11   = Geoidal separation (Diff. between WGS-84 earth ellipsoid and
         mean sea level.  -=geoid is below WGS-84 ellipsoid)
  12   = Meters  (Units of geoidal separation)
  13   = Age in seconds since last update from diff. reference station
  14   = Diff. reference station ID#
  15   = Checksum
*/



void loop() {


}





  /*Serial.println(dataArray[0]);
  Serial.println(dataArray[1]);
  Serial.println(dataArray[2]);
  Serial.println(dataArray[3]);
  Serial.println(dataArray[4]);
  Serial.println(dataArray[5]);
  Serial.println(dataArray[6]);
  Serial.println(dataArray[7]);
  Serial.println(dataArray[8]);
  Serial.println(dataArray[9]);
  Serial.println(dataArray[10]);
  Serial.println(dataArray[11]);
  Serial.println(dataArray[12]);
  Serial.println(dataArray[13]);
  Serial.println(dataArray[14]);
  Serial.println(dataArray[15]);
  Serial.println(dataArray[16]);
  Serial.println(dataArray[17]);
  Serial.println(dataArray[18]);
  Serial.println(dataArray[19]);
  Serial.println(dataArray[20]);*/




int main ()
{
	
		// put your main code here, to run repeatedly:
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


}
