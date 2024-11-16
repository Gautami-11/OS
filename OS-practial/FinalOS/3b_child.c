// 1. Purpose and Main Use of the Code
// This C program sorts an array of integers in descending order using the bubble sort algorithm. The array is populated with command-line arguments, demonstrating the use of command-line argument parsing (using argc and argv), type conversion (using atoi()), and basic array manipulation. The program also illustrates fundamental concepts of sorting algorithms and handling variable-length inputs through command-line arguments.

// 2. Line-by-Line Explanation and Code Comments

#include <stdio.h>              // Standard I/O library for input and output functions.
#include <stdlib.h>             // Standard library for utility functions like atoi() and exit().
#include <sys/types.h>          // Defines data types used in system calls, like pid_t.
#include <unistd.h>             // Includes system calls like fork(), though not used in this code.

void bubble_dsc(int arr[], int n) {  // Function to sort an array in descending order.
    int i, j, temp;                  // Declares variables for looping and temporary storage.
    for (i = 0; i < n; i++) {        // Outer loop for bubble sort.
        for (j = 0; j < n - i - 1; j++) { // Inner loop to compare adjacent elements.
            if (arr[j] < arr[j + 1]) {    // Checks if the current element is less than the next.
                temp = arr[j];            // Swaps elements if condition is true.
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nArray in descending order: ");
    for (i = 0; i < n; i++) {        // Loop to print the sorted array.
        printf("\t%d", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) { // Main function with command line arguments.
    if (argc < 2) {                  // Checks if at least one number is provided as input.
        printf("No numbers provided.\n");
        return 1;                    // Exits with a non-zero status to indicate an error.
    }

    int n = argc - 1;                // The number of integers to sort, derived from command-line arguments.
    int a[n];                        // Array to hold the integers.

    // Convert arguments to integers
    for (int i = 1; i <= n; i++) {   // Loops through each argument, starting from the first number.
        a[i - 1] = atoi(argv[i]);    // Converts argument to integer and stores it in the array.
    }

    bubble_dsc(a, n);                // Calls bubble_dsc() to sort the array in descending order.

    return 0;                        // Exits the program successfully.
}
/*
3. Key Concepts and Simplified Explanations
argc and argv: argc is the count of command-line arguments, and argv is an array containing each argument as a string. argv[0] is the program name, and subsequent indices contain the user-provided values.

atoi(): Converts a string argument to an integer. It allows command-line arguments to be used in arithmetic operations by converting them to the appropriate data type.

Bubble Sort (Descending Order): A simple sorting technique where larger elements "bubble" to the top of the array in each pass. The array is sorted from highest to lowest by repeatedly swapping adjacent elements when they are in the wrong order.

Array: A data structure that stores multiple values of the same data type in contiguous memory locations, making it easy to access elements via their index.

4. Possible Questions and Answers
How does the program receive numbers to sort?

The program takes numbers as command-line arguments, converts them to integers using atoi(), and stores them in an array.
Explain the bubble sort algorithm used in this program.

Bubble sort repeatedly compares adjacent elements in an array and swaps them if they are in the wrong order. In this code, elements are sorted in descending order by swapping if the current element is less than the next.
What happens if no numbers are provided to the program?

The program checks if there are fewer than two arguments (indicating no numbers), displays a message, and exits with an error code.
Why is argc - 1 used for array size?

The first argument (argv[0]) is the program’s name. The actual numbers start from the second argument, so the array size is argc - 1.
Why is atoi() necessary here?

atoi() converts the command-line argument strings to integers so that they can be stored in an integer array and used in sorting.
*/
