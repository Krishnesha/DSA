#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void combinationSum2Backtrack(
    int *candidates,
    int candidatesSize,
    int target,
    int start,
    int *current,
    int currentSize,
    int **result,
    int *returnSize,
    int **returnColumnSizes
) {

    // Target reached
    if (target == 0) {

        result[*returnSize] =
            (int *)malloc(currentSize * sizeof(int));

        for (int i = 0; i < currentSize; i++)
            result[*returnSize][i] = current[i];

        (*returnColumnSizes)[*returnSize] = currentSize;

        (*returnSize)++;

        return;
    }

    for (int i = start; i < candidatesSize; i++) {

        // Skip duplicate numbers at same level
        if (i > start && candidates[i] == candidates[i - 1])
            continue;

        // Since sorted, no later number will work
        if (candidates[i] > target)
            break;

        current[currentSize] = candidates[i];

        combinationSum2Backtrack(
            candidates,
            candidatesSize,
            target - candidates[i],
            i + 1,
            current,
            currentSize + 1,
            result,
            returnSize,
            returnColumnSizes
        );
    }
}

int** combinationSum2(
    int* candidates,
    int candidatesSize,
    int target,
    int* returnSize,
    int** returnColumnSizes
) {

    // Sort the array
    qsort(candidates, candidatesSize,
          sizeof(int), compare);

    int maxResults = 10000;

    int **result =
        (int **)malloc(maxResults * sizeof(int *));

    *returnColumnSizes =
        (int *)malloc(maxResults * sizeof(int));

    int *current =
        (int *)malloc(candidatesSize * sizeof(int));

    *returnSize = 0;

    combinationSum2Backtrack(
        candidates,
        candidatesSize,
        target,
        0,
        current,
        0,
        result,
        returnSize,
        returnColumnSizes
    );

    free(current);

    return result;
}
//krish