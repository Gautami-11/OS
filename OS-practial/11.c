// Purpose and Main Use of the Code
// The provided code implements three disk scheduling algorithms: SSTF (Shortest Seek Time First), SCAN, and C-LOOK. It presents a menu to the user to choose an algorithm, takes input for the number of requests and their positions, and calculates the total head movement for each algorithm.

// Libraries Used
// stdio.h: For input and output functions like printf() and scanf().
// stdlib.h: For functions such as abs() and exit(), as well as memory management.
// Code with Line-by-Line Explanation
// c
// Copy code
#include <stdio.h>  // Include standard I/O library for input and output functions
#include <stdlib.h> // Include standard library for memory allocation and process control functions

// Function prototypes for the disk scheduling algorithms
int SSTF(); 
int SCAN(); 
int CLOOK(); 

int main() {
    int ch, YN = 1, i, l, f; // Variable declaration
    char F[10], s[25]; // Arrays to store flags and strings
    for (i = 0; i < f; i++) { // Initialize array F
         F[i] = -1; // Set initial values in F to -1
    }

    do {
        //system("clear"); // Optional: clear the screen (commented out)
        // Display menu for user to choose a disk scheduling algorithm
        printf("\n\n\t*********** MENU ***********"); 
        printf("\n\n\t1:SSTF\n\n\t2:SCAN\n\n\t3:CLOOK\n\n\t4:EXIT"); 
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &ch); // Read user choice

        // Switch case for algorithm selection
        switch (ch) {
            case 1: // If SSTF is chosen
                for (i = 0; i < f; i++) {
                    F[i] = -1; // Reset F
                }
                SSTF(); // Call SSTF function
                break;
            case 2: // If SCAN is chosen
                for (i = 0; i < f; i++) {
                    F[i] = -1; // Reset F
                }
                SCAN(); // Call SCAN function
                break;
            case 3: // If CLOOK is chosen
                for (i = 0; i < f; i++) {
                    F[i] = -1; // Reset F
                }
                CLOOK(); // Call CLOOK function
                break;
            case 4: // If EXIT is chosen
                exit(0); // Terminate the program
        } 

        // Prompt user for continuation
        printf("\n\n\tDo you want to continue? If YES, press 1; if NO, press 0: ");
        scanf("%d", &YN); // Read user input for continuation
    } while (YN == 1); // Repeat while user chooses to continue
    return (0); // Return 0 to indicate successful completion
}

// SSTF Algorithm
int SSTF() {
    int RQ[100], i, n, TotalHeadMoment = 0, initial, count = 0; // Variable declaration
    printf("Enter the number of Requests\n");
    scanf("%d", &n); // Read number of requests
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]); // Read each request position
    }
    printf("Enter initial head position\n");
    scanf("%d", &initial); // Read initial head position

    // Main logic for SSTF algorithm
    while (count != n) {
        int min = 1000, d, index; // Initialize min to a high value
        for (i = 0; i < n; i++) {
            d = abs(RQ[i] - initial); // Calculate distance from current position
            if (min > d) { // If the current distance is less than min
                min = d; // Update min
                index = i; // Store index of closest request
            }
        }
        TotalHeadMoment += min; // Accumulate total head movement
        initial = RQ[index]; // Move head to the closest request

        RQ[index] = 1000; // Mark the request as serviced
        count++; // Increment serviced request count
    }
    printf("Total head movement is %d", TotalHeadMoment); // Print total head movement
    return 0; // Return to the main function
}

