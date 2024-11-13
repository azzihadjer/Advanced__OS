
#include "shared.h"

void init_semaphores() {
    key_t key =1234;
    semid = semget(key, 3, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }
    semctl(semid, MUTEX, SETVAL, 1);          // Mutex
    semctl(semid, EMPTY, SETVAL, BUFFER_SIZE); // counting Empty slots
    semctl(semid, FULL, SETVAL, 0);           // counting Full slots
}

void P(int sem_num) {
    sem_op.sem_num = sem_num;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);
}

void V(int sem_num) {
    sem_op.sem_num = sem_num;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);
}

void producer() {
    for (int item = 0; item < NUM_ITEMS; item++) {
        printf("[Producer] Trying to produce item %d\n", item + 1);

        P(EMPTY);
        printf("[Producer] Found empty slot for item %d\n", item + 1);

        P(MUTEX);
        printf("[Producer] Writing item %d to buffer position %d\n", item + 1, shm_ptr->in);

        shm_ptr->buffer[shm_ptr->in] = item + 1;
        shm_ptr->in = (shm_ptr->in + 1) % BUFFER_SIZE;

        V(MUTEX);
        printf("[Producer] Item %d produced and mutex released\n", item + 1);

        V(FULL);
        printf("[Producer] Signaled full slot for item %d\n", item + 1);

        sleep(1);
    }

    printf("[Producer] Production complete\n");
}

int main() {
    key_t key = 1234;

    shm_id = shmget(key, sizeof(SharedBuffer), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    shm_ptr = (SharedBuffer *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (SharedBuffer *)-1) {
        perror("shmat failed");
        exit(1);
    }

    shm_ptr->in = 0;
    shm_ptr->out = 0;

    init_semaphores();
    producer();

    shmdt(shm_ptr);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}
