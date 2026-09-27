#include <stdlib.h>

int** insert(int** intervals, int intervalsSize, int* intervalsColSize,
             int* newInterval, int newIntervalSize,
             int* returnSize, int** returnColumnSizes) {

    int** result = malloc((intervalsSize + 1) * sizeof(int*));
    *returnColumnSizes = malloc((intervalsSize + 1) * sizeof(int));

    int count = 0;
    int i = 0;

    // 1. Add intervals completely before newInterval
    while (i < intervalsSize && intervals[i][1] < newInterval[0]) {
        result[count] = malloc(2 * sizeof(int));

        result[count][0] = intervals[i][0];
        result[count][1] = intervals[i][1];

        (*returnColumnSizes)[count] = 2;

        count++;
        i++;
    }

    // 2. Merge overlapping intervals
    int start = newInterval[0];
    int end = newInterval[1];

    while (i < intervalsSize && intervals[i][0] <= end) {
        if (intervals[i][0] < start)
            start = intervals[i][0];

        if (intervals[i][1] > end)
            end = intervals[i][1];

        i++;
    }

    result[count] = malloc(2 * sizeof(int));
    result[count][0] = start;
    result[count][1] = end;
    (*returnColumnSizes)[count] = 2;
    count++;

    // 3. Add remaining intervals
    while (i < intervalsSize) {
        result[count] = malloc(2 * sizeof(int));

        result[count][0] = intervals[i][0];
        result[count][1] = intervals[i][1];

        (*returnColumnSizes)[count] = 2;

        count++;
        i++;
    }

    *returnSize = count;

    return result;
}
//krish