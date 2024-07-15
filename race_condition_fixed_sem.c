#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// Shared variable
int counter = 0;

// Number of iterations per thread
#define ITERATIONS 100000

// Semaphore for synchronizing access to the shared variable
sem_t semaphore;

// Function for the threads
void* incrementCounter(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Wait (decrement) the semaphore
        sem_wait(&semaphore);
        
        // Critical section: Increment the shared counter
        counter++;
        
        // Signal (increment) the semaphore
        sem_post(&semaphore);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the semaphore
    sem_init(&semaphore, 0, 1); // Initial value of 1 (binary semaphore)

    // Number of threads
    int num_threads = 4;

    // Thread identifiers
    pthread_t threads[num_threads];

    // Create the threads
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, incrementCounter, NULL);
    }

    // Wait for the threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}
