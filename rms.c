#include <stdio.h>
#include <math.h>

#define MAX 10
#define TIME 20
#define QUANTUM 10

struct Task {
    int id;
    float C, T, D;
    float remaining;
    float weight;
};

// -------- GANTT CHART --------
void printGantt(int timeline[]) {
    printf("\nGantt Chart:\n|");
    for(int i = 0; i < TIME; i++) {
        if(timeline[i] == 0)
            printf(" Idle |");
        else
            printf(" T%d |", timeline[i]);
    }

    printf("\n0");
    for(int i = 1; i <= TIME; i++)
        printf("    %d", i);
    printf("\n");
}

// -------- RMS --------
void RMS(struct Task t[], int n) {
    float U = 0, bound;

    // Utilization
    for(int i = 0; i < n; i++)
        U += (t[i].C / t[i].T);

    bound = n * (pow(2, 1.0/n) - 1);

    printf("\n===== RMS =====\n");
    printf("Utilization = %.2f | Bound = %.2f\n", U, bound);

    // Sort by period
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(t[i].T > t[j].T) {
                struct Task temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }

    // Reset remaining
    for(int i = 0; i < n; i++)
        t[i].remaining = t[i].C;

    int timeline[TIME];

    // Simulation
    for(int time = 0; time < TIME; time++) {
        int executed = -1;

        for(int i = 0; i < n; i++) {
            if(t[i].remaining > 0) {
                executed = i;
                break;
            }
        }

        if(executed != -1) {
            timeline[time] = t[executed].id;
            t[executed].remaining--;

            // periodic reset
            if((time + 1) % (int)t[executed].T == 0)
                t[executed].remaining = t[executed].C;
        } else {
            timeline[time] = 0;
        }
    }

    printGantt(timeline);
}

// -------- EDF --------
void EDF(struct Task t[], int n) {
    float U = 0;

    printf("\n===== EDF =====\n");

    for(int i = 0; i < n; i++) {
        U += (t[i].C / t[i].D);
        t[i].remaining = t[i].C;
    }

    printf("Utilization = %.2f\n", U);

    int timeline[TIME];

    for(int time = 0; time < TIME; time++) {
        int idx = -1;
        float minD = 9999;

        for(int i = 0; i < n; i++) {
            if(t[i].remaining > 0 && t[i].D < minD) {
                minD = t[i].D;
                idx = i;
            }
        }

        if(idx != -1) {
            timeline[time] = t[idx].id;
            t[idx].remaining--;
        } else {
            timeline[time] = 0;
        }
    }

    printGantt(timeline);
}

// -------- PROPORTIONAL --------
void PROPORTIONAL(struct Task t[], int n) {
    float total = 0;

    printf("\n===== PROPORTIONAL =====\n");

    for(int i = 0; i < n; i++) {
        printf("Enter weight for Task %d: ", t[i].id);
        scanf("%f", &t[i].weight);
        total += t[i].weight;
    }

    int timeline[TIME];
    int time = 0;

    while(time < TIME) {
        for(int i = 0; i < n && time < TIME; i++) {
            int slice = (t[i].weight / total) * QUANTUM;
            if(slice < 1) slice = 1;

            for(int j = 0; j < slice && time < TIME; j++) {
                timeline[time++] = t[i].id;
            }
        }
    }

    printGantt(timeline);
}

// -------- MAIN --------
int main() {
    int n;
    struct Task t[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        t[i].id = i + 1;

        printf("\nTask %d:\n", i+1);
        printf("Execution Time: ");
        scanf("%f", &t[i].C);
        printf("Period: ");
        scanf("%f", &t[i].T);
        printf("Deadline: ");
        scanf("%f", &t[i].D);
    }

    RMS(t, n);
    EDF(t, n);
    PROPORTIONAL(t, n);

    return 0;
}
