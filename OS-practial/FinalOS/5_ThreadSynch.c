// Purpose and Main Use of Code
// This C program demonstrates thread synchronization using counting semaphores in the context of the producer-consumer problem. It creates multiple producer threads that generate items and a consumer thread that consumes those items. The program uses semaphores to manage access to a shared buffer, ensuring that producers do not overfill the buffer and consumers do not consume from an empty buffer. This is accomplished with counting semaphores for tracking the number of filled and empty slots in the buffer and a mutex semaphore for protecting critical sections of the code.

// Line-by-Line Explanation and Code Comments

#include <stdio.h>              // Standard I/O library for printf and scanf functions.
#include <sys/syscall.h>        // Provides access to system calls, such as getpid.
#include <pthread.h>            // Library for working with threads (pthread functions).
#include <semaphore.h>          // Library for semaphore functions.
#include <stdlib.h>            // Standard library for general functions like rand.
#include <unistd.h>            // Provides access to the POSIX operating system API.
#include <sys/types.h>         // Defines data types used in system calls.

#define BUFFER_SIZE 20         // Maximum size of the buffer for storing produced items.

void *producer(void *arg);      // Function prototype for the producer thread.
void *consumer(void *arg);      // Function prototype for the consumer thread.

typedef struct {
    int buffer[BUFFER_SIZE];    // Circular buffer for produced items.
    sem_t full, empty;          // Semaphores to track filled and empty slots in the buffer.
    int in, out;                // Indices for the next empty slot and the next filled slot.
} shared_data;

shared_data sh;                 // Shared data structure instance to hold buffer and semaphores.

sem_t mutex;                    // Mutex semaphore for critical section protection.

int main() {
    pthread_t ptid1, ptid2, ctid1; // Thread identifiers for producers and consumer.
    sh.in = 0;                     // Initialize the index for the next empty slot.
    sh.out = 0;                    // Initialize the index for the next filled slot.
    sem_init(&sh.empty, 0, BUFFER_SIZE); // Initialize the empty semaphore (all slots empty).
    sem_init(&sh.full, 0, 0);     // Initialize the full semaphore (no slots filled).
    sem_init(&mutex, 0, 1);       // Initialize the mutex semaphore (initially unlocked).

    // Create producer and consumer threads.
    pthread_create(&ptid1, NULL, producer, NULL);
    pthread_create(&ptid2, NULL, producer, NULL);
    pthread_create(&ctid1, NULL, consumer, NULL);

    // Wait for threads to finish execution.
    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);
    pthread_join(ctid1, NULL);

    return 0;                     // Exit the main program successfully.
}

// Producer thread function
void *producer(void *arg) {
    int item;
    while (1) {                   // Infinite loop to produce items.
        item = rand() % 100;     // Produce a random item between 0 and 99.
        sem_wait(&sh.empty);      // Wait for an empty slot in the buffer.
        sem_wait(&mutex);         // Lock the critical section to access shared buffer.

        // Insert the produced item into the buffer.
        sh.buffer[sh.in] = item; 
        printf("PRODUCER Thread id = %ld produced Item = %d at index %d\n", pthread_self(), item, sh.in);
        sh.in = (sh.in + 1) % BUFFER_SIZE; // Update the index, wrapping around the buffer.

        sem_post(&mutex);         // Unlock the critical section.
        sem_post(&sh.full);       // Signal that a new item has been produced.
        sleep(1);                 // Simulate time taken to produce an item.
    }
}

// Consumer thread function
void *consumer(void *arg) {
    int item;
    while (1) {                   // Infinite loop to consume items.
        sem_wait(&sh.full);       // Wait for a filled slot in the buffer.
        sem_wait(&mutex);         // Lock the critical section to access shared buffer.

        // Remove the item from the buffer.
        item = sh.buffer[sh.out];
        printf("\tCONSUMER Thread id = %ld consumed Item = %d from index %d\n", pthread_self(), item, sh.out);
        sh.out = (sh.out + 1) % BUFFER_SIZE; // Update the index, wrapping around the buffer.

        sem_post(&mutex);         // Unlock the critical section.
        sem_post(&sh.empty);      // Signal that an item has been consumed.
        sleep(2);                 // Simulate time taken to consume an item.
    }
}
/*
Explanation of Specific Keywords and Libraries

#include: Preprocessor directive used to include standard libraries for functionalities (e.g., I/O operations, threading, semaphore functions).
typedef struct: Used to define a new data type called shared_data, encapsulating the buffer and its associated semaphores and indices.
sem_t: Data type used to define semaphores for synchronization.
sem_init: Function to initialize a semaphore.
sem_wait: Function to decrement (wait on) a semaphore. If the semaphore value is 0, the calling thread blocks until it becomes greater than 0.
sem_post: Function to increment (signal) a semaphore, potentially waking a blocked thread.
pthread_create: Function to create a new thread.
pthread_join: Function to wait for a thread to finish execution.
rand(): Function to generate a random number.
sleep(): Function to suspend execution for a specified period, simulating time taken for producing/consuming an item.
    
// Expected Oral Questions and Answers
What is the producer-consumer problem?

The producer-consumer problem is a classic synchronization problem where producers generate data and consumers use it. It requires proper synchronization to prevent race conditions and ensure that producers do not overfill the buffer while consumers do not consume from an empty buffer.
How are semaphores used in this program?

Counting semaphores (full and empty) track the number of filled and empty slots in the buffer, while a mutex semaphore ensures that only one thread can access the critical section of code that modifies the buffer at a time.
What is the role of the mutex semaphore?

The mutex semaphore protects the critical section of the code to ensure that only one producer or consumer can access the shared buffer at any given time, preventing race conditions.
Why do we use circular buffers in this context?

Circular buffers allow for efficient use of space by wrapping around the end of the buffer to the beginning. This prevents the need for shifting elements in the buffer when items are consumed.
What could happen if semaphores were not used?

Without semaphores, race conditions could occur, leading to situations where producers add items to a full buffer or consumers try to remove items from an empty buffer, causing data corruption and undefined behavior.
*/

