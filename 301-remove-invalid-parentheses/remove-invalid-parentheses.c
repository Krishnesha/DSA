#include <stdlib.h>
#include <string.h>

char** removeInvalidParentheses(char* s, int* returnSize) {
    int n = strlen(s);

    int left = 0, right = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            left++;
        } else if (s[i] == ')') {
            if (left > 0)
                left--;
            else
                right++;
        }
    }

   
    char** result = malloc(10000 * sizeof(char*));
    *returnSize = 0;

    
    void dfs(int pos, int lremove, int rremove,
             int balance, char* path) {

        if (pos == n) {
            if (lremove == 0 && rremove == 0 && balance == 0) {
                path[strlen(path)] = '\0';

                // Check for duplicate
                for (int i = 0; i < *returnSize; i++) {
                    if (strcmp(result[i], path) == 0)
                        return;
                }

                result[*returnSize] = malloc(strlen(path) + 1);
                strcpy(result[*returnSize], path);
                (*returnSize)++;
            }
            return;
        }

        char c = s[pos];
        int len = strlen(path);

        
        if (c == '(' && lremove > 0) {
            dfs(pos + 1, lremove - 1, rremove,
                balance, path);
        }

        if (c == ')' && rremove > 0) {
            dfs(pos + 1, lremove, rremove - 1,
                balance, path);
        }

       
        if (c == '(') {
            path[len] = c;
            path[len + 1] = '\0';

            dfs(pos + 1, lremove, rremove,
                balance + 1, path);

            path[len] = '\0';
        }
        else if (c == ')') {
            if (balance > 0) {
                path[len] = c;
                path[len + 1] = '\0';

                dfs(pos + 1, lremove, rremove,
                    balance - 1, path);

                path[len] = '\0';
            }
        }
        else {
           
            path[len] = c;
            path[len + 1] = '\0';

            dfs(pos + 1, lremove, rremove,
                balance, path);

            path[len] = '\0';
        }
    }

    char* path = malloc(n + 1);
    path[0] = '\0';

    dfs(0, left, right, 0, path);

    free(path);

    return result;
}
//krish