// Purpose and Main Use of Code
// This C program implements two CPU scheduling algorithms: Round Robin (RR) and Shortest Job First (SJF) - Preemptive. It takes process details as input, including arrival time and burst time, and schedules them based on the selected algorithm. The program calculates and displays the average waiting time (WT) and average turnaround time (TAT) for the scheduled processes, providing insights into process management and scheduling in operating systems.

// Line-by-Line Explanation and Code Comments

#include <stdio.h>      // Standard I/O functions like printf and scanf.
#include <string.h>     // String manipulation functions like strcmp.
#include <stdlib.h>     // Standard utility functions like atoi, exit.

#define MAX 20          // Maximum number of processes the program can handle.

// Structure to represent a process.
typedef struct process {
    int BT, AT, TAT, WT, PNO, PID;  // Process attributes (burst time, arrival time, etc.).
    char name[10];                  // Name of the process.
} process;

// Structure for the ready queue.
typedef struct RQ {
    process pr[MAX];    // Array to store processes in the ready queue.
    int f, r;           // Front and rear indices for the ready queue.
} RQ;

// Function Prototypes
void get_PCB(process[], int *);      // Gets process details from the user.
void sort_AT(process[], int);        // Sorts processes by arrival time.
void sort_BT(RQ *);                  // Sorts the ready queue by burst time.
void disp_table(process[], int);     // Displays the process table.
void SJF_P(process[], int);          // Executes the SJF-P scheduling algorithm.
void RR(process p[], int n, int tq); // Executes the Round Robin scheduling algorithm.
float cal_avgwt(process[], int);     // Calculates average waiting time.
float cal_avgtat(process[], int);    // Calculates average turnaround time.

void menu() {                        // Menu for user selection of scheduling algorithm.
    printf("\n\t\t****MENU*****");
    printf("\n\t\t1. RR");
    printf("\n\t\t2. SJF P");
    printf("\n\t\t3. EXIT");
    printf("\n\t\tEnter Choice: \t");
}

int main() {
    int ch, TQ, n;
    process P[MAX];                  // Array to hold processes.
    float avg_WT, avg_TAT;

    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &TQ);               // User input for time quantum.

    get_PCB(P, &n);                  // Gets process details from the user.

    do {
        menu();                      // Display menu.
        scanf("%d", &ch);           // User choice for scheduling algorithm.
        switch (ch) {
            case 1: {                // Round Robin Scheduling
                RR(P, n, TQ);        // Call RR function.
                disp_table(P, n);    // Display the process table.
                avg_WT = cal_avgwt(P, n); // Calculate average waiting time.
                avg_TAT = cal_avgtat(P, n); // Calculate average turnaround time.
                printf("\nAVERAGE WT  : %f", avg_WT);
                printf("\nAVERAGE TAT : %f", avg_TAT);
                break;
            }
            case 2: {                // Shortest Job First - Preemptive
                SJF_P(P, n);         // Call SJF function.
                disp_table(P, n);    // Display the process table.
                avg_WT = cal_avgwt(P, n); // Calculate average waiting time.
                avg_TAT = cal_avgtat(P, n); // Calculate average turnaround time.
                printf("\nAVERAGE WT  : %f", avg_WT);
                printf("\nAVERAGE TAT : %f", avg_TAT);
                break;
            }
            case 3:                   // Exit
                break;
        }
    } while (ch != 3);              // Loop until user chooses to exit.

    return 0;                        // Exits the program successfully.
}

// Calculate average waiting time
float cal_avgwt(process p[], int n) {
    float avg = 0;                   // Initialize average waiting time.
    for (int i = 0; i < n; i++) {
        avg += p[i].WT;              // Sum up waiting times.
    }
    return avg / n;                  // Return the average.
}

// Calculate average turnaround time
float cal_avgtat(process p[], int n) {
    float avg = 0;                   // Initialize average turnaround time.
    for (int i = 0; i < n; i++) {
        avg += p[i].TAT;             // Sum up turnaround times.
    }
    return avg / n;                  // Return the average.
}

// Returns the index of the first process based on arrival time.
int get_first_process(process p[], int n) {
    int min = p[0].AT;               // Initialize minimum arrival time.
    int in = 0;                      // Initialize index of process.
    for (int j = 1; j < n; j++) {
        if (p[j].AT < min) {         // Find the process with the earliest arrival time.
            min = p[j].AT;           // Update minimum arrival time.
            in = j;                  // Update index.
        }
    }
    return in;                       // Return the index of the first process.
}

