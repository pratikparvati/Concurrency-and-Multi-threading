#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

// This function will be executed by each thread
void* threadFunction(void* arg) {
    // Retrieve the thread ID from the argument passed to the thread
    int thread_id = *(int*)arg;
    
    // Print the thread ID to indicate the thread is running
    printf("Thread %d is running.\n", thread_id);
    
    // Free the allocated memory for the argument
    free(arg);
    
    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    // Array to hold thread identifiers
    pthread_t threads[NUM_THREADS];
    
    // Variable to hold return code of pthread_create
    int rc;
    
    // Loop to create the specified number of threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Dynamically allocate memory to store the thread ID
        int* thread_id = malloc(sizeof(int));
        
        // Check if memory allocation was successful
        if (thread_id == NULL) {
            printf("Error: Unable to allocate memory for thread ID\n");
            exit(-1);
        }
        
        // Assign the thread ID value
        *thread_id = i;
        
        // Print a message indicating the creation of a new thread
        printf("Creating thread %d\n", i);
        
        // Create a new thread that will execute the threadFunction
        rc = pthread_create(&threads[i], NULL, threadFunction, thread_id);
        
        // Check if the thread was created successfully
        if (rc) {
            // Print an error message if thread creation failed
            printf("Error: Unable to create thread %d, %d\n", i, rc);
            exit(-1);
        }
    }

    // Loop to join (wait for) each created thread
    for (int i = 0; i < NUM_THREADS; i++) {
        // Wait for the thread to complete
        pthread_join(threads[i], NULL);
    }

    // Print a message indicating all threads have completed
    printf("All threads completed.\n");
    
    // Return success from the main function
    return 0;
}
