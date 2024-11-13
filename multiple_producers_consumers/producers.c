#include "shared.h"


void *producer(void *arg) {
    struct shared_memory *shm = (struct shared_memory *)arg;
    int item;

    while (1) {
        item = rand() % 100;  

     
        sem_wait(&shm->empty);
       
        pthread_mutex_lock(&shm->mutex);

   
        shm->buffer[shm->in] = item;
        printf("[ Producer %lu]: produced item %d to post: %d\n", pthread_self(), item, shm->in);
        shm->in = (shm->in + 1) % BUFFER_SIZE; 

        
        pthread_mutex_unlock(&shm->mutex);

        sem_post(&shm->full);
        
        sleep(rand() % 3);
    }

    return NULL;
}
