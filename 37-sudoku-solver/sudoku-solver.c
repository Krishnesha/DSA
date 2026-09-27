int isSafe(char** board, int row, int col, char num) {
    // Check row
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == num)
            return 0;
    }

    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num)
            return 0;
    }

    // Check 3x3 box
    int r = (row / 3) * 3;
    int c = (col / 3) * 3;

    for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++) {
            if (board[i][j] == num)
                return 0;
        }
    }

    return 1;
}

int solve(char** board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (board[i][j] == '.') {

                for (char num = '1'; num <= '9'; num++) {

                    if (isSafe(board, i, j, num)) {
                        board[i][j] = num;

                        if (solve(board))
                            return 1;

                        // Wrong choice → undo
                        board[i][j] = '.';
                    }
                }

                return 0;
            }
        }
    }

    return 1;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
    solve(board);
}
//krish