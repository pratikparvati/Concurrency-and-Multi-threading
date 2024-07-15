#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// Define two semaphores
sem_t semaphore1;
sem_t semaphore2;

// Function for the first thread
void* threadFunction1(void* arg) {
    // Acquire the first semaphore
    sem_wait(&semaphore1);
    printf("Thread 1 acquired semaphore1\n");
    
    // Simulate some work by sleeping
    sleep(1);
    
    // Acquire the second semaphore
    sem_wait(&semaphore2);
    printf("Thread 1 acquired semaphore2\n");
    
    // Release the semaphores in reverse order
    sem_post(&semaphore2);
    sem_post(&semaphore1);
    
    pthread_exit(NULL);
}

// Function for the second thread
void* threadFunction2(void* arg) {
    // Acquire the first semaphore
    sem_wait(&semaphore1);
    printf("Thread 2 acquired semaphore1\n");
    
    // Simulate some work by sleeping
    sleep(1);
    
    // Acquire the second semaphore
    sem_wait(&semaphore2);
    printf("Thread 2 acquired semaphore2\n");
    
    // Release the semaphores in reverse order
    sem_post(&semaphore2);
    sem_post(&semaphore1);
    
    pthread_exit(NULL);
}

int main() {
    // Initialize the semaphores with initial value 1 (binary semaphore)
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 1);
    
    // Thread identifiers
    pthread_t thread1, thread2;
    
    // Create the first thread
    pthread_create(&thread1, NULL, threadFunction1, NULL);
    printf("Thread 1 created\n");
    
    // Create the second thread
    pthread_create(&thread2, NULL, threadFunction2, NULL);
    printf("Thread 2 created\n");
    
    // Wait for the threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // Destroy the semaphores
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    
    printf("Main thread completed\n");
    
    return 0;
}
