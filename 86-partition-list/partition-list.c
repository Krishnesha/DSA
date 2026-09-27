/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* partition(struct ListNode* head, int x) {

    // Dummy heads for two lists
    struct ListNode lessDummy;
    struct ListNode greaterDummy;

    lessDummy.next = NULL;
    greaterDummy.next = NULL;

    struct ListNode *less = &lessDummy;
    struct ListNode *greater = &greaterDummy;

    struct ListNode *curr = head;

    while (curr != NULL) {

        if (curr->val < x) {
            less->next = curr;
            less = less->next;
        } else {
            greater->next = curr;
            greater = greater->next;
        }

        curr = curr->next;
    }

    // Important: terminate greater list
    greater->next = NULL;

    // Join both lists
    less->next = greaterDummy.next;

    return lessDummy.next;
}
//krish