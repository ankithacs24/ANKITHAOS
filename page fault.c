#include <stdio.h>

int main()
{
    int frames, n, i, j, k, pos, max, faults;

    printf("Enter the number of Frames: ");
    scanf("%d", &frames);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    int ref[n];

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    // ---------------- FIFO ----------------
    int fifo[frames], front = 0;
    faults = 0;

    for(i = 0; i < frames; i++)
        fifo[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(fifo[j] == ref[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            fifo[front] = ref[i];
            front = (front + 1) % frames;
            faults++;

            printf("PF No. %d: ", faults);

            for(j = 0; j < frames; j++)
            {
                if(fifo[j] != -1)
                    printf("%d ", fifo[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("FIFO Page Faults: %d\n", faults);

    // ---------------- LRU ----------------
    int lru[frames], recent[frames];

    faults = 0;

    for(i = 0; i < frames; i++)
    {
        lru[i] = -1;
        recent[i] = 0;
    }

    printf("\nLRU Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(lru[j] == ref[i])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if(!found)
        {
            pos = 0;

            for(j = 1; j < frames; j++)
            {
                if(recent[j] < recent[pos])
                    pos = j;
            }

            for(j = 0; j < frames; j++)
            {
                if(lru[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            lru[pos] = ref[i];
            recent[pos] = i;
            faults++;

            printf("PF No. %d: ", faults);

            for(j = 0; j < frames; j++)
            {
                if(lru[j] != -1)
                    printf("%d ", lru[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("LRU Page Faults: %d\n", faults);

    // ---------------- Optimal ----------------
    int opt[frames];

    faults = 0;

    for(i = 0; i < frames; i++)
        opt[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(opt[j] == ref[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int empty = -1;

            for(j = 0; j < frames; j++)
            {
                if(opt[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if(empty != -1)
            {
                pos = empty;
            }
            else
            {
                max = -1;

                for(j = 0; j < frames; j++)
                {
                    int nextUse = 999;

                    for(k = i + 1; k < n; k++)
                    {
                        if(opt[j] == ref[k])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > max)
                    {
                        max = nextUse;
                        pos = j;
                    }
                }
            }

            opt[pos] = ref[i];
            faults++;

            printf("PF No. %d: ", faults);

            for(j = 0; j < frames; j++)
            {
                if(opt[j] != -1)
                    printf("%d ", opt[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("Optimal Page Faults: %d\n", faults);

    return 0;
}
