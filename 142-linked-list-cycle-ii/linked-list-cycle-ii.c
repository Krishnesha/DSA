struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    // Step 1: Detect whether a cycle exists
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            // Step 2: Find beginning of cycle
            struct ListNode* ptr = head;

            while (ptr != slow) {
                ptr = ptr->next;
                slow = slow->next;
            }

            return ptr;
        }
    }

    return NULL;
}
//krish