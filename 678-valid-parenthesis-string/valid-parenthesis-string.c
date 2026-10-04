bool checkValidString(char* s) {
    int minOpen = 0;
    int maxOpen = 0;

    for (int i = 0; s[i] != '\0'; i++) {

        if (s[i] == '(') {
            minOpen++;
            maxOpen++;
        }
        else if (s[i] == ')') {
            minOpen--;
            maxOpen--;
        }
        else {  // '*'
            minOpen--;  // '*' acts as ')'
            maxOpen++;  // '*' acts as '('
        }

        // Too many ')' 
        if (maxOpen < 0)
            return false;

        // minOpen cannot be negative
        if (minOpen < 0)
            minOpen = 0;
    }

    // All '(' must be matched
    return minOpen == 0;
}
//krish