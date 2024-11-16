// Purpose and Main Use of Code
// This C program implements the Banker's Algorithm, a deadlock avoidance algorithm used in operating systems to manage resources and ensure that processes can run without entering a deadlock state. The program takes the number of processes, the number of resources, and their allocation and maximum requirements as input, then determines whether the system is in a safe state. If it is, it provides a safe sequence of process execution.

// Line-by-Line Explanation and Code Comments

#include <stdio.h> // Standard input/output library.

struct process {
    int max[10];       // Maximum resources needed by the process.
    int allocate[10];  // Resources currently allocated to the process.
    int need[10];      // Remaining resources needed by the process (max - allocate).
} p[10]; // Array of structures to hold details of up to 10 processes.

int n, m; // Number of processes (n) and number of resources (m).
void input(int[]); // Function prototype for input.
void display(); // Function prototype for displaying process details.
int isSafestate(int[], int[]); // Function prototype to check if the system is in a safe state.
int safetyalgorithm(int[], int[]); // Function prototype for the safety algorithm.

int main() {
    int i;
    printf("\nEnter No of processes: "); // Prompt for number of processes.
    scanf("%d", &n);
    printf("Enter no of resources: "); // Prompt for number of resources.
    scanf("%d", &m);
    int available[m]; // Array to hold available resources.
    int safesequence[n]; // Array to hold the safe sequence of processes.

    printf("\n*****Enter details of process*****");
    input(available); // Call to input function to gather process data.
    display(); // Call to display function to show process details.

    // Check if the system is in a safe state.
    if (isSafestate(available, safesequence)) {
        printf("\n\tSYSTEM IS IN SAFE STATE...");
        printf("\nsafesequence is: ");
        for (i = 0; i < n; i++)
            printf("P%d -> ", safesequence[i]); // Display the safe sequence.
    } else {
        printf("\nSYSTEM IS IN UNSAFE STATE!!!");
    }
    return 0; // End of the program.
}

// Function to input the details of processes and available resources.
void input(int available[m]) {
    int i, j;
    for (i = 0; i < n; i++) {
        printf("\nEnter the details of process P%d: ", i);
        printf("\n\tEnter the allocated resources: ");
        for (j = 0; j < m; j++) {
            scanf("%d", &p[i].allocate[j]); // Input allocated resources for the process.
        }
        printf("\tEnter the max resources: ");
        for (j = 0; j < m; j++) {
            scanf("%d", &p[i].max[j]); // Input maximum resources needed for the process.
            p[i].need[j] = p[i].max[j] - p[i].allocate[j]; // Calculate the remaining resources needed.
        }
    }
    printf("\nEnter the available resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &available[j]); // Input the available resources in the system.
    }
}

// Function to display the process details.
void display() {
    int i, j;
    printf("\n\tPID\tALLOCATE\tMAX\t\tNEED\n");
    for (i = 0; i < n; i++) {
        printf("\tP%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d ", p[i].allocate[j]); // Print allocated resources.
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", p[i].max[j]); // Print maximum resources.
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", p[i].need[j]); // Print remaining resources needed.
        printf("\n");
    }
}

// Function to check if the system is in a safe state.
int isSafestate(int available[m], int safesequence[n]) {
    return safetyalgorithm(available, safesequence) == 1; // Call the safety algorithm.
}

// Safety algorithm implementation to determine the safe state.
int safetyalgorithm(int available[m], int safesequence[n]) {
    int i, j;
    int work[m]; // Array to hold the available resources.
    int finish[n]; // Array to indicate if a process is finished.
    
    for (j = 0; j < m; j++)
        work[j] = available[j]; // Initialize work with available resources.
    
    for (i = 0; i < n; i++)
        finish[i] = 0; // Initialize finish array to 0.

    int proceed = 1, k = 0; // Proceed flag and index for safe sequence.
    while (proceed) {
        proceed = 0; // Reset proceed flag.
        for (i = 0; i < n; i++) {
            int flag = 1; // Flag to check if process can proceed.
            if (finish[i] == 0) { // Check if the process is not finished.
                for (j = 0; j < m; j++) {
                    if (p[i].need[j] <= work[j]) { // Check if resources can be allocated.
                        continue; // If resources can be allocated, continue checking.
                    } else {
                        flag = 0; // Set flag to 0 if resources cannot be allocated.
                        break; // Break from the loop if allocation is not possible.
                    }
                }
                if (flag == 0) continue; // Skip to the next process if not able to proceed.

                // Allocate resources to the process.
                for (j = 0; j < m; j++) {
                    work[j] += p[i].allocate[j]; // Add allocated resources to work.
                }
                finish[i] = 1; // Mark the process as finished.
                safesequence[k++] = i; // Add to safe sequence.
                proceed = 1; // Set proceed flag to 1 to continue the loop.
            }
        }
    }

    // Check if all processes are finished.
    for (i = 0; i < n && finish[i] == 1; i++)
        continue;
    if (i == n)
        return 1; // System is in a safe state.
    return 0; // System is not in a safe state.
}
/*
// Explanation of Specific Keywords and Libraries
#include: Preprocessor directive to include standard libraries for input/output functions.
struct: A user-defined data type in C that allows the grouping of different data types under a single name. Here, it's used to define a structure for each process.
scanf(): Function to read formatted input from the standard input (keyboard).
printf(): Function to write formatted output to the standard output (screen).
int[]: Represents an array of integers in function parameters.
return: Keyword used to exit from a function and optionally return a value.
    
// Expected Oral Questions and Answers
What is the Banker's Algorithm?

The Banker's Algorithm is a deadlock avoidance algorithm that dynamically allocates resources to processes while ensuring that the system remains in a safe state. It simulates resource allocation and checks if granting a request leads to a safe state.
What does a "safe state" mean?

A safe state is one in which the system can allocate resources to each process in such a way that every process can finish its execution without causing a deadlock. It guarantees that all processes can complete with the available resources.
What happens in an "unsafe state"?

An unsafe state is a condition where the system cannot guarantee that all processes will finish executing without risking deadlock. In this state, resource allocation requests can lead to deadlock scenarios.
What are the components of the Banker's Algorithm?

The main components include the allocation matrix, maximum matrix, need matrix, available resources, and the process states (finished or unfinished).
Why do we use arrays to represent resources and processes?

Arrays are used to efficiently manage multiple processes and resources, allowing for easy access and manipulation of their attributes (like allocated, maximum, and needed resources) in a structured way.
*/
