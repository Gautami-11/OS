/*# Banker's Algorithm in C

This document outlines the implementation of the Banker's Algorithm in C, which is used to determine if a system is in a safe state with respect to resource allocation among multiple processes.
*/
#include <stdio.h>

struct process {
    int max[10], allocate[10], need[10];
} p[10];

int n, m;

void input(int available[]) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter allocated resources for P%d: ", i);
        for (int j = 0; j < m; j++){
         scanf("%d", &p[i].allocate[j]);
        printf("Enter max resources for P%d: ", i);
        }
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i].max[j]);
            p[i].need[j] = p[i].max[j] - p[i].allocate[j];
        }
    }
    printf("\nEnter available resources: ");
    for (int j = 0; j < m; j++) {
    scanf("%d", &available[j]);
    }
}

void display() {
    printf("\n\tPID\tALLOCATE\tMAX\t\tNEED\n");
    for (int i = 0; i < n; i++) {
        printf("\tP%d\t", i);
        for (int j = 0; j < m; j++){ printf("%d ", p[i].allocate[j]);
        printf("\t\t");}
        for (int j = 0; j < m; j++){ printf("%d ", p[i].max[j]);
        printf("\t\t");}
        for (int j = 0; j < m; j++) {printf("%d ", p[i].need[j]);
        printf("\n");}
    }
}

int isSafestate(int available[], int safesequence[]) {
    int work[10], finish[10] = {0}, k = 0;
    for (int j = 0; j < m; j++) {
    work[j] = available[j];
}
    while (1) {
        int proceed = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int flag = 1;
                for (int j = 0; j < m; j++) {
                    if (p[i].need[j] > work[j]) {
                        flag = 0; break;
                    }
                }
                if (flag) {
                    for (int j = 0; j < m; j++) work[j] += p[i].allocate[j];
                    finish[i] = 1; safesequence[k++] = i; proceed = 1;
                }
            }
        }
        if (!proceed) break;
    }
    for (int i = 0; i < n; i++) if (!finish[i]) return 0;
    return 1;
}

int main() {
    printf("Enter No of processes: "); scanf("%d", &n);
    printf("Enter No of resources: "); scanf("%d", &m);
    int available[10], safesequence[10];

    input(available);
    display();

    if (isSafestate(available, safesequence)) {
        printf("\nSYSTEM IS IN SAFE STATE...\nsafesequence is: ");
        for (int i = 0; i < n; i++) printf("P%d -> ", safesequence[i]);
    } else {
        printf("\nSYSTEM IS IN UNSAFE STATE!!!");
    }
    return 0;
}

