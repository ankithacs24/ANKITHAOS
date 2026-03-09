#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, time = 0, smallest;
    int arrival[20], burst[20], remaining[20];
    int completion[20], waiting[20], turnaround[20];
    int completed = 0;
    float total_wait = 0, total_turn = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &arrival[i]);

        printf("Enter burst time of process %d: ", i+1);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i];
    }

    while(completed != n) {
        smallest = -1;
        int min = INT_MAX;

        for(i = 0; i < n; i++) {
            if(arrival[i] <= time && remaining[i] > 0 && remaining[i] < min) {
                min = remaining[i];
                smallest = i;
            }
        }

        if(smallest == -1) {
            time++;
            continue;
        }

        remaining[smallest]--;
        time++;

        if(remaining[smallest] == 0) {
            completed++;
            completion[smallest] = time;

            turnaround[smallest] = completion[smallest] - arrival[smallest];
            waiting[smallest] = turnaround[smallest] - burst[smallest];

            total_wait += waiting[smallest];
            total_turn += turnaround[smallest];
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
            i+1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wait/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_turn/n);

    return 0;
}
