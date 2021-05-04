//Libary til GPS funktioner

#ifndef GPSFUNC
#define GPSFUNC

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>





void* TestFuncGPS (void * arg) {
    while(1) {
        sleep(10);
        printf("GPS DATA \n");

    }
    return NULL;
}




#endif
