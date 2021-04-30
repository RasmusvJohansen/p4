//MAIN

//Inkludere biblioteker til de andre funktioner

#include "GPS_lib.h"


//Inkludere almindelige biblioteker

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


void almFunc() {;
    while(1) {
sleep(1);
printf("Program starter på ny \n");

    }}


int main () {
    pthread_t newthread;
    printf("Program starter \n");

    pthread_create(&newthread, NULL, TestFuncGPS, NULL);
    almFunc();
    

}