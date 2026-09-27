struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct ListNode dummy;
    dummy.next = NULL;

    struct ListNode* curr = head;

    while (curr != NULL) {
        struct ListNode* next = curr->next;

        // Find position to insert
        struct ListNode* prev = &dummy;

        while (prev->next != NULL &&
               prev->next->val < curr->val) {
            prev = prev->next;
        }

        // Insert curr
        curr->next = prev->next;
        prev->next = curr;

        curr = next;
    }

    return dummy.next;
}
//krish