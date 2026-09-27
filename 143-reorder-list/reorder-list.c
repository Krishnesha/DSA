/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

void reorderList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return;

    // Find middle
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    struct ListNode *prev = NULL;
    struct ListNode *curr = slow->next;
    slow->next = NULL;

    while (curr != NULL) {
        struct ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Merge two halves
    struct ListNode *first = head;
    struct ListNode *second = prev;

    while (second != NULL) {
        struct ListNode *next1 = first->next;
        struct ListNode *next2 = second->next;

        first->next = second;
        second->next = next1;

        first = next1;
        second = next2;
    }
}
//krish