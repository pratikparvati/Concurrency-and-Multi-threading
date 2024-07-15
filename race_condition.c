#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Shared variable
int counter = 0;

// Number of iterations per thread
#define ITERATIONS 100000

// Function for the threads
void* incrementCounter(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Increment the shared counter
        counter++;
    }
    pthread_exit(NULL);
}

int main() {
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

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}
