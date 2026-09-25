#include <stdlib.h>
//krish
typedef struct {
    int *left;      // max heap
    int *right;     // min heap
    int leftSize;
    int rightSize;
    int capacity;
} MedianFinder;

/* ---------- MAX HEAP ---------- */

void maxPush(int *heap, int *size, int value) {
    int i = (*size)++;
    heap[i] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

int maxPop(int *heap, int *size) {
    int value = heap[0];

    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < *size && heap[left] > heap[largest])
            largest = left;

        if (right < *size && heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }

    return value;
}

/* ---------- MIN HEAP ---------- */

void minPush(int *heap, int *size, int value) {
    int i = (*size)++;
    heap[i] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] <= heap[i])
            break;

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

int minPop(int *heap, int *size) {
    int value = heap[0];

    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < *size && heap[left] < heap[smallest])
            smallest = left;

        if (right < *size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        i = smallest;
    }

    return value;
}

/* ---------- MEDIAN FINDER ---------- */

MedianFinder* medianFinderCreate() {
    MedianFinder *obj = malloc(sizeof(MedianFinder));

    obj->capacity = 100000;

    obj->left = malloc(obj->capacity * sizeof(int));
    obj->right = malloc(obj->capacity * sizeof(int));

    obj->leftSize = 0;
    obj->rightSize = 0;

    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {

    if (obj->leftSize == 0 || num <= obj->left[0]) {
        maxPush(obj->left, &obj->leftSize, num);
    } else {
        minPush(obj->right, &obj->rightSize, num);
    }

    /* Balance the two heaps */

    if (obj->leftSize > obj->rightSize + 1) {
        int x = maxPop(obj->left, &obj->leftSize);
        minPush(obj->right, &obj->rightSize, x);
    }

    if (obj->rightSize > obj->leftSize) {
        int x = minPop(obj->right, &obj->rightSize);
        maxPush(obj->left, &obj->leftSize, x);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {

    if (obj->leftSize > obj->rightSize) {
        return obj->left[0];
    }

    return ((double)obj->left[0] + obj->right[0]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->left);
    free(obj->right);
    free(obj);
}