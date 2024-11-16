# Operating Systems Practicals Guide

This README provides instructions on running OS practicals on Ubuntu. The practicals are organized as per the OSL chits PDF.

## Practical 1b - Shell Script
### Problem Statement
Write a program to implement an address book with options given below: a) Create address book.
b) View address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit

### How to Run
bash 1b.sh OR sh 1b.sh

## Practical 2 - C Program
### Description
Implement the C program in which main program accepts the integers to be sorted. Main
program uses the FORK system call to create a new process called a child process. Parent process
sorts the integers using sorting algorithm and waits for child process using WAIT system call to sort
the integers using any sorting algorithm. Also demonstrate zombie and orphan states.

### How to Run
gcc 2.c  
./a.out

## Practical 3a_parent 3b_parent - C Program
### Description
Implement the C program in which main program accepts an array. Main program uses the
FORK system call to create a new process called a child process. Parent process sorts an array and
passes the sorted array to child process through the command line arguments of EXECVE system call.
The child process uses EXECVE system call to load new program which display array in reverse
order.

### How to Run
gcc -o parent 3a_parent.c  
gcc -o child 3b_child.c  
./parent 2 4 6 3 8 1 0 (Any random digits)

## Practical 4 - C Program
### Description
Name: Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Preemptive)
and Round Robin with different arrival time.
Note: Assume any one CPU scheduling algorithm

### How to Run
gcc 4.c  
./a.out

## Practical 5 - C Program
### Description
Name: Thread synchronization using counting semaphores. Application to demonstrate: producer-
consumer problem with counting semaphores and mutex.

### How to Run
gcc 5.c  
./a.out

## Practical 6 - C Program
### Description
Name: Thread synchronization and mutual exclusion using mutex. Application to demonstrate:
Reader- Writer problem with reader priority.

### How to Run
gcc 6.c  
./a.out

## Practical 7 - C Program
### Description
Name: Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.

### How to Run
gcc 7.c  
./a.out

## Practical 8 - C Program
### Description
Name: Implement the C program for Page Replacement Algorithms: FCFS, LRU, and Optimal for
frame size as minimum three.
Note: Assume any one Page Replacement Algorithm.

### How to Run
gcc 8.c  
./a.out

## Practical 9 - C Program
### Description
Name: FIFOS: Full duplex communication between two independent processes. First process accepts
sentences and writes on one pipe to be read by second process and second process counts number of
characters, number of words and number of lines in accepted sentences, writes this output in a text file
and writes the contents of the file on second pipe to be read by first process and displays on standard
output.

### How to Run
gcc 9.c  
./a.out

## Practical 10 a b - C Program
### Description
Name: Inter-process Communication using Shared Memory using System V. Application to
demonstrate: Client and Server Programs in which server process creates a shared memory segment
and writes the message to the shared memory segment. Client process reads the message from the
shared memory segment and displays it to the screen.

### How to Run
First create file named shmfile  
gcc -o 10a 10a.c  
./10a  
gcc -o 10b 10b.c  
./10b

## Practical 11 - C Program
### Description
Name: Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, C-Look considering
the initial head position moving away from the spindle.
Note: Assume any one Disk Scheduling Algorithm.

### How to Run
gcc 11.c  
./a.out

## FAQ


