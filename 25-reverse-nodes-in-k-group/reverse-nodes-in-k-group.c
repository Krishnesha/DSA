struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode* curr = head;
    int count = 0;

    // Check if there are k nodes
    while (curr != NULL && count < k) {
        curr = curr->next;
        count++;
    }

    if (count < k)
        return head;

    // Reverse k nodes
    curr = head;
    struct ListNode* prev = NULL;
    struct ListNode* next = NULL;

    for (int i = 0; i < k; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Connect with the remaining nodes
    head->next = reverseKGroup(curr, k);

    return prev;
}
//krish