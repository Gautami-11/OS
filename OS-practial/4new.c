#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

typedef struct process {
    int BT, AT, TAT, WT, PID;
    char name[10];
} process;

void get_PCB(process[], int *);
void disp_table(process[], int);
void SJF_P(process[], int);
float cal_avgwt(process[], int);
float cal_avgtat(process[], int);

void menu() {
    printf("\n\t\t***MENU**");
    printf("\n\t\t1. SJF P");
    printf("\n\t\t2. EXIT");
    printf("\n\t\tEnter Choice: \t");
}

int main() {
    int ch, TQ, n;
    process P[MAX];
    float avg_WT, avg_TAT;

    get_PCB(P, &n);

    do {
        menu();
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                SJF_P(P, n);
                disp_table(P, n);
                avg_WT = cal_avgwt(P, n);
                avg_TAT = cal_avgtat(P, n);
                printf("\nAVERAGE WT  : %.2f", avg_WT);  // Ensure floating-point output
                printf("\nAVERAGE TAT : %.2f", avg_TAT);
                break;
            case 2:
                break;
            default:
                printf("Invalid choice! Please try again.");
        }

    } while (ch != 2);

    return 0;
}

float cal_avgwt(process p[], int n) {
    float avg = 0;
    for (int i = 0; i < n; i++) {
        avg += p[i].WT;
    }
    return avg / n;  // Correct floating-point average calculation
}

float cal_avgtat(process p[], int n) {
    float avg = 0;
    for (int i = 0; i < n; i++) {
        avg += p[i].TAT;
    }
    return avg / n;  // Correct floating-point average calculation
}

void disp_table(process p[], int n) {
    printf("\n\n P_NAME \t AT \t BT \t WT \t TAT \t");
    for (int i = 0; i < n; i++) {
        printf("\n %-10s \t %d \t %d \t %d \t %d \t", p[i].name, p[i].AT, p[i].BT, p[i].WT, p[i].TAT);
    }
}

void get_PCB(process p[], int *n) {
    printf("\nEnter total number of processes: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        printf("\nEnter Following details for Process %d", i + 1);
        printf("\nName: ");
        scanf("%s", p[i].name);
        printf("Arrival Time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
        p[i].TAT = 0;  // Initialize TAT
        p[i].WT = 0;   // Initialize WT
        p[i].PID = i;  // Set process ID
    }
}

void SJF_P(process p[], int n) {
    int time = 0, completed = 0;
    int min_index;
    int is_completed[MAX] = {0};  // Track completed processes

    while (completed < n) {
        min_index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && is_completed[i] == 0) {
                if (min_index == -1 || p[i].BT < p[min_index].BT) {
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            time += p[min_index].BT;  // Increment time by burst time of selected process
            p[min_index].TAT = time - p[min_index].AT;  // Calculate TAT
            p[min_index].WT = p[min_index].TAT - p[min_index].BT;  // Calculate WT
            is_completed[min_index] = 1;  // Mark process as completed
            completed++;  // Increment completed process count
        } else {
            time++;  // If no process is ready, just increment time
        }
    }
}

