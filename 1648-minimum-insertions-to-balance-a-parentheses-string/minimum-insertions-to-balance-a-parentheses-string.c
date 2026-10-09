
int minInsertions(char* s) {
    int insertions = 0;
    int open = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            open++;
        } else {
            if (i + 1 < strlen(s) && s[i + 1] == ')') {
                i++;  
            } else {
                insertions++;  
            }

            if (open > 0) {
                open--;
            } else {
                insertions++; 
            }
        }
    }

    return insertions + 2 * open;
}
//krish