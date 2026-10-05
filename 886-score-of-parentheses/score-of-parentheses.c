int scoreOfParentheses(char* s) {
    int stack[100];
    int top = 0;

    stack[0] = 0;

    for (int i = 0; s[i] != '\0'; i++) {

        if (s[i] == '(') {
            // Start a new level
            stack[++top] = 0;
        } 
        else {
            // Closing parenthesis
            int current = stack[top--];

            if (current == 0)
                current = 1;       // "()" = 1
            else
                current = 2 * current;  // "(A)" = 2*A

            stack[top] += current;
        }
    }

    return stack[0];
}
//krish
