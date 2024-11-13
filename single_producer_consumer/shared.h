// shared.h
#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10
#define MUTEX 0  // for mutual exclusion
#define EMPTY 1  // index for counting empty slots
#define FULL 2   // index for counting full slots

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
} SharedBuffer;

int semid;
int shm_id;
SharedBuffer *shm_ptr;
struct sembuf sem_op;

void init_semaphores(key_t key);
void P(int sem_num);
void V(int sem_num);

#endif // SHARED_H
