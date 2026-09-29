#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s) {
    int n = strlen(s);

    if (n <= 1)
        return s;

    int start = 0;
    int maxLen = 1;

    for (int i = 0; i < n; i++) {

        // Odd length palindrome
        int left = i;
        int right = i;

        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                start = left;
                maxLen = right - left + 1;
            }
            left--;
            right++;
        }

        // Even length palindrome
        left = i;
        right = i + 1;

        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                start = left;
                maxLen = right - left + 1;
            }
            left--;
            right++;
        }
    }

    // Create the answer
    char* ans = malloc((maxLen + 1) * sizeof(char));

    strncpy(ans, s + start, maxLen);
    ans[maxLen] = '\0';

    return ans;
}
//krish