// 1. Problem Statement
// Implement a C program where the main program accepts integers to be sorted. The main program uses the fork() system call to create a new process called a child process. The parent process sorts the integers using a sorting algorithm and waits for the child process using the wait() system call to sort the integers with another sorting algorithm. Additionally, demonstrate zombie and orphan process states.

// 2. Concept & Purpose of the Code
// This C program illustrates process creation and management using system calls in an operating system context. The main features include:

// Process Creation: The program uses fork() to create a child process, allowing concurrent execution of code.
// Sorting Algorithms: The parent process sorts integers in descending order, while the child sorts them in ascending order using bubble sort.
// Orphan and Zombie States: The code demonstrates the orphan process (when the child outlives the parent) and the zombie process (the parent waits for the child to complete).
// This demonstrates fundamental concepts of operating systems regarding process management, inter-process communication, and sorting algorithms.

// 3. Line-by-Line Explanation with Comments

#include<stdio.h>       // Standard I/O library for printf() and scanf()
#include<unistd.h>      // Library for POSIX API, including fork(), getpid(), getppid(), and sleep()
#include<sys/wait.h>    // Library for process control, including wait() for synchronization
#include<stdlib.h>      // Standard library for general functions, including system()
#define MAX 20          // Define the maximum size of the array as 20

// Function to sort array in ascending order using bubble sort
void bubble_asc(int arr[], int n) { 
    int i, j, temp;                      // Declare loop variables and temporary variable for swapping
    for(i = 0; i < n; i++) {             // Loop over each element in the array
        for(j = 0; j < n - i - 1; j++) { // Loop for comparing adjacent elements
            if(arr[j] > arr[j + 1]) {    // Check if the current element is greater than the next
                temp = arr[j];           // Swap if condition is true
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort array in descending order using bubble sort
void bubble_dsc(int arr[], int n) { 
    int i, j, temp;                      // Declare loop variables and temporary variable for swapping
    for(i = 0; i < n; i++) {             // Loop over each element in the array
        for(j = 0; j < n - i - 1; j++) { // Loop for comparing adjacent elements
            if(arr[j] < arr[j + 1]) {    // Check if the current element is less than the next
                temp = arr[j];           // Swap if condition is true
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array elements
void print(int arr[], int n) {
    int i;
    for(i = 0; i < n; i++) {           // Loop to print each element in the array
        printf("\t%d", arr[i]);        // Display element followed by a tab
    }
    printf("\n\n");                    // Newline for better readability
}

int main() {
    int i, n, arr[MAX], f, pid;

    // Prompt user to enter the number of elements in the array
    printf("\nHOW MANY NOS DO YOU WANT IN ARRAY : ");
    scanf("%d", &n);                    // Read number of elements from user

    // Prompt user to enter each array element
    printf("ENTER ARRAY ELEMENT : ");
    for(i = 0; i < n; i++) {            // Loop to accept each element
        scanf("%d", &arr[i]);           // Read each element into the array
    }

    // Create a child process
    pid = fork();

    if(pid == 0) {                       // Check if it's the child process
        // Child process block
        printf("\n\t\t**********ORPHAN STATE**************\n");
        sleep(5);                       // Sleep for 5 seconds to simulate orphan state
        printf("\n\t CHILD PROCESS PID : %d ", getpid());
        printf("\n\t PARENT PROCESS PPID : %d", getppid());  // Display orphan state
        system("ps -el | grep init");  // Show orphaned child reassigned to 'init' process

        printf("\n\nARRAY IN ASSCENDING ORDER : ");
        bubble_asc(arr, n);            // Sort array in ascending order
        print(arr, n);                 // Print sorted array
    
    } else if(pid > 0) {                // Check if it's the parent process
        // Parent process block
        printf("\n\t\t\t**********ZOMBIE STATE**************\n");
        system("ps -el | grep Z");      // Display any zombie processes in the system
        f = wait(0);                    // Parent waits for child to finish, causing zombie state

        printf("\n\tTERMINATED CHILD PID : %d", f);
        printf("\n\tPARENT PID (MAIN) : %d", getpid());
        printf("\n\tPARENTS PARENT PPID (BASH) : %d ", getppid());

        printf("\n\nARRAY IN DESCENDING ORDER : ");
        bubble_dsc(arr, n);            // Sort array in descending order
        print(arr, n);                 // Print sorted array
    
    } else {
        // If fork() fails
        printf("\nERROR IN FORK!!");
    }

    return 0;                            // Exit the program
}
/*
//4. Explanation of Specific Keywords
fork(): A system call that creates a new process. The new process is called a child process. It returns 0 to the child and the child's PID to the parent.
wait(): A system call that makes the parent process wait until all its child processes have terminated. It prevents zombie processes by cleaning up after child termination.
sleep(): Suspends execution of the calling process for a specified duration (in seconds). Used here to illustrate the orphan state.
system(): Executes a shell command from within the C program. It's used to run commands like ps to display the current processes.
getpid(): Returns the process ID (PID) of the calling process.
getppid(): Returns the parent process ID (PPID) of the calling process.

//5. Expected Oral Questions and Answers
What does the fork() function do?

fork() creates a new process. The new process is a duplicate of the current process. It allows for concurrent execution of processes.
Explain the difference between a zombie process and an orphan process.

A zombie process is a terminated child process that still has an entry in the process table because its parent has not yet called wait(). An orphan process is a child whose parent has terminated; it is re-parented to the init process.
Why do we use wait() in this program?

We use wait() to make sure the parent process waits for the child process to complete its execution, which helps prevent zombie processes.
What happens if fork() fails?

If fork() fails, it returns a negative value, indicating an error in process creation. The program should handle this error appropriately.
How does the bubble sort algorithm work?

Bubble sort repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. The process continues until no swaps are needed, indicating the list is sorted.*/
