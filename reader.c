#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = 1234; // Key for the shared memory
    int shmid; // ID of the shared memory
    char * shm; // Pointer to the shared memory

    // Locate the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    // Attach the shared memory segment
    if ((shm = shmat(shmid, NULL, 0)) == (char * ) - 1) {
        perror("shmat");
        exit(1);
    }

    // Read the message from the shared memory and print it to the console
    printf("Message: %s", shm);

    // Detach the shared memory segment
    shmdt(shm);

    return 0;
}