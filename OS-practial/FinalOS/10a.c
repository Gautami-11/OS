// Purpose and Main Use of the Code
// This code demonstrates how to create and use shared memory in C using System V IPC (Inter-Process Communication). It creates a shared memory segment, allows data to be written into it, and then detaches the segment from the process. Shared memory is a method for processes to communicate with each other by sharing a segment of memory.

// Libraries Used
// stdio.h: Standard Input Output library for using functions like printf() and fgets().
// sys/ipc.h: Provides functions and definitions for IPC mechanisms like message queues and shared memory.
// sys/shm.h: Contains the definitions for shared memory operations, such as shmget() and shmat().
// stdlib.h: Includes functions for memory allocation, process control, conversions, etc.
// string.h: Used for string manipulation functions.
// Code with Line-by-Line Explanation
// c
// Copy code
#include <stdio.h>          // Include standard I/O library for input and output functions
#include <sys/ipc.h>       // Include library for IPC (Inter-Process Communication) functions
#include <sys/shm.h>       // Include library for shared memory functions
#include <stdlib.h>        // Include standard library for memory allocation and process control
#include <string.h>        // Include library for string handling functions

int main() {              
    // Create a unique key for the shared memory segment
    key_t key = ftok("shmfile", 65);  // Generate a unique key using the ftok function; "shmfile" is a pathname and 65 is a project identifier
    if (key == -1) {                   
        perror("ftok");                // Print error message if ftok fails
        exit(1);                       // Exit the program with a failure status
    }

    // Create a shared memory segment with a size of 1024 bytes
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Allocate shared memory segment; 0666 is the permission and IPC_CREAT creates it if it doesn't exist
    if (shmid == -1) {                  
        perror("shmget");              // Print error message if shmget fails
        exit(1);                       // Exit the program with a failure status
    }

    // Attach the shared memory segment to the process's address space
    char *str = (char *) shmat(shmid, NULL, 0); // Attach shared memory to the process's address space; NULL indicates the OS chooses the address
    if (str == (char *) -1) {        
        perror("shmat");               // Print error message if shmat fails
        exit(1);                       // Exit the program with a failure status
    }

    printf("Write Data: ");           // Prompt the user to write data
    fgets(str, 100, stdin);           // Read a string from standard input and store it in the shared memory segment

    // Detach the shared memory segment
    if (shmdt(str) == -1) {           
        perror("shmdt");               // Print error message if shmdt fails
        exit(1);                       // Exit the program with a failure status
    }

    return 0;                          // Return 0 to indicate successful completion of the program
}
// Possible Questions
// What is the purpose of using shared memory?

// Answer: Shared memory is used for inter-process communication (IPC) where multiple processes can access the same segment of memory. It allows for efficient data exchange and reduces the overhead associated with other IPC mechanisms like message queues or pipes.
// Explain the use of ftok() function.

// Answer: The ftok() function generates a unique key for the shared memory segment. It takes a pathname and a project identifier as arguments. The pathname must refer to an existing file, and the project identifier is an integer used to distinguish between different IPC resources created from the same file.
// What are the permissions used when creating a shared memory segment?

// Answer: The permission 0666 allows read and write access to the shared memory segment for both the owner and the group. The IPC_CREAT flag indicates that the system should create the shared memory segment if it does not already exist.
// What does the shmat() function do?

// Answer: The shmat() function attaches the shared memory segment identified by its ID to the address space of the calling process. It returns a pointer to the start of the shared memory segment, allowing the process to read from and write to it.
// Why is it necessary to detach the shared memory segment?

// Answer: Detaching the shared memory segment using shmdt() is important to prevent memory leaks and to ensure that the memory can be freed when it is no longer needed. Failing to detach may lead to resource exhaustion in the system.
// Familiar Words and Concepts
// Key: A unique identifier used to access shared resources.
// Segment: A contiguous block of memory.
// Attach: To link a shared memory segment to the process's address space.
// Detach: To remove the association between the process and the shared memory segment.
// Memory Leak: A situation where allocated memory is not released back to the system, leading to reduced available memory.
// Feel free to provide more code for additional explanations and questions!
