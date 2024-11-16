// 1. Concept Behind the Code
// The code implements three page replacement algorithms commonly used in operating systems to manage memory. These algorithms decide which page to replace in the memory when a new page needs to be loaded and the memory (or frame) is full. The algorithms included are:

// FIFO (First In, First Out): The oldest page is replaced first.
// LRU (Least Recently Used): The page that has not been used for the longest time is replaced.
// Optimal: The page that will not be used for the longest period in the future is replaced.
// 2. Line-by-Line Explanation of Code

#include<stdio.h> 
typedef struct { 
    char data[20][2]; 
    int end; 
} queue; 
Includes the standard I/O library and defines a queue structure to hold pages and track the end of the queue.

void enqueue(queue *q, char data, int position); 
char dequeue(queue *q, int position); 
void fifo(char string[], int frameSize, int count); 
void optimal(char string[], int frameSize, int count); 
void lru(char string[], int frameSize, int count); 
Function prototypes for operations like enqueue, dequeue, and the three page replacement algorithms.

void main() { 
    int frameSize, count, cnt, ch; 
    char string[50]; 
    printf("Enter the string: "); 
    count = 0; 
    do { 
        scanf("%c", &string[count]); 
        count++; 
    } while (string[count - 1] != '\n'); 
    count--;
    printf("\nEnter the size of the frame: "); 
    scanf("%d", &frameSize); 
The main function prompts the user for a string representing page requests and the frame size.

do { 
    printf("\nMENU\n====\n1.FIFO\n2.Least Recently Used (LRU)\n3.Optimal\n4.Exit\n\nYour Choice:"); 
    scanf("%d", &ch); 
    switch (ch) { 
        case 1:
            fifo(string, frameSize, count); 
            break;
        case 2:
            lru(string, frameSize, count); 
            break; 
        case 3:
            optimal(string, frameSize, count); 
            break; 
        case 4:
            break; 
        default:
            printf("\nInvalid choice! Please try again!"); 
            continue; 
    } 
} while (ch != 4); 
Displays a menu to choose the page replacement algorithm and executes the corresponding function based on user input.
FIFO Algorithm

void fifo(char string[], int frameSize, int count) { 
    int cnt, cnt2, flag, faults = 0; 
    queue q; 
    int firstin = -1; 
    q.end = 0; 
    printf("\nData Requested\tFrame contents\t    Page Fault\n=============================================="); 
Initializes variables and prints the header for output.

for (cnt = 0; cnt < count; cnt += 1) { 
    printf("\n\n\t%c", string[cnt]); 
    flag = 0; 
    for (cnt2 = 0; cnt2 < q.end; cnt2++) { 
        if (string[cnt] == q.data[cnt2][0]) { 
            flag = 1; 
            break; 
        } 
    } 
Iterates through each page request, checks if the page is already in the frame.

if (flag == 0) { // Page fault
    faults++; 
    if (q.end < frameSize) {	
        enqueue(&q, string[cnt], q.end); 
        q.end++; 
    } else { 
        dequeue(&q, firstin); 
        firstin = (firstin + 1) % (q.end); 
        enqueue(&q, string[cnt], firstin); 
    } 
Handles page faults: if the page is not found, it either adds it to the frame (if space is available) or replaces an existing page.

    //LRU Algorithm

void lru(char string[], int frameSize, int count) { 
    int cnt, cnt2, selector, flag, faults = 0; 
    queue q; 
    q.end = 0; 
    int lastUsed[20] = {0}; 
Initializes the LRU algorithm, with an array to track the last usage of each page.

for (cnt = 0; cnt < count; cnt += 1) { 
    printf("\n\n\t%c", string[cnt]); 
    flag = 0; 
    // Check if the page is already in the frame
    for (cnt2 = 0; cnt2 < q.end; cnt2++) {	 
        if (string[cnt] == q.data[cnt2][0]) { 
            flag = 1; 
            break; 
        } 
    } 
Checks if the requested page is in the frame and handles page faults.

//Optimal Algorithm

void optimal(char string[], int frameSize, int count) {
    int cnt, cnt2, selector, flag, max, faults = 0;
    int distance[20];
    queue q;
    q.end = 0;
Initializes the optimal page replacement algorithm, calculating the future usage of pages to determine which one to replace.

    3. Explanation for Specific Keywords
Queue: A data structure used to store elements in a specific order. In this case, it's used to manage pages in memory.
Enqueue: Adding an item to the end of the queue.
Dequeue: Removing an item from the front of the queue.
Page Fault: Occurs when a requested page is not in the memory, requiring a page replacement.
    
// 4. Expected Oral Questions and Answers
Q: What is a page fault?

A: A page fault occurs when a program attempts to access a page that is not currently in physical memory, requiring the operating system to load the page from disk.
Q: Explain the FIFO page replacement algorithm.

A: FIFO replaces the oldest page in memory when a new page needs to be loaded. It maintains a queue of pages, and the page that has been in the queue the longest is removed first.
Q: What are the disadvantages of the LRU algorithm?

A: LRU can be complex to implement as it requires keeping track of the order of page usage, which may involve additional overhead in terms of time and memory.
Q: How does the optimal page replacement algorithm work?

A: The optimal algorithm replaces the page that will not be used for the longest time in the future, which minimizes page faults but requires knowledge of future page requests.
5. Output Example
For the input string 95864854758457874625 and frame size 3, the program will output the page fault results for each algorithm selected.

You can run the program to see the detailed output for the specified string and frame size. Make sure to provide the correct input format for the string and the frame size as required by the program.
