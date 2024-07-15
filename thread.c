#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// This function will be executed by the thread
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
    // Thread identifier
    pthread_t thread;
    
    // Variable to hold return code of pthread_create
    int rc;
    
    // Dynamically allocate memory to store the thread ID
    int* thread_id = malloc(sizeof(int));
    
    // Check if memory allocation was successful
    if (thread_id == NULL) {
        printf("Error: Unable to allocate memory for thread ID\n");
        exit(-1);
    }
    
    // Assign the thread ID value
    *thread_id = 0;
    
    // Print a message indicating the creation of the thread
    printf("Creating thread %d\n", *thread_id);
    
    // Create a new thread that will execute the threadFunction
    // pthread_create(&thread, NULL, threadFunction, thread_id)
    // Arguments:
    // 1. &thread: Pointer to pthread_t variable to store thread identifier
    // 2. NULL: Attributes for the thread, NULL means default attributes
    // 3. threadFunction: The function to be executed by the thread
    // 4. thread_id: Argument passed to the thread function (threadFunction)
    rc = pthread_create(&thread, NULL, threadFunction, thread_id);
    
    // Check if the thread was created successfully
    if (rc) {
        // Print an error message if thread creation failed
        printf("Error: Unable to create thread %d, %d\n", *thread_id, rc);
        exit(-1);
    }

    // Wait for the thread to complete
    // pthread_join(thread, NULL)
    // Arguments:
    // 1. thread: The thread identifier of the thread to wait for
    // 2. NULL: Pointer to a location where the thread's exit status can be stored, NULL means status is ignored
    pthread_join(thread, NULL);

    // Print a message indicating the thread has completed
    printf("Thread %d completed.\n", *thread_id);
    
    // Return success from the main function
    return 0;
}
