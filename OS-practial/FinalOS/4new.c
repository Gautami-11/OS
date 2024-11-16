// Purpose and Main Use of Code
// This C program implements two CPU scheduling algorithms: Round Robin (RR) and Shortest Job First (SJF) - Preemptive. It takes process details as input, including arrival time and burst time, and schedules them based on the selected algorithm. The program calculates and displays the average waiting time (WT) and average turnaround time (TAT) for the scheduled processes, providing insights into process management and scheduling in operating systems.

#include <stdio.h>   // Standard I/O library for input-output functions
#include <string.h>  // String manipulation functions
#include <stdlib.h>  // Standard library for memory allocation and other utilities

#define MAX 20       // Maximum number of processes allowed

// Define a structure to store process details
typedef struct process {
    int BT, AT, TAT, WT, PID; // BT: Burst Time, AT: Arrival Time, TAT: Turnaround Time, WT: Waiting Time, PID: Process ID
    char name[10];            // Process name
} process;

// Function prototypes for each main operation
void get_PCB(process[], int *);           // Get process control block (details of processes)
void disp_table(process[], int);          // Display the process table
void SJF_P(process[], int);               // Shortest Job First (Preemptive) scheduling
float cal_avgwt(process[], int);          // Calculate average waiting time
float cal_avgtat(process[], int);         // Calculate average turnaround time

// Function to display the menu options
void menu() {
    printf("\n\t\t***MENU**");
    printf("\n\t\t1. SJF P");
    printf("\n\t\t2. EXIT");
    printf("\n\t\tEnter Choice: \t");
}

int main() {
    int ch, n;              // `ch` for menu choice, `n` for number of processes
    process P[MAX];         // Array to store process details, max size defined by MAX
    float avg_WT, avg_TAT;  // Variables to store average waiting time and turnaround time

    get_PCB(P, &n);         // Call function to get process details from user

    do {
        menu();             // Display menu
        scanf("%d", &ch);   // Get user choice

        switch (ch) {
            case 1:
                SJF_P(P, n);                         // Run SJF Preemptive scheduling algorithm
                disp_table(P, n);                    // Display the process table with WT and TAT
                avg_WT = cal_avgwt(P, n);            // Calculate average WT
                avg_TAT = cal_avgtat(P, n);          // Calculate average TAT
                printf("\nAVERAGE WT  : %.2f", avg_WT);   // Print average WT
                printf("\nAVERAGE TAT : %.2f", avg_TAT);   // Print average TAT
                break;
            case 2:
                break;                               // Exit the program
            default:
                printf("Invalid choice! Please try again.");  // Handle invalid choices
        }

    } while (ch != 2);      // Loop until user chooses to exit

    return 0;
}

// Function to calculate average waiting time
float cal_avgwt(process p[], int n) {
    float avg = 0;                            // Initialize average WT to 0
    for (int i = 0; i < n; i++) {              // Loop through all processes
        avg += p[i].WT;                        // Sum up WT of each process
    }
    return avg / n;                            // Return the average WT
}

// Function to calculate average turnaround time
float cal_avgtat(process p[], int n) {
    float avg = 0;                            // Initialize average TAT to 0
    for (int i = 0; i < n; i++) {             // Loop through all processes
        avg += p[i].TAT;                      // Sum up TAT of each process
    }
    return avg / n;                           // Return the average TAT
}

// Function to display the process table
void disp_table(process p[], int n) {
    printf("\n\n P_NAME \t AT \t BT \t WT \t TAT \t");  // Column headers
    for (int i = 0; i < n; i++) {                        // Loop through all processes
        printf("\n %-10s \t %d \t %d \t %d \t %d \t", 
               p[i].name, p[i].AT, p[i].BT, p[i].WT, p[i].TAT);  // Display process details
    }
}

