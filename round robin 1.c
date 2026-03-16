


#include <stdio.h>

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n], ct[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
        ct[i] = 0;


    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0, completed_processes = 0;

    do {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                done = 0;
                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    wt[i] = time - at[i] - bt[i];
                    tat[i] = time - at[i];
                    rt[i] = 0;
                    ct[i] = 1;
                    completed_processes++;
                }
            }
        }


        int any_ready = 0;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                any_ready = 1;
                break;
            }
        }
        if (!any_ready) {
            time++;
        }

    } while (completed_processes < n);


    int total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}

