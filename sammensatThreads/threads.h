pthread_mutex_t bLock;
pthread_mutex_t gLock;
bool storage = true;



void* T1 (void* arg) { //Thread til billede delen
	while(storage == true) {
	//for(int i = 0; i < 10; i++) {
	
	pthread_mutex_lock(&gLock);
	
	readFPGA();
	printf("\n Billede program startet \n");
	lavBMP();
	billedebehandling();
	skalerKomprimer();


	
	// put billede i queue
	printf("\n Billede program sluttet \n");
	cout << storage << "\n";
	//sleep(2.5);
	
	pthread_mutex_unlock(&gLock);


}
	return NULL; 
}

void* T2 (void* arg) { //Thread til GPS delen
	while(1) {
		
		pthread_mutex_lock(&bLock);
		laesGPS();
		//cout << "thread 2 lever\n";
		//Put GPS data i queue
		
		pthread_mutex_unlock(&bLock);
		

	}
	pthread_exit(NULL);
	return NULL;
}

void* T3(void* arg){ //Thread til sende delen
	
	while(1){
		pthread_mutex_lock(&gLock);
		pthread_mutex_lock(&bLock);
		
		printf("Sover i 5 \n");
		sleep(5);
		cout << "thread 3 lever\n";
		//åben billede fra billede queue
		//åben gps fra gps queue
		//kombiner billede fra GPS og billede Q.
		
		pthread_mutex_unlock(&gLock);
		pthread_mutex_unlock(&bLock);
		
		
		//send billede. 
	}
}
	
