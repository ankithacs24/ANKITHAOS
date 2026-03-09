#include <stdio.h>

int main() {
    int n, i, j;
    int at[20], bt[20], pr[20];
    int ct[20], wt[20], tat[20];
    int completed[20] = {0};
    int time = 0, done = 0, pos;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    while(done < n) {
        int highest = 9999;
        pos = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0 && pr[i] < highest) {
                highest = pr[i];
                pos = i;
            }
        }

        if(pos == -1) {
            time++;
        } else {
            ct[pos] = time + bt[pos];
            time = ct[pos];

            tat[pos] = ct[pos] - at[pos];
            wt[pos] = tat[pos] - bt[pos];

            avg_wt += wt[pos];
            avg_tat += tat[pos];

            completed[pos] = 1;
            done++;
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
