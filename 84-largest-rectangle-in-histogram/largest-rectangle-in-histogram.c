#include <stdlib.h>

int largestRectangleArea(int* heights, int heightsSize) {

    int* stack = malloc((heightsSize + 1) * sizeof(int));
    int top = -1;

    int maxArea = 0;

    for (int i = 0; i <= heightsSize; i++) {

        int currentHeight;

        // Sentinel 0 at the end
        if (i == heightsSize)
            currentHeight = 0;
        else
            currentHeight = heights[i];

        // Remove taller bars
        while (top >= 0 && heights[stack[top]] > currentHeight) {

            int height = heights[stack[top--]];

            int width;

            if (top == -1) {
                width = i;
            } else {
                width = i - stack[top] - 1;
            }

            int area = height * width;

            if (area > maxArea)
                maxArea = area;
        }

        stack[++top] = i;
    }

    free(stack);

    return maxArea;
}
