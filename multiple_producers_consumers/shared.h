#ifndef SHARED_H
#define SHARED_H

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2


struct shared_memory {
    int buffer[BUFFER_SIZE];  
    int in;                   
    int out;                 
    
    sem_t full;
    sem_t empty;              
    pthread_mutex_t mutex;    //to protect buffer access
};


void *producer(void *arg);
void *consumer(void *arg);

#endif
