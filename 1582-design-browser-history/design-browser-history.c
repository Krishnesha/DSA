#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *url;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *cur;
} BrowserHistory;

BrowserHistory* browserHistoryCreate(char* homepage) {
    BrowserHistory *obj = malloc(sizeof(BrowserHistory));

    Node *node = malloc(sizeof(Node));
    node->url = malloc(strlen(homepage) + 1);
    strcpy(node->url, homepage);

    node->prev = NULL;
    node->next = NULL;

    obj->cur = node;

    return obj;
}

void browserHistoryVisit(BrowserHistory* obj, char* url) {
    Node *node = malloc(sizeof(Node));
    node->url = malloc(strlen(url) + 1);
    strcpy(node->url, url);

    node->prev = obj->cur;
    node->next = NULL;

    // Clear forward history
    if (obj->cur->next != NULL) {
        Node *temp = obj->cur->next;

        while (temp != NULL) {
            Node *next = temp->next;
            free(temp->url);
            free(temp);
            temp = next;
        }
    }

    obj->cur->next = node;
    obj->cur = node;
}

char* browserHistoryBack(BrowserHistory* obj, int steps) {
    while (steps > 0 && obj->cur->prev != NULL) {
        obj->cur = obj->cur->prev;
        steps--;
    }

    return obj->cur->url;
}

char* browserHistoryForward(BrowserHistory* obj, int steps) {
    while (steps > 0 && obj->cur->next != NULL) {
        obj->cur = obj->cur->next;
        steps--;
    }

    return obj->cur->url;
}

void browserHistoryFree(BrowserHistory* obj) {
    Node *cur = obj->cur;

    while (cur->prev != NULL)
        cur = cur->prev;

    while (cur != NULL) {
        Node *next = cur->next;
        free(cur->url);
        free(cur);
        cur = next;
    }

    free(obj);
}
//krish