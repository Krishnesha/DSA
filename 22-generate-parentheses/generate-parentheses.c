#include <stdlib.h>
#include <string.h>

void backtrack(char **result, char *current, int pos,
               int open, int close, int n, int *count) {

    
    if (pos == 2 * n) {
        current[pos] = '\0';

        result[*count] = (char *)malloc((2 * n + 1) * sizeof(char));
        strcpy(result[*count], current);

        (*count)++;
        return;
    }

    
    if (open < n) {
        current[pos] = '(';

        backtrack(result, current, pos + 1,
                  open + 1, close, n, count);
    }

   
    if (close < open) {
        current[pos] = ')';

        backtrack(result, current, pos + 1,
                  open, close + 1, n, count);
    }
}

char** generateParenthesis(int n, int* returnSize) {

    // Maximum number of combinations for n <= 8 is 1430
    char **result = (char **)malloc(1430 * sizeof(char *));

    char *current = (char *)malloc((2 * n + 1) * sizeof(char));

    int count = 0;

    backtrack(result, current, 0, 0, 0, n, &count);

    free(current);

    *returnSize = count;

    return result;
}
//krish