// Checks for processes arriving at the current time and adds them to the ready queue.
void check_arrival(RQ *r, process p[], int time, int n) {
    for (int i = 0; i < n; i++) {
        int flag = 0;                // Flag to check if process is already in the ready queue.
        for (int j = r->f; j <= r->r; j++) {
            if (strcmp(p[i].name, r->pr[j].name) == 0) { // Check if already in queue.
                flag = 1;
                break;                // Break if found.
            }
        }
        if (p[i].AT == time && flag == 0) { // If process arrives at the current time.
            if (r->r + 1 < MAX) {   // Check if there's space in the ready queue.
                r->pr[++r->r] = p[i]; // Add process to ready queue.
            }
        }
    }
}

// Round Robin Scheduling
void RR(process p[], int n, int tq) {
    int time = 0;                   // Initialize time.
    RQ r;                           // Ready queue.
    r.f = r.r = -1;                // Initialize front and rear.
    int start = get_first_process(p, n); // Get the first process based on arrival time.
    r.pr[0] = p[start];            // Add it to the ready queue.
    r.f = r.r = 0;                 // Set front and rear to 0.
    check_arrival(&r, p, time, n); // Check for arrivals at time 0.

    while (r.f != -1) {            // While there are processes in the queue.
        for (int count = 0; count < tq && r.pr[r.f].BT > 0; count++) {
            r.pr[r.f].BT--;         // Process executes for time quantum.
            time++;                 // Increment time.
            check_arrival(&r, p, time, n); // Check for new arrivals.
        }

        if (r.pr[r.f].BT > 0) {     // If the process is not finished.
            if (r.r + 1 < MAX) {    // Check if there's space in the ready queue.
                r.pr[++r.r] = r.pr[r.f]; // Add it back to the end of the queue.
            }
        } else {                    // If the process is finished.
            p[r.pr[r.f].PID].TAT = time - p[r.pr[r.f].PID].AT; // Calculate turnaround time.
            p[r.pr[r.f].PID].WT = p[r.pr[r.f].PID].TAT - (p[r.pr[r.f].PID].BT); // Calculate waiting time.
        }

        if (r.f == r.r) {           // If queue is empty after execution.
            r.f = r.r = -1;         // Reset front and rear.
        } else {
            r.f++;                   // Move front to the next process.
        }
    }
}

// Sort the ready queue by burst time.
void sort_BT(RQ *r) {
    for (int i = r->f; i <= r->r; i++) {
        for (int j = i + 1; j <= r->r; j++) {
            if (r->pr[j].BT < r->pr[i].BT) { // Compare burst times.
                process temp = r->pr[j];    // Swap processes.
                r->pr[j] = r->pr[i];
                r->pr[i] = temp;
            }
        }
    }
}

// Returns the total burst time for all processes.
int get_total_time(process p[], int n) {
    int sum = 0;                   // Initialize sum.
    for (int i = 0; i < n; i++) {
        sum += p[i].BT;            // Sum burst times.
    }
    return sum;                   // Return total burst time.
}

// Shortest Job First - Preemptive Scheduling
void SJF_P(process p[], int n) {
    int time = 0, sum = get_total_time(p, n); // Initialize time and total burst time.
    RQ r;                           // Ready queue.
    r.f = r.r = -1;                // Initialize front and rear.

    while (time < sum) {           // Loop until all processes are executed.
        check_arrival(&r, p, time, n); // Check for arrivals.
        sort_BT(&r);               // Sort the ready queue by burst time.

        if (r.f == -1) {           // If no processes in the ready queue.
            time++;                 // Increment time.
            continue;              // Continue to next iteration.
        }

        r.pr[r.f].BT--;            // Execute the first process in the queue.
        time++;                     // Increment time.

        if (r.pr[r.f].BT == 0) {   // If the process is finished.
            p[r.pr[r.f].PID].TAT = time - p[r.pr[r.f].PID].AT; // Calculate turnaround time.
            p[r.pr[r.f].PID].WT = p[r.pr[r.f].PID].TAT - (p[r.pr[r.f].PID].BT); // Calculate waiting time.
            r.f++;                  // Move front to the next process.
            if (r.f > r.r) {       // If queue becomes empty.
                r.f = r.r = -1;    // Reset front and rear.
            }
        }
    }
}

// Get process details from the user.
void get_PCB(process p[], int *n) {
    printf("Enter number of processes: ");
    scanf("%d", n);                // User input for number of processes.
    for (int i = 0; i < *n; i++) {
        printf("Enter name, Arrival Time, and Burst Time of process %d: ", i + 1);
        scanf("%s%d%d", p[i].name, &p[i].AT, &p[i].BT); // Get process details.
        p[i].PID = i;              // Set process ID.
    }
}

// Display the process table.
void disp_table(process p[], int n) {
    printf("\nProcess\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].AT, p[i].BT, p[i].TAT, p[i].WT); // Print details.
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
