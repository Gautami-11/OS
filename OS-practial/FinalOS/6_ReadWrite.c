// Purpose and Main Use of Code
// This C program demonstrates thread synchronization and mutual exclusion using mutexes in the context of the Reader-Writer problem, specifically prioritizing readers. It creates multiple reader threads that read a shared buffer and one writer thread that writes to it. The program uses mutexes to control access to the shared buffer, ensuring that writers can only write when no readers are accessing the buffer, while allowing multiple readers to read simultaneously.

// Line-by-Line Explanation and Code Comments

#include <stdio.h>              // Standard I/O library for printf and scanf functions.
#include <unistd.h>             // Provides access to the POSIX operating system API.
#include <semaphore.h>          // Library for semaphore functions (not used in this code).
#include <pthread.h>            // Library for working with threads (pthread functions).
#include <sys/syscall.h>        // Provides access to system calls, such as getpid.

void *reader(void *argp);      // Function prototype for the reader thread.
void *writer(void *argp);      // Function prototype for the writer thread.
int buffer;                    // Shared buffer to hold the data.
int flag = 0;                  // Flag to indicate if the buffer is filled.
int read_count = 0;            // Count of active readers.

int getbuff() {                 // Function to get input from the user to add to the buffer.
    int temp;
    printf("Enter the no to add in buffer: ");
    scanf("%d", &temp);
    return temp;
}

void readbuff(int buffer) {     // Function to read the buffer and display its content.
    printf("Element read by reader = %d\n", buffer);
}

// Mutex initializations for controlling access.
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // Mutex for reader access.
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;     // Mutex for writer access.

int main() {
    pthread_t wtid1, rtid1, rtid2; // Thread identifiers for writer and readers.
    pthread_create(&wtid1, NULL, writer, NULL); // Create writer thread.
    pthread_create(&rtid1, NULL, reader, NULL); // Create first reader thread.
    pthread_create(&rtid2, NULL, reader, NULL); // Create second reader thread.

    pthread_join(wtid1, NULL); // Wait for writer thread to finish.
    pthread_join(rtid1, NULL); // Wait for first reader thread to finish.
    pthread_join(rtid2, NULL); // Wait for second reader thread to finish.

    return 0; // Exit the main program successfully.
}

// Writer thread function
void* writer(void *argp) {
    while (1) {                // Infinite loop for continuous writing.
        pthread_mutex_lock(&wrt); // Lock the writer mutex.
        if (flag == 0) {        // Check if the buffer is empty.
            buffer = getbuff(); // Get input from the user to fill the buffer.
            flag = 1;          // Set the flag to indicate that the buffer is filled.
        }
        pthread_mutex_unlock(&wrt); // Unlock the writer mutex.
    }
}

// Reader thread function
void* reader(void *argp) {
    while (1) {                // Infinite loop for continuous reading.
        pthread_mutex_lock(&mutex1); // Lock the mutex for reader access.
        read_count++;          // Increment the count of active readers.

        if (read_count == 1) { // If this is the first reader.
            pthread_mutex_lock(&wrt); // Lock the writer mutex to prevent writing.
        }
        pthread_mutex_unlock(&mutex1); // Unlock the reader access mutex.

        if (flag == 1) {      // Check if the buffer is filled.
            readbuff(buffer); // Read the buffer and display the content.
            sleep(1);         // Simulate time taken to read.
            flag = 0;        // Reset the flag to indicate that the buffer has been read.
        }

        pthread_mutex_lock(&mutex1); // Lock the mutex for reader access.
        read_count--;          // Decrement the count of active readers.

        if (read_count == 0) { // If this is the last reader.
            pthread_mutex_unlock(&wrt); // Unlock the writer mutex to allow writing.
        }
        pthread_mutex_unlock(&mutex1); // Unlock the reader access mutex.
    }
}
// Explanation of Specific Keywords and Libraries 
/*
#include: Preprocessor directive used to include standard libraries for functionalities (e.g., I/O operations, threading).
pthread_mutex_t: Data type used to define a mutex for thread synchronization.
pthread_mutex_lock: Function to lock a mutex, ensuring exclusive access to a resource.
pthread_mutex_unlock: Function to unlock a mutex, allowing other threads to access the resource.
pthread_create: Function to create a new thread.
pthread_join: Function to wait for a thread to finish execution.
scanf: Function to read input from the user.
printf: Function to print output to the console.
sleep(): Function to suspend execution for a specified duration.
    
// Expected Oral Questions and Answers
What is the Reader-Writer problem?

The Reader-Writer problem is a synchronization issue where multiple threads (readers and writers) access a shared resource (like a database or a file). The challenge is to ensure that writers have exclusive access to the resource while allowing multiple readers to read simultaneously.
How does this code prioritize readers?

This implementation prioritizes readers by allowing multiple readers to read the shared buffer simultaneously as long as no writers are writing. The writer will block if there are any active readers.
What happens if the flag variable is not used?

Without the flag variable, the writer may overwrite the buffer while readers are accessing it, potentially leading to race conditions and undefined behavior as readers would be reading stale or corrupted data.
Why do we use mutexes in this program?

Mutexes are used to ensure mutual exclusion, preventing multiple threads from accessing the shared buffer simultaneously. This avoids race conditions and ensures data integrity.
What could be the potential issue if there are many readers and few writers?

If there are many readers and only a few writers, the writers may starve (i.e., they may never get a chance to write) if the readers keep coming in and locking the resource. This implementation somewhat mitigates starvation by allowing writers to access the buffer once all readers have finished.
*/
