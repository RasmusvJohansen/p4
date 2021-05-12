#include "header.h"



int main(){
	
	pthread_t newthread, newthread2, newthread3, newthread4;
    printf("Program starter \n");
    pthread_create(&newthread, NULL, T1, NULL);    
    pthread_create(&newthread2, NULL, T2, NULL);
    pthread_create(&newthread3, NULL, T3, NULL);
    pthread_join(newthread, NULL);
    pthread_join(newthread2, NULL);
    pthread_join(newthread3, NULL);
    printf("Program slutter \n");
	return 0;
}
