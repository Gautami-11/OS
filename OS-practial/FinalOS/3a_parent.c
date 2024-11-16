// 1. Problem Statement
// Implement a C program in which the main program accepts an array. The main program uses the FORK system call to create a new process called a child process. The parent process sorts the array and passes the sorted array to the child process through the command line arguments of the EXECVE system call. The child process uses the EXECVE system call to load a new program that displays the array in reverse order.

// 2. Concept & Purpose of the Code
// This C program demonstrates inter-process communication using command line arguments and the execution of a new program using execve(). The key features include:

// Process Creation: The program creates a child process using the fork() system call.
// Sorting: The parent process sorts an array of integers in ascending order.
// Argument Passing: The sorted array is passed to the child process as command line arguments.
// Program Execution: The child process uses execve() to load and execute a separate program that will print the sorted array in reverse order.
// This program showcases concepts of process management, sorting algorithms, and argument handling in C programming.

// 3. Line-by-Line Explanation with Comments

#include <stdio.h>           // Standard I/O library for printf() and scanf()
#include <sys/types.h>      // Contains definitions for data types used in system calls
#include <unistd.h>         // Contains declarations for fork(), execve(), and other POSIX functions
#include <sys/wait.h>       // Contains declarations for wait() function
#include <stdlib.h>         // Standard library for general functions including atoi() and exit()

// Function to sort the array in ascending order using bubble sort
void bubble_asc(int arr[], int n) {
    int i, j, temp;                // Declare loop variables and temporary variable for swapping
    for (i = 0; i < n; i++) {      // Loop over each element in the array
        for (j = 0; j < n - i - 1; j++) { // Loop for comparing adjacent elements
            if (arr[j] > arr[j + 1]) { // Check if the current element is greater than the next
                temp = arr[j];    // Swap if condition is true
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nArray in ascending order: "); // Output statement for sorted array
    for (i = 0; i < n; i++) {
        printf("\t%d", arr[i]);    // Print each sorted element
    }
    printf("\n");                  // Newline for better readability
}

int main(int argc, char *argv[]) { // Main function with command line arguments
    if (argc < 2) {                // Check if at least one number is provided
        printf("Please provide numbers to sort.\n"); // Prompt for input
        return 1;                  // Exit with error code
    }

    int n = argc - 1;             // Number of integers provided (exclude program name)
    int a[n];                     // Declare array of size n
    pid_t pid;                    // Declare process ID variable

    // Convert command line arguments to integers
    for (int i = 1; i <= n; i++) {
        a[i - 1] = atoi(argv[i]); // Convert arguments from string to integer and store in array
    }

    bubble_asc(a, n);             // Sort the array in ascending order

    // Prepare arguments for child process
    char *args[n + 2];            // Array for child arguments (+2 for program name and NULL termination)
    args[0] = "./child";          // Assume the child executable is named "child"
    for (int i = 0; i < n; i++) {
        args[i + 1] = argv[i + 1]; // Pass sorted values to child
    }
    args[n + 1] = NULL;           // NULL terminate the argument list

    pid = fork();                 // Create a child process
    if (pid == 0) {              // Check if it's the child process
        printf("\nI am Child Process, my pid is %d \n", getpid()); // Print child PID
        execve("./child", args, NULL); // Execute child program with arguments
        perror("execve failed"); // Only reached if execve fails
        exit(1);                  // Exit with error code
    } else if (pid > 0) {        // Check if it's the parent process
        wait(NULL);              // Wait for child process to finish
        printf("\nI am Parent Process, my pid is %d \n", getpid()); // Print parent PID
    } else {
        perror("Fork failed");    // Handle error in fork
        return 1;                 // Exit with error code
    }

    return 0;                     // Exit program
}
/*

// 4. Explanation of Specific Keywords
fork(): Creates a new process. The child process is an exact duplicate of the parent, and it returns 0 to the child process and the child's PID to the parent.
execve(): Replaces the current process image with a new process image specified by the path. It is used to run the child program in this case.
wait(): A system call that makes the parent process wait until the child process terminates. It helps manage process state and prevents zombie processes.
atoi(): Converts a string to an integer. It is used to convert the command line arguments from strings to integers for sorting.
getpid(): Returns the process ID of the calling process. It is used to print the PID of both the parent and child processes.

// 5. Expected Oral Questions and Answers
What does the execve() function do?

execve() replaces the current process image with a new process image specified by the provided filename. It is used to run a different program within a process.
Explain how the parent process passes data to the child process.

The parent process sorts the array and prepares it as command line arguments, which are passed to the child process using execve().
What happens if fork() fails?

If fork() fails, it returns a negative value, and the program should handle this case, typically by printing an error message and exiting.
How does the bubble sort algorithm work?

Bubble sort repeatedly compares adjacent elements and swaps them if they are in the wrong order. The process continues until no swaps are needed, meaning the array is sorted.
What is the purpose of wait(NULL) in the parent process?

wait(NULL) causes the parent process to wait until the child process finishes executing, ensuring proper synchronization and preventing zombie processes.
*/
