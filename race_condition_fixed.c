#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Shared variable
int counter = 0;

// Number of iterations per thread
#define ITERATIONS 100000

// Mutex for synchronizing access to the shared variable
pthread_mutex_t counter_mutex;

// Function for the threads
void* incrementCounter(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Lock the mutex before accessing the shared variable
        pthread_mutex_lock(&counter_mutex);
        
        // Increment the shared counter
        counter++;
        
        // Unlock the mutex after accessing the shared variable
        pthread_mutex_unlock(&counter_mutex);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

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

    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}
