#include <stdio.h>

int main() {
    int n, m, i, j, k;

    // n = number of processes
    // m = number of resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m];
    int available[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display Need Matrix
    printf("\nNeed Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int finish[n], safeSequence[n];
    int work[m];

    // Initialize
    for(i = 0; i < n; i++)
        finish[i] = 0;

    for(i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {

            // Check if process is unfinished
            if(finish[i] == 0) {

                // Check Need <= Work
                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                // If process can execute
                if(possible) {

                    // Add allocation to work
                    for(k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // No process found
        if(found == 0) {
            break;
        }
    }

    // Check safe state
    if(count == n) {
        printf("\nSystem is in SAFE STATE\n");
        printf("Safe Sequence: ");

        for(i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }
    }
    else {
        printf("\nSystem is NOT in Safe State\n");
    }

    return 0;
}
