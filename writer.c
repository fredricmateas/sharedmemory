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
    char message[SHM_SIZE]; // Message to write into shared memory

    // Create the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    // Attach the shared memory segment
    if ((shm = shmat(shmid, NULL, 0)) == (char * ) - 1) {
        perror("shmat");
        exit(1);
    }

    // Prompt the user to enter a message to write into the shared memory
    printf("Enter a message: ");
    fgets(message, SHM_SIZE, stdin);

    // Write the message into the shared memory
    strncpy(shm, message, strlen(message) + 1); // include the null terminator

    // Detach the shared memory segment
    shmdt(shm);

    return 0;
}