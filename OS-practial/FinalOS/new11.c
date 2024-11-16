#include <stdio.h>  // Include standard I/O library for input and output functions
#include <stdlib.h> // Include standard library for memory allocation and process control functions

// Function prototypes
int SSTF(); // Declaration of the SSTF function that will be defined later

// SSTF Algorithm Implementation
int SSTF() {
    int RQ[100], i, n, TotalHeadMoment = 0, initial, count = 0; // Variable declaration
    // RQ[]: array to hold the disk request positions
    // n: number of requests
    // TotalHeadMoment: cumulative distance the disk head moves
    // initial: starting position of the disk head
    // count: number of requests serviced

    printf("Enter the number of Requests\n");
    scanf("%d", &n); // Read the number of requests from the user

    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]); // Read each request position and store it in RQ array
    }

    printf("Enter initial head position\n");
    scanf("%d", &initial); // Read the initial position of the disk head

    // Main logic for the SSTF (Shortest Seek Time First) algorithm
    while (count != n) { // Loop until all requests are serviced
        int min = 1000, d, index; // Initialize min to a high value for comparison
        // min: minimum distance found; d: current distance; index: index of closest request
        
        for (i = 0; i < n; i++) { // Iterate through all requests
            d = abs(RQ[i] - initial); // Calculate distance from current head position to the request
            if (min > d ) { // If current distance is less than min and request is unserviced
                min = d; // Update min to the current distance
                index = i; // Store the index of the closest request
            }
        }

        TotalHeadMoment += min; // Accumulate the total head movement
        initial = RQ[index]; // Move the head to the closest request

        RQ[index] = 1000; // Mark the serviced request by assigning a value that won't be a valid request
        count++; // Increment the count of serviced requests
    }

    // Output the total head movement after servicing all requests
    printf("Total head movement is %d", TotalHeadMoment); 
    return 0; // Return to the main function
}

int main() {
    int ch, YN = 1; // Variable declaration
    // ch: user choice for menu; YN: variable to control the continuation of the program

    do {
        printf("\n\n\t*********** MENU ***********"); // Display the menu header
        printf("\n\n\t1:SSTF\n\n\t2:EXIT"); // Menu options for SSTF and exit
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &ch); // Read user choice

        switch (ch) { // Process user choice
            case 1: 
                SSTF(); // Call the SSTF function to process disk requests
                break; // Break from the switch statement
            
            case 2: 
                exit(0); // Terminate the program
        } 

        printf("\n\n\tDo you want to continue? If YES, press 1; if NO, press 0: ");
        scanf("%d", &YN); // Read user input to decide whether to continue
    } while (YN == 1); // Repeat the loop while the user chooses to continue

    return 0; // Return 0 to indicate successful completion of the program
}

