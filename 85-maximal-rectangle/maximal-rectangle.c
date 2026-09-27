#include <stdlib.h>

int largestRectangleArea(int* heights, int n) {
    int* stack = malloc((n + 1) * sizeof(int));
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {

        int currentHeight;

        if (i == n)
            currentHeight = 0;
        else
            currentHeight = heights[i];

        while (top >= 0 && heights[stack[top]] > currentHeight) {

            int h = heights[stack[top--]];

            int width;

            if (top < 0)
                width = i;
            else
                width = i - stack[top] - 1;

            int area = h * width;

            if (area > maxArea)
                maxArea = area;
        }

        stack[++top] = i;
    }

    free(stack);

    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {

    if (matrixSize == 0)
        return 0;

    int cols = matrixColSize[0];

    int* heights = calloc(cols, sizeof(int));

    int maxArea = 0;

    for (int i = 0; i < matrixSize; i++) {

        // Build histogram for current row
        for (int j = 0; j < cols; j++) {

            if (matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }

        // Find largest rectangle in histogram
        int area = largestRectangleArea(heights, cols);

        if (area > maxArea)
            maxArea = area;
    }

    free(heights);

    return maxArea;
}