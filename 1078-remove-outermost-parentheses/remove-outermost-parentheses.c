char* removeOuterParentheses(char* s) {
    int depth = 0;
    int j=0;

    for (int i = 0; s[i] != '\0'; i++) {

        if (s[i] == '(') {
            depth++;

            if (depth > 1) {
                s[j++] = '(';
            }
        }
        else {
            depth--;

         
            if (depth > 0) {
                s[j++] = ')';
            }
        }
    }

    s[j] = '\0';

    return s;
}
//krish