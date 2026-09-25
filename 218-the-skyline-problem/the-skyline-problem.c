#include <stdlib.h>

typedef struct {
    int left;
    int right;
    int height;
} Building;

typedef struct {
    int height;
    int right;
} HeapNode;

/* Sort buildings by left coordinate */
int compareBuildings(const void *a, const void *b) {
    Building *x = (Building *)a;
    Building *y = (Building *)b;

    return x->left - y->left;
}

/* ---------- MAX HEAP ---------- */

void heapPush(HeapNode *heap, int *size, int height, int right) {
    int i = (*size)++;

    heap[i].height = height;
    heap[i].right = right;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent].height >= heap[i].height)
            break;

        HeapNode temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

void heapPop(HeapNode *heap, int *size) {
    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < *size &&
            heap[left].height > heap[largest].height)
            largest = left;

        if (right < *size &&
            heap[right].height > heap[largest].height)
            largest = right;

        if (largest == i)
            break;

        HeapNode temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }
}

/* ---------- SKYLINE ---------- */

int** getSkyline(int** buildings, int buildingsSize,
                 int* buildingsColSize,
                 int* returnSize,
                 int** returnColumnSizes) {

    *returnSize = 0;

    int capacity = 2 * buildingsSize + 1;

    int **result = malloc(capacity * sizeof(int *));
    *returnColumnSizes = malloc(capacity * sizeof(int));

    Building *arr = malloc(buildingsSize * sizeof(Building));

    /* Copy buildings */
    for (int i = 0; i < buildingsSize; i++) {
        arr[i].left = buildings[i][0];
        arr[i].right = buildings[i][1];
        arr[i].height = buildings[i][2];
    }

    /* Sort by left coordinate */
    qsort(arr, buildingsSize, sizeof(Building), compareBuildings);

    /* Max heap */
    HeapNode *heap =
        malloc(buildingsSize * sizeof(HeapNode));

    int heapSize = 0;
    int i = 0;
    int currentHeight = 0;

    while (i < buildingsSize || heapSize > 0) {

        int x;

        if (heapSize == 0) {
            x = arr[i].left;
        }
        else if (i == buildingsSize) {
            x = heap[0].right;
        }
        else if (arr[i].left < heap[0].right) {
            x = arr[i].left;
        }
        else {
            x = heap[0].right;
        }

        /* Add all buildings that start at x */
        while (i < buildingsSize &&
               arr[i].left <= x) {

            heapPush(heap, &heapSize,
                     arr[i].height,
                     arr[i].right);

            i++;
        }

        /* Remove buildings that ended at x */
        while (heapSize > 0 &&
               heap[0].right <= x) {
            heapPop(heap, &heapSize);
        }

        int newHeight = 0;

        if (heapSize > 0)
            newHeight = heap[0].height;

        /* Height changed → key point */
        if (newHeight != currentHeight) {

            result[*returnSize] =
                malloc(2 * sizeof(int));

            result[*returnSize][0] = x;
            result[*returnSize][1] = newHeight;

            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;

            currentHeight = newHeight;
        }
    }

    free(arr);
    free(heap);

    return result;
}