// Function to get process details from user
void get_PCB(process p[], int *n) {
    printf("\nEnter total number of processes: ");
    scanf("%d", n);                              // Input number of processes
    for (int i = 0; i < *n; i++) {               // Loop through each process to input details
        printf("\nEnter Following details for Process %d", i + 1);
        printf("\nName: ");
        scanf("%s", p[i].name);                  // Input process name
        printf("Arrival Time: ");
        scanf("%d", &p[i].AT);                   // Input arrival time
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);                   // Input burst time
        p[i].TAT = 0;                            // Initialize TAT to 0
        p[i].WT = 0;                             // Initialize WT to 0
        p[i].PID = i;                            // Set process ID to index value
    }
}

// Shortest Job First (Preemptive) scheduling algorithm
void SJF_P(process p[], int n) {
    int time = 0, completed = 0;               // `time` to track CPU time, `completed` to count completed processes
    int min_index;                             // Variable to store index of process with shortest remaining time
    int is_completed[MAX] = {0};               // Array to mark completed processes

    while (completed < n) {                    // Loop until all processes are completed
        min_index = -1;                        // Reset `min_index` for each time unit
        for (int i = 0; i < n; i++) {          // Loop through all processes
            if (p[i].AT <= time && !is_completed[i]) {  // Check if process has arrived and not completed
                if (min_index == -1 || p[i].BT < p[min_index].BT) {  // Find process with shortest burst time
                    min_index = i;             // Update `min_index` to current process
                }
            }
        }

        if (min_index != -1) {                 // If a process is found to execute
            time += p[min_index].BT;           // Increment time by the burst time of selected process
            p[min_index].TAT = time - p[min_index].AT;  // Calculate TAT
            p[min_index].WT = p[min_index].TAT - p[min_index].BT;  // Calculate WT
            is_completed[min_index] = 1;       // Mark process as completed
            completed++;                       // Increment completed process count
        } else {
            time++;                            // Increment time if no process is ready
        }
    }
}

/*Explanation of Specific Keywords and Libraries
#include: Preprocessor directive to include standard libraries for I/O, string manipulation, and utility functions.
struct: Used to define a structure, which is a user-defined data type that groups related variables.
void: Specifies that a function does not return a value.
float: Data type representing floating-point numbers.
int: Data type for integer numbers.
char: Data type for character variables, used for strings in C.
scanf: Standard library function to read input from the user.
printf: Standard library function to output formatted text to the console.
return: Used to exit a function and optionally return a value.
while, for, if, else: Control flow statements used for loops and conditional execution.
continue: Skips the remaining code in the current iteration of a loop and continues with the next iteration.
    
    
    Explanation of the SJF Preemptive Scheduling Algorithm (SJF_P function)

    Initialize variables:
        time: Tracks the current time of the CPU.
        completed: Counts the number of completed processes.
        is_completed: Array initialized to 0 for each process, marking whether the process is completed or not.

    Loop until all processes are completed:
        For each time unit, the algorithm finds the process with the shortest burst time that has arrived and is not completed.
        If a suitable process is found, the time is incremented by its burst time, marking it as completed and calculating its WT and TAT.
        If no process has arrived or all arrived processes are completed, increment time to move forward.

Overall Structure

The code starts by gathering process details, then shows a menu where the user can choose to run SJF Preemptive scheduling or exit. Once selected, the algorithm calculates and displays each process's WT and TAT, along with the averages.

// Expected Oral Questions and Answers
What is the purpose of this program?

This program implements CPU scheduling algorithms (Round Robin and Shortest Job First - Preemptive) and calculates average waiting and turnaround times for the processes.
What are the key differences between Round Robin and SJF?

Round Robin uses time slices for each process, while SJF selects the process with the shortest remaining time for execution, which can lead to higher waiting times for longer processes.
What is a time quantum in Round Robin?

Time quantum is the maximum amount of time a process can execute before being interrupted and placed back in the ready queue.
How does the program handle process arrivals?

The program checks for newly arriving processes at each time increment and adds them to the ready queue.
Why is it important to calculate average waiting and turnaround times?

Average waiting and turnaround times provide insights into the efficiency of the scheduling algorithm, helping to evaluate and optimize process management in operating systems.
*/
