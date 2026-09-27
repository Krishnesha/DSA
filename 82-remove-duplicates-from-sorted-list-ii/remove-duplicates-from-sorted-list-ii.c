struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode* prev = &dummy;
    struct ListNode* curr = head;

    while (curr != NULL) {

        // Duplicate found
        if (curr->next != NULL &&
            curr->val == curr->next->val) {

            int value = curr->val;

            // Skip all nodes having this value
            while (curr != NULL && curr->val == value) {
                curr = curr->next;
            }

            prev->next = curr;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}
//krish