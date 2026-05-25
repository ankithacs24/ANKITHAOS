#include <stdio.h>

int search(int key, int frame[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frame[i] == key)
            return 1;
    }
    return 0;
}

void FIFO(int pages[], int n, int capacity) {
    int frame[capacity];
    int index = 0, faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frame, capacity)) {
            frame[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }
    }

    printf("\nFIFO Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int capacity) {
    int frame[capacity], time[capacity];
    int faults = 0, counter = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = 0;

            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[pos])
                    pos = j;
            }

            counter++;
            frame[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}

void Optimal(int pages[], int n, int capacity) {
    int frame[capacity];
    int faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frame, capacity)) {

            int pos = -1, farthest = i;

            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }

                if (k == n) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
                pos = 0;

            frame[pos] = pages[i];
            faults++;
        }
    }

    printf("Optimal Page Faults = %d\n", faults);
}

int main() {
    int n, capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}
