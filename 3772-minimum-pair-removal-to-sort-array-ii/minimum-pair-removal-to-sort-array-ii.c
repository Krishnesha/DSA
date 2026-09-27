#include <stdlib.h>

typedef long long ll;

typedef struct Node {
    ll val;
    int idx;               // original index, used for leftmost tie-breaking
    struct Node *prev;
    struct Node *next;
    int alive;
} Node;

typedef struct {
    ll sum;
    Node *left;
    Node *right;
} Pair;

typedef struct {
    Pair *data;
    int size;
    int capacity;
} MinHeap;

/* ---------- Heap functions ---------- */

int pairLess(Pair a, Pair b) {
    if (a.sum != b.sum)
        return a.sum < b.sum;

    // If sums are equal, choose the leftmost pair
    return a.left->idx < b.left->idx;
}

void heapPush(MinHeap *h, Pair p) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(Pair));
    }

    int i = h->size++;
    h->data[i] = p;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (!pairLess(h->data[i], h->data[parent]))
            break;

        Pair temp = h->data[i];
        h->data[i] = h->data[parent];
        h->data[parent] = temp;

        i = parent;
    }
}

Pair heapPop(MinHeap *h) {
    Pair result = h->data[0];

    h->size--;

    if (h->size > 0) {
        h->data[0] = h->data[h->size];

        int i = 0;

        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < h->size &&
                pairLess(h->data[left], h->data[smallest])) {
                smallest = left;
            }

            if (right < h->size &&
                pairLess(h->data[right], h->data[smallest])) {
                smallest = right;
            }

            if (smallest == i)
                break;

            Pair temp = h->data[i];
            h->data[i] = h->data[smallest];
            h->data[smallest] = temp;

            i = smallest;
        }
    }

    return result;
}

/* ---------- Main solution ---------- */

int minimumPairRemoval(int* nums, int numsSize) {
    if (numsSize <= 1)
        return 0;

    /*
        Create linked list.

        Example:
        [5, 2, 3, 1]

        5 <-> 2 <-> 3 <-> 1
    */

    Node *nodes = malloc(numsSize * sizeof(Node));

    for (int i = 0; i < numsSize; i++) {
        nodes[i].val = nums[i];
        nodes[i].idx = i;
        nodes[i].prev = (i > 0) ? &nodes[i - 1] : NULL;
        nodes[i].next = (i + 1 < numsSize) ? &nodes[i + 1] : NULL;
        nodes[i].alive = 1;
    }

    /* Initialize heap */
    MinHeap heap;

    heap.size = 0;
    heap.capacity = numsSize * 2 + 10;
    heap.data = malloc(heap.capacity * sizeof(Pair));

    /*
        Insert every adjacent pair.
    */
    for (int i = 0; i < numsSize - 1; i++) {
        Pair p;

        p.left = &nodes[i];
        p.right = &nodes[i + 1];
        p.sum = nodes[i].val + nodes[i + 1].val;

        heapPush(&heap, p);
    }

    /*
        Number of adjacent inversions.

        We only need to continue while the linked list
        is not non-decreasing.
    */
    int bad = 0;

    Node *cur = &nodes[0];

    while (cur != NULL && cur->next != NULL) {
        if (cur->val > cur->next->val)
            bad++;

        cur = cur->next;
    }

    int operations = 0;

    while (bad > 0) {

        Pair p;

        /*
            Lazy deletion:
            The heap contains old pairs which may no longer
            represent adjacent nodes.
        */
        while (1) {
            p = heapPop(&heap);

            Node *a = p.left;
            Node *b = p.right;

            if (!a->alive || !b->alive)
                continue;

            if (a->next != b)
                continue;

            if (a->val + b->val != p.sum)
                continue;

            break;
        }

        Node *a = p.left;
        Node *b = p.right;

        /*
            Before merging, remove the old inversion
            relationships involving:

                prev -> a
                a -> b
                b -> next
        */

        Node *prev = a->prev;
        Node *next = b->next;

        if (prev != NULL && prev->val > a->val)
            bad--;

        if (a->val > b->val)
            bad--;

        if (next != NULL && b->val > next->val)
            bad--;

        /*
            Merge a and b.

            a becomes:
                a.val = a.val + b.val

            b is removed.
        */
        a->val += b->val;

        a->next = next;

        if (next != NULL)
            next->prev = a;

        b->alive = 0;

        /*
            Add the new inversion relationships.
        */

        if (prev != NULL && prev->val > a->val)
            bad++;

        if (next != NULL && a->val > next->val)
            bad++;

        /*
            Add new adjacent pairs to heap:

                prev <-> a
                a <-> next
        */

        if (prev != NULL) {
            Pair newPair;

            newPair.left = prev;
            newPair.right = a;
            newPair.sum = prev->val + a->val;

            heapPush(&heap, newPair);
        }

        if (next != NULL) {
            Pair newPair;

            newPair.left = a;
            newPair.right = next;
            newPair.sum = a->val + next->val;

            heapPush(&heap, newPair);
        }

        operations++;
    }

    free(heap.data);
    free(nodes);

    return operations;
}