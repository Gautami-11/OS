#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct process {
    int BT, AT, TAT, WT, PID;
    char name[10];
} process;

typedef struct RQ {
    process pr[MAX];
    int f, r;
} RQ;

void get_PCB(process[], int *);
void disp_table(process[], int);
void RR(process p[], int n, int tq);
float cal_avgwt(process[], int);
float cal_avgtat(process[], int);

int main() {
    int TQ, n;
    process P[MAX];
    float avg_WT, avg_TAT;

    printf("\nEnter Time Quantum for Round Robin : ");
    scanf("%d", &TQ);

    get_PCB(P, &n);

    RR(P, n, TQ);
    disp_table(P, n);
    avg_WT = cal_avgwt(P, n);
    avg_TAT = cal_avgtat(P, n);
    printf("\nAVERAGE WT  : %f", avg_WT);
    printf("\nAVERAGE TAT : %f", avg_TAT);

    return 0;
}

float cal_avgwt(process p[], int n) {
    float avg = 0;
    for (int i = 0; i < n; i++) {
        avg += p[i].WT;
    }
    return avg / n;
}

float cal_avgtat(process p[], int n) {
    float avg = 0;
    for (int i = 0; i < n; i++) {
        avg += p[i].TAT;
    }
    return avg / n;
}

int get_first_process(process p[], int n) {
    int min = p[0].AT;
    int in = 0;
    for (int j = 1; j < n; j++) {
        if (p[j].AT < min) {
            min = p[j].AT;
            in = j;
        }
    }
    return in;
}

void check_arrival(RQ *r, process p[], int time, int n) {
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = r->f; j <= r->r; j++) {
            if (strcmp(p[i].name, r->pr[j].name) == 0) {
                flag = 1;
                break;
            }
        }
        if (p[i].AT == time && flag == 0) {
            if (r->r + 1 < MAX) {
                r->pr[++r->r] = p[i];
            }
        }
    }
}

void RR(process p[], int n, int tq) {
    int time = 0;
    RQ r;
    r.f = r.r = -1;
    int start = get_first_process(p, n);
    r.pr[0] = p[start];
    r.f = r.r = 0;
    check_arrival(&r, p, time, n);

    while (r.f != -1) {
        for (int count = 0; count < tq && r.pr[r.f].BT > 0; count++) {
            r.pr[r.f].BT--;
            time++;
            check_arrival(&r, p, time, n);
        }

        if (r.pr[r.f].BT > 0) {
            if (r.r + 1 < MAX) {
                r.pr[++r.r] = r.pr[r.f];
            }
        } else {
            p[r.pr[r.f].PID].TAT = time - p[r.pr[r.f].PID].AT;
            p[r.pr[r.f].PID].WT = p[r.pr[r.f].PID].TAT - (p[r.pr[r.f].PID].BT);
        }

        if (r.f == r.r) {
            r.f = r.r = -1;
        } else {
            r.f++;
        }
    }
}

void disp_table(process p[], int n) {
    printf("\n\n P_NAME \t AT \t BT \t WT \t TAT \t");
    for (int i = 0; i < n; i++) {
        printf("\n %-10s \t %d \t %d \t %d \t %d \t", p[i].name, p[i].AT, p[i].BT, p[i].WT, p[i].TAT);
    }
}

void get_PCB(process p[], int *n) {
    printf("\nEnter total no of processes : ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        printf("\n Enter Following details for Process %d", i + 1);
        printf("\nName :\t");
        scanf("%s", p[i].name);
        printf("\nArrival Time :\t");
        scanf("%d", &p[i].AT);
        printf("\nBurst Time :\t");
        scanf("%d", &p[i].BT);
        p[i].PID = i;
    }
}

