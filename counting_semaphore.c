#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_RESOURCES 2

sem_t semaphore;  // Counting semaphore
int resources = MAX_RESOURCES;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    // Attempt to acquire the semaphore
    sem_wait(&semaphore);
    
    if (resources > 0) {
        resources--;
        printf("Thread %d: Resource acquired. Remaining resources: %d\n", thread_id, resources);
        sleep(2);  // Simulate some work
        resources++;
        printf("Thread %d: Resource released. Remaining resources: %d\n", thread_id, resources);
    } else {
        printf("Thread %d: No resources available.\n", thread_id);
    }
    
    // Release the semaphore
    sem_post(&semaphore);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2, thread3;
    int id1 = 1, id2 = 2, id3 = 3;
    
    // Initialize the semaphore with maximum resources
    sem_init(&semaphore, 0, MAX_RESOURCES);
    
    // Create threads
    pthread_create(&thread1, NULL, thread_function, &id1);
    pthread_create(&thread2, NULL, thread_function, &id2);
    pthread_create(&thread3, NULL, thread_function, &id3);
    
    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    // Destroy the semaphore
    sem_destroy(&semaphore);
    
    return 0;
}
