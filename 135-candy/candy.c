#include <stdlib.h>

int candy(int* ratings, int ratingsSize) {
    int* candies = malloc(ratingsSize * sizeof(int));

    // Everyone gets at least 1 candy
    for (int i = 0; i < ratingsSize; i++) {
        candies[i] = 1;
    }

    // Left to right
    for (int i = 1; i < ratingsSize; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // Right to left
    for (int i = ratingsSize - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i] < candies[i + 1] + 1) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    // Calculate total
    int total = 0;

    for (int i = 0; i < ratingsSize; i++) {
        total += candies[i];
    }

    free(candies);

    return total;
}
//krish