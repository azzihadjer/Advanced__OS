#include "shared.h"


void create_producer_threads(pthread_t *prod_threads, struct shared_memory *shm) {
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&prod_threads[i], NULL, producer, (void *)shm);
    }
}


void create_consumer_threads(pthread_t *cons_threads, struct shared_memory *shm) {
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&cons_threads[i], NULL, consumer, (void *)shm);
    }
}


void join_producer_threads(pthread_t *prod_threads) {
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }
}


void join_consumer_threads(pthread_t *cons_threads) {
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }
}

int main() {
    pthread_t prod_threads[NUM_PRODUCERS], cons_threads[NUM_CONSUMERS];
    struct shared_memory shm;

    
    shm.in = 0;
    shm.out = 0;


    sem_init(&shm.empty, 0, BUFFER_SIZE); 
    sem_init(&shm.full, 0, 0);             


    pthread_mutex_init(&shm.mutex, NULL);

    
    create_producer_threads(prod_threads, &shm);
    create_consumer_threads(cons_threads, &shm);

    
    join_producer_threads(prod_threads);
    join_consumer_threads(cons_threads);


    pthread_mutex_destroy(&shm.mutex);
    sem_destroy(&shm.empty);
    sem_destroy(&shm.full);

    return 0;
}
