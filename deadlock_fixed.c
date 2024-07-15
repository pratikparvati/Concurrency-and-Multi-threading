#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define two mutexes
pthread_mutex_t lock1;
pthread_mutex_t lock2;

// Function for the first thread
void* threadFunction1(void* arg) {
    // Acquire the locks in the same order
    pthread_mutex_lock(&lock1);
    printf("Thread 1 acquired lock1\n");
    
    // Simulate some work by sleeping
    sleep(1);
    
    // Try to acquire the second lock
    pthread_mutex_lock(&lock2);
    printf("Thread 1 acquired lock2\n");
    
    // Simulate some work by sleeping
    sleep(1);
    
    // Release the locks
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    
    pthread_exit(NULL);
}

// Function for the second thread
void* threadFunction2(void* arg) {
    // Acquire the locks in the same order
    pthread_mutex_lock(&lock1);
    printf("Thread 2 acquired lock1\n");
    
    // Simulate some work by sleeping
    sleep(1);
    
    // Try to acquire the second lock
    pthread_mutex_lock(&lock2);
    printf("Thread 2 acquired lock2\n");
    
    // Simulate some work by sleeping
    sleep(1);
    
    // Release the locks
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    
    pthread_exit(NULL);
}

int main() {
    // Initialize the mutexes
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);
    
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
    
    // Destroy the mutexes
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    
    printf("Main thread completed\n");
    
    return 0;
}
