#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool wordBreak(char* s, char** wordDict, int wordDictSize) {

    int n = strlen(s);

    /*
     * dp[i] = true if s[0...i-1] can be segmented.
     */
    bool* dp = calloc(n + 1, sizeof(bool));

    dp[0] = true;

    for (int i = 1; i <= n; i++) {

        for (int j = 0; j < i; j++) {

            /*
             * If s[0...j-1] can be segmented,
             * check whether s[j...i-1] is a dictionary word.
             */
            if (!dp[j])
                continue;

            int len = i - j;

            for (int k = 0; k < wordDictSize; k++) {

                if ((int)strlen(wordDict[k]) != len)
                    continue;

                bool match = true;

                for (int x = 0; x < len; x++) {
                    if (s[j + x] != wordDict[k][x]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    dp[i] = true;
                    break;
                }
            }

            if (dp[i])
                break;
        }
    }

    bool answer = dp[n];

    free(dp);

    return answer;
}
//krish