// SCAN Algorithm
int SCAN() {
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move; // Variable declaration
    printf("Enter the number of Requests\n");
    scanf("%d", &n); // Read number of requests
    printf("Enter the Requests sequence\n"); 
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]); // Read each request position
    }
    printf("Enter initial head position\n");
    scanf("%d", &initial); // Read initial head position
    printf("Enter total disk size\n"); 
    scanf("%d", &size); // Read total disk size
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move); // Read head movement direction

    // Sort the requests in ascending order
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp; // Temporary variable for swapping
                temp = RQ[j]; // Swap elements
                RQ[j] = RQ[j + 1]; 
                RQ[j + 1] = temp;
            }
        }
    }

    int index; // Variable to hold the index of the next request
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i; // Find the first request greater than initial
            break;
        }
    }

    // Handle upward movement
    if (move == 1) {
        for (i = index; i < n; i++) {
            TotalHeadMoment += abs(RQ[i] - initial); // Accumulate head movement
            initial = RQ[i]; // Move head to current request
        }
        TotalHeadMoment += abs(size - RQ[i - 1] - 1); // Move to end of disk
        initial = size - 1; // Set head position to end of disk
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMoment += abs(RQ[i] - initial); // Move back through requests
            initial = RQ[i]; // Update head position
        }
    }
    else { // Handle downward movement
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMoment += abs(RQ[i] - initial); // Move backward
            initial = RQ[i]; // Update head position
        }
        TotalHeadMoment += abs(RQ[i + 1] - 0); // Move to the beginning of the disk
        initial = 0; // Set head position to start of disk
        for (i = index; i < n; i++) {
            TotalHeadMoment += abs(RQ[i] - initial); // Move forward through requests
            initial = RQ[i]; // Update head position
        }
    }
    printf("Total head movement is %d", TotalHeadMoment); // Print total head movement
    return 0; // Return to the main function
}

// C-LOOK Algorithm
int CLOOK() {
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move; // Variable declaration
    printf("Enter the number of Requests\n");
    scanf("%d", &n); // Read number of requests
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]); // Read each request position
    }
    printf("Enter initial head position\n");
    scanf("%d", &initial); // Read initial head position
    printf("Enter total disk size\n");
    scanf("%d", &size); // Read total disk size
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move); // Read head movement direction

    // Sort the requests in ascending order
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp; // Temporary variable for swapping
                temp = RQ[j]; // Swap elements
                RQ[j] = RQ[j + 1]; 
                RQ[j + 1] = temp;
            }
        }
    }

    int index; // Variable to hold the index of the next request
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i; // Find the first request greater than initial
            break;
        }
    }

    // Handle upward movement
    if (move == 1) {
        for (i = index; i < n; i++) {
            TotalHeadMoment += abs(RQ[i] - initial); // Accumulate head movement
            initial = RQ[i]; // Move head to current request
        }
        for (i = 0; i < index; i++) {
            TotalHeadMoment += abs(RQ[i] - initial); // Move to next cycle
            initial = RQ[i]; // Update head position
        }
    }
    else { // Handle downward movement
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMoment += abs(RQ[i] - initial); // Move backward
            initial = RQ[i]; // Update head position
        }
        for (i = n - 1; i >= index; i--) {
            TotalHeadMoment += abs(RQ[i] - initial); // Move forward through requests
            initial = RQ[i]; // Update head position
        }
    }
    printf("Total head movement is %d", TotalHeadMoment); // Print total head movement
    return 0; // Return to the main function
}
// Keywords and Their Explanations
// #include <stdio.h>: A preprocessor directive to include the standard input-output library for functions like printf() and scanf().
// #include <stdlib.h>: A preprocessor directive to include the standard library for functions like abs() (absolute value) and exit() (to terminate the program).
// int main(): The main function where execution begins.
// switch-case: A control statement used to execute different parts of code based on the value of a variable.
// while: A loop that executes a block of code as long as a specified condition is true.
// scanf(): A function used to read formatted input from standard input (keyboard).
// printf(): A function used to output formatted data to standard output (console).
// abs(): A function that returns the absolute value of an integer.
// exit(0): A function that terminates the program successfully.
// Possible Questions and Answers
// What is the purpose of the SSTF algorithm?

// Answer: The SSTF (Shortest Seek Time First) algorithm aims to reduce the total head movement of the disk by servicing the request that is closest to the current head position.
// How does the SCAN algorithm work?

// Answer: The SCAN algorithm moves the disk arm in one direction, servicing all requests until it reaches the end of the disk, then reverses direction and services requests on the way back.
// What is the difference between C-LOOK and SCAN?

// Answer: C-LOOK services requests in a circular manner without going to the end of the disk, whereas SCAN goes to the end before reversing direction.
// Why do we sort the request queue in the SCAN and C-LOOK algorithms?

// Answer: Sorting the request queue is essential for both algorithms to determine the order of servicing requests efficiently, ensuring that the head movement is minimized.
// What happens if the head movement direction is not specified in the SCAN algorithm?

// Answer: If the direction is not specified, the SCAN algorithm cannot determine the path to service requests, potentially leading to incorrect calculations of total head movement.
// Conclusion
