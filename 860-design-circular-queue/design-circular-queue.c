#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *arr;
    int front;
    int rear;
    int size;
    int capacity;
} MyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue *q = malloc(sizeof(MyCircularQueue));

    q->arr = malloc(sizeof(int) * k);
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = k;

    return q;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (obj->size == obj->capacity)
        return false;

    obj->arr[obj->rear] = value;

    obj->rear = (obj->rear + 1) % obj->capacity;
    obj->size++;

    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (obj->size == 0)
        return false;

    obj->front = (obj->front + 1) % obj->capacity;
    obj->size--;

    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (obj->size == 0)
        return -1;

    return obj->arr[obj->front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (obj->size == 0)
        return -1;

    int index = (obj->rear - 1 + obj->capacity) % obj->capacity;

    return obj->arr[index];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->size == 0;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return obj->size == obj->capacity;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->arr);
    free(obj);
}
//krish