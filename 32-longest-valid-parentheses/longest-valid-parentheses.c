int longestValidParentheses(char* s) {
    int n = 0;

    while (s[n] != '\0') {
        n++;
    }

    int stack[n + 1];
    int top = -1;

    // Base index
    stack[++top] = -1;

    int maxLen = 0;

    for (int i = 0; i < n; i++) {

        if (s[i] == '(') {
            // Store index of '('
            stack[++top] = i;
        } 
        else {
            // Remove matching '('
            top--;

            if (top == -1) {
                // No matching '('
                stack[++top] = i;
            } 
            else {
                // Length of valid substring
                int len = i - stack[top];

                if (len > maxLen) {
                    maxLen = len;
                }
            }
        }
    }

    return maxLen;
}
//krish