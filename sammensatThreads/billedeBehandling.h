//anvendte variabler
int billedeCounter = 0;
int countSort = 0;


//Benyttes til at navngive billede
char* bmpName;
string nameWithNumber;
string skaleretName;
string jpgName;

//Der produceres en BMP fil ud fra modtaget FPGA data
void lavBMP(){
    Image image(m, n); //Definere billedestørrlse i Image.h
    for (int i= 0; i < n; i++){ //Der anvedes to forloops for at gennemgå matrix array
        for (int j = 0; j < m; j++){
	    image.SetColor(Color(billede[i][j].R,billede[i][j].G,billede[i][j].B), j, i); //Sender array data til Image.h
        }	
    }
    nameWithNumber = "/home/pi/Desktop/Storage/0RAW/random" + to_string(billedeCounter) + ".bmp"; //Generere et navn til at gemme billedefilen med
    bmpName = const_cast<char*>(nameWithNumber.c_str()); //Omdannes til en char så det fungerer opsætningen i Image.h
    image.Export(bmpName); //Laver bitmapfilen
}

void billedebehandling(){ //undersøger om billedet er sort eller indeholder ild
	for (int i=0; i<m; i++){ //billedematricen køres igennem
		for(int j=0; j<n; j++){
			if(billede[i][j].R < 27 and billede[i][j].G < 27 and billede[i][j].B < 27){ //Det undersøges om hver pixel har en RGB værdi under 27. Hvis ja, vurderes denne som sort.
				countSort = countSort + 1; //Antallet af sorte pixels tælles.
			}
			if(billede[i][j].R > 150 and billede[i][j].G > 50 and billede[i][j].B > 0){ //Der vurderes ud fra en øvre og nedre grænse om en pixel indeholder en farve der potientielt kan være ild
				if(billede[i][j].R < 255 and billede[i][j].G < 233 and billede[i][j].B < 66){
					//cout << "brand ved: " << i << ", " << j << "\n";
					brandPixels[i][j].i = i; //koordinater til pixels med brand gemmes.
					brandPixels[i][j].j = j;
				}
			}
			if(i != brandPixels[i][j].i and j != brandPixels[i][j].j){ //alle andre pixels laves hvide.
				billede[i][j].R = 255;
				billede[i][j].G = 255;
				billede[i][j].B = 255;
			}
		}
	}
	cout << "Sorte pixels: " << countSort << "\n";
	if(countSort > (n*m)*0.4){ //Er mere end 60% sort kan billedet ikke bruges.
		cout << "Billedet kan ikke bruges\n";
	}
	countSort = 0;
}

void skalerKomprimer(){
    Mat gemtBillede; //Den gemte BMP fil importeres i openCV
    gemtBillede = imread(bmpName,IMREAD_COLOR); 
    //imshow("Originalt billede",gemtBillede);
    //waitKey(0);
    resize(gemtBillede,gemtBillede,Size(192,144)); //Billedet gives nye dimentioner i openCV
    //imshow("nedskaleret",gemtBillede);
    //waitKey(0);
    //imwrite("test/random.jpg",gemtBillede);
    
    skaleretName = "/home/pi/Desktop/Storage/1Skaleret/Skaleret" + to_string(billedeCounter) + ".bmp"; //Gives nummerede navne
    jpgName = "/home/pi/Desktop/Storage/2Komprimeret/Komprimeret" + to_string(billedeCounter) + ".jpg";
    
    imwrite(jpgName, gemtBillede, {IMWRITE_JPEG_QUALITY, 15}); //jpg gemmes med 85% komprimering
    imwrite(skaleretName,gemtBillede);
    billedeCounter ++; //billedeCounter tælles op så næste billede får et nyt nummer
}
