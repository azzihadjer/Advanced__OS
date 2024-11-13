#include "shared.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *consumer(void *arg) {
    struct shared_memory *shm = (struct shared_memory *)arg;
    int item;

    while (1) {
        
        sem_wait(&shm->full);

        pthread_mutex_lock(&shm->mutex);

        
        item = shm->buffer[shm->out];
        printf("[ Consumer %lu]: consumed item %d from post: %d\n", pthread_self(), item,shm->out);  // Updated log message
        shm->out = (shm->out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&shm->mutex);

        sem_post(&shm->empty);

        sleep(rand() % 3);
    }

    return NULL;
}
