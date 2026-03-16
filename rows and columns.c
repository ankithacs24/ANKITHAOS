#include <stdio.h>

int main() {
    int a[10][10], row, col, i, j;
    int rsum, csum;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &row, &col);

    printf("Enter matrix elements:\n");

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for(i = 0; i < row; i++) {
        rsum = 0;
        for(j = 0; j < col; j++) {
            rsum = rsum + a[i][j];
        }
        printf("Sum of row %d = %d\n", i+1, rsum);
    }


    for(j = 0; j < col; j++) {
        csum = 0;
        for(i = 0; i < row; i++) {
            csum = csum + a[i][j];
        }
        printf("Sum of column %d = %d\n", j+1, csum);
    }

    return 0;
}
