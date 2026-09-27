#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEVEL 16

typedef struct Node {
    int value;
    struct Node *next[MAX_LEVEL];
} Node;

typedef struct {
    Node *head;
} Skiplist;

/* Create a new node */
Node* createNode(int value, int level) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->value = value;

    for (int i = 0; i < level; i++)
        node->next[i] = NULL;

    return node;
}

/* Generate random level */
int randomLevel() {
    int level = 1;

    while ((rand() % 2) && level < MAX_LEVEL)
        level++;

    return level;
}

/* Create Skiplist */
Skiplist* skiplistCreate() {
    Skiplist *obj = (Skiplist *)malloc(sizeof(Skiplist));

    obj->head = createNode(-1, MAX_LEVEL);

    return obj;
}

/* Search */
bool skiplistSearch(Skiplist* obj, int target) {

    Node *current = obj->head;

    /* Start from highest level */
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {

        while (current->next[i] != NULL &&
               current->next[i]->value < target) {

            current = current->next[i];
        }
    }

    current = current->next[0];

    if (current != NULL && current->value == target)
        return true;

    return false;
}

/* Add */
void skiplistAdd(Skiplist* obj, int num) {

    Node *update[MAX_LEVEL];

    Node *current = obj->head;

    /* Find position at every level */
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {

        while (current->next[i] != NULL &&
               current->next[i]->value < num) {

            current = current->next[i];
        }

        update[i] = current;
    }

    /* Generate level for new node */
    int level = randomLevel();

    Node *newNode = createNode(num, level);

    /* Insert node */
    for (int i = 0; i < level; i++) {

        newNode->next[i] = update[i]->next[i];

        update[i]->next[i] = newNode;
    }
}

/* Erase */
bool skiplistErase(Skiplist* obj, int num) {

    Node *update[MAX_LEVEL];

    Node *current = obj->head;

    /* Find position */
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {

        while (current->next[i] != NULL &&
               current->next[i]->value < num) {

            current = current->next[i];
        }

        update[i] = current;
    }

    current = current->next[0];

    /* Number not found */
    if (current == NULL || current->value != num)
        return false;

    /* Remove from every level */
    for (int i = 0; i < MAX_LEVEL; i++) {

        if (update[i]->next[i] != current)
            break;

        update[i]->next[i] = current->next[i];
    }

    free(current);

    return true;
}

/* Free Skiplist */
void skiplistFree(Skiplist* obj) {

    Node *current = obj->head;

    while (current != NULL) {

        Node *next = current->next[0];

        free(current);

        current = next;
    }

    free(obj);
}
//krish